#if !defined(TL_H)
#define TL_H

#if defined(_MSC_VER)
	#define TL_COMPILER_MSVC 1
#elif defined(__GNUC__)
	#define TL_COMPILER_GCC 1
#elif defined(__clang__)
	#define TL_COMPILER_CLANG 1
#else
	#error Unknown compiler
#endif


#if !defined(TL_DEFF)
 #define TL_DEFF
#endif

#define TL_BUILD_DEBUG

#define TL_MakeStatement(S) do{S}while(0)
#define TL_Stringify_(S) #S
#define TL_Stringify(S) TL_Stringify_(S)

#define TL_Glue_(A,B) A##B
#define TL_Glue(A,B) TL_Glue_(A,B)

////////////////////////////////////////////////////////////////
//
// Asserts
//
#if defined(TL_COMPILER_MSVC)
# define TL_Trap() __debugbreak()
#elif TL_COMPILER_CLANG || TL_COMPILER_GCC
 #define TL_Trap() __builtin_trap()
#else
 #error Unknown trap intrinsic for this compiler.
#endif

#if defined(TL_BUILD_DEBUG)
 #define TL_Assert(x) TL_MakeStatement(if(!(x)) {TL_Trap();})
#else
 #define TL_Assert(x)
#endif

#define TL_InvalidPath        TL_Assert(!"Invalid Path!")
#define TL_NotImplemented     TL_Assert(!"Not Implemented!")
#define TL_InvalidDefaultCase default: {TL_InvalidPath;} break

#define TL_StaticAssertMsg(cond, msg) typedef char TL_Glue(static_assertion_at_line_, msg)[(!!(cond))*2-1]
#define TL_StaticAssert(cond)TL_StaticAssertMsg(cond, __LINE__)

#define TL_NoOp ((void)0)

////////////////////////////////////////////////////////////////
//
// Base Types
//
//
#pragma warning (push,0)
 #include <stdint.h>
#pragma warning (pop)

typedef size_t TL_Memory_Index;

TL_StaticAssert(sizeof(char) == 1);
typedef char TL_Byte;

typedef intptr_t TL_PointerSizeSigned;
typedef uintptr_t TL_PointerSizeUnsigned;

typedef intptr_t TL_IntPtr;
typedef uintptr_t TL_UintPtr;

typedef uint8_t TL_U8;
typedef uint16_t TL_U16;
typedef uint32_t TL_U32;
typedef uint64_t TL_U64;

typedef int8_t TL_S8;
typedef int16_t TL_S16;
typedef int32_t TL_S32;
typedef int64_t TL_S64;

typedef TL_U8 TL_B8;
typedef TL_U16 TL_B16;
typedef TL_U32 TL_B32;
typedef TL_U64 TL_B64;

typedef float TL_F32;
typedef double TL_F64;

TL_StaticAssert(sizeof(TL_U8)  == sizeof(TL_S8));
TL_StaticAssert(sizeof(TL_U16) == sizeof(TL_S16));
TL_StaticAssert(sizeof(TL_U32) == sizeof(TL_S32));
TL_StaticAssert(sizeof(TL_U64) == sizeof(TL_S64));

TL_StaticAssert(sizeof(TL_U8)  == 1);
TL_StaticAssert(sizeof(TL_U16) == 2);
TL_StaticAssert(sizeof(TL_U32) == 4);
TL_StaticAssert(sizeof(TL_U64) == 8);

TL_StaticAssert(sizeof(TL_UintPtr) == sizeof(TL_IntPtr));

TL_StaticAssert(sizeof(TL_F32) == 4);
TL_StaticAssert(sizeof(TL_F64) == 8);

#ifndef TL_U8_Min
 #define TL_U8_Min 0u
 #define TL_U8_Max 0xffu
 #define TL_S8_Min (-0x7f - 1)
 #define TL_S8_Max 0x7f
 
 #define TL_U16_Min 0u
 #define TL_U16_Max 0xffffu
 #define TL_S16_Min (-0x7fff - 1)
 #define TL_S16_Max 0x7fff
 
 #define TL_U32_Min 0u
 #define TL_U32_Max 0xffffffffu
 #define TL_S32_Min (-0x7fffffff - 1)
 #define TL_S32_Max 0x7fffffff
 
 #define TL_U64_Min 0ull
 #define TL_U64_Max 0xffffffffffffffffull
 #define TL_S64_Min (-0x7fffffffffffffffll - 1)
 #define TL_S64_Max 0x7fffffffffffffffll
 
 
 #define TL_F32_Min 1.17549435e-38f
 #define TL_F32_Max 3.40282347e+38f
 
 #define TL_F64_Min 2.2250738585072014e-308
 #define TL_F64_Max 1.7976931348623157e+308
 
 
 // TODO: REMOVE?
 #if !defined(__cplusplus)
   #if defined(_MSC_VER) && _MSC_VER <= 1800
    #define TL_Inline __inline
   #elif !defined(__STDC_VERSION__)
    #define TL_Inline __inline__
   #else
    #define TL_Inline
   #endif
 #endif
 // NOTE: Get true and false Remove??
 #if !defined(__cplusplus)
  #if (defined(_MSC_VER) && _MSC_VER < 1800) || (!defined(_MSC_VER) && !defined(__STDC_VERSION__))
   #ifndef true
    #define true  (0 == 0)
   #endif
   #ifndef false
    #define false (0 != 0)
   #endif
   typedef b8 bool;
  #else
   #include <stdbool.h>
  #endif
 #endif

#endif

////////////////////////////////////////////////////////////////
//
// Macros
//
//

#define TL_Internal static
#define TL_LocalPersist static
#define TL_Global static

#if defined(__cplusplus)
 #define TL_ZeroStruct {}
#else
 #define TL_ZeroStruct {0}
#endif

//NOTE: only for searching
#define TL_Cast(Type, var) ((Type) (var))

#define TL_DerefPtr(var) (*(var))
#define TL_AddressOf(var) (&(var))

#define TL_Swap(Type, a, b) TL_MakeStatement(Type temp = (a); (a) = (b); (b) = temp;)

// #define Between(min, SIGN1, var, SIGN2, max) (((min) SIGN1 (var)) && ((var) SIGN2 (max)))
#define TL_ArrayCount(array) (sizeof((array)) / sizeof((array)[0]))

#define TL_Bit(pos) (TL_Cast(TL_U64, 1) << (pos))

#define TL_Pow2(value) (1 << (value))
#define TL_AlignPow2(value, align) (((value) + ((align) - 1)) & ~((align) - 1))
#define TL_Align4(value) (((value) + 3) & ~3)
#define TL_Align8(value) (((value) + 7) & ~7)
#define TL_Align16(value) (((value) + 0xF) & ~0xF)


#define TL_CeilIntegerDiv(a, b) (((a) + (b) - 1)/(b))

#define TL_IntFromPtr(ptr) TL_Cast(TL_U64, ptr)
#define TL_PtrFromInt(integer) TL_Cast(void*, TL_Cast(TL_U8*, 0) + (integer))

//---------------------------------------------
// Member Offsets

#define TL_Member(Type, member) TL_Cast(Type*, 0)->member
#define TL_OffsetOf(Type, member) TL_IntFromPtr(&TL_Member(Type, member))
#define TL_MemberFromOffset(Type, ptr, offset) TL_Cast(Type, TL_Cast(TL_U8*, ptr) + (offset))
#define TL_CastFromMember(Type, member, ptr) TL_Cast(Type*, TL_Cast(TL_U8*, ptr) - TL_OffsetOf(Type, member))

//---------------------------------------------
// For Loop Macros

#define TL_SetupDefer(Setup, Defer) for(int _i_ = ((Setup), 0); !_i_; _i_ += 1, (Defer))
//NOTE: Enters "loop" when Setup is not 0
#define TL_OnSuccessfulSetup_StatementAndDefer(Setup, Defer) for(int _i_ = !(Setup); !_i_; _i_ += 1, (Defer))
#define TL_SetupDeferGuardedStatement(Setup, Defer) for(int _i_ = 2 * !(Setup); (_i_ == 2 ? ((Defer), 0) : !_i_); _i_ += 1, (Defer))

#define TL_EachIndex(it, count) (TL_U64 it = 0; it < (count); it += 1)
//#define TL_EachIndex(Type, it, count) (Type it = 0; it < (count); it += 1)
#define TL_EachElement(it, array) (TL_U64 it = 0; it < TL_ArrayCount(array); it += 1)
//#define TL_EachElement(Type, it, array) (Type it = 0; it < TL_ArrayCount(array); it += 1)
#define TL_EachEnumVal(Type, it) (Type it = TL_Cast(Type, 0); it < Type##_COUNT; it = TL_Cast(Type, it+1))
#define TL_EachNonZeroEnumVal(Type, it) (Type it = TL_Cast(Type, 1); it < Type##_COUNT; it = TL_Cast(Type, it+1))

//---------------------------------------------
// Clamps, Mins, Maxes

#define TL_Min(a, b) (((a)<(b))?(a):(b))
#define TL_Max(a, b) (((a)>(b))?(a):(b))
#define TL_ClampTop(a, x) TL_Min(a, x)
#define TL_ClampBot(x, b) TL_Max(x, b)
#define TL_Clamp(min, x, max) (((x)<(min))?(min):((x)>(max))?(max):(x))

//----------------------------------------------
// Units

#define TL_KB(n)  (TL_Cast(TL_U64, n) << 10)
#define TL_MB(n)  (TL_Cast(TL_U64, n) << 20)
#define TL_GB(n)  (TL_Cast(TL_U64, n) << 30)
#define TL_TB(n)  (TL_Cast(TL_U64, n) << 40)

#define TL_Thousand(n)   ((n)*1000)
#define TL_Million(n)    ((n)*1000000)
#define TL_Billion(n)    ((n)*1000000000)

//----------------------------------------------
// Double Linkend List

#define TL_DLL_Init(Sentinel) \
 (Sentinel)->next = (Sentinel); \
 (Sentinel)->prev = (Sentinel); \

#define TL_DLL_Insert(Sentinel, Element) \
 (Element)->next = (Sentinel)->next; \
 (Element)->prev = (Sentinel); \
 (Element)->prev->next = (Element); \
 (Element)->next->prev = (Element); \

//----------------------------------------------
// Linkage Keywords 

#if __cplusplus
 #define TL_C_LINKAGE_BEGIN extern "C"{
 #define TL_C_LINKAGE_END }
 #define TL_C_LINKAGE extern "C"
#else
 #define TL_C_LINKAGE_BEGIN
 #define TL_C_LINKAGE_END
 #define TL_C_LINKAGE
#endif


////////////////////////////////
// Safe Casts

TL_DEFF TL_U16 tl_safe_cast_U32_to_U16(TL_U32 x);
TL_DEFF TL_S16 tl_safe_cast_S32_to_S16(TL_S32 x);
TL_DEFF TL_U32 tl_safe_cast_U64_to_U32(TL_U64 x);
TL_DEFF TL_S32 tl_safe_cast_S64_to_S32(TL_S64 x);


////////////////////////////////////////////////////////////////
//
// Memory
//
//


TL_DEFF void* tl_memory_copy(TL_Memory_Index size, void* source_init, void* dest_init);

TL_DEFF void tl_memory_zero_size(void* ptr, TL_Memory_Index size);
#define TL_MemoryZero(ptr,size) tl_memory_zero_size((ptr),(size))
#define TL_MemoryZeroStruct(struct_) tl_memory_zero_size(&(struct_),sizeof(struct_))
#define TL_MemoryZeroArray(pointer, count) tl_memory_zero_size(pointer, sizeof((pointer)[0])*count)

//TODO: own implementations
#define TL_MemoryMove(dst, src, size)    memmove((dst), (src), (size))
#define TL_MemorySet(dst, byte, size)    memset((dst), (byte), (size))
#define TL_MemoryStrlen(ptr)             strlen(ptr)
#define TL_MemoryCompare(a, b, size)     memcmp((a), (b), (size))

#define TL_MemoryMatch(a,b,z)     (TL_MemoryCompare((a),(b),(z)) == 0)
#define TL_MemoryMatchStruct(a,b)  TL_MemoryMatch((a),(b),sizeof(*(a)))
#define TL_MemoryMatchArray(a,b)   TL_MemoryMatch((a),(b),sizeof(a))

//
// Arena Allocator
//
typedef struct TL_Memory_Arena TL_Memory_Arena;
struct TL_Memory_Arena {
  TL_Memory_Index size;
  TL_U8* base;
  TL_Memory_Index used;

  TL_S32 temp_count;
  TL_S32 padding;
};

TL_DEFF void tl_arena_initialize(TL_Memory_Arena* arena, TL_Memory_Index size, void* base);
TL_DEFF void tl_arena_subdivide(TL_Memory_Arena* sub_arena, TL_Memory_Arena* arena, TL_Memory_Index size, TL_Memory_Index alignment);

TL_DEFF void* tl_arena_push_size_(TL_Memory_Arena* arena, TL_Memory_Index size_init, TL_Memory_Index alignment);
#define TL_ArenaPushStruct(arena, Type, alignment) (Type*)tl_arena_push_size_(arena, sizeof(Type), alignment)
#define TL_ArenaPushArray(arena, count, Type, alignment) (Type*)tl_arena_push_size_((arena), (count)*sizeof(Type), alignment)
#define TL_ArenaPushSize(arena, size, alignment) tl_arena_push_size_(arena, size, alignment)
#define TL_ArenaPushCopy(arena, size, source, alignment) tl_memory_copy(size, source, tl_arena_push_size_(arena, size, alignment))

TL_DEFF TL_Memory_Index tl_arena_get_remaining_size(TL_Memory_Arena* arena, TL_Memory_Index alignment);
TL_DEFF TL_Memory_Index tl_arena_get_alignment_offset(TL_Memory_Arena* arena, TL_Memory_Index alignment);

TL_DEFF void tl_arena_check(TL_Memory_Arena* arena);

TL_DEFF char* tl_arena_push_c_string(TL_Memory_Arena* arena, char* source);

typedef struct TL_Memory_TempMemory TL_Memory_TempMemory;
struct TL_Memory_TempMemory 
{
  TL_Memory_Arena* arena;
  TL_Memory_Index used;
};
TL_DEFF TL_Memory_TempMemory tl_begin_temporary_memory(TL_Memory_Arena* arena);
TL_DEFF void tl_end_temporary_memory(TL_Memory_TempMemory temp_mem);

////////////////////////////////////////////////////////////////
//
// Intrinsics
//
//
#if TL_COMPILER_MSVC
 #include <intrin.h>
#elif TL_COMPILER_CLANG
 #include <x86intrin.h>
#else
 #error SSE/NEON optimizations are not avaialble for this compiler yet!!!
#endif

#if defined(TL_COMPILER_MSVC)
 #define TL_CompletePreviousWritesBeforeFutureWrite _WriteBarrier()
 #define TL_CompletePreviousReadsBeforeFutureRead _ReadBarrier()

 TL_DEFF TL_U32 TL_atomic_compare_exchange_u32(volatile TL_U32* value, TL_U32 new_value, TL_U32 expected);
 TL_DEFF TL_U64 TL_atomic_exchange(volatile TL_U64* value, TL_U64 new_value);
 TL_DEFF TL_U32 TL_atomic_add_U32(volatile TL_U32* value, TL_U32 addend);
 TL_DEFF TL_U64 TL_atomic_add_U64(volatile TL_U64* value, TL_U64 addend);
#else
 not supported
#endif

////////////////////////////////////////////////////////////////
//
// Math/TL_Vector Operations
//

#include <math.h>

#define TL_Pi32 3.14159265359f
#define TL_Tau32 6.28318530717958647692f

TL_DEFF TL_F32 tl_sign_of_F32(TL_F32 value);
TL_DEFF TL_S32 tl_sign_of_S32(TL_S32 value);
TL_DEFF TL_S32 tl_round_F32_to_S32(TL_F32 float32);
TL_DEFF TL_U32 tl_round_F32_to_U32(TL_F32 float32);
TL_DEFF TL_S32 tl_floor_F32_to_S32(TL_F32 float32);
TL_DEFF TL_S32 tl_floor_F32_to_U32(TL_F32 float32);
TL_DEFF TL_S32 tl_ceil_F32_to_S32(TL_F32 float32);
TL_DEFF TL_S32 tl_truncate_F32_to_S32(TL_F32 float32);
TL_DEFF TL_F32 tl_sin(TL_F32 angle);
TL_DEFF TL_F32 tl_cos(TL_F32 angle);
TL_DEFF TL_F32 tl_atan2(TL_F32 y, TL_F32 x);
TL_DEFF TL_F32 tl_absolute_value(TL_F32 value);
TL_DEFF TL_F32 tl_square_root(TL_F32 a);
typedef struct TL_BitScanResult TL_BitScanResult;
struct TL_BitScanResult {
 TL_B32 found;
 TL_U32 index;
};
TL_DEFF TL_BitScanResult tl_find_least_significant_set_bit(TL_U32 value);
TL_DEFF TL_U32 tl_rotate_left(TL_U32 value, TL_S32 amount);
TL_DEFF TL_U32 tl_rotate_right(TL_U32 value, TL_S32 amount);

TL_DEFF TL_F32 tl_square(TL_F32 a);
TL_DEFF TL_F32 tl_lerp(TL_F32 a, TL_F32 t, TL_F32 b);
TL_DEFF TL_F32 tl_clamp_min_max(TL_F32 min, TL_F32 value, TL_F32 max);
TL_DEFF TL_F32 tl_clamp01(TL_F32 value);
TL_DEFF TL_F32 tl_map_range_to01(TL_F32 min, TL_F32 t, TL_F32 max);
TL_DEFF TL_F32 tl_safe_ratio_n(TL_F32 numerator, TL_F32 divisor, TL_F32 n);
TL_DEFF TL_F32 tl_safe_ratio_0(TL_F32 numerator, TL_F32 divisor);
TL_DEFF TL_F32 tl_safe_ratio_1(TL_F32 numerator, TL_F32 divisor);

//
// TL_V2 
// 
typedef union TL_V2 TL_V2;
union TL_V2 {
 struct {
  TL_F32 x, y;
 };
 struct {
  TL_F32 u, v;
 };
 TL_F32 e[2];
};
TL_DEFF TL_V2 tl_v2(TL_F32 x, TL_F32 y);
TL_DEFF TL_V2 tl_x_V2(TL_F32 x);
TL_DEFF TL_V2 tl_zero_V2();
TL_DEFF TL_V2 tl_one_V2();
TL_DEFF TL_V2 tl_hadamard_V2(TL_V2 a, TL_V2 b);
TL_DEFF TL_F32 tl_inner_V2(TL_V2 a, TL_V2 b);
TL_DEFF TL_F32 tl_length_square_V2(TL_V2 a);
TL_DEFF TL_F32 tl_length_V2(TL_V2 a);
TL_DEFF TL_V2 tl_perpendicular_V2(TL_V2 a);
TL_DEFF TL_V2 tl_clamp01_V2(TL_V2 value);
TL_DEFF TL_V2 tl_get_unit_circle_vector_V2(TL_F32 angle);

TL_DEFF TL_V2 tl_add_V2(TL_V2 a, TL_V2 b);
TL_DEFF TL_V2 tl_subtract_V2(TL_V2 a, TL_V2 b);
TL_DEFF TL_V2 tl_multiply_V2(TL_F32 a, TL_V2 b);
TL_DEFF TL_V2 tl_invert_V2(TL_V2 a);

#if defined (__cplusplus)
 TL_DEFF TL_V2 operator*(TL_F32 a, TL_V2 b);
 TL_DEFF TL_V2 operator*(TL_V2 b, TL_F32 a);
 TL_DEFF TL_V2& operator*=(TL_V2& a, TL_F32 b);
 TL_DEFF TL_V2 operator-(TL_V2 a);
 TL_DEFF TL_V2 operator+(TL_V2 a, TL_V2 b);
 TL_DEFF TL_V2& operator+=(TL_V2& a, TL_V2 b);
 TL_DEFF TL_V2 operator-(TL_V2 a, TL_V2 b);
 TL_DEFF TL_V2& operator-=(TL_V2& a, TL_V2 b);
#endif
//
// TL_V3 
//
typedef union TL_V3 TL_V3;
union TL_V3 {
 struct {
  TL_F32 x, y, z;
 };
 struct {
  TL_V2 xy;
  TL_F32 ignored0_;
 };
 struct {
  TL_F32 ignored1_;
  TL_V2 yz;
 };
 struct {
  TL_F32 r, g, b;
 };
 struct {
  TL_F32 u, v, w;
 };
 struct {
  TL_V2 uv;
  TL_F32 ignored2_;
 };
 struct {
  TL_F32 ignored3_;
  TL_V2 vw;
 };
 TL_F32 e[3];
};
TL_DEFF TL_V3 tl_v3(TL_F32 x, TL_F32 y, TL_F32 z);
TL_DEFF TL_V3 tl_x_V3(TL_F32 x);
TL_DEFF TL_V3 tl_zero_V3();
TL_DEFF TL_V3 tl_one_V3();
TL_DEFF TL_V3 tl_hadamard_V3(TL_V3 a, TL_V3 b);
TL_DEFF TL_F32 tl_inner_V3(TL_V3 a, TL_V3 b);
TL_DEFF TL_F32 tl_length_square_V3(TL_V3 a);
TL_DEFF TL_F32 tl_length_V3(TL_V3 a);
TL_DEFF TL_V3 tl_normalize_V3(TL_V3 a);
TL_DEFF TL_V3 tl_clamp01_V3(TL_V3 value);
TL_DEFF TL_V3 tl_lerp_V3(TL_V3 a, TL_F32 t, TL_V3 b);

TL_DEFF TL_V3 tl_add_V3(TL_V3 a, TL_V3 b);
TL_DEFF TL_V3 tl_subtract_V3(TL_V3 a, TL_V3 b);
TL_DEFF TL_V3 tl_multiply_V3(TL_F32 a, TL_V3 b);
TL_DEFF TL_V3 tl_invert_V3(TL_V3 a);

#if defined(__cplusplus)
 TL_DEFF TL_V3 operator*(TL_F32 a, TL_V3 b);
 TL_DEFF TL_V3 operator*(TL_V3 b, TL_F32 a);
 TL_DEFF TL_V3& operator*=(TL_V3& a, TL_F32 b);
 TL_DEFF TL_V3 operator-(TL_V3 a);
 TL_DEFF TL_V3 operator+(TL_V3 a, TL_V3 b);
 TL_DEFF TL_V3& operator+=(TL_V3& a, TL_V3 b);
 TL_DEFF TL_V3 operator-(TL_V3 a, TL_V3 b);
 TL_DEFF TL_V3& operator-=(TL_V3& a, TL_V3 b);
#endif
//
// TL_V4 
//
typedef union TL_V4 TL_V4;
union TL_V4 {
 struct {
  union {
   TL_V3 xyz;
   struct{TL_F32 x, y, z;};
  };
  TL_F32 w;
 };
 struct {
  TL_V2 xy;
  TL_F32 ignored0_;
  TL_F32 ignored1_;
 };
 struct {
  TL_F32 ignored2_;
  TL_V2 yz;
  TL_F32 ignored3_;
 };
 struct {
  TL_F32 ignored4_;
  TL_F32 ignored5_;
  TL_V2 zw;
 };
 struct {
  union {
   struct { TL_F32 r, g, b; };
   TL_V3 rgb;
  };
  TL_F32 a;
 }; 
 TL_F32 e[4];
};

TL_DEFF TL_V4 tl_v4(TL_F32 x, TL_F32 y, TL_F32 z, TL_F32 w);
TL_DEFF TL_V4 tl_x_V4(TL_F32 x);
TL_DEFF TL_V4 tl_0_V4();
TL_DEFF TL_V4 tl_1_V4();
TL_DEFF TL_V4 tl_hadamard_V4(TL_V4 a, TL_V4 b);
TL_DEFF TL_F32 tl_inner_V4(TL_V4 a, TL_V4 b);
TL_DEFF TL_F32 tl_length_square_V4(TL_V4 a);
TL_DEFF TL_F32 tl_length_V4(TL_V4 a);
TL_DEFF TL_V4 tl_clamp01_V4(TL_V4 value);
TL_DEFF TL_V4 tl_lerp_V4(TL_V4 a, TL_F32 t, TL_V4 b);

TL_DEFF TL_V4 tl_add_V4(TL_V4 a, TL_V4 b);
TL_DEFF TL_V4 tl_subtract_V4(TL_V4 a, TL_V4 b);
TL_DEFF TL_V4 tl_multiply_V4(TL_F32 a, TL_V4 b);
TL_DEFF TL_V4 tl_invert_V4(TL_V4 a);

#if defined(__cplusplus)
 TL_DEFF TL_V4 operator*(TL_F32 a, TL_V4 b);
 TL_DEFF TL_V4 operator*(TL_V4 b, TL_F32 a);
 TL_DEFF TL_V4& operator*=(TL_V4& a, TL_F32 b);
 TL_DEFF TL_V4 operator-(TL_V4 a);
 TL_DEFF TL_V4 operator+(TL_V4 a, TL_V4 b);
 TL_DEFF TL_V4& operator+=(TL_V4& a, TL_V4 b);
 TL_DEFF TL_V4 operator-(TL_V4 a, TL_V4 b);
 TL_DEFF TL_V4& operator-=(TL_V4& a, TL_V4 b);
#endif

////////////////////////////////////////////////////////////////
//
// Rectangle Operations
//
//

//
//  Rectangle 2
//
typedef struct TL_Rectangle2 TL_Rectangle2;
struct TL_Rectangle2 {
 TL_V2 min;
 TL_V2 max;
};
TL_DEFF TL_V2 tl_get_center_Rectangle2(TL_Rectangle2 rect);
TL_DEFF TL_V2 tl_get_dim_Rectangle2(TL_Rectangle2 rect);
TL_DEFF TL_Rectangle2 tl_min_max_Rectangle2(TL_V2 min, TL_V2 max);
TL_DEFF TL_Rectangle2 tl_min_dim_Rectangle2(TL_V2 min, TL_V2 dim);
TL_DEFF TL_Rectangle2 tl_center_radius_Rectangle2(TL_V2 center, TL_V2 radius);
TL_DEFF TL_Rectangle2 tl_add_radius_to_Rectangle2(TL_Rectangle2 a, TL_V2 radius);
TL_DEFF TL_Rectangle2 tl_offset_Rectangle2(TL_Rectangle2 a, TL_V2 tl_offset_Rectangle);
TL_DEFF TL_Rectangle2 tl_center_dim_Rectangle2(TL_V2 center, TL_V2 dim);
TL_DEFF TL_Rectangle2 tl_union_Rectangle2(TL_Rectangle2 a, TL_Rectangle2 b);
TL_DEFF TL_Rectangle2 tl_inverted_infinity_Rectangle2();
TL_DEFF TL_V2 tl_get_barycentric_Rectangle2(TL_Rectangle2 a, TL_V2 p);
TL_DEFF TL_B32 tl_is_in_Rectangle2(TL_Rectangle2 rectangle, TL_V2 test);
//
// Integer Rectangle 2
//
typedef struct TL_Rectangle2_S32 TL_Rectangle2_S32;
struct TL_Rectangle2_S32 {
 TL_S32 min_x, min_y;
 TL_S32 max_x, max_y;
};
TL_DEFF TL_Rectangle2_S32 tl_intersection_Rectangle2_S32(TL_Rectangle2_S32 a, TL_Rectangle2_S32 b);
TL_DEFF TL_Rectangle2_S32 tl_union_Rectangle2_S32(TL_Rectangle2_S32 a, TL_Rectangle2_S32 b);
TL_DEFF TL_Rectangle2_S32 tl_inverted_infinity_Rectangle2_S32();
TL_DEFF TL_S32 tl_get_clamped_area_Rectangle2_S32(TL_Rectangle2_S32 a);
TL_DEFF TL_B32 tl_has_area_Rectangle2_S32(TL_Rectangle2_S32 a);

//
//  Rectangle 3
//
typedef struct TL_Rectangle3 TL_Rectangle3;
struct TL_Rectangle3 {
 TL_V3 min;
 TL_V3 max;
};
TL_DEFF TL_V3 tl_get_center_Rectangle3(TL_Rectangle3 rect);
TL_DEFF TL_V3 tl_get_dim_Rectangle3(TL_Rectangle3 rect);
TL_DEFF TL_Rectangle3 tl_min_max_Rectangle3(TL_V3 min, TL_V3 max);
TL_DEFF TL_Rectangle3 tl_min_dim_Rectangle3(TL_V3 min, TL_V3 dim);
TL_DEFF TL_Rectangle3 tl_center_radius_Rectangle3(TL_V3 center, TL_V3 radius);
TL_DEFF TL_Rectangle3 tl_add_radius_to_Rectangle3(TL_Rectangle3 a, TL_V3 radius);
TL_DEFF TL_Rectangle3 tl_offset_Rectangle3(TL_Rectangle3 a, TL_V3 tl_offset_Rectangle);
TL_DEFF TL_Rectangle3 tl_center_dim_Rectangle3(TL_V3 center, TL_V3 dim);
TL_DEFF TL_Rectangle2 tl_to_Rectangle2_xy(TL_Rectangle3 a);
TL_DEFF TL_B32 tl_is_in_Rectangle3(TL_Rectangle3 rectangle, TL_V3 test);
TL_DEFF TL_B32 tl_axis_aligned_intersect_Rectangle3(TL_Rectangle3 a, TL_Rectangle3 b);
TL_DEFF TL_V3 tl_get_barycentric_Rectangle3(TL_Rectangle3 a, TL_V3 p);


////////////////////////////////////////////////////////////////
//
// Color Operations
//
//

TL_DEFF TL_V4 tl_linear1_from_srgb255(TL_V4 color);
TL_DEFF TL_V4 tl_srgb255_from_linear1(TL_V4 color);


////////////////////////////////////////////////////////////////
//
//printf replacment
//

#include <stdarg.h>
#define TL_VariadicArgumentList_Init(List, LastNamedArgument) va_start(List, LastNamedArgument)
#define TL_VariadicArgumentList_Next(List, Type) va_arg(List, Type)
#define TL_VariadicArgumentList_Destroy(List) va_end(List)
TL_StaticAssert(sizeof(char) == sizeof(TL_Byte));
typedef TL_Byte* TL_VariadicArgumentList;

typedef struct TL_C_StringCursor TL_C_StringCursor;
struct TL_C_StringCursor {
 TL_PointerSizeUnsigned size;
 char* at;
};

TL_DEFF TL_B32 tl_c_strings_are_equal(char* a, char* b);
TL_DEFF TL_U32 tl_c_string_length(char* string); 

TL_DEFF TL_S32 tl_S32_from_c_string_and_advance_cursor(char** string);
TL_DEFF TL_S32 tl_S32_from_c_string(char* string);
TL_DEFF void tl_write_char(TL_C_StringCursor* dest, char value);
TL_DEFF TL_U64 tl_read_variadic_argument_U32(TL_U32 length, TL_VariadicArgumentList* arg_list);
TL_DEFF TL_S64 tl_read_variadic_argument_S32(TL_U32 length, TL_VariadicArgumentList* arg_list);
TL_DEFF TL_F64 tl_read_variadic_argument_F32(TL_U32 length, TL_VariadicArgumentList* arg_list);
TL_DEFF void tl_U64_to_ascii(TL_C_StringCursor* dest, TL_U64 value, TL_U8 base, TL_B32 upper_case);
TL_DEFF void tl_F64_to_ascii(TL_C_StringCursor* dest, TL_F64 value, TL_U32 precision);
TL_DEFF TL_PointerSizeUnsigned tl_format_string_list(char* dest_init, TL_PointerSizeUnsigned dest_size, char* format, TL_Byte* arg_list);
TL_DEFF TL_PointerSizeUnsigned tl_format_string(char* dest, TL_PointerSizeUnsigned dest_size, char* format, ...);

//REMOVE!!!!!
#define TL_IMPLEMENTATION
#if defined(TL_IMPLEMENTATION)
////////////////////////////////////////////////////////////////
//
//
//
// Implementation
//
//
//
////////////////////////////////////////////////////////////////

//---------------------------------------------
// Safe Casts

TL_DEFF TL_S16 tl_safe_cast_S32_to_S16(TL_S32 value) {
 TL_Assert(value <= TL_S16_Max);
 TL_Assert(value >= TL_S16_Min);
 TL_S16 result = TL_Cast(TL_S16, value);

 return result;
}
TL_DEFF TL_U16 tl_safe_cast_U32_to_U16(TL_U32 value) {
 TL_Assert(value <= TL_U16_Max);
 TL_U16 result = TL_Cast(TL_U16, value);

 return result;
}
TL_DEFF TL_S32 tl_safe_cast_S64_to_S32(TL_S64 value) {
 TL_Assert(value >= TL_S32_Min && value <= TL_S32_Max);
 TL_S32 result = TL_Cast(TL_S32, value);

 return result;
}
TL_DEFF TL_U32 tl_safe_cast_U64_to_U32(TL_U64 value) {
 TL_Assert(value <= TL_U32_Max);
 TL_U32 result = TL_Cast(TL_U32, value);

 return result;
}
TL_DEFF TL_U32 tl_safe_cast_U64(TL_U64 value) {
 TL_Assert(value <= TL_S32_Max);
 TL_U32 result = TL_Cast(TL_U32, value);

 return result;
}


////////////////////////////////////////////////////////////////
//
// Memory
//
//

//----------------------------------------------
// Address Sanitizer

#if defined(TL_COMPILER_MSVC)
# if defined(__SANITIZE_ADDRESS__)
#  define ASAN_ENABLED 1
#  define NO_ASAN __declspec(no_sanitize_address)
# else
#  define NO_ASAN
# endif
#elif TL_COMPILER_CLANG
# if defined(__has_feature)
#  if __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#   define ASAN_ENABLED 1
#  endif
# endif
# define NO_ASAN __attribute__((no_sanitize("address")))
#else
# define NO_ASAN
#endif

#if defined(ASAN_ENABLED)
 #pragma comment(lib, "clang_rt.asan-x86_64.lib")
 C_LINKAGE void __asan_poison_memory_region(void const volatile *addr, size_t size);
 C_LINKAGE void __asan_unpoison_memory_region(void const volatile *addr, size_t size);
 #define TL_AsanPoisonMemoryRegion(addr, size)   __asan_poison_memory_region((addr), (size))
 #define TL_AsanUnpoisonMemoryRegion(addr, size) __asan_unpoison_memory_region((addr), (size))
#else
 #define TL_AsanPoisonMemoryRegion(addr, size)   ((void)(addr), (void)(size))
 #define TL_AsanUnpoisonMemoryRegion(addr, size) ((void)(addr), (void)(size))
#endif


TL_DEFF void tl_memory_zero_size(void* ptr, TL_Memory_Index size) {
 TL_U8* byte = TL_Cast(TL_U8*, ptr);
 while(size--) {
  *byte++ = 0;
 }
}

TL_DEFF void* tl_memory_copy(TL_Memory_Index size, void* source_init, void* dest_init) {
 TL_U8* source = TL_Cast(TL_U8*, source_init);
 TL_U8* dest = TL_Cast(TL_U8*, dest_init);
 while(size--) {
  *dest++ = *source++;
 }

 return dest_init;
}


////////////////////////////////////////////////////////////////
//
// Custom Allocation
//
//

//
// Arena Allocator
//

TL_DEFF void tl_arena_initialize(TL_Memory_Arena* arena, TL_Memory_Index size, void* base) {
 arena->size = size;
 arena->base = TL_Cast(TL_U8*, base);
 arena->used = 0;
 arena->temp_count = 0;
 
 TL_AsanPoisonMemoryRegion(base, size);
}

TL_DEFF void tl_arena_subdivide(TL_Memory_Arena* sub_arena, TL_Memory_Arena* arena, TL_Memory_Index size, TL_Memory_Index alignment) {
 sub_arena->size = size;
 sub_arena->base = TL_Cast(TL_U8*, TL_ArenaPushSize(arena, size, alignment));
 sub_arena->used = 0;
 sub_arena->temp_count = 0;
}

TL_DEFF void* tl_arena_push_size_(TL_Memory_Arena* arena, TL_Memory_Index size_init, TL_Memory_Index alignment) {
 TL_Memory_Index size = size_init;
 TL_Memory_Index alignment_offset = tl_arena_get_alignment_offset(arena, alignment);
 
 size += alignment_offset;
 TL_Assert((arena->used + size) <= arena->size);

 void* result = TL_Cast(void*, arena->base + arena->used + alignment_offset);
 arena->used += size;
 TL_Assert(size >= size_init);
 TL_AsanUnpoisonMemoryRegion(result, size);

 return result;
}

TL_DEFF TL_Memory_Index tl_arena_get_remaining_size(TL_Memory_Arena* arena, TL_Memory_Index alignment) {
 TL_Memory_Index result = arena->size - (arena->used + tl_arena_get_alignment_offset(arena, alignment));

 return result;
}

TL_DEFF TL_Memory_Index tl_arena_get_alignment_offset(TL_Memory_Arena* arena, TL_Memory_Index alignment) {
 TL_Memory_Index result_pointer = TL_Cast(TL_Memory_Index, arena->base + arena->used);
 TL_Memory_Index alignment_offset = 0;

 //NOTE: Alignment assumed to be a power of 2
 TL_Memory_Index alignment_mask = alignment - 1;
 if(result_pointer & alignment_mask) {
   alignment_offset = alignment - (result_pointer & alignment_mask); 
 }

 return alignment_offset;
}

TL_DEFF void tl_arena_check(TL_Memory_Arena* arena) {
 TL_Assert(arena->temp_count == 0);
}

TL_DEFF char* tl_arena_push_c_string(TL_Memory_Arena* arena, char* source) {
 TL_U32 size = 1;
 for(
  char* at = source;
  *at;
  ++at
 ) {
   ++size;
 }
 char* dest = TL_Cast(char*, tl_arena_push_size_(arena, size, true));
 for TL_EachIndex(char_index, size) {
   dest[char_index] = source[char_index];
 }

 return dest;
}

TL_DEFF TL_Memory_TempMemory tl_begin_temporary_memory(TL_Memory_Arena* arena) {
 TL_Memory_TempMemory result;

 result.arena = arena;
 result.used = arena->used;

 ++arena->temp_count;

 return result;
}

TL_DEFF void tl_end_temporary_memory(TL_Memory_TempMemory temp_mem) {
 TL_Memory_Arena* arena = temp_mem.arena;

 TL_Assert(arena->used >= temp_mem.used);
 arena->used = temp_mem.used;

 TL_Assert(arena->temp_count > 0);
 --arena->temp_count;
}


////////////////////////////////////////////////////////////////
//
// Intrinsics
//
//

#if defined(TL_COMPILER_MSVC)
 TL_DEFF TL_U32 tl_atomic_compare_exchange_U32(volatile TL_U32* value, TL_U32 new_value, TL_U32 expected) {
  TL_U32 result = _InterlockedCompareExchange(TL_Cast(volatile long*, value), new_value, expected);

  return result;
 }

 TL_DEFF TL_U64 tl_atomic_exchange_U64(volatile TL_U64* value, TL_U64 new_value) {
  TL_U64 result = _InterlockedExchange64(TL_Cast(volatile __int64*, value), new_value);

  return result;
 }

 TL_DEFF TL_U32 tl_atomic_add_U32(volatile TL_U32* value, TL_U32 addend) {
  //NOTE: Returns the original value prior to adding
  TL_U32 result = _InterlockedExchangeAdd(TL_Cast(volatile long*, value), addend);

  return result;
 }
 TL_DEFF TL_U64 tl_atomic_add_U64(volatile TL_U64* value, TL_U64 addend) {
  //NOTE: Returns the original value prior to adding
  TL_U64 result = _InterlockedExchangeAdd64(TL_Cast(volatile __int64*, value), addend);

  return result;
 }
#else
 not supported
#endif

TL_DEFF TL_F32 tl_sign_of_F32(TL_F32 value) {
  TL_F32 result = (value >= 0) ? 1.0f : -1.0f; 

  return result;
}

TL_DEFF TL_S32 tl_sign_of_S32(TL_S32 value) {
  TL_S32 result = (value >= 0) ? 1 : -1; 

  return result;
}
    
TL_DEFF TL_S32 tl_round_F32_to_S32(TL_F32 float32) {
  TL_S32 result = TL_Cast(TL_S32, roundf(float32));
  return result;
}

TL_DEFF TL_U32 tl_round_F32_to_U32(TL_F32 float32) {
  TL_U32 result = TL_Cast(TL_U32, roundf(float32));
  return result;
}

TL_DEFF TL_S32 tl_floor_F32_to_S32(TL_F32 float32) {
  TL_S32 result = TL_Cast(TL_S32, floorf(float32));
  return result;
}
TL_DEFF TL_S32 tl_floor_F32_to_U32(TL_F32 float32) {
  TL_S32 result = TL_Cast(TL_U32, floorf(float32));
  return result;
}

TL_DEFF TL_S32 tl_ceil_F32_to_S32(TL_F32 float32) {
  TL_S32 result = TL_Cast(TL_S32, ceilf(float32));
  return result;
}

TL_DEFF TL_S32 tl_truncate_F32_to_S32(TL_F32 float32) {
  TL_S32 result = TL_Cast(TL_S32, float32);
  return result;
}

TL_DEFF TL_F32 tl_sin(TL_F32 angle) {
  TL_F32 result = sinf(angle);
  return result;
}

TL_DEFF TL_F32 tl_cos(TL_F32 angle) {
  TL_F32 result = cosf(angle);
  return result;
}

TL_DEFF TL_F32 tl_atan2(TL_F32 y, TL_F32 x) {
  TL_F32 result = atan2f(y, x);
  return result;
}

TL_DEFF TL_F32 tl_absolute_value(TL_F32 value) {
  TL_F32 result = fabsf(value);
  return result;
}

TL_DEFF TL_F32 tl_square_root(TL_F32 a) {
  TL_F32 result = sqrtf(a);
  return result;
}


//
// Scalar Operations
//

TL_DEFF TL_F32 tl_square(TL_F32 a) {
 TL_F32 result = a*a;

 return result;
}

TL_DEFF TL_F32 tl_lerp(TL_F32 a, TL_F32 t, TL_F32 b) {
 TL_F32 result = (1.0f - t)*a + b*t;

 return result;
}

TL_DEFF TL_F32 tl_clamp_min_max(TL_F32 min, TL_F32 value, TL_F32 max) {
 TL_F32 result = value;

 if(result < min) {
  result = min;
 }
 
 if(result > max) {
  result = max;
 }

 return result;
}

TL_DEFF TL_F32 tl_clamp01(TL_F32 value) {
 TL_F32 result;

 result = tl_clamp_min_max(0.0f, value, 1.0f);
 TL_Assert(result <= 1.0f);

 return result;
}

TL_DEFF TL_F32 tl_map_range_to01(TL_F32 min, TL_F32 t, TL_F32 max) {
 TL_F32 result = 0.0f;

 TL_F32 range = max - min;
 if(range != 0.0f) {
  result = tl_clamp01((t - min) / range);
 }

 return result;
}

TL_DEFF TL_F32 tl_safe_ratio_n(TL_F32 numerator, TL_F32 divisor, TL_F32 n) {
 TL_F32 result = n;

 if(divisor != 0.0f) {
  result = numerator / divisor;
 }

 return result;
}

TL_DEFF TL_F32 tl_safe_ratio_0(TL_F32 numerator, TL_F32 divisor) {
 TL_F32 result = tl_safe_ratio_n(numerator, divisor, 0.0f);

 return result;
}

TL_DEFF TL_F32 tl_safe_ratio_1(TL_F32 numerator, TL_F32 divisor) {
 TL_F32 result = tl_safe_ratio_n(numerator, divisor, 1.0f);

 return result;
}

//
// TL_V2 
//

TL_DEFF TL_V2 tl_v2(TL_F32 x, TL_F32 y) {
 TL_V2 result;

 result.x = x;
 result.y = y;

 return result;
}
TL_DEFF TL_V2 tl_x_V2(TL_F32 x) {
 TL_V2 result;

 result.x = x;
 result.y = x;

 return result;
}
TL_DEFF TL_V2 tl_zero_V2() {
 TL_V2 result;

 result.x = 0.f;
 result.y = 0.f;

 return result;
}

TL_DEFF TL_V2 tl_one_V2() {
 TL_V2 result;

 result.x = 1.f;
 result.y = 1.f;

 return result;
}

TL_DEFF TL_V2 tl_hadamard_V2(TL_V2 a, TL_V2 b) {
 TL_V2 result = {
  a.x*b.x,
  a.y*b.y
 };

 return result;
}

TL_DEFF TL_F32 tl_inner_V2(TL_V2 a, TL_V2 b) {
 TL_F32 result = a.x*b.x + a.y*b.y;

 return result;
}

TL_DEFF TL_F32 tl_length_square_V2(TL_V2 a) {
 TL_F32 result = tl_inner_V2(a, a);

 return result;
}

TL_DEFF TL_F32 tl_length_V2(TL_V2 a) {
 TL_F32 result = tl_square_root(tl_length_square_V2(a));

 return result;
}

TL_DEFF TL_V2 tl_perpendicular_V2(TL_V2 a) {
 TL_V2 result = { -a.y, a.x };

 return result;
}

TL_DEFF TL_V2 tl_clamp01_V2(TL_V2 value) {
 TL_V2 result; 

 result.x = tl_clamp01(value.x);
 result.y = tl_clamp01(value.y);

 return result;
}

TL_DEFF TL_V2 tl_get_unit_circle_vector_V2(TL_F32 angle) {
 TL_V2 result = {tl_cos(angle), tl_sin(angle)};

 return result;
}

TL_DEFF TL_V2 tl_add_V2(TL_V2 a, TL_V2 b) {
 TL_V2 result;
 
 result.x = a.x + b.x;
 result.y = a.y + b.y;

 return result;
}
TL_DEFF TL_V2 tl_subtract_V2(TL_V2 a, TL_V2 b) {
 TL_V2 result;
 
 result.x = a.x - b.x;
 result.y = a.y - b.y;

 return result;
}
TL_DEFF TL_V2 tl_multiply_V2(TL_F32 a, TL_V2 b){
 TL_V2 result;
 
 result.x = a * b.x;
 result.y = a * b.y;

 return result;
}
TL_DEFF TL_V2 tl_invert_V2(TL_V2 a) {
 TL_V2 result;

 result.x = -a.x;
 result.y = -a.y;

 return result;
}

#if defined(__cplusplus)
 TL_DEFF TL_V2 operator*(TL_F32 a, TL_V2 b) {
  TL_V2 result;

  result.x = a*b.x;
  result.y = a*b.y;

  return result;
 }

 TL_DEFF TL_V2 operator*(TL_V2 b, TL_F32 a) {
  TL_V2 result = a*b;

  return result;
 }

 TL_DEFF TL_V2& operator*=(TL_V2& a, TL_F32 b) {
  a = b * a;

  return a;
 }

 TL_DEFF TL_V2 operator-(TL_V2 a) {
  TL_V2 result;

  result.x = -a.x;
  result.y = -a.y;

  return result;
 }

 TL_DEFF TL_V2 operator+(TL_V2 a, TL_V2 b) {
  TL_V2 result;

  result.x = a.x + b.x;
  result.y = a.y + b.y;

  return result;
 }

 TL_DEFF TL_V2& operator+=(TL_V2& a, TL_V2 b) {
  a = a + b;

  return a;
 }

 TL_DEFF TL_V2 operator-(TL_V2 a, TL_V2 b) {
  TL_V2 result;

  result.x = a.x - b.x;
  result.y = a.y - b.y;

  return result;
 }
#endif

//
// TL_V3 
//

TL_DEFF TL_V3 tl_v3(TL_F32 x, TL_F32 y, TL_F32 z) {
 TL_V3 result;

 result.x = x;
 result.y = y;
 result.z = z;

 return result;
}

TL_DEFF TL_V3 tl_x_V3(TL_F32 x) {
 TL_V3 result;

 result.x = x;
 result.y = x;
 result.z = x;

 return result;
}

TL_DEFF TL_V3 tl_zero_V3() {
 TL_V3 result;

 result.x = 0.f;
 result.y = 0.f;
 result.z = 0.f;

 return result;
}

TL_DEFF TL_V3 tl_one_V3() {
 TL_V3 result;

 result.x = 1.f;
 result.y = 1.f;
 result.z = 1.f;

 return result;
}

TL_DEFF TL_V3 tl_hadamard_V3(TL_V3 a, TL_V3 b) {
 TL_V3 result = {
  a.x*b.x,
  a.y*b.y,
  a.z*b.z
 };

 return result;
}

TL_DEFF TL_F32 tl_inner_V3(TL_V3 a, TL_V3 b) {
 TL_F32 result = a.x*b.x + a.y*b.y + a.z*b.z;

 return result;
}

TL_DEFF TL_F32 tl_length_square_V3(TL_V3 a) {
 TL_F32 result = tl_inner_V3(a, a);

 return result;
}

TL_DEFF TL_F32 tl_length_V3(TL_V3 a) {
 TL_F32 result = tl_square_root(tl_length_square_V3(a));

 return result;
}

TL_DEFF TL_V3 tl_normalize(TL_V3 a) {
 TL_V3 result = tl_multiply_V3(1.0f/tl_length_V3(a), a);

 return result;
}

TL_DEFF TL_V3 tl_clamp01_V3(TL_V3 value) 
{
 TL_V3 result; 

 result.x = tl_clamp01(value.x);
 result.y = tl_clamp01(value.y);
 result.z = tl_clamp01(value.z);

 return result;
}

TL_DEFF TL_V3 tl_lerp_V3(TL_V3 a, TL_F32 t, TL_V3 b) 
{
 TL_V3 result = tl_add_V3(
  tl_multiply_V3(1.0f - t, a), 
  tl_multiply_V3(t, b)
 );

 return result;
}

TL_DEFF TL_V3 tl_add_V3(TL_V3 a, TL_V3 b) {
 TL_V3 result;
 
 result.x = a.x + b.x;
 result.y = a.y + b.y;
 result.z = a.z + b.z;

 return result;
}
TL_DEFF TL_V3 tl_subtract_V3(TL_V3 a, TL_V3 b) {
 TL_V3 result;
 
 result.x = a.x - b.x;
 result.y = a.y - b.y;
 result.z = a.z - b.z;

 return result;
}
TL_DEFF TL_V3 tl_multiply_V3(TL_F32 a, TL_V3 b) {
 TL_V3 result;
 
 result.x = a * b.x;
 result.y = a * b.y;
 result.z = a * b.z;

 return result;
}

#if defined(__cplusplus)
 TL_DEFF TL_V3 operator*(TL_F32 a, TL_V3 b) {
  TL_V3 result;

  result.x = a*b.x;
  result.y = a*b.y;
  result.z = a*b.z;

  return result;
 }

 TL_DEFF TL_V3 operator*(TL_V3 b, TL_F32 a) {
  TL_V3 result = a*b;

  return result;
 }

 TL_DEFF TL_V3& operator*=(TL_V3& a, TL_F32 b) {
  a = b * a;

  return a;
 }

 TL_DEFF TL_V3 operator-(TL_V3 a) {
  TL_V3 result;

  result.x = -a.x;
  result.y = -a.y;
  result.z = -a.z;

  return result;
 }

 TL_DEFF TL_V3 operator+(TL_V3 a, TL_V3 b) {
  TL_V3 result;

  result.x = a.x + b.x;
  result.y = a.y + b.y;
  result.z = a.z + b.z;

  return result;
 }

 TL_DEFF TL_V3& operator+=(TL_V3& a, TL_V3 b) {
  a = a + b;

  return a;
 }

 TL_DEFF TL_V3 operator-(TL_V3 a, TL_V3 b) {
  TL_V3 result;

  result.x = a.x - b.x;
  result.y = a.y - b.y;
  result.z = a.z - b.z;

  return result;
 }

 TL_DEFF TL_V3& operator-=(TL_V3& a, TL_V3 b) {
  a = a - b;

  return a;
 }
#endif
//
// TL_V4
//

TL_DEFF TL_V4 tl_v4(TL_F32 x, TL_F32 y, TL_F32 z, TL_F32 w) {
 TL_V4 result;

 result.x = x;
 result.y = y;
 result.z = z;
 result.w = w;

 return result;
}

TL_DEFF TL_V4 tl_x_V4(TL_F32 x) {
 TL_V4 result;

 result.x = x;
 result.y = x;
 result.z = x;
 result.w = x;

 return result;
}

TL_DEFF TL_V4 tl_zero_V4() {
 TL_V4 result;

 result.x = 0.f;
 result.y = 0.f;
 result.z = 0.f;
 result.w = 0.f;

 return result;
}

TL_DEFF TL_V4 tl_one_V4() {
 TL_V4 result;

 result.x = 1.f;
 result.y = 1.f;
 result.z = 1.f;
 result.w = 1.f;

 return result;
}

TL_DEFF TL_V4 tl_hadamard_V4(TL_V4 a, TL_V4 b) {
 TL_V4 result = {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w};

 return result;
}

TL_DEFF TL_F32 tl_inner_V4(TL_V4 a, TL_V4 b) {
 TL_F32 result = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;

 return result;
}

TL_DEFF TL_F32 tl_length_square_V4(TL_V4 a) {
 TL_F32 result = tl_inner_V4(a, a);

 return result;
}

TL_DEFF TL_F32 tl_length_V4(TL_V4 a) {
 TL_F32 result = tl_square_root(tl_length_square_V4(a));

 return result;
}

TL_DEFF TL_V4 tl_clamp01_V4(TL_V4 value) {
 TL_V4 result; 

 result.x = tl_clamp01(value.x);
 result.y = tl_clamp01(value.y);
 result.z = tl_clamp01(value.z);
 result.w = tl_clamp01(value.w);

 return result;
}

TL_DEFF TL_V4 tl_lerp_V4(TL_V4 a, TL_F32 t, TL_V4 b) 
{
 TL_V4 result = tl_add_V4(
  tl_multiply_V4(1.0f - t, a), 
  tl_multiply_V4(t, b)
 );

 return result;
}

TL_DEFF TL_V4 tl_add_V4(TL_V4 a, TL_V4 b) {
 TL_V4 result;
 
 result.x = a.x + b.x;
 result.y = a.y + b.y;
 result.z = a.z + b.z;
 result.w = a.w + b.w;

 return result;
}
TL_DEFF TL_V4 tl_subtract_V4(TL_V4 a, TL_V4 b) {
 TL_V4 result;
 
 result.x = a.x - b.x;
 result.y = a.y - b.y;
 result.z = a.z - b.z;
 result.w = a.w - b.w;

 return result;
}
TL_DEFF TL_V4 tl_multiply_V4(TL_F32 a, TL_V4 b) {
 TL_V4 result;
 
 result.x = a * b.x;
 result.y = a * b.y;
 result.z = a * b.z;
 result.w = a * b.w;

 return result;
}
#if defined(__cplusplus)
TL_DEFF TL_V4 operator*(TL_F32 a, TL_V4 b) 
{
 TL_V4 result;

 result.x = a*b.x;
 result.y = a*b.y;
 result.z = a*b.z;
 result.w = a*b.w;

 return result;
}

TL_DEFF TL_V4 operator*(TL_V4 b, TL_F32 a) 
{
 TL_V4 result = a*b;

 return result;
}

TL_DEFF TL_V4& operator*=(TL_V4& a, TL_F32 b) 
{
 a = b * a;

 return a;
}

TL_DEFF TL_V4 operator-(TL_V4 a) 
{
 TL_V4 result;

 result.x = -a.x;
 result.y = -a.y;
 result.z = -a.z;
 result.w = -a.w;

 return result;
}

TL_DEFF TL_V4 operator+(TL_V4 a, TL_V4 b) 
{
 TL_V4 result;

 result.x = a.x + b.x;
 result.y = a.y + b.y;
 result.z = a.z + b.z;
 result.w = a.w + b.w;

 return result;
}

TL_DEFF TL_V4& operator+=(TL_V4& a, TL_V4 b) 
{
 a = a + b;

 return a;
}

TL_DEFF TL_V4 operator-(TL_V4 a, TL_V4 b) 
{
 TL_V4 result;

 result.x = a.x - b.x;
 result.y = a.y - b.y;
 result.z = a.z - b.z;
 result.w = a.w - b.w;

 return result;
}

TL_DEFF TL_V4& operator-=(TL_V4& a, TL_V4 b) 
{
 a = a - b;

 return a;
}
#endif

//
//  Rectangle 2
//

TL_DEFF TL_V2 tl_get_min_corner_Rectangle2(TL_Rectangle2 rect) {
 TL_V2 result = rect.min;

 return result;
}

TL_DEFF TL_V2 tl_get_max_corner_Rectangle2(TL_Rectangle2 rect) {
 TL_V2 result = rect.max;

 return result;
}

TL_DEFF TL_V2 tl_get_center_Rectangle2(TL_Rectangle2 rect) {
 TL_V2 result = tl_multiply_V2(0.5f, tl_add_V2(rect.min, rect.max));

 return result;
}

TL_DEFF TL_V2 tl_get_dim_Rectangle2(TL_Rectangle2 rect) {
 TL_V2 result = tl_subtract_V2(rect.max, rect.min);

 return result;
}

TL_DEFF TL_Rectangle2 tl_min_max_Rectangle2(TL_V2 min, TL_V2 max) {
 TL_Rectangle2 result;

 result.min = min;
 result.max = max;

 return result;
}

TL_DEFF TL_Rectangle2 tl_min_dim_Rectangle2(TL_V2 min, TL_V2 dim) {
 TL_Rectangle2 result;

 result.min = min;
 result.max = tl_add_V2(min, dim);

 return result;
}

TL_DEFF TL_Rectangle2 tl_center_radius_Rectangle2(TL_V2 center, TL_V2 radius) {
 TL_Rectangle2 result;

 result.min = tl_subtract_V2(center, radius);
 result.max = tl_add_V2(center, radius);

 return result;
}

TL_DEFF TL_Rectangle2 tl_add_radius_to_Rectangle2(TL_Rectangle2 a, TL_V2 radius) {
 TL_Rectangle2 result;

 result.min = tl_subtract_V2(a.min, radius);
 result.max = tl_add_V2(a.max, radius);

 return result;
}

TL_DEFF TL_Rectangle2 tl_offset_Rectangle2(TL_Rectangle2 a, TL_V2 tl_offset_Rectangle) {
 TL_Rectangle2 result;

 result.min = tl_add_V2(a.min, tl_offset_Rectangle);
 result.max = tl_add_V2(a.max, tl_offset_Rectangle);

 return result;
}

TL_DEFF TL_Rectangle2 tl_center_dim_Rectangle2(TL_V2 center, TL_V2 dim) {
 TL_Rectangle2 result = tl_center_radius_Rectangle2(center, tl_multiply_V2(0.5f, dim));

 return result;
}

TL_DEFF TL_B32 tl_is_in_Rectangle2(TL_Rectangle2 rectangle, TL_V2 test) {
 TL_B32 result = (
     (test.x >= rectangle.min.x)
  && (test.y >= rectangle.min.y)
  && (test.x < rectangle.max.x)
  && (test.y < rectangle.max.y)
 );

 return result;
}

TL_DEFF TL_V2 tl_get_barycentric_Rectangle2(TL_Rectangle2 a, TL_V2 p) {
 TL_V2 result;

 result.x = tl_safe_ratio_0(p.x-a.min.x, a.max.x - a.min.x);
 result.y = tl_safe_ratio_0(p.y-a.min.y, a.max.y - a.min.y);
 
 return result;
}


//
//  Rectangle 3
//

TL_DEFF TL_V3 tl_get_min_corner_Rectangle3(TL_Rectangle3 rect) {
 TL_V3 result = rect.min;

 return result;
}

TL_DEFF TL_V3 tl_get_max_corner_Rectangle3(TL_Rectangle3 rect) {
 TL_V3 result = rect.max;

 return result;
}

TL_DEFF TL_V3 tl_get_center_Rectangle3(TL_Rectangle3 rect) {
 TL_V3 result = tl_multiply_V3(0.5f, tl_add_V3(rect.min, rect.max));

 return result;
}
TL_DEFF TL_V3 tl_get_dim_Rectangle3(TL_Rectangle3 rect) {
 TL_V3 result = tl_subtract_V3(rect.max, rect.min);

 return result;
}
TL_DEFF TL_Rectangle3 tl_offset_Rectangle3(TL_Rectangle3 a, TL_V3 tl_offset_Rectangle) {
 TL_Rectangle3 result;

 result.min = tl_add_V3(a.min, tl_offset_Rectangle);
 result.max = tl_add_V3(a.max, tl_offset_Rectangle);

 return result;
}

TL_DEFF TL_Rectangle3 tl_min_max_Rectangle3(TL_V3 min, TL_V3 max) {
 TL_Rectangle3 result;

 result.min = min;
 result.max = max;

 return result;
}

TL_DEFF TL_Rectangle3 tl_min_dim_Rectangle3(TL_V3 min, TL_V3 dim) {
 TL_Rectangle3 result;

 result.min = min;
 result.max = tl_add_V3(min, dim);

 return result;
}

TL_DEFF TL_Rectangle3 tl_center_radius_Rectangle3(TL_V3 center, TL_V3 radius) {
 TL_Rectangle3 result;

 result.min = tl_subtract_V3(center, radius);
 result.max = tl_add_V3(center, radius);

 return result;
}

TL_DEFF TL_Rectangle3 tl_add_radius_to_Rectangle3(TL_Rectangle3 a, TL_V3 radius) {
 TL_Rectangle3 result;

 result.min = tl_subtract_V3(a.min, radius);
 result.max = tl_add_V3(a.max, radius);

 return result;
}

TL_DEFF TL_Rectangle3 tl_center_dim_Rectangle3(TL_V3 center, TL_V3 dim) {
 TL_Rectangle3 result = tl_center_radius_Rectangle3(center, tl_multiply_V3(0.5f, dim));

 return result;
}

TL_DEFF TL_B32 tl_is_in_Rectangle3(TL_Rectangle3 rectangle, TL_V3 test) {
 TL_B32 result = (
     (test.x >= rectangle.min.x) 
  && (test.y >= rectangle.min.y) 
  && (test.z >= rectangle.min.z) 
  && (test.x < rectangle.max.x) 
  && (test.y < rectangle.max.y) 
  && (test.z < rectangle.max.z)
 );

 return result;
}

TL_DEFF TL_B32 tl_axis_aligned_intersect_Rectangle3(TL_Rectangle3 a, TL_Rectangle3 b) {
 TL_B32 result = !(
     (b.max.x <= a.min.x)
  || (b.min.x >= a.max.x)
  || (b.max.y <= a.min.y)
  || (b.min.y >= a.max.y)
  || (b.max.z <= a.min.z)
  || (b.min.z >= a.max.z)
 );

 TL_B32 x = (b.max.x < a.min.x);
 TL_B32 x1 = (b.min.x > a.max.x);
 TL_B32 y = (b.max.y < a.min.y);
 TL_B32 y1 = (b.min.y > a.max.y);
 TL_B32 z = (b.max.z < a.min.z);
 TL_B32 z1 = (b.min.z > a.max.z);
 
 return result;
}
TL_DEFF TL_Rectangle2 tl_to_Rectangle2_xy(TL_Rectangle3 a) {
 TL_Rectangle2 result;

 result.min = a.min.xy;
 result.max = a.max.xy;

 return result;
}


// NOTE: Barycentric means relative to a shape in an already exsiting coordinate system 
// and it is normalized meaning, min is (0,0,0...) and max is (1,1,1..)
// https://youtu.be/Hm_CTQwV13U?t=1736
TL_DEFF TL_V3 tl_get_barycentric_Rectangle(TL_Rectangle3 a, TL_V3 p) {
 TL_V3 result;

 result.x = tl_safe_ratio_0(p.x-a.min.x, a.max.x - a.min.x);
 result.y = tl_safe_ratio_0(p.y-a.min.y, a.max.y - a.min.y);
 result.z = tl_safe_ratio_0(p.z-a.min.z, a.max.z - a.min.z);
 
 return result;
}


//
// Integer Rectangle 2
//

TL_DEFF TL_Rectangle2_S32 tl_inverted_infinity_Rectangle2_S32() {
 TL_Rectangle2_S32 result;

 result.min_x = result.min_y = TL_S32_Max;
 result.max_x = result.max_y = -TL_S32_Max;

 return result;
}

TL_DEFF TL_Rectangle2_S32 tl_intersection_Rectangle2_S32(TL_Rectangle2_S32 a, TL_Rectangle2_S32 b) {
 TL_Rectangle2_S32 result;

 result.min_x = (a.min_x < b.min_x) ? b.min_x : a.min_x;
 result.min_y = (a.min_y < b.min_y) ? b.min_y : a.min_y;
 result.max_x = (a.max_x > b.max_x) ? b.max_x : a.max_x;
 result.max_y = (a.max_y > b.max_y) ? b.max_y : a.max_y;

 return result;
}

TL_DEFF TL_Rectangle2 tl_union_Rectangle2(TL_Rectangle2 a, TL_Rectangle2 b) {
 TL_Rectangle2 result;

 result.min.x = (a.min.x < b.min.x) ? a.min.x : b.min.x;
 result.min.y = (a.min.y < b.min.y) ? a.min.y : b.min.y;
 result.max.x = (a.max.x > b.max.x) ? a.max.x : b.max.x;
 result.max.y = (a.max.y > b.max.y) ? a.max.y : b.max.y;

 return result;
}

TL_DEFF TL_Rectangle2_S32 tl_union_Rectangle2_S32(TL_Rectangle2_S32 a, TL_Rectangle2_S32 b) {
 TL_Rectangle2_S32 result;

 result.min_x = (a.min_x < b.min_x) ? a.min_x : b.min_x;
 result.min_y = (a.min_y < b.min_y) ? a.min_y : b.min_y;
 result.max_x = (a.max_x > b.max_x) ? a.max_x : b.max_x;
 result.max_y = (a.max_y > b.max_y) ? a.max_y : b.max_y;

 return result;
}

TL_DEFF TL_S32 tl_get_clamped_area_Rectangle2(TL_Rectangle2_S32 a) {
 TL_S32 width = (a.max_x - a.min_x);
 TL_S32 height = (a.max_y - a.min_y);
 TL_S32 result = 0;

 if(width > 0 && height > 0) {
  result = width * height;
 }

 return result;
}

TL_DEFF TL_B32 tl_has_area_Rectangle2_S32(TL_Rectangle2_S32 a) {
 TL_B32 result = ((a.min_x < a.max_x) && (a.min_y < a.max_y));
 return result;
}

TL_DEFF TL_Rectangle2 tl_inverted_infinity_Rectangle2() {
 TL_Rectangle2 result;

 result.min.x = result.min.y = TL_F32_Max;
 result.max.x = result.max.y = -TL_F32_Max;

 return result;
}

TL_DEFF TL_S32 tl_get_clamped_area_Rectangle2_S32(TL_Rectangle2_S32 a) {
 TL_S32 width = (a.max_x - a.min_x);
 TL_S32 height = (a.max_y - a.min_y);
 TL_S32 result = 0;

 if(width > 0 && height > 0) {
  result = width * height;
 }

 return result;
}

//
// Color
//
TL_DEFF TL_V4 tl_linear1_from_srgb255(TL_V4 color) {
 TL_V4 result;

 TL_F32 Inv255 = 1.0f / 255.0f;

 result.r = tl_square(Inv255*color.r);
 result.g = tl_square(Inv255*color.g);
 result.b = tl_square(Inv255*color.b);
 result.a = Inv255*color.a;

 return result;
}

TL_DEFF TL_V4 tl_srgb255_from_linear1(TL_V4 color) {
 TL_V4 result;

 TL_F32 One255 = 255.0f;

 result.r = One255*tl_square_root(color.r);
 result.g = One255*tl_square_root(color.g);
 result.b = One255*tl_square_root(color.b);
 result.a = One255*color.a;

 return result;
}
TL_DEFF TL_BitScanResult tl_find_least_significant_set_bit(TL_U32 value) {
  TL_BitScanResult result = TL_ZeroStruct;
#if defined(TL_COMPILER_MSVC)
  result.found = _BitScanForward(TL_Cast(unsigned long*, TL_AddressOf(result.index)), value);
#else
  for TL_EachIndex(test, 32) {
    if (value & (1 << test)) {
      result.index = test;
      result.found = true;
      break;
    }
  }
#endif
  return result;
}

TL_DEFF TL_U32 tl_rotate_left(TL_U32 value, TL_S32 amount) {
#if defined(TL_COMPILER_MSVC)
    TL_U32 result = _rotl(value, amount);
#else
    amount &= 31;
    TL_U32 result = (value << amount) | (value >> (32 - amount));
#endif
    return result;
}

TL_DEFF TL_U32 tl_rotate_right(TL_U32 value, TL_S32 amount) {
#if defined(TL_COMPILER_MSVC)
    TL_U32 result = _rotr(value, amount);
#else
    amount &= 31;
    TL_U32 result = (value << amount) | (value >> (32 - amount));
#endif
    return result;
}

////////////////////////////////////////////////////////////////
//
// Strings
//

//
// C-Strings
//

TL_DEFF TL_B32 tl_c_strings_are_equal(char* a, char* b) {
 while(*a && *b && (*a == *b)) {
  ++a;
  ++b;
 }
 TL_B32 result = *a == *b;

 return result;
}

TL_DEFF TL_U32 tl_c_string_length(char* string) 
{ //NOTE: does not include \0
 TL_U32 count = 0;

 while(*string++) {
  ++count;
 }

 return count;
}

//
//printf replacement
//
TL_DEFF TL_S32 tl_S32_from_c_string_and_advance_cursor(char** string) {
 TL_S32 result = 0;

 char* at = *string;
 while(('0' <= *at) && (*at <= '9')) {
  result *= 10;
  result += (*at - '0');
  ++at;
 }

 *string = at;
 
 return result;
}
TL_DEFF TL_S32 tl_S32_from_c_string(char* string) {
 TL_S32 result = tl_S32_from_c_string_and_advance_cursor(&string);

 return result;
}

TL_DEFF void tl_write_char(TL_C_StringCursor* dest, char value) {
 if(dest->size)
 {
  --dest->size;
  *dest->at++ = value;
 }
}

TL_DEFF TL_U64 tl_read_variadic_argument_U32(TL_U32 length, TL_VariadicArgumentList* arg_list) {
 TL_Assert(length <= 8);
 TL_U64 result = 0;

 switch(length) {
  TL_InvalidDefaultCase;
  // 1 & 2 get promoted to an int
  case 1:
  case 2:
  case 4: {
   result = TL_VariadicArgumentList_Next(*arg_list, TL_U32);
  }break;
  case 8: {
   result = TL_VariadicArgumentList_Next(*arg_list, TL_U64);
  }break;
 }

 return result;
}
TL_DEFF TL_S64 tl_read_variadic_argument_S32(TL_U32 length, TL_VariadicArgumentList* arg_list) {
 TL_U64 temp = tl_read_variadic_argument_U32(length, arg_list);

 TL_S64 result = 0;
 result = *TL_Cast(TL_S64*, &temp);

 return result;
}
TL_DEFF TL_F64 tl_read_variadic_argument_F32(TL_U32 length, TL_VariadicArgumentList* arg_list) {
 TL_F64 result = 0;

 switch(length) {
  TL_InvalidDefaultCase;
  case 4: {
   result = TL_VariadicArgumentList_Next(*arg_list, TL_F32);
  }break;
  case 8: {
   result = TL_VariadicArgumentList_Next(*arg_list, TL_F64);
  }break;
 }

 return result;
}
TL_DEFF void tl_U64_to_ascii(TL_C_StringCursor* dest, TL_U64 value, TL_U8 base, TL_B32 upper_case) {
 TL_Assert(base > 1);
 TL_Assert(base <= 16);
 char lookup_table_upper[] = {"0123456789ABCDEF"};
 char lookup_table_lower[] = {"0123456789abcdef"};
 TL_StaticAssert(TL_ArrayCount(lookup_table_upper) == TL_ArrayCount(lookup_table_lower));

 TL_U32 table_size = TL_ArrayCount(lookup_table_upper);
 char* lookup_table = upper_case ? lookup_table_upper : lookup_table_lower;

 //
 //extract number in reverse
 //
 char* init_cursor = dest->at;
 do {
  TL_U64 digit_index = value % base;
  char digit = lookup_table[digit_index];
  tl_write_char(dest, digit);
  value /= base;
 } while(value != 0);

 //
 //reverse the number
 //
 TL_S64 char_count = dest->at - init_cursor;
 for (
  TL_S64 swap_index = 0;
  swap_index < char_count/2;
  swap_index += 1
 ) {
  TL_Swap(char, init_cursor[swap_index], init_cursor[(char_count - 1) - swap_index]);
 }
}
TL_DEFF void tl_F64_to_ascii(TL_C_StringCursor* dest, TL_F64 value, TL_U32 precision) {
 //
 //int part
 //
 if(value < 0) {
  tl_write_char(dest, '-');
  value = -value;
 }

 TL_U64 int_part = TL_Cast(TL_U64, value);
 value -= TL_Cast(TL_F64, int_part);
 tl_U64_to_ascii(dest, int_part, 10, true);

 tl_write_char(dest, '.');

 //
 //fractional part
 //
 char lookup_table_decimal[] = {"0123456789"};
 for (
  TL_U64 precision_index = 0;
  precision_index < precision;
  ++precision_index
 ) {
  //TODO: this prints with error fix!
  value *= 10.f;
  TL_U32 digit = TL_Cast(TL_U32, value);
  value -= TL_Cast(TL_F32, digit);
  tl_write_char(dest, lookup_table_decimal[digit]);
 }

}

TL_DEFF TL_PointerSizeUnsigned tl_format_string_list(char* dest_init, TL_PointerSizeUnsigned dest_size, char* format, TL_Byte* arg_list) {
 TL_C_StringCursor dest = {dest_size, dest_init};
 if(dest_size) {
  char* at = format;
  while(*at) {
   if(*at == '%') {
    ++at;

    TL_B32 force_sign = false;
    TL_B32 pad_with_zeros = false;
    TL_B32 left_justify = false;
    TL_B32 positive_sign_is_blank = false;
    TL_B32 annotate_if_not_zero = false;

    //
    // Handle the flags
    //

    TL_B32 parsing = true;
    while(parsing) {
     switch(*at) {
      case '-': {left_justify = true;}break;
      case '+': {force_sign = true;}break;
      case ' ': {positive_sign_is_blank = true;}break;
      case '#': {annotate_if_not_zero = true;}break;
      case '0': {pad_with_zeros = true;}break;
      default: {parsing = false;}break;
     }
     if(parsing) {
      ++at;
     }
    }

    //
    // Handle width
    //
    TL_S32 width = 0;
    if(*at == '*') {
     ++at;
     width = TL_VariadicArgumentList_Next(arg_list, TL_S32);
    } else if (('0' <= *at) && (*at <= '9')) {
     TL_Assert(*at != '0');
     width = tl_S32_from_c_string_and_advance_cursor(&at);
    }

    //
    // Handle precision
    //
    TL_B32 precsison_specified = false;
    TL_S32 precsison = 0; //NOTE: default for printf is 6
    if(*at == '.') {
     ++at;
     if(*at == '*') {
      ++at;
      precsison = TL_VariadicArgumentList_Next(arg_list, TL_S32);
      precsison_specified = true;
     } else if (('0' <= *at) && (*at <= '9')) {
      precsison = tl_S32_from_c_string_and_advance_cursor(&at);
      precsison_specified = true;
     } else {
      TL_Assert(!"Malformed printf precision!");
     }
    }
    if(!precsison_specified) {
     precsison = 2; //NOTE: default for printf is 6
    }

    //
    // Handle length
    //
    TL_U32 integer_length = 4;
    TL_U32 float_length = 8;
    if((at[0] == 'h') && (at[1] == 'h')) {
     at += 2;
    } else if((at[0] == 'l') && (at[1] == 'l')) {
     at += 2;
     integer_length = 8;
    } else {
     switch(*at) {
      case 'h': { ++at; }break;
      case 'l': { ++at; }break;
      case 'j': { ++at; }break;
      case 'z': { ++at; }break;
      case 't': { ++at; }break;
      case 'L': { ++at; }break;
     }
    }

    char temp_buffer [64] = {0};
    char* temp = temp_buffer;
    TL_C_StringCursor buffer = {TL_ArrayCount(temp_buffer), temp};

    char* temp_prefix = "";
    TL_B32 is_float = false;
    switch(*at) {
     case 'd': 
     case 'i': {
      TL_S64 value;
      if( (at[0] == 'i')
       && (at[1] == '6')
       && (at[2] == '4')
      ) {
       at += 2;
       value = tl_read_variadic_argument_S32(sizeof(TL_S64), &arg_list);
      } else {
       value = tl_read_variadic_argument_S32(sizeof(TL_S32), &arg_list);
      }

      TL_B32 was_negative = value < 0;
      if(was_negative) {
       value = -value;
      }
      tl_U64_to_ascii(&buffer, value, 10, true);

      if(was_negative) {
       temp_prefix = "-";
      } else if(force_sign) {
       TL_Assert(!positive_sign_is_blank);
       temp_prefix = "+";
      } else if(positive_sign_is_blank) {
       temp_prefix = " ";
      }
     }break;

     case 'u': {
      TL_U64 value = tl_read_variadic_argument_U32(integer_length, &arg_list);
      tl_U64_to_ascii(&buffer, value, 10, true);
     }break;

     case 'o': {
      TL_U64 value = tl_read_variadic_argument_U32(integer_length, &arg_list);
      tl_U64_to_ascii(&buffer, value, 8, true);
      if(annotate_if_not_zero && (value != 0)) {
       temp_prefix = "O";
      }
     }break;

     case 'x': {
      TL_U64 value = tl_read_variadic_argument_U32(integer_length, &arg_list);
      tl_U64_to_ascii(&buffer, value, 16, false);
      if(annotate_if_not_zero && (value != 0)) {
       temp_prefix = "0x";
      }
     }break;

     case 'X': {
      TL_U64 value = tl_read_variadic_argument_U32(integer_length, &arg_list);
      tl_U64_to_ascii(&buffer, value, 16, true);
      if(annotate_if_not_zero && (value != 0))
      {
       temp_prefix = "0X";
      }
     }break;
     case 'F': 
     case 'e': 
     case 'E': 
     case 'g': 
     case 'G': 
     case 'a': 
     case 'A': 
      TL_NotImplemented;
      //fallthrough
     case 'f': {
      TL_F64 value = tl_read_variadic_argument_F32(float_length, &arg_list);
      is_float = true;
      tl_F64_to_ascii(&buffer, value, precsison);
     }break;
     case 'c': {
      int character = TL_VariadicArgumentList_Next(arg_list, int);
      tl_write_char(&buffer, TL_Cast(char, character));
     }break;
     case 's': {
      char* string = TL_VariadicArgumentList_Next(arg_list, char*);

      temp = string;
      if(precsison_specified) {
       buffer.size = 0;
       for(
        char* scan = string;
        *scan;
        ++scan
       ) {
        ++buffer.size;
       }
      } else {
       buffer.size = tl_c_string_length(string);
      }
      buffer.at = string + buffer.size;
     }break;
     case 'p': {
      void* value = TL_VariadicArgumentList_Next(arg_list, void*);
      tl_U64_to_ascii(&buffer, *TL_Cast(TL_PointerSizeUnsigned*, value), 16, true);
     }break;
     case 'n': {
      TL_StaticAssert(sizeof(TL_U32) == sizeof(int));
      TL_U32* tab_dest = TL_VariadicArgumentList_Next(arg_list, TL_U32*);
      *tab_dest = TL_Cast(TL_U32, dest.at - dest_init);
     }break;
     case '%': {
      tl_write_char(&dest, '%');
     }break;
     default: {
      TL_Assert(!"Unrecognized printf specifier!");
     }
    }

    if(buffer.at - temp) {
     TL_PointerSizeSigned remaining_precision = precsison;
     if(is_float || !precsison_specified) {
      remaining_precision = buffer.at - temp;
     }

     TL_PointerSizeSigned prefix_length = TL_Cast(TL_U32, tl_c_string_length(temp_prefix));
     TL_PointerSizeSigned remaining_width = width;
     TL_PointerSizeSigned computed_width = remaining_precision + prefix_length;
     if(remaining_width < computed_width) {
      remaining_width = computed_width;
     }

     if(pad_with_zeros) {
      TL_Assert(!left_justify);
      left_justify = false;
     }

     if(!left_justify) {
      while(remaining_width > (remaining_precision + prefix_length)) {
       tl_write_char(&dest, pad_with_zeros ? '0' : ' ');
       --remaining_width;
      }
     }

     for(
      char* prefix = temp_prefix;
      *prefix;
      ++prefix
     ) {
      tl_write_char(&dest, *prefix);
      --remaining_width;
     }

     if(remaining_precision > remaining_width) {
      remaining_precision = remaining_width;
     }

     while(remaining_precision > (buffer.at - temp)) {
      tl_write_char(&dest, '0');
      --remaining_precision;
      --remaining_width;
     }

     while(remaining_precision && (buffer.at != temp)) {
      tl_write_char(&dest, *temp++);
      --remaining_precision;
      --remaining_width;
     }

     if(left_justify) {
      while(remaining_width) {
       tl_write_char(&dest, pad_with_zeros ? '0' : ' ');
       --remaining_width;
      }
     }
    }
    if(*at) {
     ++at;
    }
   } else {
    tl_write_char(&dest, *at++);
   }
  }

  if(dest.size) {
   dest.at[0] = 0;
  } else {
   dest.at[-1] = 0;
  }
 }
 TL_PointerSizeUnsigned result = dest.at - dest_init;

 return result;
}

TL_DEFF TL_PointerSizeUnsigned tl_format_string(char* dest, TL_PointerSizeUnsigned dest_size, char* format, ...) {
 TL_Byte* arg_list;
 TL_VariadicArgumentList_Init(arg_list, format);
 TL_Memory_Index result = tl_format_string_list(dest, dest_size, format, arg_list);
 TL_VariadicArgumentList_Destroy(arg_list);

 return result;
}
////////////////////////////////////////////////////////////////////////////////////////


#endif // TL_IMPLEMENTATION
#if !defined(TL_ADD_PREFIX)

 // Types
 #define Byte       TL_Byte
 #define U8         TL_U8
 #define U16        TL_U16
 #define U32        TL_U32
 #define U64        TL_U64
 #define S8         TL_S8
 #define S16        TL_S16
 #define S32        TL_S32
 #define S64        TL_S64
 #define F32        TL_F32
 #define F64        TL_F64
 #define B8         TL_B8
 #define B16        TL_B16
 #define B32        TL_B32
 #define B64        TL_B64
 #define IntPtr     TL_IntPtr
 #define UintPtr    TL_UintPtr
 #define PointerSizeSigned   TL_PointerSizeSigned
 #define PointerSizeUnsigned TL_PointerSizeUnsigned
 #define Memory_Index        TL_Memory_Index

 // Min Max
 #define U8_Min  TL_U8_Min
 #define U8_Max  TL_U8_Max
 #define S8_Min  TL_S8_Min
 #define S8_Max  TL_S8_Max
 
 #define U16_Min TL_U16_Min
 #define U16_Max TL_U16_Max
 #define S16_Min TL_S16_Min
 #define S16_Max TL_S16_Max
 
 #define U32_Min TL_U32_Min
 #define U32_Max TL_U32_Max
 #define S32_Min TL_S32_Min
 #define S32_Max TL_S32_Max
 
 #define U64_Min TL_U64_Min
 #define U64_Max TL_U64_Max
 #define S64_Min TL_S64_Min
 #define S64_Max TL_S64_Max
 
 #define F32_Min TL_F32_Min
 #define F32_Max TL_F32_Max
 
 #define F64_Min TL_F64_Min
 #define F64_Max TL_F64_Max

 #define Pi32 TL_Pi32
 #define Tau32 TL_Tau32
 // Member Offsets

 #define Member              TL_Member
 #define OffsetOf            TL_OffsetOf
 #define MemberFromOffset    TL_MemberFromOffset
 #define CastFromMember      TL_CastFromMember
 // Macros
 #define SetupDefer          TL_SetupDefer
 #define OnSuccessfulSetup_StatementAndDefer TL_OnSuccessfulSetup_StatementAndDefer
 #define SetupDeferGuardedStatement TL_SetupDeferGuardedStatement
 #define MakeStatement       TL_MakeStatement
 #define Stringify           TL_Stringify
 #define GlueMacro           TL_Glue
 #define Assert              TL_Assert
 #define InvalidPath         TL_InvalidPath
 #define NotImplemented      TL_NotImplemented
 #define InvalidDefaultCase  TL_InvalidDefaultCase
 #define StaticAssertMsg     TL_StaticAssertMsg
 #define StaticAssert        TL_StaticAssert
 #define NoOp                TL_NoOp
 #define Internal            TL_Internal
 #define LocalPersist        TL_LocalPersist
 #define Global              TL_Global
 #define ZeroStruct          TL_ZeroStruct
 #define Cast                TL_Cast
 #define DerefPtr            TL_DerefPtr
 #define AddressOf           TL_AddressOf
 #define Swap                TL_Swap
 #define ArrayCount          TL_ArrayCount
 #define Bit                 TL_Bit
 #define Pow2                TL_Pow2
 #define AlignPow2           TL_AlignPow2
 #define Align4              TL_Align4
 #define Align8              TL_Align8
 #define Align16             TL_Align16
 #define CeilIntegerDiv      TL_CeilIntegerDiv
 #define IntFromPtr          TL_IntFromPtr
 #define PtrFromInt          TL_PtrFromInt
 
 // Loops
 #define EachIndex           TL_EachIndex
 #define EachElement         TL_EachElement
 #define EachEnumVal         TL_EachEnumVal
 #define EachNonZeroEnumVal  TL_EachNonZeroEnumVal
 
 // Clamps and math
 #define Min                 TL_Min
 #define Max                 TL_Max
 #define ClampTop            TL_ClampTop
 #define ClampBot            TL_ClampBot
 #define Clamp               TL_Clamp
 
 // Units
 #define KB                  TL_KB
 #define MB                  TL_MB
 #define GB                  TL_GB
 #define TB                  TL_TB
 #define Thousand            TL_Thousand
 #define Million             TL_Million
 #define Billion             TL_Billion
 //DLL
 #define DLL_Init TL_DLL_Init
 #define DLL_Insert TL_DLL_Insert

 //C Linkage
 #define C_LINKAGE_BEGIN TL_C_LINKAGE_BEGIN
 #define C_LINKAGE_END TL_C_LINKAGE_END
 #define C_LINKAGE TL_C_LINKAGE
 
 // Safe Casts
 #define safe_cast_U32_to_U16    tl_safe_cast_U32_to_U16
 #define safe_cast_S32_to_S16    tl_safe_cast_S32_to_S16
 #define safe_cast_U64_to_U32    tl_safe_cast_U64_to_U32
 #define safe_cast_S64_to_S32    tl_safe_cast_S64_to_S32
 
 // Memory
 #define memory_copy           tl_memory_copy
 #define memory_zero_size      tl_memory_zero_size
 #define MemoryZeroStruct      TL_MemoryZeroStruct
 #define MemoryZeroArray       TL_MemoryZeroArray
 #define MemoryMove            TL_MemoryMove
 #define MemorySet             TL_MemorySet
 #define MemoryStrlen          TL_MemoryStrlen
 #define MemoryCompare         TL_MemoryCompare
 #define MemoryMatch           TL_MemoryMatch
 #define MemoryMatchStruct     TL_MemoryMatchStruct
 #define MemoryMatchArray      TL_MemoryMatchArray
 
 // Arena Allocator
//TL_Memory_TempMemory
 #define Memory_Arena            TL_Memory_Arena
 #define Memory_TempMemory       TL_Memory_TempMemory

 #define arena_initialize        tl_arena_initialize
 #define arena_subdivide         tl_arena_subdivide
 #define ArenaPushSize           TL_ArenaPushSize
 #define ArenaPushStruct         TL_ArenaPushStruct
 #define ArenaPushArray          TL_ArenaPushArray
 #define ArenaPushCopy           TL_ArenaPushCopy
 #define arena_get_remaining_size tl_arena_get_remaining_size
 #define arena_get_alignment_offset tl_arena_get_alignment_offset
 #define arena_check             tl_arena_check
 #define arena_push_c_string     tl_arena_push_c_string
 #define begin_temporary_memory  tl_begin_temporary_memory
 #define end_temporary_memory    tl_end_temporary_memory
 
 ////////////////////////////////////////////////////////////////
 // Intrinsics
 #define atomic_compare_exchange_U32 tl_atomic_compare_exchange_U32
 #define atomic_exchange_U64             tl_atomic_exchange_U64
 #define atomic_add_U32                  tl_atomic_add_U32
 #define CompletePreviousWritesBeforeFutureWrite TL_CompletePreviousWritesBeforeFutureWrite
 #define CompletePreviousReadsBeforeFutureRead  TL_CompletePreviousReadsBeforeFutureRead
 
 ////////////////////////////////////////////////////////////////
 // Math 

 #define sign_of_F32                 tl_sign_of_F32
 #define sign_of_S32                 tl_sign_of_S32
 #define round_F32_to_S32      tl_round_F32_to_S32
 #define round_F32_to_U32      tl_round_F32_to_U32
 #define floor_F32_to_S32      tl_floor_F32_to_S32
 #define floor_F32_to_U32      tl_floor_F32_to_U32
 #define ceil_F32_to_S32       tl_ceil_F32_to_S32
 #define truncate_F32_to_S32   tl_truncate_F32_to_S32
 #define sin                     tl_sin
 #define cos                     tl_cos
 #define atan2                   tl_atan2
 #define absolute_value          tl_absolute_value
 #define square_root             tl_square_root
 #define find_least_significant_set_bit tl_find_least_significant_set_bit
 #define rotate_left             tl_rotate_left
 #define rotate_right            tl_rotate_right
 #define square                  tl_square
 #define lerp                    tl_lerp
 #define clamp_min_max           tl_clamp_min_max
 #define map_range_to01          tl_map_range_to01
 #define safe_ratio_n            tl_safe_ratio_n
 #define safe_ratio_0            tl_safe_ratio_0
 #define safe_ratio_1            tl_safe_ratio_1

 // Vector Operations
 #define clamp01                 tl_clamp01
 #define unit_circle_vector   tl_get_unit_circle_vector
 #define normalize            tl_normalize
 #define lerp                 tl_lerp

 // V2
 #define v2                      tl_v2
 #define V2                      TL_V2
 #define one_V2                  tl_one_V2
 #define zero_V2                 tl_zero_V2
 #define add_V2                  tl_add_V2
 #define multiply_V2             tl_multiply_V2
 #define subtract_V2             tl_subtract_V2
 #define clamp01_V2              tl_clamp01_V2
 #define inner_V2                tl_inner_V2
 #define perpendicular_V2        tl_perpendicular_V2
 #define invert_V2               tl_invert_V2
 #define lerp_V2                 tl_lerp_V2
 #define length_V2               tl_length_V2
 #define length_square_V2        tl_length_square_V2
 #define hadamard_V2             tl_hadamard_V2
 // V3
 #define v3                      tl_v3
 #define V3                      TL_V3
 #define one_V3                  tl_one_V3
 #define zero_V3                 tl_zero_V3
 #define add_V3                  tl_add_V3
 #define multiply_V3             tl_multiply_V3
 #define subtract_V3             tl_subtract_V3
 #define clamp01_V3              tl_clamp01_V3
 #define inner_V3                tl_inner_V3
 #define perpendicular_V3        tl_perpendicular_V3
 #define invert_V3               tl_invert_V3
 #define lerp_V3                 tl_lerp_V3
 #define length_V3               tl_length_V3
 #define length_square_V3        tl_length_square_V3
 #define hadamard_V3             tl_hadamard_V3
 // V4
 #define v4                      tl_v4
 #define V4                      TL_V4
 #define one_V4                  tl_one_V4
 #define zero_V4                 tl_zero_V4
 #define add_V4                  tl_add_V4
 #define multiply_V4             tl_multiply_V4
 #define subtract_V4             tl_subtract_V4
 #define clamp01_V4              tl_clamp01_V4
 #define inner_V4                tl_inner_V4
 #define perpendicular_V4        tl_perpendicular_V4
 #define invert_V4               tl_invert_V4
 #define lerp_V4                 tl_lerp_V4
 #define length_V4               tl_length_V4
 #define length_square_V4        tl_length_square_V4
 #define hadamard_V4             tl_hadamard_V4

 
 ////////////////////////////////////////////////////////////////
 // Rectangle Operations
 // Rectangle2
 #define Rectangle2             TL_Rectangle2
 #define offset_Rectangle2      tl_offset_Rectangle2
 #define center_dim_Rectangle2  tl_center_dim_Rectangle2
 #define get_center_Rectangle2             tl_get_center_Rectangle2
 #define get_dim_Rectangle2                tl_get_dim_Rectangle2
 #define min_max_Rectangle2           tl_min_max_Rectangle2
 #define min_dim_Rectangle2           tl_min_dim_Rectangle2
 #define center_radius_Rectangle2     tl_center_radius_Rectangle2
 #define add_radius_to_Rectangle2          tl_add_radius_to_Rectangle2
 #define is_in_Rectangle2       tl_is_in_Rectangle2
 #define get_barycentric_Rectangle2        tl_get_barycentric_Rectangle2
 #define axis_aligned_intersect_Rectangle2 tl_axis_aligned_intersect_Rectangle2
 #define intersection_Rectangle2 tl_intersection_Rectangle2
 #define has_area_Rectangle2 tl_has_area_Rectangle2
 #define inverted_infinity_Rectangle2 tl_inverted_infinity_Rectangle2

 // Rectangle2_S32
 #define Rectangle2_S32         TL_Rectangle2_S32
 #define offset_Rectangle2_S32  tl_offset_Rectangle2_S32
 #define get_center_Rectangle2_S32             tl_get_center_Rectangle2_S32
 #define get_dim_Rectangle2_S32                tl_get_dim_Rectangle2_S32
 #define rect_min_max_Rectangle2_S32           tl_min_max_Rectangle2_S32
 #define rect_min_dim_Rectangle2_S32           tl_min_dim_Rectangle2_S32
 #define center_radius_Rectangle2_S32     tl_center_radius_Rectangle2_S32
 #define add_radius_to_Rectangle2_S32          tl_add_radius_to_Rectangle2_S32
 #define is_in_Rectangle2_S32   tl_is_in_Rectangle2_S32
 #define get_barycentric_Rectangle2_S32        tl_get_barycentric_Rectangle2_S32
 #define intersection_Rectangle2_S32 tl_intersection_Rectangle2_S32
 #define has_area_Rectangle2_S32 tl_has_area_Rectangle2_S32
 #define inverted_infinity_Rectangle2_S32 tl_inverted_infinity_Rectangle2_S32

 // Rectangle3
 #define Rectangle3             TL_Rectangle3
 #define center_dim_Rectangle2_S32  tl_center_dim_Rectangle2_S32
 #define center_dim_Rectangle3  tl_center_dim_Rectangle3
 #define get_center_Rectangle3             tl_get_center_Rectangle3
 #define rect_min_dim_Rectangle3           tl_min_dim_Rectangle3
 #define center_radius_Rectangle3     tl_center_radius_Rectangle3
 #define add_radius_to_Rectangle3          tl_add_radius_to_Rectangle3
 #define get_barycentric_Rectangle3        tl_get_barycentric_Rectangle3
 #define offset_Rectangle3      tl_offset_Rectangle3
 #define is_in_Rectangle3       tl_is_in_Rectangle3
 #define intersection_Rectangle3 tl_intersection_Rectangle3
 #define has_area_Rectangle3 tl_has_area_Rectangle3
 #define get_dim_Rectangle3                tl_get_dim_Rectangle3
 #define min_max_Rectangle3           tl_min_max_Rectangle3
 #define inverted_infinity_Rectangle3 tl_inverted_infinity_Rectangle3

 
 ////////////////////////////////////////////////////////////////
 // Color Operations
 #define linear1_from_srgb255    tl_linear1_from_srgb255
 #define srgb255_from_linear1    tl_srgb255_from_linear1
 
 ////////////////////////////////////////////////////////////////
 // printf Replacement
 #define c_strings_are_equal     tl_c_strings_are_equal
 #define c_string_length         tl_c_string_length
 #define S32_from_c_string_and_advance_cursor tl_S32_from_c_string_and_advance_cursor
 #define S32_from_c_string       tl_S32_from_c_string
 #define write_char              tl_write_char
 #define read_variadic_argument_U32 tl_read_variadic_argument_U32
 #define read_variadic_argument_S32 tl_read_variadic_argument_S32
 #define read_variadic_argument_F32 tl_read_variadic_argument_F32
 #define U64_to_ascii            tl_U64_to_ascii
 #define F64_to_ascii            tl_F64_to_ascii
 #define format_string_list      tl_format_string_list
 #define format_string           tl_format_string
 

#endif // strip prefix

#endif // TL_H
