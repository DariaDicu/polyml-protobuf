// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// https://developers.google.com/protocol-buffers/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "ml_enum.h"
#include "ml_helpers.h"
#include "ml_message.h"
#include "ml_builder.h"

#include <algorithm>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/stubs/strutil.h>
#include <unordered_map>

namespace google {
namespace protobuf {
namespace compiler {
namespace ml {
	MessageGenerator::MessageGenerator(const Descriptor* descriptor,
		const unordered_map<const Descriptor*, int>* message_order):
		descriptor_(descriptor),
		message_order_(message_order) {
			SortNestedTypes();
		}

	MessageGenerator::~MessageGenerator() {};

	void MessageGenerator::GenerateSignature(io::Printer* printer, 
		bool toplevel) {
		if (toplevel) {
			string signature = descriptor_->name();
			UpperString(&signature);
			printer->Print("signature $signature$ =\nsig\n",
			"signature", signature);
		} else {
			string signature = descriptor_->name();
			printer->Print("structure $signature$ : sig\n",
			"signature", signature);
		}
		printer->Indent();

		// Print child signatures.
		for (int i = 0; i < descriptor_->enum_type_count(); i++) {
			EnumGenerator generator(descriptor_->enum_type(i));
			generator.GenerateSignature(printer, false /* toplevel */);
			// Print type alias.
			string name = descriptor_->enum_type(i)->name();
			UncapitalizeString(name);
			printer->Print("type $name$\n", "name", name);
		}

		// Print child signatures.
		for (int i = 0; i < ordered_nested_types_.size(); i++) {
			MessageGenerator generator(ordered_nested_types_[i], 
				message_order_);
			generator.GenerateSignature(printer, false /* toplevel */);
			// Print type alias.
			string name = ordered_nested_types_[i]->name();
			UncapitalizeString(name);
			printer->Print("type $name$\n", "name", name);
		}

		printer->Print("type t\n");
		BuilderGenerator builder_gen(descriptor_);
		builder_gen.GenerateSignature(printer);
		printer->Print("val encode : t -> Word8Vector.vector\n");
		printer->Print("val encodeToplevel : t -> Word8Vector.vector\n");
		printer->Print("val decode : ByteInputStream.stream -> t * parseResult\n");
		printer->Print("val decodeToplevel : ByteInputStream.stream -> t * parseResult\n");

		// End is the same regardless of toplevel being true/false.
		printer->Outdent();
		printer->Print("end\n");
	}

	void MessageGenerator::GenerateStructure(io::Printer* printer,
		bool toplevel) {
		// Generate structure.
		string structure = descriptor_->name();
		CapitalizeString(structure);
		//printer->Print("structure $structure$ :> $signature$ = ",
		if (toplevel) {
			string signature = descriptor_->name();
			UpperString(&signature);
			printer->Print("structure $structure$ : $signature$ = \n",
				"structure", structure,
				"signature", signature);
		} else {
			printer->Print("structure $structure$ = \n",
				"structure", structure);
		}
		printer->Print("struct\n");
		printer->Indent();

		// Print structures for nested types.
		for (int i = 0; i < descriptor_->enum_type_count(); i++) {
			EnumGenerator generator(descriptor_->enum_type(i));
			generator.GenerateStructure(printer, false /* toplevel */);
		}
		for (int i = 0; i < ordered_nested_types_.size(); i++) {
			MessageGenerator generator(ordered_nested_types_[i], 
				message_order_);
			generator.GenerateStructure(printer, false /* toplevel */);
		}
		// Print main type declaration.
		printer->Print("type t = {\n");
		printer->Indent();
		for (int i = 0; i < descriptor_->field_count(); i++) {
			const FieldDescriptor* field = descriptor_->field(i);
			string name = field->name();
			SanitizeForMl(name);

			string type = GetFormattedTypeFromField(field);
			if (type != "Word8Vector.vector") UncapitalizeString(type);

			string label = LabelName(field->label());
			printer->Print("$name$: $type$ $label$",
				"name", name,
				"type", type,
				"label", label);
			if (i < descriptor_->field_count() - 1) {
				printer->Print(",\n");
			} else {
				printer->Print("\n");
			}
		}
		printer->Outdent();
		printer->Print("}\n");

		BuilderGenerator builder_gen(descriptor_);
		builder_gen.GenerateStructure(printer);

		// Printing the encode function.
		printer->Print("fun encodeToplevel m = \n");
		printer->Indent();
		printer->Print("let\n");
		printer->Indent();
		for (int i = 0; i < descriptor_->field_count(); i++) {
			const FieldDescriptor* field = descriptor_->field(i);
			string name = field->name();
			SanitizeForMl(name);
			string type_name = field->type_name();
			string tag = to_string(field->number());
			string code = to_string(GetWireCode(field->type()));

			// Get name of the helper function we need to call.
			string function_name;

			bool is_repeated = (field->label() == 
				FieldDescriptor::LABEL_REPEATED);

			bool is_optional = (field->label() == 
				FieldDescriptor::LABEL_OPTIONAL);

			bool is_required = (field->label() ==
				FieldDescriptor::LABEL_REQUIRED);

			// Default is optional.
			if ((!is_required) && (!is_repeated)) is_optional = true;

			// Default value for packed encoding is true, unless otherwise 
			// specified. Only primitives can be packed.
			bool is_packed = (code == "2" || !is_repeated) ? false : true;
			if(field->options().has_packed() && !field->options().packed()) {
				is_packed = false;
			}
			// Packed fields have wire type 2.
			if (is_packed) code = "2";

			if (type_name.compare("message") == 0 || 
				type_name.compare("enum") == 0) {
				string type = GetFormattedTypeFromField(field);
				CapitalizeString(type);
				function_name = type + ".encode";
			} else {
				CapitalizeString(type_name);
				function_name = "encode" + type_name;
			}

			// Get function for label.
			string label_function = "encodeOptional";
			if (is_repeated) {
				if (is_packed) {
					label_function = "encodePackedRepeated";
				} else {
					label_function = "encodeRepeated";
				}
			} else if (is_optional) {
				label_function = "encodeOptional";
			} else if (is_required) {
				label_function = "encodeRequired";
			}
			printer->Print("val $name$ = ($label_function$ $enc_func$)"
				" (encodeKey(Tag($tag$), Code($code$))) (#$name$ m)\n",
				"name", name,
				"code", code,
				"enc_func", function_name,
				"label_function", label_function,
				"tag", tag);
		}
		printer->Outdent();
		printer->Print("in\n");
		printer->Indent();
		printer->Print("Word8Vector.concat [\n");
		printer->Indent();
		// Listing all encoded fields in the message.
		for (int i = 0; i < descriptor_->field_count(); i++) {
			const FieldDescriptor* field = descriptor_->field(i);
			string name = field->name();
			SanitizeForMl(name);

			if (i > 0) printer->Print(",\n");
			printer->Print("$name$", "name", name);
		}
		printer->Print("\n");
		printer->Outdent();
		printer->Print("]\n");
		printer->Outdent();
		printer->Print("end\n\n");
		printer->Outdent();

		// Printing the encodeEmbedded function
		printer->Print("fun encode m = encodeMessage (encodeToplevel m)\n\n");

		// Printing the decode next field function. This is hidden from signature.
		// ========== Start of decode next field ==========
		printer->Print("fun decodeNextField buff obj remaining = \n");
		printer->Indent();
		printer->Print("if (remaining = 0) then\n");
		printer->Indent();
		printer->Print("(obj, buff)\n");
		printer->Outdent();
		printer->Print("else if (remaining < 0) then\n");
		printer->Indent();
		printer->Print("raise Exception(DECODE, \"Field encoding does not match "
			"length in message header.\")\n");
		printer->Outdent();
		printer->Print("else\n");
		printer->Indent();
		printer->Print("let\n");
		printer->Indent();
		printer->Print("val ((Tag(t), Code(c)), parse_result) = "
			"decodeKey buff\n");
		printer->Print("val ParseResult(buff, ParsedByteCount(keyByteCount)) = "
				"parse_result\n");
		printer->Print("val remaining = remaining - keyByteCount\n");
		printer->Outdent();
		printer->Print("in\n");
		printer->Indent();
		printer->Print("if (remaining <= 0) then\n");
		printer->Indent();
		printer->Print("raise Exception(DECODE, \"Not enough bytes left after "
			"parsing message field key.\")\n");
		printer->Outdent();
		printer->Print("else case (t) of ");
		for (int i = 0; i < descriptor_->field_count(); i++) {
			// ML code will look like:
			// fun decodeMessageHelper decode_fun modifier_fun rec_fun obj buff remaining = 
			// case (tag_) of 0 => 
			// let
			// 	val (field_value, parsed_bytes) = parseFuncForType buff
			// in
			// 	if (remaining > parsed_bytes)
			// 		(ModuleName.setOrAddForLabel (obj, field_value),
			// 		parseNextField buff obj (remaining - parsed_bytes))
			// 	else 
			// 		raise Exception(PARSE, 
			// 			"Error in matching the message length with fields length.")
			// end
			// | 1 => ...
			const FieldDescriptor* field = descriptor_->field(i);
			string name = field->name();
			SanitizeForMl(name);
			string type_name = field->type_name();
			string tag = to_string(field->number());
			string module_name = GetFormattedTypeFromField(field);
			CapitalizeString(module_name);
			string code = to_string(GetWireCode(field->type()));

			string function_name;
			if (type_name.compare("message") == 0 || 
			  type_name.compare("enum") == 0) {
				function_name = module_name + ".decode";
			} else {
				CapitalizeString(type_name);
				function_name = "decode" + type_name;
			}
		
			bool is_repeated = (field->label() == 
				FieldDescriptor::LABEL_REPEATED);

			bool is_optional = (field->label() == 
				FieldDescriptor::LABEL_OPTIONAL);

			string setter_name;

			if (is_repeated) {
				setter_name = "Builder.add_" + name;
			} else {
				setter_name = "Builder.set_" + name;
			}

			if (i > 0) printer->Print("\n| ");
			printer->Print("$tag$ => ", "tag", tag);

			// If it is possible to get packed encoding (wire type is not zero),
			// then we must print function for packed encoding if extracted
			// wire type is 2 (it becomes 2 for packed encoded fields). 
			if (is_repeated && code != "2") {
				printer->Print("if (c = 2) then (decodeNextPacked ($function_name$) "
					"($setter_name$) (decodeNextField) obj buff remaining)\n"
					"else (decodeNextUnpacked ($function_name$) "
					"($setter_name$) (decodeNextField) obj buff remaining)\n",
					"function_name", function_name,
					"setter_name", setter_name);
			} else {
				printer->Print("decodeNextUnpacked ($function_name$) "
					"($setter_name$) (decodeNextField) obj buff remaining",
					"function_name", function_name,
					"setter_name", setter_name);
			}
		}
		// Raise exception for unknown tag.
		printer->Print("\n");
		if (descriptor_->field_count() > 0) printer->Print("|");
		printer->Print(" n => raise Exception(DECODE, \"Unknown field tag\")\n");
		printer->Outdent();
		printer->Print("end\n\n");
		printer->Outdent();
		printer->Outdent();
		// ========== End of decode next field ==========

		// ========== Start of decode ==========
		printer->Print("fun decode buff = decodeFullHelper false decodeNextField "
			"(Builder.build) (Builder.init ()) buff\n\n");

		// ========== End of decode ==========
		// ========== Start of decode ==========
		printer->Print("fun decodeToplevel buff = decodeFullHelper true decodeNextField "
			"(Builder.build) (Builder.init ()) buff\n\n");

		printer->Outdent();
		printer->Print("end\n");

		string type_name = descriptor_->name();
		string structure_name = descriptor_->name();
		UncapitalizeString(type_name);
		CapitalizeString(structure_name);
		printer->Print("type $type_name$ = $structure_name$.t\n",
			"type_name", type_name,
			"structure_name", structure_name);
	}

	struct op_comp : std::binary_function<const Descriptor*, const Descriptor*, bool>
    {
	    op_comp(const unordered_map<const Descriptor*, int>* order) : order_(order) {}
	    bool operator() (const Descriptor* d1, const Descriptor* d2) {
			return (*order_).find(d1)->second < (*order_).find(d2)->second;
		}
	    const unordered_map<const Descriptor*, int>* order_;
	};

	void MessageGenerator::SortNestedTypes() {
		vector<const Descriptor*> ordered_nested_types;
		for (int i = 0; i < descriptor_->nested_type_count(); i++) {
			ordered_nested_types.push_back(descriptor_->nested_type(i));
		}
		std::sort(ordered_nested_types.begin(), ordered_nested_types.end(), 
			op_comp(message_order_));
		ordered_nested_types_ = ordered_nested_types;
	}
}  // namespace ml
}  // namespace compiler
}  // namespace protobuf
}  // namespace google