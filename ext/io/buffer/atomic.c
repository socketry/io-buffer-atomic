// Released under the MIT License.
// Copyright, 2025, by Samuel Williams.

#include <ruby.h>
#include <ruby/io/buffer.h>
#include <ruby/atomic.h>
#include <stdint.h>
#include <string.h>

// We need stdatomic.h for typed atomic operations on different widths
#ifdef HAVE_STDATOMIC_H
	#include <stdatomic.h>
	#define HAVE_TYPED_ATOMICS 1
#elif defined(__GNUC__) && (__GNUC__ >= 4)
	// Use GCC built-in atomic operations
	#define USE_GCC_ATOMICS 1
	#define HAVE_TYPED_ATOMICS 1
#elif defined(_MSC_VER)
	// Use MSVC intrinsics
	#include <intrin.h>
	#define USE_MSVC_ATOMICS 1
	#define HAVE_TYPED_ATOMICS 1
#else
	#error "Atomic operations not available on this platform"
#endif

// Helper to get buffer pointer and validate
static void* get_buffer_pointer(VALUE buffer, size_t offset, size_t size) {
	void *base;
	size_t buffer_size;
	
	rb_io_buffer_get_bytes_for_writing(buffer, &base, &buffer_size);
	
	if (offset + size > buffer_size) {
		rb_raise(rb_eRangeError, "Offset + size exceeds buffer size");
	}
	
	return (char*)base + offset;
}

// Convert Ruby symbol to ID
static ID get_type_id(VALUE type_sym) {
	return RB_SYM2ID(type_sym);
}

#ifdef HAVE_TYPED_ATOMICS

#ifdef HAVE_STDATOMIC_H
// Using stdatomic.h - proper typed atomic operations

// Static IDs for type checking (initialized in Init function)
static ID RB_IO_BUFFER_DATA_TYPE_U8;
static ID RB_IO_BUFFER_DATA_TYPE_S8;
static ID RB_IO_BUFFER_DATA_TYPE_u16;
static ID RB_IO_BUFFER_DATA_TYPE_U16;
static ID RB_IO_BUFFER_DATA_TYPE_s16;
static ID RB_IO_BUFFER_DATA_TYPE_S16;
static ID RB_IO_BUFFER_DATA_TYPE_u32;
static ID RB_IO_BUFFER_DATA_TYPE_U32;
static ID RB_IO_BUFFER_DATA_TYPE_s32;
static ID RB_IO_BUFFER_DATA_TYPE_S32;
static ID RB_IO_BUFFER_DATA_TYPE_u64;
static ID RB_IO_BUFFER_DATA_TYPE_U64;
static ID RB_IO_BUFFER_DATA_TYPE_s64;
static ID RB_IO_BUFFER_DATA_TYPE_S64;

// Macro for atomic fetch_add operations (returns new value)
#define ATOMIC_FETCH_ADD_IMPL(name, ctype, atomic_type, size, num2val, val2num) \
	static VALUE atomic_fetch_add_##name(VALUE self, size_t offset, long value) { \
		void *pointer = get_buffer_pointer(self, offset, size); \
		ctype result = atomic_fetch_add((atomic_type*)pointer, (ctype)value) + (ctype)value; \
		return val2num(result); \
	}

// Macro for atomic bitwise operations (returns new value)
#define ATOMIC_BITWISE_IMPL(name, ctype, atomic_type, size, num2val, val2num, op) \
	static VALUE atomic_##op##_##name(VALUE self, size_t offset, long value) { \
		void *pointer = get_buffer_pointer(self, offset, size); \
		atomic_fetch_##op((atomic_type*)pointer, (ctype)value); \
		ctype result = atomic_load((atomic_type*)pointer); \
		return val2num(result); \
	}

// Macro for atomic compare and swap
#define ATOMIC_CAS_IMPL(name, ctype, atomic_type, size, num2val, val2num) \
	static int atomic_cas_##name(VALUE self, size_t offset, VALUE expected_value, VALUE desired_value) { \
		void *pointer = get_buffer_pointer(self, offset, size); \
		ctype expected = (ctype)num2val(expected_value); \
		ctype desired = (ctype)num2val(desired_value); \
		/* atomic_compare_exchange_strong already checks if current == expected */ \
		return atomic_compare_exchange_strong((atomic_type*)pointer, &expected, desired); \
	}

// Generate implementations for each type
ATOMIC_FETCH_ADD_IMPL(u8, uint8_t, atomic_uint_least8_t, 1, NUM2UINT, UINT2NUM)
ATOMIC_FETCH_ADD_IMPL(i8, int8_t, atomic_int_least8_t, 1, NUM2INT, INT2NUM)
ATOMIC_FETCH_ADD_IMPL(u16, uint16_t, atomic_uint_least16_t, 2, NUM2UINT, UINT2NUM)
ATOMIC_FETCH_ADD_IMPL(i16, int16_t, atomic_int_least16_t, 2, NUM2INT, INT2NUM)
ATOMIC_FETCH_ADD_IMPL(u32, uint32_t, atomic_uint_least32_t, 4, NUM2UINT, UINT2NUM)
ATOMIC_FETCH_ADD_IMPL(i32, int32_t, atomic_int_least32_t, 4, NUM2INT, INT2NUM)
ATOMIC_FETCH_ADD_IMPL(u64, uint64_t, atomic_uint_least64_t, 8, NUM2ULL, ULL2NUM)
ATOMIC_FETCH_ADD_IMPL(i64, int64_t, atomic_int_least64_t, 8, NUM2LL, LL2NUM)

ATOMIC_BITWISE_IMPL(u8, uint8_t, atomic_uint_least8_t, 1, NUM2UINT, UINT2NUM, and)
ATOMIC_BITWISE_IMPL(i8, int8_t, atomic_int_least8_t, 1, NUM2INT, INT2NUM, and)
ATOMIC_BITWISE_IMPL(u16, uint16_t, atomic_uint_least16_t, 2, NUM2UINT, UINT2NUM, and)
ATOMIC_BITWISE_IMPL(i16, int16_t, atomic_int_least16_t, 2, NUM2INT, INT2NUM, and)
ATOMIC_BITWISE_IMPL(u32, uint32_t, atomic_uint_least32_t, 4, NUM2UINT, UINT2NUM, and)
ATOMIC_BITWISE_IMPL(i32, int32_t, atomic_int_least32_t, 4, NUM2INT, INT2NUM, and)
ATOMIC_BITWISE_IMPL(u64, uint64_t, atomic_uint_least64_t, 8, NUM2ULL, ULL2NUM, and)
ATOMIC_BITWISE_IMPL(i64, int64_t, atomic_int_least64_t, 8, NUM2LL, LL2NUM, and)

ATOMIC_BITWISE_IMPL(u8, uint8_t, atomic_uint_least8_t, 1, NUM2UINT, UINT2NUM, or)
ATOMIC_BITWISE_IMPL(i8, int8_t, atomic_int_least8_t, 1, NUM2INT, INT2NUM, or)
ATOMIC_BITWISE_IMPL(u16, uint16_t, atomic_uint_least16_t, 2, NUM2UINT, UINT2NUM, or)
ATOMIC_BITWISE_IMPL(i16, int16_t, atomic_int_least16_t, 2, NUM2INT, INT2NUM, or)
ATOMIC_BITWISE_IMPL(u32, uint32_t, atomic_uint_least32_t, 4, NUM2UINT, UINT2NUM, or)
ATOMIC_BITWISE_IMPL(i32, int32_t, atomic_int_least32_t, 4, NUM2INT, INT2NUM, or)
ATOMIC_BITWISE_IMPL(u64, uint64_t, atomic_uint_least64_t, 8, NUM2ULL, ULL2NUM, or)
ATOMIC_BITWISE_IMPL(i64, int64_t, atomic_int_least64_t, 8, NUM2LL, LL2NUM, or)

ATOMIC_BITWISE_IMPL(u8, uint8_t, atomic_uint_least8_t, 1, NUM2UINT, UINT2NUM, xor)
ATOMIC_BITWISE_IMPL(i8, int8_t, atomic_int_least8_t, 1, NUM2INT, INT2NUM, xor)
ATOMIC_BITWISE_IMPL(u16, uint16_t, atomic_uint_least16_t, 2, NUM2UINT, UINT2NUM, xor)
ATOMIC_BITWISE_IMPL(i16, int16_t, atomic_int_least16_t, 2, NUM2INT, INT2NUM, xor)
ATOMIC_BITWISE_IMPL(u32, uint32_t, atomic_uint_least32_t, 4, NUM2UINT, UINT2NUM, xor)
ATOMIC_BITWISE_IMPL(i32, int32_t, atomic_int_least32_t, 4, NUM2INT, INT2NUM, xor)
ATOMIC_BITWISE_IMPL(u64, uint64_t, atomic_uint_least64_t, 8, NUM2ULL, ULL2NUM, xor)
ATOMIC_BITWISE_IMPL(i64, int64_t, atomic_int_least64_t, 8, NUM2LL, LL2NUM, xor)

ATOMIC_CAS_IMPL(u8, uint8_t, atomic_uint_least8_t, 1, NUM2UINT, UINT2NUM)
ATOMIC_CAS_IMPL(i8, int8_t, atomic_int_least8_t, 1, NUM2INT, INT2NUM)
ATOMIC_CAS_IMPL(u16, uint16_t, atomic_uint_least16_t, 2, NUM2UINT, UINT2NUM)
ATOMIC_CAS_IMPL(i16, int16_t, atomic_int_least16_t, 2, NUM2INT, INT2NUM)
ATOMIC_CAS_IMPL(u32, uint32_t, atomic_uint_least32_t, 4, NUM2UINT, UINT2NUM)
ATOMIC_CAS_IMPL(i32, int32_t, atomic_int_least32_t, 4, NUM2INT, INT2NUM)
ATOMIC_CAS_IMPL(u64, uint64_t, atomic_uint_least64_t, 8, NUM2ULL, ULL2NUM)
ATOMIC_CAS_IMPL(i64, int64_t, atomic_int_least64_t, 8, NUM2LL, LL2NUM)

// Generic implementations using macros (similar to Ruby's IO_BUFFER_SET_VALUE pattern)
static VALUE atomic_increment_impl(VALUE self, ID type_identifier, size_t offset, long value) {
#define ATOMIC_FETCH_ADD_CASE(name, impl_name) \
	if (type_identifier == RB_IO_BUFFER_DATA_TYPE_##name) { \
		return atomic_fetch_add_##impl_name(self, offset, value); \
	}
	
	ATOMIC_FETCH_ADD_CASE(U8, u8)
	ATOMIC_FETCH_ADD_CASE(S8, i8)
	ATOMIC_FETCH_ADD_CASE(u16, u16)
	ATOMIC_FETCH_ADD_CASE(U16, u16)
	ATOMIC_FETCH_ADD_CASE(s16, i16)
	ATOMIC_FETCH_ADD_CASE(S16, i16)
	ATOMIC_FETCH_ADD_CASE(u32, u32)
	ATOMIC_FETCH_ADD_CASE(U32, u32)
	ATOMIC_FETCH_ADD_CASE(s32, i32)
	ATOMIC_FETCH_ADD_CASE(S32, i32)
	ATOMIC_FETCH_ADD_CASE(u64, u64)
	ATOMIC_FETCH_ADD_CASE(U64, u64)
	ATOMIC_FETCH_ADD_CASE(s64, i64)
	ATOMIC_FETCH_ADD_CASE(S64, i64)
#undef ATOMIC_FETCH_ADD_CASE
	
	rb_raise(rb_eArgError, "Unsupported type for atomic operations: %"PRIsVALUE, rb_id2str(type_identifier));
	return Qnil;
}

static VALUE atomic_and_impl(VALUE self, ID type_identifier, size_t offset, long value) {
#define ATOMIC_AND_CASE(name, impl_name) \
	if (type_identifier == RB_IO_BUFFER_DATA_TYPE_##name) { \
		return atomic_and_##impl_name(self, offset, value); \
	}
	
	ATOMIC_AND_CASE(U8, u8)
	ATOMIC_AND_CASE(S8, i8)
	ATOMIC_AND_CASE(u16, u16)
	ATOMIC_AND_CASE(U16, u16)
	ATOMIC_AND_CASE(s16, i16)
	ATOMIC_AND_CASE(S16, i16)
	ATOMIC_AND_CASE(u32, u32)
	ATOMIC_AND_CASE(U32, u32)
	ATOMIC_AND_CASE(s32, i32)
	ATOMIC_AND_CASE(S32, i32)
	ATOMIC_AND_CASE(u64, u64)
	ATOMIC_AND_CASE(U64, u64)
	ATOMIC_AND_CASE(s64, i64)
	ATOMIC_AND_CASE(S64, i64)
#undef ATOMIC_AND_CASE
	
	rb_raise(rb_eArgError, "Unsupported type for atomic operations: %"PRIsVALUE, rb_id2str(type_identifier));
	return Qnil;
}

static VALUE atomic_or_impl(VALUE self, ID type_identifier, size_t offset, long value) {
#define ATOMIC_OR_CASE(name, impl_name) \
	if (type_identifier == RB_IO_BUFFER_DATA_TYPE_##name) { \
		return atomic_or_##impl_name(self, offset, value); \
	}
	
	ATOMIC_OR_CASE(U8, u8)
	ATOMIC_OR_CASE(S8, i8)
	ATOMIC_OR_CASE(u16, u16)
	ATOMIC_OR_CASE(U16, u16)
	ATOMIC_OR_CASE(s16, i16)
	ATOMIC_OR_CASE(S16, i16)
	ATOMIC_OR_CASE(u32, u32)
	ATOMIC_OR_CASE(U32, u32)
	ATOMIC_OR_CASE(s32, i32)
	ATOMIC_OR_CASE(S32, i32)
	ATOMIC_OR_CASE(u64, u64)
	ATOMIC_OR_CASE(U64, u64)
	ATOMIC_OR_CASE(s64, i64)
	ATOMIC_OR_CASE(S64, i64)
#undef ATOMIC_OR_CASE
	
	rb_raise(rb_eArgError, "Unsupported type for atomic operations: %"PRIsVALUE, rb_id2str(type_identifier));
	return Qnil;
}

static VALUE atomic_xor_impl(VALUE self, ID type_identifier, size_t offset, long value) {
#define ATOMIC_XOR_CASE(name, impl_name) \
	if (type_identifier == RB_IO_BUFFER_DATA_TYPE_##name) { \
		return atomic_xor_##impl_name(self, offset, value); \
	}
	
	ATOMIC_XOR_CASE(U8, u8)
	ATOMIC_XOR_CASE(S8, i8)
	ATOMIC_XOR_CASE(u16, u16)
	ATOMIC_XOR_CASE(U16, u16)
	ATOMIC_XOR_CASE(s16, i16)
	ATOMIC_XOR_CASE(S16, i16)
	ATOMIC_XOR_CASE(u32, u32)
	ATOMIC_XOR_CASE(U32, u32)
	ATOMIC_XOR_CASE(s32, i32)
	ATOMIC_XOR_CASE(S32, i32)
	ATOMIC_XOR_CASE(u64, u64)
	ATOMIC_XOR_CASE(U64, u64)
	ATOMIC_XOR_CASE(s64, i64)
	ATOMIC_XOR_CASE(S64, i64)
#undef ATOMIC_XOR_CASE
	
	rb_raise(rb_eArgError, "Unsupported type for atomic operations: %"PRIsVALUE, rb_id2str(type_identifier));
	return Qnil;
}

static VALUE atomic_compare_and_swap_impl(VALUE self, ID type_identifier, size_t offset, VALUE expected_value, VALUE desired_value) {
#define ATOMIC_CAS_CASE(name, impl_name) \
	if (type_identifier == RB_IO_BUFFER_DATA_TYPE_##name) { \
		return atomic_cas_##impl_name(self, offset, expected_value, desired_value) ? Qtrue : Qfalse; \
	}
	
	ATOMIC_CAS_CASE(U8, u8)
	ATOMIC_CAS_CASE(S8, i8)
	ATOMIC_CAS_CASE(u16, u16)
	ATOMIC_CAS_CASE(U16, u16)
	ATOMIC_CAS_CASE(s16, i16)
	ATOMIC_CAS_CASE(S16, i16)
	ATOMIC_CAS_CASE(u32, u32)
	ATOMIC_CAS_CASE(U32, u32)
	ATOMIC_CAS_CASE(s32, i32)
	ATOMIC_CAS_CASE(S32, i32)
	ATOMIC_CAS_CASE(u64, u64)
	ATOMIC_CAS_CASE(U64, u64)
	ATOMIC_CAS_CASE(s64, i64)
	ATOMIC_CAS_CASE(S64, i64)
#undef ATOMIC_CAS_CASE
	
	rb_raise(rb_eArgError, "Unsupported type for atomic operations: %"PRIsVALUE, rb_id2str(type_identifier));
	return Qfalse;
}

#endif // HAVE_STDATOMIC_H

#else
#error "Typed atomic operations not available"
#endif // HAVE_TYPED_ATOMICS

// Ruby method wrappers
static VALUE atomic_increment(int argc, VALUE *argv, VALUE self) {
	VALUE type_symbol, offset_value, value_value;
	
	rb_scan_args(argc, argv, "21", &type_symbol, &offset_value, &value_value);
	
	if (value_value == Qnil) {
		value_value = INT2NUM(1);
	}
	
	ID type_identifier = get_type_id(type_symbol);
	size_t offset = NUM2SIZET(offset_value);
	long value = NUM2LONG(value_value);
	
	return atomic_increment_impl(self, type_identifier, offset, value);
}

static VALUE atomic_decrement(int argc, VALUE *argv, VALUE self) {
	VALUE type_symbol, offset_value, value_value;
	
	rb_scan_args(argc, argv, "21", &type_symbol, &offset_value, &value_value);
	
	if (value_value == Qnil) {
		value_value = INT2NUM(1);
	}
	
	ID type_identifier = get_type_id(type_symbol);
	size_t offset = NUM2SIZET(offset_value);
	long value = NUM2LONG(value_value);
	
	return atomic_increment_impl(self, type_identifier, offset, -value);
}

static VALUE atomic_add(VALUE self, VALUE type_symbol, VALUE offset_value, VALUE value_value) {
	ID type_identifier = get_type_id(type_symbol);
	size_t offset = NUM2SIZET(offset_value);
	long value = NUM2LONG(value_value);
	
	return atomic_increment_impl(self, type_identifier, offset, value);
}

static VALUE atomic_subtract(VALUE self, VALUE type_symbol, VALUE offset_value, VALUE value_value) {
	ID type_identifier = get_type_id(type_symbol);
	size_t offset = NUM2SIZET(offset_value);
	long value = NUM2LONG(value_value);
	
	return atomic_increment_impl(self, type_identifier, offset, -value);
}

static VALUE atomic_and(VALUE self, VALUE type_symbol, VALUE offset_value, VALUE value_value) {
	ID type_identifier = get_type_id(type_symbol);
	size_t offset = NUM2SIZET(offset_value);
	long value = NUM2LONG(value_value);
	
	return atomic_and_impl(self, type_identifier, offset, value);
}

static VALUE atomic_or(VALUE self, VALUE type_symbol, VALUE offset_value, VALUE value_value) {
	ID type_identifier = get_type_id(type_symbol);
	size_t offset = NUM2SIZET(offset_value);
	long value = NUM2LONG(value_value);
	
	return atomic_or_impl(self, type_identifier, offset, value);
}

static VALUE atomic_xor(VALUE self, VALUE type_symbol, VALUE offset_value, VALUE value_value) {
	ID type_identifier = get_type_id(type_symbol);
	size_t offset = NUM2SIZET(offset_value);
	long value = NUM2LONG(value_value);
	
	return atomic_xor_impl(self, type_identifier, offset, value);
}

static VALUE atomic_compare_and_swap(VALUE self, VALUE type_symbol, VALUE offset_value, VALUE expected_value, VALUE desired_value) {
	ID type_identifier = get_type_id(type_symbol);
	size_t offset = NUM2SIZET(offset_value);
	
	return atomic_compare_and_swap_impl(self, type_identifier, offset, expected_value, desired_value);
}

// Helper macro to define method only if it doesn't exist
// Uses rb_method_boundp to check if method is already defined (feature detection)
#define DEFINE_METHOD_IF_NOT_EXISTS(klass, name, func, argc) \
	do { \
		ID method_identifier = rb_intern(name); \
		if (!rb_method_boundp(klass, method_identifier, 0)) { \
			rb_define_method(klass, name, func, argc); \
		} \
	} while (0)

void Init_IO_Buffer_Atomic(void) {
#ifdef HAVE_RB_EXT_RACTOR_SAFE
	rb_ext_ractor_safe(true);
#endif
	
	VALUE IO_Buffer = rb_const_get(rb_cIO, rb_intern("Buffer"));
	
	// Initialize type IDs (matching Ruby's pattern)
#define IO_BUFFER_DEFINE_DATA_TYPE(name) RB_IO_BUFFER_DATA_TYPE_##name = rb_intern_const(#name)
	IO_BUFFER_DEFINE_DATA_TYPE(U8);
	IO_BUFFER_DEFINE_DATA_TYPE(S8);
	IO_BUFFER_DEFINE_DATA_TYPE(u16);
	IO_BUFFER_DEFINE_DATA_TYPE(U16);
	IO_BUFFER_DEFINE_DATA_TYPE(s16);
	IO_BUFFER_DEFINE_DATA_TYPE(S16);
	IO_BUFFER_DEFINE_DATA_TYPE(u32);
	IO_BUFFER_DEFINE_DATA_TYPE(U32);
	IO_BUFFER_DEFINE_DATA_TYPE(s32);
	IO_BUFFER_DEFINE_DATA_TYPE(S32);
	IO_BUFFER_DEFINE_DATA_TYPE(u64);
	IO_BUFFER_DEFINE_DATA_TYPE(U64);
	IO_BUFFER_DEFINE_DATA_TYPE(s64);
	IO_BUFFER_DEFINE_DATA_TYPE(S64);
#undef IO_BUFFER_DEFINE_DATA_TYPE
	
	DEFINE_METHOD_IF_NOT_EXISTS(IO_Buffer, "atomic_increment", atomic_increment, -1);
	DEFINE_METHOD_IF_NOT_EXISTS(IO_Buffer, "atomic_decrement", atomic_decrement, -1);
	DEFINE_METHOD_IF_NOT_EXISTS(IO_Buffer, "atomic_add", atomic_add, 3);
	DEFINE_METHOD_IF_NOT_EXISTS(IO_Buffer, "atomic_subtract", atomic_subtract, 3);
	DEFINE_METHOD_IF_NOT_EXISTS(IO_Buffer, "atomic_and", atomic_and, 3);
	DEFINE_METHOD_IF_NOT_EXISTS(IO_Buffer, "atomic_or", atomic_or, 3);
	DEFINE_METHOD_IF_NOT_EXISTS(IO_Buffer, "atomic_xor", atomic_xor, 3);
	DEFINE_METHOD_IF_NOT_EXISTS(IO_Buffer, "atomic_compare_and_swap", atomic_compare_and_swap, 4);
}
