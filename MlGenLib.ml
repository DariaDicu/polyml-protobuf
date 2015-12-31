(* For now, this is just a Word8Vector, it does not have a channel underneath*)
(* Buffer is a vector and an index in the vector*)
(* For now only considering integers, no floats or zigzags *)
type byte = Word8.word
type key = int * int
datatype errorCode = PARSE;
exception Exception of errorCode*string

signature BYTE = 
sig
	val fromInt : int -> byte
	val toInt : byte -> int
	val getMsb : byte -> bool
	val getTail : byte -> byte
end

structure Byte :> BYTE = 
struct
	fun fromInt n = Word8.fromInt n
	fun toInt b = Word8.toInt b
	fun getMsb b = Word8.>>(b, Word.fromInt 7) > (fromInt 0)
	fun getTail b = Word8.>>(Word8.<<(b, Word.fromInt 1), Word.fromInt 1)
end

signature BYTE_BUFFER = 
sig
	type byte_vector
	type buffer
	val fromVector : byte_vector -> buffer
	val fromList  : byte list -> buffer
	(* Modifies buffer by putting index after next byte *)
	val nextByte : buffer -> byte * buffer
	(* Modifies buffer by putting index after next block. Returns both 
	buffers, first the next block, then the remaining one. *)
	val nextFixedBlock : buffer -> int -> buffer * buffer
end

structure ByteBuffer :> BYTE_BUFFER =
struct
	type byte_vector = Word8Vector.vector
	type buffer = byte_vector * int
	fun fromVector buff = (buff, 0)
	fun fromList l = fromVector (Word8Vector.fromList l)
	fun nextByte (buff, i) =
		let
			(*Subscript exception raise here if no next_byte*)
			(*TODO - build your own error *)
			val b = Word8Vector.sub (buff, i)
		in
			(b, (buff, i+1))
		end
	(* Tested, works. *)
	fun nextFixedBlock (buff, i) length = 
		(* get block from i to (i + length - 1) *)
		let 
			val block = Word8Vector.tabulate (length, fn n =>
							Word8Vector.sub (buff, i+n))
		in
			((block, 0), (buff, i+length))
		end
end

fun parseVarint_core buff i prev_val = 
let 
	val (b, next_buff) = ByteBuffer.nextByte buff
	(* TODO - Treat overflow? *)
	(* little endian *)
	val next_val = 
		prev_val + IntInf.<<((Byte.toInt (Byte.getTail b)), Word.fromInt(i * 7))
	val msb = Byte.getMsb b
in
	if (msb = true) then 
		(* if msb in this byte is 1, varint contains the next byte *)
		parseVarint_core next_buff (i+1) next_val
	else
		(* final value is tuple of value and remaining buffer *)
		(next_val, next_buff) 
end

fun parseVarint buff = parseVarint_core buff 0 0

fun parseKey buff = 
let
	val (v, next_buff) = parseVarint buff
	(* Type of the key is represented by last 3 bits. *)
	val code = IntInf.andb(v, 7)
	(* Field number is represented by the remaining bits. *)
	val tag = IntInf.~>>(v, Word.fromInt 3)
in
	((tag, code), next_buff)
end

fun parseFixed i remaining buff prev_val = 
let
	val (b, next_buff) = ByteBuffer.nextByte buff
	val next_val = 
		prev_val + IntInf.<<((Byte.toInt (Byte.getTail b)), Word.fromInt(i * 7))
in
	if (i > 1) then
		parseFixed (i+1) (remaining-1) next_buff next_val
	else
		(next_val, next_buff)
end

fun parse32 buff = parseFixed 0 4 buff 0

fun parse64 buff = parseFixed 0 8 buff 0

fun parse_message buff expected_tag = 
let
	val ((tag, code), buff) = parseKey buff
	val (length, buff) = parseVarint buff
	val (message, buff) = ByteBuffer.nextFixedBlock buff length
in
	if (code <> 2) then
		raise Exception(PARSE, "Attempting to parse wrong wire type.")
	else if (tag <> expected_tag) then
		raise Exception(PARSE, "Parsed tag does not match expected tag.")
	else
		(* Returns resulting message, as well as remaining buffer. *)
		(message, buff)
end

(*
fun parseNext buff = 
let
	val ((tag, code), next_buff) = parseKey buff
in
	case code of 0 => parseVarint next_buff
			   | 1 => parse64 next_buff
			   | 2 =>
			   | 3 => raise Exception("Groups are unsupported.")
			   | 4 => raise Exception("Groups are unsupported.")
			   | 5 => parse32 next_buff
			   | n => raise Exception("Wire type unsupported.")
end
*)













