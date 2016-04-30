// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: embedded.proto

#ifndef PROTOBUF_embedded_2eproto__INCLUDED
#define PROTOBUF_embedded_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_embedded_2eproto();
void protobuf_AssignDesc_embedded_2eproto();
void protobuf_ShutdownFile_embedded_2eproto();

class M1;
class M1_M2;
class M3;

// ===================================================================

class M1_M2 : public ::google::protobuf::Message {
 public:
  M1_M2();
  virtual ~M1_M2();

  M1_M2(const M1_M2& from);

  inline M1_M2& operator=(const M1_M2& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const M1_M2& default_instance();

  void Swap(M1_M2* other);

  // implements Message ----------------------------------------------

  inline M1_M2* New() const { return New(NULL); }

  M1_M2* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const M1_M2& from);
  void MergeFrom(const M1_M2& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(M1_M2* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // required int32 id = 2;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 2;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:M1.M2)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_id();
  inline void clear_has_id();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::int32 id_;
  friend void  protobuf_AddDesc_embedded_2eproto();
  friend void protobuf_AssignDesc_embedded_2eproto();
  friend void protobuf_ShutdownFile_embedded_2eproto();

  void InitAsDefaultInstance();
  static M1_M2* default_instance_;
};
// -------------------------------------------------------------------

class M1 : public ::google::protobuf::Message {
 public:
  M1();
  virtual ~M1();

  M1(const M1& from);

  inline M1& operator=(const M1& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const M1& default_instance();

  void Swap(M1* other);

  // implements Message ----------------------------------------------

  inline M1* New() const { return New(NULL); }

  M1* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const M1& from);
  void MergeFrom(const M1& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(M1* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef M1_M2 M2;

  // accessors -------------------------------------------------------

  // required .M1.M2 message2_1 = 1;
  bool has_message2_1() const;
  void clear_message2_1();
  static const int kMessage21FieldNumber = 1;
  const ::M1_M2& message2_1() const;
  ::M1_M2* mutable_message2_1();
  ::M1_M2* release_message2_1();
  void set_allocated_message2_1(::M1_M2* message2_1);

  // optional .M1.M2 message2_2 = 2;
  bool has_message2_2() const;
  void clear_message2_2();
  static const int kMessage22FieldNumber = 2;
  const ::M1_M2& message2_2() const;
  ::M1_M2* mutable_message2_2();
  ::M1_M2* release_message2_2();
  void set_allocated_message2_2(::M1_M2* message2_2);

  // repeated .M3 message3_list = 3;
  int message3_list_size() const;
  void clear_message3_list();
  static const int kMessage3ListFieldNumber = 3;
  const ::M3& message3_list(int index) const;
  ::M3* mutable_message3_list(int index);
  ::M3* add_message3_list();
  ::google::protobuf::RepeatedPtrField< ::M3 >*
      mutable_message3_list();
  const ::google::protobuf::RepeatedPtrField< ::M3 >&
      message3_list() const;

  // @@protoc_insertion_point(class_scope:M1)
 private:
  inline void set_has_message2_1();
  inline void clear_has_message2_1();
  inline void set_has_message2_2();
  inline void clear_has_message2_2();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::M1_M2* message2_1_;
  ::M1_M2* message2_2_;
  ::google::protobuf::RepeatedPtrField< ::M3 > message3_list_;
  friend void  protobuf_AddDesc_embedded_2eproto();
  friend void protobuf_AssignDesc_embedded_2eproto();
  friend void protobuf_ShutdownFile_embedded_2eproto();

  void InitAsDefaultInstance();
  static M1* default_instance_;
};
// -------------------------------------------------------------------

class M3 : public ::google::protobuf::Message {
 public:
  M3();
  virtual ~M3();

  M3(const M3& from);

  inline M3& operator=(const M3& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const M3& default_instance();

  void Swap(M3* other);

  // implements Message ----------------------------------------------

  inline M3* New() const { return New(NULL); }

  M3* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const M3& from);
  void MergeFrom(const M3& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(M3* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // @@protoc_insertion_point(class_scope:M3)
 private:
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  friend void  protobuf_AddDesc_embedded_2eproto();
  friend void protobuf_AssignDesc_embedded_2eproto();
  friend void protobuf_ShutdownFile_embedded_2eproto();

  void InitAsDefaultInstance();
  static M3* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// M1_M2

// optional string name = 1;
inline bool M1_M2::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void M1_M2::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void M1_M2::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void M1_M2::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& M1_M2::name() const {
  // @@protoc_insertion_point(field_get:M1.M2.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void M1_M2::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:M1.M2.name)
}
inline void M1_M2::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:M1.M2.name)
}
inline void M1_M2::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:M1.M2.name)
}
inline ::std::string* M1_M2::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:M1.M2.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* M1_M2::release_name() {
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void M1_M2::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:M1.M2.name)
}

// required int32 id = 2;
inline bool M1_M2::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void M1_M2::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void M1_M2::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void M1_M2::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 M1_M2::id() const {
  // @@protoc_insertion_point(field_get:M1.M2.id)
  return id_;
}
inline void M1_M2::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:M1.M2.id)
}

// -------------------------------------------------------------------

// M1

// required .M1.M2 message2_1 = 1;
inline bool M1::has_message2_1() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void M1::set_has_message2_1() {
  _has_bits_[0] |= 0x00000001u;
}
inline void M1::clear_has_message2_1() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void M1::clear_message2_1() {
  if (message2_1_ != NULL) message2_1_->::M1_M2::Clear();
  clear_has_message2_1();
}
inline const ::M1_M2& M1::message2_1() const {
  // @@protoc_insertion_point(field_get:M1.message2_1)
  return message2_1_ != NULL ? *message2_1_ : *default_instance_->message2_1_;
}
inline ::M1_M2* M1::mutable_message2_1() {
  set_has_message2_1();
  if (message2_1_ == NULL) {
    message2_1_ = new ::M1_M2;
  }
  // @@protoc_insertion_point(field_mutable:M1.message2_1)
  return message2_1_;
}
inline ::M1_M2* M1::release_message2_1() {
  clear_has_message2_1();
  ::M1_M2* temp = message2_1_;
  message2_1_ = NULL;
  return temp;
}
inline void M1::set_allocated_message2_1(::M1_M2* message2_1) {
  delete message2_1_;
  message2_1_ = message2_1;
  if (message2_1) {
    set_has_message2_1();
  } else {
    clear_has_message2_1();
  }
  // @@protoc_insertion_point(field_set_allocated:M1.message2_1)
}

// optional .M1.M2 message2_2 = 2;
inline bool M1::has_message2_2() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void M1::set_has_message2_2() {
  _has_bits_[0] |= 0x00000002u;
}
inline void M1::clear_has_message2_2() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void M1::clear_message2_2() {
  if (message2_2_ != NULL) message2_2_->::M1_M2::Clear();
  clear_has_message2_2();
}
inline const ::M1_M2& M1::message2_2() const {
  // @@protoc_insertion_point(field_get:M1.message2_2)
  return message2_2_ != NULL ? *message2_2_ : *default_instance_->message2_2_;
}
inline ::M1_M2* M1::mutable_message2_2() {
  set_has_message2_2();
  if (message2_2_ == NULL) {
    message2_2_ = new ::M1_M2;
  }
  // @@protoc_insertion_point(field_mutable:M1.message2_2)
  return message2_2_;
}
inline ::M1_M2* M1::release_message2_2() {
  clear_has_message2_2();
  ::M1_M2* temp = message2_2_;
  message2_2_ = NULL;
  return temp;
}
inline void M1::set_allocated_message2_2(::M1_M2* message2_2) {
  delete message2_2_;
  message2_2_ = message2_2;
  if (message2_2) {
    set_has_message2_2();
  } else {
    clear_has_message2_2();
  }
  // @@protoc_insertion_point(field_set_allocated:M1.message2_2)
}

// repeated .M3 message3_list = 3;
inline int M1::message3_list_size() const {
  return message3_list_.size();
}
inline void M1::clear_message3_list() {
  message3_list_.Clear();
}
inline const ::M3& M1::message3_list(int index) const {
  // @@protoc_insertion_point(field_get:M1.message3_list)
  return message3_list_.Get(index);
}
inline ::M3* M1::mutable_message3_list(int index) {
  // @@protoc_insertion_point(field_mutable:M1.message3_list)
  return message3_list_.Mutable(index);
}
inline ::M3* M1::add_message3_list() {
  // @@protoc_insertion_point(field_add:M1.message3_list)
  return message3_list_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::M3 >*
M1::mutable_message3_list() {
  // @@protoc_insertion_point(field_mutable_list:M1.message3_list)
  return &message3_list_;
}
inline const ::google::protobuf::RepeatedPtrField< ::M3 >&
M1::message3_list() const {
  // @@protoc_insertion_point(field_list:M1.message3_list)
  return message3_list_;
}

// -------------------------------------------------------------------

// M3

// optional string name = 1;
inline bool M3::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void M3::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void M3::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void M3::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& M3::name() const {
  // @@protoc_insertion_point(field_get:M3.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void M3::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:M3.name)
}
inline void M3::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:M3.name)
}
inline void M3::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:M3.name)
}
inline ::std::string* M3::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:M3.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* M3::release_name() {
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void M3::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:M3.name)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_embedded_2eproto__INCLUDED