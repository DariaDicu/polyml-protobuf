use "benchmarks/simple_message.pb.ml";
use "benchmarks/primitives.pb.ml";

val timer = ref (Timer.totalRealTimer ());

(* Returns a Word8Vector from the raw bits in the file *)
fun getByteInputStream file_name = 
let
	val raw_vector = BinIO.inputAll (BinIO.openIn file_name)
	val input_stream = ByteInputStream.fromVector raw_vector
in
	input_stream
end

(* Writes to file_name bytes from the Word8Vector argument. Useful for porting 
benchmark test data to other languages for testing *)
fun writeToFile file_name raw_bytes = 
let
	val ostream = BinIO.openOut file_name
in
	(BinIO.output (ostream, raw_bytes);
	BinIO.flushOut ostream)
end

fun reset_timer () = (timer := Timer.startRealTimer ())

fun print_time t = print("Test ran in " ^ (Real.toString t) ^ " s\n")

(* Prints the CPU time taken to serialize a SimpleMessage 100.000 times *)
fun testSerialization message_instance encoding_function = 
let 
	val counter = ref 100000
	val run_cnt = ref 5;
	val avg_time = ref 0.0;
in
	(* Take mid 3 runs and average *)
	while !run_cnt > 0 do (
		reset_timer();
		counter := 100000;
		while !counter > 0 do (
			Byte.bytesToString (encoding_function message_instance);
			counter := !counter - 1
		);
		if ((!run_cnt) <> 5 andalso (!run_cnt) <> 1) then
			avg_time := (!avg_time) + Time.toReal(Timer.checkRealTimer (!timer))
		else ();
		run_cnt := !run_cnt - 1
	);
	print_time ((!avg_time)/3.0)
end

(* Prints the CPU time taken to deserialize a SimpleMessage 100.000 times *)
fun testDeserialization message_instance encode_function decode_function = 
let
	val counter = ref 100000
	val raw_bytes = encode_function message_instance
	val input_stream = ByteInputStream.fromVector raw_bytes
	val run_cnt = ref 5
	val avg_time = ref 0.0
in
	while !run_cnt > 0 do (
		reset_timer();
		counter := 100000;
		while !counter > 0 do (
			decode_function input_stream;
			counter := !counter - 1
		);
		if ((!run_cnt) <> 5 andalso (!run_cnt) <> 1) then
			avg_time := (!avg_time) + Time.toReal(Timer.checkRealTimer (!timer))
		else ();
		run_cnt := !run_cnt - 1
	);
	print_time ((!avg_time)/3.0)
end

(* Returns some instance of SimpleMessage with fields filled in *)
fun getSimpleMessageInstance () = 
let
	(* Build 3 M3 messages to add to repeated field *)
	val builder = SimpleMessage.Builder.init();
	val builder = SimpleMessage.Builder.set_id(builder, 123);
	val builder = SimpleMessage.Builder.set_name(builder, "Myname Israndom");
	val builder = SimpleMessage.Builder.add_phone_number(builder, "1234567890");
	val builder = SimpleMessage.Builder.add_phone_number(builder, "2192121921");
	val builder = SimpleMessage.Builder.add_phone_number(builder, "9493438344");
	val builder = SimpleMessage.Builder.add_phone_number(builder, "4384383843");
in
	SimpleMessage.Builder.build builder
end

(* Returns some instance of FullPrimitiveCollection with fields filled in *)
fun getPrimitivesMessageInstance () =
let
	val builder = FullPrimitiveCollection.Builder.init();
in 
	(
	FullPrimitiveCollection.Builder.set_my_int32 (builder, ~1);
	FullPrimitiveCollection.Builder.set_my_int64 (builder, 221921921929121);
	FullPrimitiveCollection.Builder.set_my_uint32 (builder, 3232321);
	FullPrimitiveCollection.Builder.set_my_uint64 (builder, 9977533344322);
	FullPrimitiveCollection.Builder.set_my_sint32 (builder, ~123);
	FullPrimitiveCollection.Builder.set_my_sint64 (builder, ~221921921929121);
	FullPrimitiveCollection.Builder.set_my_fixed32 (builder, ~323231);
	FullPrimitiveCollection.Builder.set_my_fixed64 (builder, 221921921929121);
	FullPrimitiveCollection.Builder.set_my_sfixed32 (builder, ~67565);
	FullPrimitiveCollection.Builder.set_my_sfixed64 (builder, 69595969659659);
	FullPrimitiveCollection.Builder.set_my_bool (builder, true);
	FullPrimitiveCollection.Builder.set_my_bytes (builder, Word8Vector.fromList [0wx1,0wxFF,0wx23]);
	FullPrimitiveCollection.Builder.set_my_string (builder, "hello");
	FullPrimitiveCollection.Builder.build builder
	)
end

(* Returns some instance of FullPrimitiveCollection with fields filled in *)
fun getFloatingPointPrimitivesMessageInstance () =
let
	val builder = FullPrimitiveCollection.Builder.init();
in 
	(
	FullPrimitiveCollection.Builder.set_my_int32 (builder, ~1);
	FullPrimitiveCollection.Builder.set_my_int64 (builder, 221921921929121);
	FullPrimitiveCollection.Builder.set_my_uint32 (builder, 3232321);
	FullPrimitiveCollection.Builder.set_my_uint64 (builder, 9977533344322);
	FullPrimitiveCollection.Builder.set_my_sint32 (builder, ~123);
	FullPrimitiveCollection.Builder.set_my_sint64 (builder, ~221921921929121);
	FullPrimitiveCollection.Builder.set_my_fixed32 (builder, ~323231);
	FullPrimitiveCollection.Builder.set_my_fixed64 (builder, 221921921929121);
	FullPrimitiveCollection.Builder.set_my_sfixed32 (builder, ~67565);
	FullPrimitiveCollection.Builder.set_my_sfixed64 (builder, 69595969659659);
	FullPrimitiveCollection.Builder.set_my_bool (builder, true);
	FullPrimitiveCollection.Builder.set_my_bytes (builder, Word8Vector.fromList [0wx1,0wxFF,0wx23]);
	FullPrimitiveCollection.Builder.set_my_string (builder, "hello");
	FullPrimitiveCollection.Builder.set_my_float (builder, 212.21211);
	FullPrimitiveCollection.Builder.set_my_double (builder, ~85521.219192);
	FullPrimitiveCollection.Builder.build builder
	)
end

fun write_test_data_to_files () = 
let
	val simple_message_instance = getSimpleMessageInstance ()
	val primitives_message_instance = getPrimitivesMessageInstance ()
	val floating_point_message_instance = getFloatingPointPrimitivesMessageInstance()
	val encoded_simple_message = SimpleMessage.encodeToplevel simple_message_instance
	val encoded_primitives_message = FullPrimitiveCollection.encodeToplevel primitives_message_instance
	val encoded_floating_point_message = FullPrimitiveCollection.encodeToplevel floating_point_message_instance
in
	(
		writeToFile "benchmarks/simple_message.dat" encoded_simple_message;
		writeToFile "benchmarks/primitives_message.dat" encoded_primitives_message;
		writeToFile "benchmarks/floating_point_message.dat" encoded_floating_point_message
	)
end

fun parse_simple_message_from_file file_name = 
let
	val input_stream = getByteInputStream file_name
in
	SimpleMessage.decode input_stream
end

fun parse_primitives_message_from_file file_name = 
let
	val input_stream = getByteInputStream file_name
in
	FullPrimitiveCollection.decode input_stream
end

fun parse_floating_point_message_from_file file_name = 
let
	val input_stream = getByteInputStream file_name
in
	FullPrimitiveCollection.decode input_stream
end

exception invalidTest

fun test 0 = 
	(* Serialization performance test for SimpleMessage *)
	let 	
		val message_instance = getSimpleMessageInstance ()
	in
		(
			print("Running serialization 100.000 times on SimpleMessage: ");
			testSerialization message_instance SimpleMessage.encodeToplevel;
			print("Running deserialization 100.000 times on SimpleMessage: ");
			testDeserialization message_instance SimpleMessage.encodeToplevel SimpleMessage.decodeToplevel
		)
	end
  | test 1 = (* Test for message of type FullPrimitiveCollection without floating point values *)
	let
		val message_instance = getPrimitivesMessageInstance ()
	in
		(
			print("Running serialization 100.000 times on FullPrimitiveCollection (no floating point): ");
			testSerialization message_instance FullPrimitiveCollection.encodeToplevel;
			print("Running deserialization 100.000 times on FullPrimitiveCollection (no floating point): ");
			testDeserialization message_instance FullPrimitiveCollection.encodeToplevel 
			FullPrimitiveCollection.decodeToplevel
		)
	end
	| test 2 = (* Test for message of type FullPrimitiveCollection with floating point values *)
	let
		val message_instance = getFloatingPointPrimitivesMessageInstance ()
	in
		(
			print("Running serialization 100.000 times on FullPrimitiveCollection (WITH floating point): ");
			testSerialization message_instance FullPrimitiveCollection.encodeToplevel;
			print("Running deserialization 100.000 times on FullPrimitiveCollection (WITH floating point): ");
			testDeserialization message_instance FullPrimitiveCollection.encodeToplevel 
			FullPrimitiveCollection.decodeToplevel
		)
	end
  | test n = raise invalidTest

val lastTest = 2;

fun runTests () = 
let
	fun run i = if i <= lastTest then (test i; run (i+1)) else ()
in
	run 0
end;

fun main() = runTests ();