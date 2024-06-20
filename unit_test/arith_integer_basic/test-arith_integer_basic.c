/* */

#include "unity.h"
#include "arith.h"
#include <stdlib.h>
#include <time.h>
#include "tdd_common.h"
#include <limits.h>

// =============================== Tests start here ==================================


/* -------------------------------------- setUp ------------------------------------------- */

void setUp(void) {
    srand(time(NULL));     // Random seed for scrambling stimuli
}

/* -------------------------------------- tearDown ------------------------------------------- */

void tearDown(void) {
}

/* ------------------------------------ test_Limits -------------------------------------

   Check that our limit-defs match the (newer) GCC limits.h

*/
void test_Limits(void)
{
    TEST_ASSERT_TRUE( MAX_S32 == LONG_MAX );
    TEST_ASSERT_TRUE( MIN_S32 == LONG_MIN );
    TEST_ASSERT_TRUE( MAX_U32 == ULONG_MAX );
    TEST_ASSERT_TRUE( MIN_U32 == 0 );

    TEST_ASSERT_TRUE( MAX_S16 == SHRT_MAX );
    TEST_ASSERT_TRUE( MIN_S16 == SHRT_MIN );
    TEST_ASSERT_TRUE( MAX_U16 == USHRT_MAX );
    TEST_ASSERT_TRUE( MIN_U16 == 0 );

    TEST_ASSERT_TRUE( MAX_S8 == SCHAR_MAX );
    TEST_ASSERT_TRUE( MIN_S8 == SCHAR_MIN );
    TEST_ASSERT_TRUE( MAX_U8 == UCHAR_MAX );
    TEST_ASSERT_TRUE( MIN_U8 == 0 );
}

/* ------------------------------------ test_ClipS32toS16 ------------------------------------- */



typedef struct { S32 in; S16 returns; } S_ClipS32toS16Chk;

PRIVATE S_ClipS32toS16Chk const clipS32toS16_Chks[] = {
    {0,                    0},
    {0xFF,              0xFF},
    {MAX_S16,           MAX_S16},
    {(S32)MAX_S16+1,    MAX_S16},
    {MAX_S16-1,         MAX_S16-1},
    {MIN_S32,           MIN_S16},
    {(S32)MIN_S16-1,    MIN_S16},
    {MIN_S16+1,         MIN_S16+1}
};

void test_ClipS32toS16(void)
{
    U8 c;
    for( c = 0; c < RECORDS_IN(clipS32toS16_Chks); c++ )
        { TEST_ASSERT_TRUE( ClipS32toS16(clipS32toS16_Chks[c].in) == clipS32toS16_Chks[c].returns ); }
}


/* ------------------------------------ test_ClipU32toU16 ------------------------------------- */

void test_ClipU32toU16(void)
{
    TEST_ASSERT_TRUE( ClipU32toU16(0) == 0 );
    TEST_ASSERT_TRUE( ClipU32toU16((U32)MAX_U16) == MAX_U16 );
    TEST_ASSERT_TRUE( ClipU32toU16((U32)MAX_U16+1) == MAX_U16 );
    TEST_ASSERT_TRUE( ClipU32toU16((U32)MAX_U16-1) == MAX_U16-1 );
    TEST_ASSERT_TRUE( ClipU32toU16(MAX_U32) == MAX_U16 );
}

/* ------------------------------------ test_ClipS32toU16 ------------------------------------- */

void test_ClipS32toU16(void)
{
    TEST_ASSERT_TRUE( ClipS32toU16(0) == 0 );
    TEST_ASSERT_TRUE( ClipS32toU16((S32)MAX_U16) == MAX_U16 );
    TEST_ASSERT_TRUE( ClipS32toU16((S32)MAX_U16+1) == MAX_U16 );
    TEST_ASSERT_TRUE( ClipS32toU16((S32)MAX_U16-1) == MAX_U16-1 );
    TEST_ASSERT_TRUE( ClipS32toU16(MAX_S32) == MAX_U16 );
    TEST_ASSERT_TRUE( ClipS32toU16(MIN_S32) == 0 );
}

/* ------------------------------------ test_ClipS64toU32 ------------------------------------- */

void test_ClipS64toU32(void)
{
    TEST_ASSERT_TRUE( ClipS64toU32(0) == 0 );
    TEST_ASSERT_TRUE( ClipS64toU32((S64)MAX_U32) == MAX_U32 );
    TEST_ASSERT_TRUE( ClipS64toU32((S64)MAX_U32+1) == MAX_U32 );
    TEST_ASSERT_TRUE( ClipS64toU32((S64)MAX_U32-1) == MAX_U32-1 );
    TEST_ASSERT_TRUE( ClipS64toU32(MAX_S64) == MAX_U32 );
    TEST_ASSERT_TRUE( ClipS64toU32(MIN_S64) == 0 );
}

/* ------------------------------------ test_ClipS16toU8 ------------------------------------- */

void test_ClipS16toU8(void)
{
    TEST_ASSERT_TRUE( ClipS16toU8(0) == 0 );
    TEST_ASSERT_TRUE( ClipS16toU8(-1) == 0 );
    TEST_ASSERT_TRUE( ClipS16toU8((S16)MAX_U8) == MAX_U8 );
    TEST_ASSERT_TRUE( ClipS16toU8((S16)MAX_U8+1) == MAX_U8 );
    TEST_ASSERT_TRUE( ClipS16toU8((S16)MAX_U8-1) == MAX_U8-1 );
    TEST_ASSERT_TRUE( ClipS16toU8(MAX_S16) == MAX_U8 );
    TEST_ASSERT_TRUE( ClipS16toU8(MIN_S16) == 0 );
}

/* ------------------------------------ test_ClipS16toS8 ------------------------------------- */

void test_ClipS16toS8(void)
{
    TEST_ASSERT_TRUE( ClipS16toS8(0) == 0 );
    TEST_ASSERT_TRUE( ClipS16toS8((S16)MIN_S8) == MIN_S8 );
    TEST_ASSERT_TRUE( ClipS16toS8((S16)MIN_S8-1) == MIN_S8 );
    TEST_ASSERT_TRUE( ClipS16toS8((S16)MIN_S8+1) == MIN_S8+1 );
    TEST_ASSERT_TRUE( ClipS16toS8((S16)MAX_S8) == MAX_S8 );
    TEST_ASSERT_TRUE( ClipS16toS8((S16)MAX_S8+1) == MAX_S8 );
    TEST_ASSERT_TRUE( ClipS16toS8((S16)MAX_S8-1) == MAX_S8-1 );
    TEST_ASSERT_TRUE( ClipS16toS8(MAX_S16) == MAX_S8 );
    TEST_ASSERT_TRUE( ClipS16toS8(MIN_S16) == MIN_S8 );
}


/* ------------------------------------ test_ClipS64toS32 ------------------------------------- */

void test_ClipS64toS32(void)
{
    TEST_ASSERT_TRUE( ClipS64toS32(0) == 0 );
    TEST_ASSERT_TRUE( ClipS64toS32((S64)MIN_S32) == MIN_S32 );
    TEST_ASSERT_TRUE( ClipS64toS32((S64)MIN_S32-1) == MIN_S32 );
    TEST_ASSERT_TRUE( ClipS64toS32((S64)MIN_S32+1) == MIN_S32+1 );
    TEST_ASSERT_TRUE( ClipS64toS32((S64)MAX_S32) == MAX_S32 );
    TEST_ASSERT_TRUE( ClipS64toS32((S64)MAX_S32+1) == MAX_S32 );
    TEST_ASSERT_TRUE( ClipS64toS32((S64)MAX_S32-1) == MAX_S32-1 );
    TEST_ASSERT_TRUE( ClipS64toS32(MAX_S64) == MAX_S32 );
    TEST_ASSERT_TRUE( ClipS64toS32(MIN_S64) == MIN_S32 );
}



/* ------------------------------------ test_ClipU16toU8 ------------------------------------- */

void test_ClipU16toU8(void)
{
    TEST_ASSERT_TRUE( ClipU16toU8(0) == 0 );
    TEST_ASSERT_TRUE( ClipU16toU8((U16)MAX_U8) == MAX_U8 );
    TEST_ASSERT_TRUE( ClipU16toU8((U16)MAX_U8+1) == MAX_U8 );
    TEST_ASSERT_TRUE( ClipU16toU8((U16)MAX_U8-1) == MAX_U8-1 );
    TEST_ASSERT_TRUE( ClipU16toU8(MAX_U16) == MAX_U8 );
}

/* ------------------------------------ test_ClipU32toS32 ------------------------------------- */

void test_ClipU32toS32(void)
{
    TEST_ASSERT_TRUE( ClipU32toS32(0) == 0 );
    TEST_ASSERT_TRUE( ClipU32toS32(MAX_U32) == MAX_S32 );
    TEST_ASSERT_TRUE( ClipU32toS32(MAX_S32) == MAX_S32 );
    TEST_ASSERT_TRUE( ClipU32toS32(1000) == 1000 );
}

/* ------------------------------------ test_ClipU64toU32 ------------------------------------- */

void test_ClipU64toU32(void)
{
    TEST_ASSERT_TRUE( ClipU64toU32(0) == 0 );
    TEST_ASSERT_TRUE( ClipU64toU32((U64)MAX_U32) == MAX_U32 );
    TEST_ASSERT_TRUE( ClipU64toU32((U64)MAX_U32+1) == MAX_U32 );
    TEST_ASSERT_TRUE( ClipU64toU32((U64)MAX_U32-1) == MAX_U32-1 );
    TEST_ASSERT_TRUE( ClipU64toU32(MAX_U64) == MAX_U32 );
    TEST_ASSERT_TRUE( ClipU64toU32(0) == 0 );
}

/* ------------------------------------ test_MinS8 ------------------------------------- */

void test_MinS8(void)
{
    U8 c;
    S8 a, b, res;
    S8 temp;

    for( c = 0; c < 20; c++ )
    {
        a = randS8(); b = randS8();

        if( MinS8(a,b) != (a < b ? a : b ) ||
            MinS8(b,a) != (b < a ? b : a ) ||
            MinS8(-b,-a) != (a > b ? -a : -b ) ||
            MinS8(-a,-b) != (a > b ? -a : -b ) ||
            MinS8(a,a) != a)
        {
            printf("MinS8() failed: a = %d b = %d res %d expr %d d\r\n", (S8)a, (S8)b, (S8)MinS8(a,b), (S8)(a < b ? a : b ));
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE( MinS8(0,0) == 0 );
    TEST_ASSERT_TRUE( MinS8(MAX_S8, 0) == 0 );
    //temp = MinS8(MIN_S8, 0);
//printf("Chk eq min -128,0 is %d T/F? %d\r\n", MinS8(MIN_S8, 0), MinS8(MIN_S8, 0) == MIN_S8 );
    TEST_ASSERT_TRUE( MinS8(MIN_S8, 0) == -128 );
    TEST_ASSERT_TRUE( MinS8(MIN_S8, MAX_S8) == -128 );
}

/* ------------------------------------ test_MaxS8 ------------------------------------- */

void test_MaxS8(void)
{
    U8 c;
    S8 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randS8(); b = randS8();

        if( MaxS8(a,b) != (a > b ? a : b ) ||
            MaxS8(b,a) != (b > a ? b : a ) ||
            MaxS8(-b,-a) != (a < b ? -a : -b ) ||
            MaxS8(-a,-b) != (a < b ? -a : -b ) ||
            MaxS8(a,a) != a)
        {
            printf("MaxS8() failed a = %d b = %d\r\n", (S8)a, (S8)b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE( MaxS8(0,0) == 0 );
    TEST_ASSERT_TRUE( MaxS8(MAX_S8, 0) == MAX_S8 );
    TEST_ASSERT_TRUE( MaxS8(MIN_S8, 0) == 0 );
    TEST_ASSERT_TRUE( MaxS8(MIN_S8, MAX_S8) == MAX_S8 );
}


/* ------------------------------------ test_MinS16 ------------------------------------- */

void test_MinS16(void)
{
    U8 c;
    S16 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randS16(); b = randS16();

        if( MinS16(a,b) != (a < b ? a : b ) ||
            MinS16(b,a) != (b < a ? b : a ) ||
            MinS16(-b,-a) != (a > b ? -a : -b ) ||
            MinS16(-a,-b) != (a > b ? -a : -b ) ||
            MinS16(a,a) != a)
        {
            printf("MinS16() failed a = %d b = %d\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE( MinS16(0,0) == 0 );
    TEST_ASSERT_TRUE( MinS16(MAX_S16, 0) == 0 );
    TEST_ASSERT_TRUE( MinS16(MIN_S16, 0) == MIN_S16 );
    TEST_ASSERT_TRUE( MinS16(MIN_S16, MAX_S16) == MIN_S16 );
}


/* ------------------------------------ test_MaxS16 ------------------------------------- */

void test_MaxS16(void)
{
    U8 c;
    S16 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randS16(); b = randS16();

        if( MaxS16(a,b) != (a > b ? a : b ) ||
            MaxS16(b,a) != (b > a ? b : a ) ||
            MaxS16(-b,-a) != (a < b ? -a : -b ) ||
            MaxS16(-a,-b) != (a < b ? -a : -b ) ||
            MaxS16(a,a) != a)
        {
            printf("MaxS16() failed a = %d b = %d\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE( MaxS16(0,0) == 0 );
    TEST_ASSERT_TRUE( MaxS16(MAX_S16, 0) == MAX_S16 );
    TEST_ASSERT_TRUE( MaxS16(MIN_S16, 0) == 0 );
    TEST_ASSERT_TRUE( MaxS16(MIN_S16, MAX_S16) == MAX_S16 );
}

/* ------------------------------------ test_MinS64 ------------------------------------- */

void test_MinS64(void)
{
    U8 c;
    S64 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randS64(); b = randS64();

        if( MinS64(a,b) != (a < b ? a : b ) ||
            MinS64(b,a) != (b < a ? b : a ) ||
            MinS64(-b,-a) != (a > b ? -a : -b ) ||
            MinS64(-a,-b) != (a > b ? -a : -b ) ||
            MinS64(a,a) != a)
        {
            printf("MinS64() failed a = %d b = %d\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE( MinS64(0,0) == 0 );
    TEST_ASSERT_TRUE( MinS64(MAX_S64, 0) == 0 );
    TEST_ASSERT_TRUE( MinS64(MIN_S64, 0) == MIN_S64 );
    TEST_ASSERT_TRUE( MinS64(MIN_S64, MAX_S64) == MIN_S64 );
}


/* ------------------------------------ test_MaxS64 ------------------------------------- */

void test_MaxS64(void)
{
    U8 c;
    S64 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randS64(); b = randS64();

        if( MaxS64(a,b) != (a > b ? a : b ) ||
            MaxS64(b,a) != (b > a ? b : a ) ||
            MaxS64(-b,-a) != (a < b ? -a : -b ) ||
            MaxS64(-a,-b) != (a < b ? -a : -b ) ||
            MaxS64(a,a) != a)
        {
            printf("MaxS64() failed a = %d b = %d\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE( MaxS64(0,0) == 0 );
    TEST_ASSERT_TRUE( MaxS64(MAX_S64, 0) == MAX_S64 );
    TEST_ASSERT_TRUE( MaxS64(MIN_S64, 0) == 0 );
    TEST_ASSERT_TRUE( MaxS64(MIN_S64, MAX_S64) == MAX_S64 );
}

/* ------------------------------------ test_ClipS32 ------------------------------------- */

void test_ClipS32(void)
{
    U8 c;
    S32 n, l, u, ret, chk;

    #define _GoodClip(n,l,u)            \
        ((u) < (l))                     \
            ? ((u >> 1) + (l >> 1) )    \
            : ((n) < (l)                \
                ? (l)                   \
                : ((n) > (u)            \
                    ? (u)               \
                    : (n)))

    for( c = 0; c < 20; c++ )
    {
        n = randS32(); l = randS32(), u = randS32();
        ret =  ClipS32(n,l,u);
        chk = _GoodClip(n,l,u);

        if( ret != chk)
        {
            printf("ClipS32() failed n = %ld l = %ld u = %ld  expected %ld got %ld\r\n", n, l, u, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    #undef _GoodClip

    // Corner cases
    TEST_ASSERT_TRUE( ClipS32(0,0,0) == 0 );
    TEST_ASSERT_TRUE( ClipS32(MAX_S32, 0, MAX_S32) == MAX_S32 );
    TEST_ASSERT_TRUE( ClipS32(MIN_S32, MIN_S32, 0) == MIN_S32 );
}

/* ------------------------------------ test_ClipU32 ------------------------------------- */

void test_ClipU32(void)
{
    U8 c;
    U32 n, l, u, ret, chk;

    #define _GoodClip(n,l,u)            \
        ((u) < (l))                     \
            ? ((u >> 1) + (l >> 1) )    \
            : ((n) < (l)                \
                ? (l)                   \
                : ((n) > (u)            \
                    ? (u)               \
                    : (n)))

    for( c = 0; c < 20; c++ )
    {
        n = randU32(); l = randU32(), u = randU32();
        ret =  ClipU32(n,l,u);
        chk = _GoodClip(n,l,u);

        if( ret != chk)
        {
            printf("ClipU32() failed n = %ld l = %ld u = %ld  expected %ld got %ld\r\n", n, l, u, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    #undef _GoodClip

    // Corner cases
    TEST_ASSERT_TRUE( ClipU32(0,0,0) == 0 );
    TEST_ASSERT_TRUE( ClipU32(MAX_U32, 0, MAX_U32) == MAX_U32 );
    TEST_ASSERT_TRUE( ClipU32(MIN_U32, MIN_U32, 0) == MIN_U32 );
}

/* ------------------------------------ test_ClipS16 ------------------------------------- */

void test_ClipS16(void)
{
    U8 c;
    S16 n, l, u, ret, chk;

    #define _GoodClip(n,l,u)            \
        ((u) < (l))                     \
            ? ((u >> 1) + (l >> 1) )    \
            : ((n) < (l)                \
                ? (l)                   \
                : ((n) > (u)            \
                    ? (u)               \
                    : (n)))

    for( c = 0; c < 20; c++ )
    {
        n = randS16(); l = randS16(), u = randS16();
        ret = ClipS16(n,l,u);
        chk = _GoodClip(n,l,u);

        if( ret != chk)
        {
            printf("ClipS16() failed n = %d l = %d u = %d  expected %d got %d\r\n", n, l, u, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    #undef _GoodClip

    // Corner cases
    TEST_ASSERT_TRUE( ClipS16(0,0,0) == 0 );
    TEST_ASSERT_TRUE( ClipS16(MAX_S16, 0, MAX_S16) == MAX_S16 );
    TEST_ASSERT_TRUE( ClipS16(MIN_S16, MIN_S16, 0) == MIN_S16 );
}


/* ------------------------------------ test_ClipU16 ------------------------------------- */

void test_ClipU16(void)
{
    U8 c;
    U16 n, l, u, ret, chk;

    #define _GoodClip(n,l,u)            \
        ((u) < (l))                     \
            ? (((u)/2) + ((l)/2))       \
            : ((n) < (l)                \
                ? (l)                   \
                : ((n) > (u)            \
                    ? (u)               \
                    : (n)))

    for( c = 0; c < 20; c++ )
    {
        n = randU16(); l = randU16(), u = randU16();
        ret = ClipU16(n,l,u);
        chk = _GoodClip(n,l,u);

        if( ret != chk)
        {
            printf("ClipU16() failed n = %u l = %u u = %u  expected %u got %u\r\n", n, l, u, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    #undef _GoodClip

    // Corner cases
    TEST_ASSERT_TRUE( ClipU16(0,0,0) == 0 );
    TEST_ASSERT_TRUE( ClipU16(0,0,MAX_U16) == 0 );
    TEST_ASSERT_TRUE( ClipU16(MAX_U16, 0, MAX_U16) == MAX_U16 );
}


/* ------------------------------------ test_ClipU8 ------------------------------------- */

void test_ClipU8(void)
{
    U8 c;
    U8 n, l, u, ret, chk;

    #define _GoodClip(n,l,u)            \
        ((u) < (l))                     \
            ? (((u)/2) + ((l)/2))       \
            : ((n) < (l)                \
                ? (l)                   \
                : ((n) > (u)            \
                    ? (u)               \
                    : (n)))

    for( c = 0; c < 20; c++ )
    {
        n = randU8(); l = randU8(), u = randU8();
        ret = ClipU8(n,l,u);
        chk = _GoodClip(n,l,u);

        if( ret != chk)
        {
            printf("ClipU8() failed n = %u l = %u u = %u  expected %u got %u\r\n", n, l, u, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    #undef _GoodClip

    // Corner cases
    TEST_ASSERT_TRUE( ClipU8(0,0,0) == 0 );
    TEST_ASSERT_TRUE( ClipU8(0,0,MAX_U8) == 0 );
    TEST_ASSERT_TRUE( ClipU8(MAX_U8, 0, MAX_U8) == MAX_U8 );
}


/* ------------------------------------ test_ClipS8 ------------------------------------- */

void test_ClipS8(void)
{
    U8 c;
    S8 n, l, u, ret, chk;

    #define _GoodClip(n,l,u)            \
        ((u) < (l))                     \
            ? (((u)/2) + ((l)/2))       \
            : ((n) < (l)                \
                ? (l)                   \
                : ((n) > (u)            \
                    ? (u)               \
                    : (n)))

    for( c = 0; c < 50; c++ )
    {
        n = randS8(); l = randS8(), u = randS8();
        ret = ClipS8(n,l,u);
        chk = _GoodClip(n,l,u);

        if( ret != chk)
        {
            printf("ClipS8() failed n = %d l = %d u = %d  expected %d got %d\r\n", n, l, u, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    #undef _GoodClip

    // Corner cases
    TEST_ASSERT_TRUE( ClipS8(0,0,0) == 0 );
    TEST_ASSERT_TRUE( ClipS8(0,0,MAX_S8) == 0 );
    TEST_ASSERT_TRUE( ClipS8(MAX_S8, 0, MAX_S8) == MAX_S8 );
    TEST_ASSERT_TRUE( ClipS8(-128, -128, MAX_S8) == -128 );

}


/* ---------------------------------- test_MinU8 ------------------------------------- */

void test_MinU8(void)
{
    U8 c;
    U8 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randU8(); b = randU8();

        if( MinU8(a,b) != (a < b ? a : b ) ||
            MinU8(b,a) != (b < a ? b : a ) ||
            MinU8(a,a) != a)
        {
            printf("MinU8() failed a = %d b = %d\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE(MinU8(0,0) == 0);
    TEST_ASSERT_TRUE(MinU8(0,10) == 0);
    TEST_ASSERT_TRUE(MinU8(20,0) == 0);
    TEST_ASSERT_TRUE(MinU8(20,10) == 10);
    TEST_ASSERT_TRUE(MinU8(MAX_U8,30) == 30);
    TEST_ASSERT_TRUE(MinU8(MAX_U8,MAX_U8) == MAX_U8);
}


/* ---------------------------------- test_MaxU8 ------------------------------------- */

void test_MaxU8(void)
{
    U8 c;
    U8 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randU8(); b = randU8();

        if( MaxU8(a,b) != (a > b ? a : b ) ||
            MaxU8(b,a) != (b > a ? b : a ) ||
            MaxU8(a,a) != a)
        {
            printf("MaxU8() failed a = %d b = %d\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE(MaxU8(0,0) == 0);
    TEST_ASSERT_TRUE(MaxU8(0,10) == 10);
    TEST_ASSERT_TRUE(MaxU8(20,0) == 20);
    TEST_ASSERT_TRUE(MaxU8(20,10) == 20);
    TEST_ASSERT_TRUE(MaxU8(MAX_U8,30) == MAX_U8);
    TEST_ASSERT_TRUE(MaxU8(MAX_U8,MAX_U8) == MAX_U8);
}

/* ---------------------------------- test_MinU16 ------------------------------------- */

void test_MinU16(void)
{
    U8 c;
    U16 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randU16(); b = randU16();

        if( MinU16(a,b) != (a < b ? a : b ) ||
            MinU16(b,a) != (b < a ? b : a ) ||
            MinU16(a,a) != a)
        {
            printf("MinU16() failed a = %u b = %u\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE(MinU16(0,0) == 0);
    TEST_ASSERT_TRUE(MinU16(0,10) == 0);
    TEST_ASSERT_TRUE(MinU16(20,0) == 0);
    TEST_ASSERT_TRUE(MinU16(MAX_U16,300) == 300);
    TEST_ASSERT_TRUE(MinU16(300,MAX_U16) == 300);
    TEST_ASSERT_TRUE(MinU16(MAX_U16,MAX_U16) == MAX_U16);
}


/* ---------------------------------- test_MaxU16 ------------------------------------- */

void test_MaxU16(void)
{
    U8 c;
    U16 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randU16(); b = randU16();

        if( MaxU16(a,b) != (a > b ? a : b ) ||
            MaxU16(b,a) != (b > a ? b : a ) ||
            MaxU16(a,a) != a)
        {
            printf("MaxU16() failed a = %u b = %u\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE(MaxU16(0,0) == 0);
    TEST_ASSERT_TRUE(MaxU16(0,10) == 10);
    TEST_ASSERT_TRUE(MaxU16(20,0) == 20);
    TEST_ASSERT_TRUE(MaxU16(MAX_U16,300) == MAX_U16);
    TEST_ASSERT_TRUE(MaxU16(300,MAX_U16) == MAX_U16);
    TEST_ASSERT_TRUE(MaxU16(MAX_U16,MAX_U16) == MAX_U16);
}


/* ---------------------------------- test_MinU32 ------------------------------------- */

void test_MinU32(void)
{
    U8 c;
    U32 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randU32(); b = randU32();

        if( MinU32(a,b) != (a < b ? a : b ) ||
            MinU32(b,a) != (b < a ? b : a ) ||
            MinU32(a,a) != a)
        {
            printf("MinU32() failed a = %lu b = %lu\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE(MinU32(0,0) == 0);
    TEST_ASSERT_TRUE(MinU32(0,10) == 0);
    TEST_ASSERT_TRUE(MinU32(20,0) == 0);
    TEST_ASSERT_TRUE(MinU32(MAX_U32,300) == 300);
    TEST_ASSERT_TRUE(MinU32(300,MAX_U32) == 300);
    TEST_ASSERT_TRUE(MinU32(MAX_U32,MAX_U32) == MAX_U32);
}


/* ---------------------------------- test_MaxU32 ------------------------------------- */

void test_MaxU32(void)
{
    U8 c;
    U32 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randU32(); b = randU32();

        if( MaxU32(a,b) != (a > b ? a : b ) ||
            MaxU32(b,a) != (b > a ? b : a ) ||
            MaxU32(a,a) != a)
        {
            printf("MaxU32() failed a = %lu b = %lu\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE(MaxU32(0,0) == 0);
    TEST_ASSERT_TRUE(MaxU32(0,10) == 10);
    TEST_ASSERT_TRUE(MaxU32(20,0) == 20);
    TEST_ASSERT_TRUE(MaxU32(MAX_U32,300) == MAX_U32);
    TEST_ASSERT_TRUE(MaxU32(300,MAX_U32) == MAX_U32);
    TEST_ASSERT_TRUE(MaxU32(MAX_U32,MAX_U32) == MAX_U32);
}


/* ---------------------------------- test_MinU64 ------------------------------------- */

void test_MinU64(void)
{
    U8 c;
    U64 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randU64(); b = randU64();

        if( MinU64(a,b) != (a < b ? a : b ) ||
            MinU64(b,a) != (b < a ? b : a ) ||
            MinU64(a,a) != a)
        {
            printf("MinU64() failed a = %lu b = %lu\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE(MinU64(0,0) == 0);
    TEST_ASSERT_TRUE(MinU64(0,10) == 0);
    TEST_ASSERT_TRUE(MinU64(20,0) == 0);
    TEST_ASSERT_TRUE(MinU64(MAX_U64,300) == 300);
    TEST_ASSERT_TRUE(MinU64(300,MAX_U64) == 300);
    TEST_ASSERT_TRUE(MinU64(MAX_U64,MAX_U64) == MAX_U64);
}

/* ---------------------------------- test_MaxU64 ------------------------------------- */

void test_MaxU64(void)
{
    U8 c;
    U64 a, b;

    for( c = 0; c < 20; c++ )
    {
        a = randU64(); b = randU64();

        if( MaxU64(a,b) != (a > b ? a : b ) ||
            MaxU64(b,a) != (b > a ? b : a ) ||
            MaxU64(a,a) != a)
        {
            printf("MaxU64() failed a = %lu b = %lu\r\n", a, b);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Corner cases
    TEST_ASSERT_TRUE(MaxU64(0,0) == 0);
    TEST_ASSERT_TRUE(MaxU64(0,10) == 10);
    TEST_ASSERT_TRUE(MaxU64(20,0) == 20);
    TEST_ASSERT_TRUE(MaxU64(MAX_U64,300) == MAX_U64);
    TEST_ASSERT_TRUE(MaxU64(300,MAX_U64) == MAX_U64);
    TEST_ASSERT_TRUE(MaxU64(MAX_U64,MAX_U64) == MAX_U64);
}



/* ------------------------------ test_AplusBU8 -------------------------------------- */

void test_AplusBU8(void)
{
    TEST_ASSERT_TRUE( AplusBU8(0,0) == 0);
    TEST_ASSERT_TRUE( AplusBU8(2,3) == 5);
    TEST_ASSERT_TRUE( AplusBU8(7,12) == 19);
    TEST_ASSERT_TRUE( AplusBU8(MAX_U8,0) == MAX_U8);
    TEST_ASSERT_TRUE( AplusBU8(0,MAX_U8) == MAX_U8);
    TEST_ASSERT_TRUE( AplusBU8(MAX_U8,MAX_U8) == MAX_U8);
}

/* ------------------------------ test_U8plusS8toU8 -------------------------------------- */

void test_U8plusS8toU8(void)
{
    TEST_ASSERT_TRUE( U8plusS8toU8(0,0) == 0);
    TEST_ASSERT_TRUE( U8plusS8toU8(2,3) == 5);
    TEST_ASSERT_TRUE( U8plusS8toU8(3,-2) == 1);
    TEST_ASSERT_TRUE( U8plusS8toU8(7,12) == 19);

    TEST_ASSERT_TRUE( U8plusS8toU8(MAX_U8,0) == MAX_U8);
    TEST_ASSERT_TRUE( U8plusS8toU8(MAX_U8,1) == MAX_U8);
    TEST_ASSERT_TRUE( U8plusS8toU8(MAX_U8,-1) == MAX_U8-1);
    TEST_ASSERT_TRUE( U8plusS8toU8(MAX_U8,MAX_S8) == MAX_U8);

    TEST_ASSERT_TRUE( U8plusS8toU8(0,MAX_S8) == MAX_S8);
    TEST_ASSERT_TRUE( U8plusS8toU8(0,MIN_S8) == 0);
    TEST_ASSERT_TRUE( U8plusS8toU8(MAX_S8,MIN_S8) == 0);

    TEST_ASSERT_TRUE( U8plusS8toU8(MAX_U8,1) == MAX_U8);
}

/* ------------------------------------ test_AplusBS16 ------------------------------------- */

void test_AplusBS16(void)
{
    U8 c;
    S16 a, b, res;
    S32 chk;

    TEST_ASSERT_TRUE(AplusBS16(MAX_S16, 0) == MAX_S16);
    TEST_ASSERT_TRUE(AplusBS16(MAX_S16, 1) == MAX_S16);
    TEST_ASSERT_TRUE(AplusBS16(MIN_S16, 0) == MIN_S16);
    TEST_ASSERT_TRUE(AplusBS16(MIN_S16, -1) == MIN_S16);
    TEST_ASSERT_TRUE(AplusBS16(MAX_S16, MIN_S16) == (S32)MAX_S16 + MIN_S16);

    for( c = 0; c < 100; c++)
    {
        a = randS16(); b = randS16();
        chk = (S32)a + b;
        res = AplusBS16(a,b);

        if( (chk > MAX_S16 && res != MAX_S16) ||
            (chk < MIN_S16 && res != MIN_S16) ||
            (chk <= MAX_S16 && chk >= MIN_S16 && res != chk))
        {
            printf("test_AplusBS16() failed: (%d + %d) expected %ld got %d\r\n", a, b, chk, res);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------------ test_AplusBU16 ------------------------------------- */

void test_AplusBU16(void)
{
    U8 c;
    U16 a, b, res;
    U32 chk;

    TEST_ASSERT_TRUE(AplusBU16(MAX_U16, 0) == MAX_U16);
    TEST_ASSERT_TRUE(AplusBU16(0, MAX_U16) == MAX_U16);
    TEST_ASSERT_TRUE(AplusBU16(MAX_U16, 1) == MAX_U16);
    TEST_ASSERT_TRUE(AplusBU16(1, MAX_U16) == MAX_U16);
    TEST_ASSERT_TRUE(AplusBU16(MAX_U16, MAX_U16) == MAX_U16);

    for( c = 0; c < 100; c++)
    {
        a = randU16(); b = randU16();
        chk = (U32)a + b;
        res = AplusBU16(a,b);

        if( (chk > MAX_U16 && res != MAX_U16) ||
            (chk <= MAX_U16 && res != chk))
        {
            printf("test_AplusBU16() failed: (%u + %u) expected %lu got %u\r\n", a, b, chk, res);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------------ test_U16plusS16_toU16 ------------------------------------- */

void test_U16plusS16_toU16(void)
{
    U8 c;
    U16 a, res;
    S16 b;
    S32 chk;

    TEST_ASSERT_TRUE(U16plusS16_toU16(MAX_U16, 0) == MAX_U16);
    TEST_ASSERT_TRUE(U16plusS16_toU16(0, MAX_S16) == MAX_S16);
    TEST_ASSERT_TRUE(U16plusS16_toU16(0, MIN_S16) == 0);
    TEST_ASSERT_TRUE(U16plusS16_toU16(MAX_S16, MIN_S16) == 0);
    TEST_ASSERT_TRUE(U16plusS16_toU16(MAX_S16, -MAX_S16) == 0);
    TEST_ASSERT_TRUE(U16plusS16_toU16(MAX_U16, 1) == MAX_U16);
    TEST_ASSERT_TRUE(U16plusS16_toU16(1, MAX_S16) == MAX_S16+1);
    TEST_ASSERT_TRUE(U16plusS16_toU16(MAX_U16, MAX_S16) == MAX_U16);

    for( c = 0; c < 100; c++)
    {
        a = randU16(); b = randS16();
        chk = (S32)a + b;
        res = U16plusS16_toU16(a,b);

        if( (chk > MAX_U16 && res != MAX_U16) ||
            (chk < MIN_U16 && res != MIN_U16) ||
            (chk >= MIN_U16 && chk <= MAX_U16 && res != chk))
        {
            printf("test_U16plusS16_toU16() failed: (%u + %d) expected %ld got %d\r\n", a, b, chk, res);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------------ test_AplusBU32 ------------------------------------- */

void test_AplusBU32(void)
{
    U8 c;
    U32 a, b, res;
    U64 chk;

    TEST_ASSERT_TRUE(AplusBU32(MAX_U32, 0) == MAX_U32);
    TEST_ASSERT_TRUE(AplusBU32(0, MAX_U32) == MAX_U32);
    TEST_ASSERT_TRUE(AplusBU32(MAX_U32, 1) == MAX_U32);
    TEST_ASSERT_TRUE(AplusBU32(1, MAX_U32) == MAX_U32);
    TEST_ASSERT_TRUE(AplusBU32(MAX_U32, MAX_U32) == MAX_U32);

    for( c = 0; c < 100; c++)
    {
        a = randU32(); b = randU32();
        chk = (U64)a + b;
        if(chk > MAX_U32) {chk = MAX_U32;}
        res = AplusBU32(a,b);

        if( (chk > MAX_U32 && res != MAX_U32) ||
            (chk <= MAX_U32 && res != chk))
        {
            printf("test_AplusBU32() failed: (%lu + %lu) expected %lu got %lu\r\n", a, b, chk, res);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------------ test_AplusBS32 ------------------------------------- */

void test_AplusBS32(void)
{
    U8 c;
    S32 a, b, res;
    S64 chk;

    TEST_ASSERT_TRUE(AplusBS32(MAX_S32, 0) == MAX_S32);
    TEST_ASSERT_TRUE(AplusBS32(0, MAX_S32) == MAX_S32);
    TEST_ASSERT_TRUE(AplusBS32(MAX_S32, 1) == MAX_S32);
    TEST_ASSERT_TRUE(AplusBS32(1, MAX_S32) == MAX_S32);
    TEST_ASSERT_TRUE(AplusBS32(MAX_S32, MAX_S32) == MAX_S32);

    for( c = 0; c < 100; c++)
    {
        a = randS32(); b = randS32();
        chk = (S64)a+b;
        if(chk > MAX_S32) {chk = MAX_S32;}
        res = AplusBS32(a,b);

        BOOL over  = a >= 0 && b >= 0 && a+b < 0;       // overflow
        BOOL under = a <= 0 && b <= 0 && a+b > 0;       // underflow

        if( (!over && !under && res != chk) || (over && res != MAX_S32) || (under && res != MIN_S32) )
        {
            printf("test_AplusBS32() failed: (%ld + %ld) expected %ld got %ld\r\n", a, b, chk, res);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------------ test_U32plusS16 ------------------------------------- */

void test_U32plusS16(void)
{
    U8 c;
    U32 a, res;
    S16 b;
    U32 chk;

    TEST_ASSERT_TRUE(U32plusS16(0, MAX_S16) == MAX_S16);
    TEST_ASSERT_TRUE(U32plusS16(0, MIN_S16) == 0);
    TEST_ASSERT_TRUE(U32plusS16(MAX_U32, 0) == MAX_U32);
    TEST_ASSERT_TRUE(U32plusS16(MAX_U32, 1) == MAX_U32);
    TEST_ASSERT_TRUE(U32plusS16(MAX_U32, MAX_S16) == MAX_U32);
    TEST_ASSERT_TRUE(U32plusS16(1, MAX_S16) == MAX_S16+1);
    TEST_ASSERT_TRUE(U32plusS16(MAX_S16, 1-MAX_S16) == 1);

    for( c = 0; c < 100; c++)
    {
        a = randU32(); b = randS16();
        chk = a+b;
        res = U32plusS16(a,b);

        BOOL over  = a >= 0 && b >= 0 && a+b < 0;       // overflow
        BOOL under = b < 0 && (U32)(-b) > a;                     // underflow

        if( (!over && !under && res != chk) || (over && res != MAX_U32) || (under && res != 0) )
        {
            printf("test_U32plusS16() failed: (%lu + %d) expected %lu got %lu\r\n", a, b, chk, res);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------------ test_U32plusS32_toU32 ------------------------------------- */

void test_U32plusS32_toU32(void)
{
    U8 c;
    U32 a, res;
    U64 chk;
    S32 b;

    TEST_ASSERT_TRUE(U32plusS32_toU32(MAX_U32, 0) == MAX_U32);
    TEST_ASSERT_TRUE(U32plusS32_toU32(0, MAX_S32) == MAX_S32);
    TEST_ASSERT_TRUE(U32plusS32_toU32(MAX_S32, 1) == (U32)MAX_S32+1);
    TEST_ASSERT_TRUE(U32plusS32_toU32(1, MAX_S32) == (U32)MAX_S32+1);
    TEST_ASSERT_TRUE(U32plusS32_toU32(MAX_U32, MAX_S32) == MAX_U32);
    TEST_ASSERT_TRUE(U32plusS32_toU32(0, MIN_S32) == 0);
    TEST_ASSERT_TRUE(U32plusS32_toU32(MAX_S32, 1-MAX_S32) == 1);

    for( c = 0; c < 100; c++)
    {
        a = randU32(); b = randS32();
        chk = (U64)a+b;
        if(chk > MAX_U32) {chk = MAX_U32;}
        res = U32plusS32_toU32(a,b);

        BOOL over  = a >= 0 && b >= 0 && a+b < 0;       // overflow
        BOOL under = b < 0 && (U32)(-b) > a;       // underflow

        if( (!over && !under && res != chk) || (over && res != MAX_U32) || (under && res != 0) )
        {
            printf("test_U32plusS32_toU32() failed: (%lu + %ld) expected %lu got %lu\r\n", a, b, chk, res);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------------ test_SignEqualsS16 ----------------------------------------

    Zero is read as a positive number.
*/

typedef struct {
    S16 a, b;
    BOOL result;
} S_SignEqualsChk;

PRIVATE S_SignEqualsChk const signEqS16_Chks[] = {
    { 0,    0,      TRUE},
    { 1,    1,      TRUE},
    {-1,   -1,      TRUE},
    { 1,   -1,      FALSE},
    { -1,   1,      FALSE},
    { -1,   0,      FALSE},
    {  0,  -1,      FALSE},
    {  1,   0,      TRUE},
    {  0,   1,      TRUE},
    {  1,   2,      TRUE},

    {  1,   MAX_S16,    TRUE},
    { -1,   MIN_S16,    TRUE},
    {  1,   MIN_S16,    FALSE},
    { -1,   MAX_S16,    FALSE},

    {  1,   0x4000,    TRUE},
    { -1,   0x4000,    FALSE},

    {  MIN_S16, MAX_S16,    FALSE}
};

void test_SignEqualsS16(void)
{
    U8 c;
    for( c = 0; c < RECORDS_IN(signEqS16_Chks); c++)
        { TEST_ASSERT_TRUE( SignEqualsS16(signEqS16_Chks[c].a, signEqS16_Chks[c].b) == signEqS16_Chks[c].result); }
}

/* ------------------------------- test_MulS16 ------------------------------------------ */

void test_MulS16()
{
    TEST_ASSERT_EQUAL_INT32(MulS16(0,0), 0);
    TEST_ASSERT_EQUAL_INT32(MulS16(MAX_S16,0), 0);
    TEST_ASSERT_EQUAL_INT32(MulS16(0,MAX_S16), 0);

    TEST_ASSERT_EQUAL_INT32(MulS16(1,MAX_S16), MAX_S16);
    TEST_ASSERT_EQUAL_INT32(MulS16(MAX_S16,1), MAX_S16);
    TEST_ASSERT_EQUAL_INT32(MulS16(1,MIN_S16), MIN_S16);
    TEST_ASSERT_EQUAL_INT32(MulS16(MIN_S16,1), MIN_S16);

    TEST_ASSERT_EQUAL_INT32(MulS16(MAX_S16,MAX_S16), (S32)MAX_S16*MAX_S16);
    TEST_ASSERT_EQUAL_INT32(MulS16(MIN_S16,MIN_S16), (S32)MIN_S16*MIN_S16);
    TEST_ASSERT_EQUAL_INT32(MulS16(MAX_S16,MIN_S16), (S32)MAX_S16*MIN_S16);
    TEST_ASSERT_EQUAL_INT32(MulS16(MIN_S16,MAX_S16), (S32)MAX_S16*MIN_S16);
}

/* ------------------------------- test_MulS32 ------------------------------------------ */

void test_MulS32()
{
    TEST_ASSERT_EQUAL_INT64(MulS32(0,0), 0);
    TEST_ASSERT_EQUAL_INT64(MulS32(MAX_S32,0), 0);
    TEST_ASSERT_EQUAL_INT64(MulS32(0,MAX_S32), 0);

    TEST_ASSERT_EQUAL_INT64(MulS32(1,MAX_S32), MAX_S32);
    TEST_ASSERT_EQUAL_INT64(MulS32(MAX_S32,1), MAX_S32);
    TEST_ASSERT_EQUAL_INT64(MulS32(1,MIN_S32), MIN_S32);
    TEST_ASSERT_EQUAL_INT64(MulS32(MIN_S32,1), MIN_S32);

    TEST_ASSERT_EQUAL_INT64(MulS32(MAX_S32,MAX_S32), (S64)MAX_S32*MAX_S32);
    TEST_ASSERT_EQUAL_INT64(MulS32(MIN_S32,MIN_S32), (S64)MIN_S32*MIN_S32);
    TEST_ASSERT_EQUAL_INT64(MulS32(MAX_S32,MIN_S32), (S64)MAX_S32*MIN_S32);
    TEST_ASSERT_EQUAL_INT64(MulS32(MIN_S32,MAX_S32), (S64)MAX_S32*MIN_S32);
}

/* ------------------------------ test_AminusBU8 -------------------------------------- */

void test_AminusBU8(void)
{
    TEST_ASSERT_TRUE( AminusBU8(0,0) == 0);
    TEST_ASSERT_TRUE( AminusBU8(MAX_U8,0) == MAX_U8);
    TEST_ASSERT_TRUE( AminusBU8(0,MAX_U8) == 0);
    TEST_ASSERT_TRUE( AminusBU8(MAX_U8,MAX_U8) == 0);
    TEST_ASSERT_TRUE( AminusBU8(4,2) == 2);
}

/* ----------------------------- test_AminusB_PtrToU8 ----------------------------------------- */

void test_AminusB_PtrToU8()
{
    // Corner cases.
    TEST_ASSERT_TRUE( AminusB_PtrToU8( (U8[]){0},(U8[]){0}) == 0);
    TEST_ASSERT_TRUE( AminusB_PtrToU8( (U8[1]){MAX_U8}, (U8[1]){0}) == MAX_U8);
    TEST_ASSERT_TRUE( AminusB_PtrToU8( (U8[1]){MAX_U8-1}, (U8[1]){0} ) == MAX_U8-1);
    TEST_ASSERT_TRUE( AminusB_PtrToU8( (U8[1]){MAX_U8}, (U8[1]){MAX_U8} ) == 0);
    TEST_ASSERT_TRUE( AminusB_PtrToU8( (U8[1]){4}, (U8[1]){2}) == 2);
}

/* ------------------------------ test_AminusBU16 -------------------------------------- */

void test_AminusBU16(void)
{
    TEST_ASSERT_TRUE( AminusBU16(0,0) == 0);
    TEST_ASSERT_TRUE( AminusBU16(MAX_U16,0) == MAX_U16);
    TEST_ASSERT_TRUE( AminusBU16(0,MAX_U16) == 0);
    TEST_ASSERT_TRUE( AminusBU16(MAX_U16,MAX_U16) == 0);
    TEST_ASSERT_TRUE( AminusBU16(4,2) == 2);
}

/* ------------------------------ test_AminusBS16 -------------------------------------- */

void test_AminusBS16(void)
{
    TEST_ASSERT_TRUE( AminusBS16(0,0) == 0);
    TEST_ASSERT_TRUE( AminusBS16(MAX_S16,0) == MAX_S16);
    TEST_ASSERT_TRUE( AminusBS16(0,MAX_S16) == -MAX_S16);
    TEST_ASSERT_TRUE( AminusBS16(MAX_S16,MAX_S16) == 0);
    TEST_ASSERT_TRUE( AminusBS16(MIN_S16,MIN_S16) == 0);
    TEST_ASSERT_TRUE( AminusBS16(MAX_S16,MIN_S16) == MAX_S16);
    TEST_ASSERT_TRUE( AminusBS16(MIN_S16,MAX_S16) == MIN_S16);
    TEST_ASSERT_TRUE( AminusBS16(4,2) == 2);
}

/* ------------------------------ test_AminusBU32 -------------------------------------- */

void test_AminusBU32(void)
{
    TEST_ASSERT_TRUE( AminusBU32(0,0) == 0);
    TEST_ASSERT_TRUE( AminusBU32(MAX_U32,0) == MAX_U32);
    TEST_ASSERT_TRUE( AminusBU32(0,MAX_U32) == 0);
    TEST_ASSERT_TRUE( AminusBU32(MAX_U32,MAX_U32) == 0);
    TEST_ASSERT_TRUE( AminusBU32(4,2) == 2);
}


/* ------------------------------ test_AminusBU16ToS16 -------------------------------------- */

void test_AminusBU16ToS16(void)
{
    U8 c;
    U16 a, b;
    S16 res;
    S32 chk;

    // Corner cases.
    TEST_ASSERT_TRUE( AminusBU16ToS16(0,0) == 0);
    TEST_ASSERT_TRUE( AminusBU16ToS16(MAX_U16,0) == MAX_S16);
    TEST_ASSERT_TRUE( AminusBU16ToS16(MAX_U16-1,0) == MAX_S16);
    TEST_ASSERT_TRUE( AminusBU16ToS16(0,MAX_U16) == MIN_S16);
    TEST_ASSERT_TRUE( AminusBU16ToS16(0,MAX_U16-1) == MIN_S16);
    TEST_ASSERT_TRUE( AminusBU16ToS16(MAX_U16,MAX_U16) == 0);

    // Some random inputs.
    for(c = 0; c < 200; c++)
    {
        a = randU16(); b = randU16();
        res = AminusBU16ToS16(a,b);
        chk = (S32)a - (S32)b;

        if( (chk >= MAX_S16 && res != MAX_S16) ||
            (chk <= MIN_S16 && res != MIN_S16) ||
            (chk < MAX_S16 && chk > MIN_S16 && chk != res) )
        {
            printf("AminusBU16ToS16() failed: %u %u -> %d excpected %ld\r\n", a, b, res, chk);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}



/* ------------------------------ test_AminusBU32toS32 -------------------------------------- */

void test_AminusBU32toS32(void)
{
    U8 c;
    U32 a, b;
    S32 res;
    S64 chk;

    // Corner cases.
    TEST_ASSERT_TRUE( AminusBU32toS32(0,0) == 0);
    TEST_ASSERT_TRUE( AminusBU32toS32(MAX_U32,0) == MAX_S32);
    TEST_ASSERT_TRUE( AminusBU32toS32(MAX_U32-1,0) == MAX_S32);
    TEST_ASSERT_TRUE( AminusBU32toS32(0,MAX_U32) == MIN_S32);
    TEST_ASSERT_TRUE( AminusBU32toS32(0,MAX_U32-1) == MIN_S32);
    TEST_ASSERT_TRUE( AminusBU32toS32(MAX_U32,MAX_U32) == 0);

    // Some random inputs.
    for(c = 0; c < 200; c++)
    {
        a = randU32(); b = randU32();
        res = AminusBU32toS32(a,b);

        // a - b, clipped to MAX_S32.  Don't rely on 64bit; check for overrange before subtracting.
        #define _aMinusb_Clip(a,b)                          \
            (((b) < MAX_U32-MAX_S32 && (a) > (b)+MAX_S32)   \
                        ? MAX_S32                           \
                        : ((a) - (b)))

        #define _aMinusb_Clip_2(a,b)                          \
            (((b) < MAX_U32-MAX_S32 && (a) > (b)+MAX_S32)   \
                        ? (S64)MAX_S32+1                           \
                        : ((a) - (b)))

        chk = (a > b) ? _aMinusb_Clip(a,b) : -_aMinusb_Clip_2(b,a);

        if( (S32)chk != res )
        {
            printf("AminusBU32toS32() failed: %lu - %lu -> %lld expected %lld\r\n", a, b, res, chk);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------ test_AminusBS32toU32 -------------------------------------- */

void test_AminusBS32toU32(void)
{
    U8 c;
    S32 a, b;
    U32 res;
    U32 chk;

    // Nil.
    TEST_ASSERT_TRUE( AminusBS32toU32(0,0) == 0);
    // Corners
    TEST_ASSERT_TRUE( AminusBS32toU32(MIN_S32,MIN_S32) == 0);
    TEST_ASSERT_TRUE( AminusBS32toU32(MAX_S32,MAX_S32) == 0);
    TEST_ASSERT_TRUE( AminusBS32toU32(MAX_S32,MIN_S32) == MAX_U32);
    TEST_ASSERT_TRUE( AminusBS32toU32(MIN_S32,MAX_S32) == 0);

    // Some random inputs.
    for(c = 0; c < 200; c++)
    {
        a = randS32(); b = randS32();
        res = AminusBS32toU32(a,b);

        chk = a > b ? ClipU64toU32((U64)((S64)a - (S64)b)) : 0;

        if( chk != res )
        {
            printf("AminusBS32toU32() failed: %ld - %ld -> %lu expected %ld\r\n", a, b, res, chk);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------ test_AbsS16 ----------------------------------------- */

void test_AbsS16(void)
{
    TEST_ASSERT_TRUE(AbsS16(0) == 0);
    TEST_ASSERT_TRUE(AbsS16(-1) == 1);
    TEST_ASSERT_TRUE(AbsS16(-3214) == 3214);
    TEST_ASSERT_TRUE(AbsS16(768) == 768);
    TEST_ASSERT_TRUE(AbsS16(MAX_S16) == MAX_S16);
    TEST_ASSERT_TRUE(AbsS16(MIN_S16) == MAX_S16);
}

/* ------------------------------ test_AbsS32 ----------------------------------------- */

void test_AbsS32(void)
{
    TEST_ASSERT_TRUE(AbsS32(0) == 0);
    TEST_ASSERT_TRUE(AbsS32(-1) == 1);
    TEST_ASSERT_TRUE(AbsS32(-3214) == 3214);
    TEST_ASSERT_TRUE(AbsS32(768) == 768);
    TEST_ASSERT_TRUE(AbsS32(MAX_S16) == MAX_S16);
    TEST_ASSERT_TRUE(AbsS32(MIN_S16) == MAX_S16+1);
    TEST_ASSERT_TRUE(AbsS32(MAX_S32) == MAX_S32);
    TEST_ASSERT_TRUE(AbsS32(MIN_S32) == MAX_S32);
}

/* ---------------------------------- test_AbsDiffU8 ----------------------------------- */

void test_AbsDiffU8(void)
{
    TEST_ASSERT_TRUE(AbsDiffU8(10,10) == 0);
    TEST_ASSERT_TRUE(AbsDiffU8(10,1) == 9);
    TEST_ASSERT_TRUE(AbsDiffU8(1,10) == 9);
    TEST_ASSERT_TRUE(AbsDiffU8(MAX_U8,0) == MAX_U8);
    TEST_ASSERT_TRUE(AbsDiffU8(0,MAX_U8) == MAX_U8);
    TEST_ASSERT_TRUE(AbsDiffU8(0,0) == 0);
    TEST_ASSERT_TRUE(AbsDiffU8(MAX_U8,MAX_U8) == 0);
    TEST_ASSERT_TRUE(AbsDiffU8(MAX_U8,MAX_U8-1) == 1);
    TEST_ASSERT_TRUE(AbsDiffU8(MAX_U8-1,MAX_U8) == 1);
}


/* ---------------------------------- test_AbsDiffU16 ----------------------------------- */

void test_AbsDiffU16(void)
{
    TEST_ASSERT_TRUE(AbsDiffU16(4999,4000) == 999);
    TEST_ASSERT_TRUE(AbsDiffU16(10,1) == 9);
    TEST_ASSERT_TRUE(AbsDiffU16(1,10) == 9);
    TEST_ASSERT_TRUE(AbsDiffU16(MAX_U16,0) == MAX_U16);
    TEST_ASSERT_TRUE(AbsDiffU16(0,MAX_U16) == MAX_U16);
    TEST_ASSERT_TRUE(AbsDiffU16(0,0) == 0);
    TEST_ASSERT_TRUE(AbsDiffU16(MAX_U16,MAX_U16) == 0);
    TEST_ASSERT_TRUE(AbsDiffU16(MAX_U16,MAX_U16-1) == 1);
    TEST_ASSERT_TRUE(AbsDiffU16(MAX_U16-1,MAX_U16) == 1);
}

/* ---------------------------------- test_AbsDiffS16 ----------------------------------- */

void test_AbsDiffS16(void)
{
    // The 4 quadrants
    TEST_ASSERT_TRUE(AbsDiffS16(4999,4000) == 999);
    TEST_ASSERT_TRUE(AbsDiffS16(-4999,4000) == 8999);
    TEST_ASSERT_TRUE(AbsDiffS16(4999,-4000) == 8999);
    TEST_ASSERT_TRUE(AbsDiffS16(-4999,-4000) == 999);

    // Byte-sized args
    TEST_ASSERT_TRUE(AbsDiffS16(10,1) == 9);
    TEST_ASSERT_TRUE(AbsDiffS16(1,10) == 9);
    TEST_ASSERT_TRUE(AbsDiffS16(-10,1) == 11);
    TEST_ASSERT_TRUE(AbsDiffS16(1,-10) == 11);
    TEST_ASSERT_TRUE(AbsDiffS16(-1,-10) == 9);

    TEST_ASSERT_TRUE(AbsDiffS16(MAX_S16,0) == MAX_S16);
    TEST_ASSERT_TRUE(AbsDiffS16(0,MAX_S16) == MAX_S16);
    TEST_ASSERT_TRUE(AbsDiffS16(MIN_S16,0) == ABS(MIN_S16));
    TEST_ASSERT_TRUE(AbsDiffS16(0,MIN_S16) == ABS(MIN_S16));

    // Differences must span full range of unsigned. (Tests correct promotion.)
    TEST_ASSERT_TRUE(AbsDiffS16(MAX_S16,MIN_S16) == MAX_U16);
    TEST_ASSERT_TRUE(AbsDiffS16(MIN_S16,MAX_S16) == MAX_U16);

    TEST_ASSERT_TRUE(AbsDiffS16(0,0) == 0);
    TEST_ASSERT_TRUE(AbsDiffS16(MAX_S16,MAX_S16) == 0);
    TEST_ASSERT_TRUE(AbsDiffS16(MIN_S16,MIN_S16) == 0);

    TEST_ASSERT_TRUE(AbsDiffS16(MAX_S16,MAX_S16-1) == 1);
    TEST_ASSERT_TRUE(AbsDiffS16(MAX_S16-1,MAX_S16) == 1);
}


/* ---------------------------------- test_AbsDiffU32 ----------------------------------- */

void test_AbsDiffU32(void)
{
    TEST_ASSERT_TRUE(AbsDiffU32(10,10) == 0);
    TEST_ASSERT_TRUE(AbsDiffU32(10,1) == 9);
    TEST_ASSERT_TRUE(AbsDiffU32(1,10) == 9);
    TEST_ASSERT_TRUE(AbsDiffU32(MAX_U32,0) == MAX_U32);
    TEST_ASSERT_TRUE(AbsDiffU32(0,MAX_U32) == MAX_U32);
    TEST_ASSERT_TRUE(AbsDiffU32(0,0) == 0);
    TEST_ASSERT_TRUE(AbsDiffU32(MAX_U32,MAX_U32) == 0);
    TEST_ASSERT_TRUE(AbsDiffU32(MAX_U32,MAX_U32-1) == 1);
    TEST_ASSERT_TRUE(AbsDiffU32(MAX_U32-1,MAX_U32) == 1);
}

/* --------------------------------- test_MinusS32 --------------------------------------*/

void test_MinusS32(void)
{
    TEST_ASSERT_TRUE(MAX_S32 + MIN_S32 == -1);

    TEST_ASSERT_TRUE( MinusS32(MAX_S32)  == -MAX_S32);
    TEST_ASSERT_TRUE( MinusS32(MIN_S32)   == MAX_S32);
    TEST_ASSERT_TRUE( MinusS32(MIN_S32+1) == MAX_S32);
    TEST_ASSERT_TRUE( MinusS32(0) == 0);
    TEST_ASSERT_TRUE( MinusS32(1) == -1);
    TEST_ASSERT_TRUE( MinusS32(-1) == 1);
}

/* -------------------------------- test_Inside_U8 ------------------------------------- */

void test_Inside_U8(void)
{
    // Corners
    TEST_ASSERT_TRUE(Inside_U8(0,0,0) == FALSE);
    TEST_ASSERT_TRUE(Inside_U8(MAX_U8,MAX_U8,MAX_U8) == FALSE);

    // Crossed limits (min > max)
    TEST_ASSERT_TRUE(Inside_U8(33,MAX_U8,0) == FALSE);

    TEST_ASSERT_TRUE(Inside_U8(33,33,33) == FALSE);

    // One above or below
    TEST_ASSERT_TRUE(Inside_U8(29,28,30) == TRUE);

    // Must be between min & max
    TEST_ASSERT_TRUE(Inside_U8(29,29,30) == FALSE);
    TEST_ASSERT_TRUE(Inside_U8(29,28,29) == FALSE);

    TEST_ASSERT_TRUE(Inside_U8(100,50,200) == TRUE);
    TEST_ASSERT_TRUE(Inside_U8(0,50,200) == FALSE);
    TEST_ASSERT_TRUE(Inside_U8(220,50,200) == FALSE);
}


/* -------------------------------- test_Inside_U16 ------------------------------------- */

void test_Inside_U16(void)
{
    // Corners
    TEST_ASSERT_TRUE(Inside_U16(0,0,0) == FALSE);
    TEST_ASSERT_TRUE(Inside_U16(MAX_U16,MAX_U16,MAX_U16) == FALSE);

    // Crossed limits (min > max)
    TEST_ASSERT_TRUE(Inside_U16(33,MAX_U16,0) == FALSE);

    TEST_ASSERT_TRUE(Inside_U16(33,33,33) == FALSE);

    // One above or below
    TEST_ASSERT_TRUE(Inside_U16(29,28,30) == TRUE);

    // Must be between min & max
    TEST_ASSERT_TRUE(Inside_U16(29,29,30) == FALSE);
    TEST_ASSERT_TRUE(Inside_U16(29,28,29) == FALSE);

    TEST_ASSERT_TRUE(Inside_U16(100,50,200) == TRUE);
    TEST_ASSERT_TRUE(Inside_U16(0,50,200) == FALSE);
    TEST_ASSERT_TRUE(Inside_U16(220,50,200) == FALSE);
}


/* -------------------------------- test_InsideEq_S16 ------------------------------------- */

void test_InsideEq_S16(void)
{
    // Corners
    TEST_ASSERT_TRUE(InsideEq_S16(0,0,0) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_S16(MAX_S16,MAX_S16,MAX_S16) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_S16(MIN_S16,MIN_S16,MIN_S16) == TRUE);

    // Crossed limits (min > max)
    TEST_ASSERT_TRUE(InsideEq_S16(33,MAX_S16,0) == FALSE);

    TEST_ASSERT_TRUE(InsideEq_S16(33,33,33) == TRUE);

    // One above or below
    TEST_ASSERT_TRUE(InsideEq_S16(29,28,30) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_S16(-29,-30,-28) == TRUE);

    // May be at min or max
    TEST_ASSERT_TRUE(InsideEq_S16( 29,29,30) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_S16( 29,28,29) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_S16(-29,-29,-28) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_S16(-29,-30,-29) == TRUE);

    TEST_ASSERT_TRUE(InsideEq_S16(100,50,200) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_S16(0,50,200) == FALSE);
    TEST_ASSERT_TRUE(Inside_S16(220,50,200) == FALSE);
}

/* -------------------------------- test_Inside_S16 ------------------------------------- */

void test_Inside_S16(void)
{
    // Corners
    TEST_ASSERT_TRUE(Inside_S16(0,0,0) == FALSE);
    TEST_ASSERT_TRUE(Inside_S16(MAX_S16,MAX_S16,MAX_S16) == FALSE);
    TEST_ASSERT_TRUE(Inside_S16(MIN_S16,MIN_S16,MIN_S16) == FALSE);

    // Crossed limits (min > max)
    TEST_ASSERT_TRUE(Inside_S16(33,MAX_S16,0) == FALSE);

    TEST_ASSERT_TRUE(Inside_S16(33,33,33) == FALSE);

    // One above or below
    TEST_ASSERT_TRUE(Inside_S16(29,28,30) == TRUE);
    TEST_ASSERT_TRUE(Inside_S16(-29,-30,-28) == TRUE);

    // Must be between min & max
    TEST_ASSERT_TRUE(Inside_S16( 29,29,30) == FALSE);
    TEST_ASSERT_TRUE(Inside_S16( 29,28,29) == FALSE);
    TEST_ASSERT_TRUE(Inside_S16(-29,-29,-28) == FALSE);
    TEST_ASSERT_TRUE(Inside_S16(-29,-30,-29) == FALSE);

    TEST_ASSERT_TRUE(Inside_S16(100,50,200) == TRUE);
    TEST_ASSERT_TRUE(Inside_S16(0,50,200) == FALSE);
    TEST_ASSERT_TRUE(Inside_S16(220,50,200) == FALSE);
}

/* -------------------------------- test_InsideEq_U8 ------------------------------------- */

void test_InsideEq_U8(void)
{
    // Corners
    TEST_ASSERT_TRUE(InsideEq_U8(0,0,0) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_U8(MAX_U8,MAX_U8,MAX_U8) == TRUE);

    // Crossed limits (min > max)
    TEST_ASSERT_TRUE(InsideEq_U8(33,MAX_U8,0) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U8(MAX_U8,MAX_U8,0) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U8(0,MAX_U8,0) == FALSE);

    TEST_ASSERT_TRUE(InsideEq_U8(33,33,33) == TRUE);

    // One above or below
    TEST_ASSERT_TRUE(InsideEq_U8(29,29,30) == TRUE);

    // Must be between min & max
    TEST_ASSERT_TRUE(InsideEq_U8( 28,29,30) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U8( 30,28,29) == FALSE);

    TEST_ASSERT_TRUE(InsideEq_U8(100,50,200) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_U8(0,50,200) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U8(220,50,200) == FALSE);
}


/* -------------------------------- test_InsideEq_U16 ------------------------------------- */

void test_InsideEq_U16(void)
{
    // Corners
    TEST_ASSERT_TRUE(InsideEq_U16(0,0,0) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_U16(MAX_U16,MAX_U16,MAX_U16) == TRUE);

    // Crossed limits (min > max)
    TEST_ASSERT_TRUE(InsideEq_U16(33,MAX_U16,0) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U16(MAX_U16,MAX_U16,0) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U16(0,MAX_U16,0) == FALSE);

    TEST_ASSERT_TRUE(InsideEq_U16(33,33,33) == TRUE);

    // One above or below
    TEST_ASSERT_TRUE(InsideEq_U16(29,29,30) == TRUE);

    // Must be between min & max
    TEST_ASSERT_TRUE(InsideEq_U16( 28,29,30) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U16( 30,28,29) == FALSE);

    TEST_ASSERT_TRUE(InsideEq_U16(100,50,200) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_U16(0,50,200) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U16(220,50,200) == FALSE);
}


/* -------------------------------- test_InsideEq_U32 ------------------------------------- */

void test_InsideEq_U32(void)
{
    // Corners
    TEST_ASSERT_TRUE(InsideEq_U32(0,0,0) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_U32(MAX_U32,MAX_U32,MAX_U32) == TRUE);

    // Crossed limits (min > max)
    TEST_ASSERT_TRUE(InsideEq_U32(33,MAX_U32,0) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U32(MAX_U32,MAX_U32,0) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U32(0,MAX_U32,0) == FALSE);

    TEST_ASSERT_TRUE(InsideEq_U32(33,33,33) == TRUE);

    // One above or below
    TEST_ASSERT_TRUE(InsideEq_U32(29,29,30) == TRUE);

    // Must be between min & max
    TEST_ASSERT_TRUE(InsideEq_U32( 28,29,30) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U32( 30,28,29) == FALSE);

    TEST_ASSERT_TRUE(InsideEq_U32(100,50,200) == TRUE);
    TEST_ASSERT_TRUE(InsideEq_U32(0,50,200) == FALSE);
    TEST_ASSERT_TRUE(InsideEq_U32(220,50,200) == FALSE);
}



/* ------------------------------------ test_Mean2_U8 ------------------------------------ */

void test_Mean2_U8(void)
{
    U8 a, b, res;
    U16 c, chk;

    TEST_ASSERT_TRUE(Mean2_U8(0,0) == 0);
    TEST_ASSERT_TRUE(Mean2_U8(MAX_U8,MAX_U8) == MAX_U8);

    for(c = 0; c < 1000; c++)
    {
        a = randU8(); b = randU8();
        res = Mean2_U8(a,b);
        chk = (a + (U16)b) / 2;

        if(res != chk)
        {
            printf("Mean2_U8() failed: (%d,%d) -> %d expected %u\r\n", a,b,res,chk);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------------ test_Mean3_U8 ------------------------------------ */

void test_Mean3_U8(void)
{
    U8 a, b, d, res;
    U16 c, sum, chk;

    TEST_ASSERT_TRUE(Mean3_U8(0,0,0) == 0);
    TEST_ASSERT_TRUE(Mean3_U8(MAX_U8,MAX_U8,MAX_U8) == MAX_U8);

    for(c = 0; c < 1000; c++)
    {
        a = randU8(); b = randU8(); d = randU8();
        res = Mean3_U8(a,b,d);
        sum = (a + (U16)b + (U16)d);
        chk = sum / 3;

        if( (sum % 3 == 0 && res != chk) ||
            (sum % 3 != 0 && res != chk && res != chk+1) )
        {
            printf("Mean3_U8() failed: (%d,%d,%d) -> %d expected %u\r\n", a,b,d,res,chk);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------------ test_Mean4_U8 ------------------------------------ */

void test_Mean4_U8(void)
{
    U8 a, b, d, e, res;
    U16 c, sum, chk;

    TEST_ASSERT_TRUE(Mean4_U8(0,0,0,0) == 0);
    TEST_ASSERT_TRUE(Mean4_U8(MAX_U8,MAX_U8,MAX_U8,MAX_U8) == MAX_U8);


    for(c = 0; c < 1000; c++)
    {
        a = randU8(); b = randU8(); d = randU8(); e = randU8();
        res = Mean4_U8(a,b,d,e);
        sum = a + b + d + (U16)e;
        chk = sum / 4;

        if( (sum % 4 == 0 && res != chk) ||
            (sum % 4 != 0 && res != chk && res != chk+1) )
        {
            printf("Mean4_U8() failed: (%d,%d,%d %d) -> %d expected %u\r\n", a,b,d,e,res,chk);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}



/* ------------------------------- test_AmulBdivC_S16 --------------------------------- */

typedef struct { S16 a, b, c, returns; } S_AmulBdivC_S16Chk;

PRIVATE S_AmulBdivC_S16Chk AmulBdivC_S16Chks[] = {
    // a    b       c    return
    // --------------------------------

    // Div zero cases.
    {0,     0,      0,      0},
    {1,     0,      0,      0},
    {0,     1,      0,      0},
    {1,     1,      0,      MAX_S16},
    {-1,   -1,      0,      MAX_S16},
    {-1,   -1,      0,      MAX_S16},
    {-1,    1,      0,      MIN_S16},
    {1,    -1,      0,      MIN_S16},

    // Clipping & signs
    {500,    500,      1,      MAX_S16},
    {-500,  -500,      1,      MAX_S16},
    {-500,   500,      1,      MIN_S16},
    {500,   -500,      1,      MIN_S16},
    {500,    500,     -1,      MIN_S16},
    {-500,   500,     -1,      MAX_S16},

    // Mul zero
    {1004,   0,      835,      0},
    {0,      666,   2345,      0},
};

void test_AmulBdivC_S16(void)
{
    U8 c;
    S16 a, b, div, ret;
    S32 chk;

    // Check corner cases tabulated above
    for(c = 0; c < RECORDS_IN(AmulBdivC_S16Chks); c++)
        { TEST_ASSERT_TRUE( AmulBdivC_S16(AmulBdivC_S16Chks[c].a, AmulBdivC_S16Chks[c].b, AmulBdivC_S16Chks[c].c) == AmulBdivC_S16Chks[c].returns); }

    // Check 100 random numbers
    for( c = 0; c < 100; c++)
    {
        a = randS16(); b = randS16();
        div = randS16(); if(div == 0) {div = 1;}
        chk = (S32)a * b / div;

        ret = AmulBdivC_S16(a,b,div);

        if( (chk > MAX_S16 && ret != MAX_S16) ||
            (chk < MIN_S16 && ret != MIN_S16) ||
            (chk < MAX_S16 && chk > MIN_S16 && chk != ret) )
        {
            printf("test_AmulBdivC_S16() failed: (%d * %d / %d) expected %ld result %d\r\n",  a,b,div, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------- test_AmulBdivC_U16 --------------------------------- */

typedef struct { U16 a, b, c, returns; } S_AmulBdivC_U16Chk;

PRIVATE S_AmulBdivC_U16Chk AmulBdivC_U16Chks[] = {
    // a    b       c    return
    // --------------------------------

    // Div zero cases.
    {0,     0,      0,      0},
    {1,     0,      0,      0},
    {0,     1,      0,      0},
    {1,     1,      0,      MAX_U16},

    // Clipping
    {500,    500,      1,      MAX_U16},

    // Mul zero
    {1004,   0,      835,      0},
    {0,      666,   2345,      0},
};

void test_AmulBdivC_U16(void)
{
    U8 c;
    U16 a, b, div, ret;
    U32 chk;

    // Check corner cases tabulated above
    for(c = 0; c < RECORDS_IN(AmulBdivC_U16Chks); c++)
        { TEST_ASSERT_TRUE( AmulBdivC_U16(AmulBdivC_U16Chks[c].a, AmulBdivC_U16Chks[c].b, AmulBdivC_U16Chks[c].c) == AmulBdivC_U16Chks[c].returns); }

    // Check 100 random numbers
    for( c = 0; c < 100; c++)
    {
        a = randU16(); b = randU16();
        div = randU16(); if(div == 0) {div = 1;}
        chk = (U32)a * b / div;

        ret = AmulBdivC_U16(a,b,div);

        if( (chk > MAX_U16 && ret != MAX_U16) ||
            (chk <= MAX_U16 && chk != ret) )
        {
            printf("test_AmulBdivC_U16() failed: (%u * %u / %u) expected %lu result %u\r\n",  a,b,div, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------- test_AmulBdivC_U32 --------------------------------- */

typedef struct { U32 a, b, c, returns; } S_AmulBdivC_U32Chk;

PRIVATE S_AmulBdivC_U32Chk AmulBdivC_U32Chks[] = {
    // a    b       c    return
    // --------------------------------

    // Div zero cases.
    {0,     0,      0,      0},
    {1,     0,      0,      0},
    {0,     1,      0,      0},
    {1,     1,      0,      MAX_U32},

    // Clipping
    {500000,    500000,      1,      MAX_U32},

    // Mul zero
    {1004,   0,      835,      0},
    {0,      666,   2345,      0},
};

void test_AmulBdivC_U32(void)
{
    U8 c;
    U32 a, b, div, ret;
    U64 chk;

    // Check corner cases tabulated above
    for(c = 0; c < RECORDS_IN(AmulBdivC_U32Chks); c++)
        { TEST_ASSERT_TRUE( AmulBdivC_U32(AmulBdivC_U32Chks[c].a, AmulBdivC_U32Chks[c].b, AmulBdivC_U32Chks[c].c) == AmulBdivC_U32Chks[c].returns); }

    // Check 100 random numbers
    for( c = 0; c < 100; c++)
    {
        a = randU32(); b = randU32();
        div = randU32(); if(div == 0) {div = 1;}
        chk = (U64)a * b / div;

        ret = AmulBdivC_U32(a,b,div);

        if( (chk > MAX_U32 && ret != MAX_U32) ||
            (chk <= MAX_U32 && chk != ret) )
        {
            printf("test_AmulBdivC_U32() failed: (%lxh * %lxh / %lxh) expected %lxh result %lxh\r\n",  a,b,div, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------- test_AmulBdivC_U16_rnd --------------------------------- */

void test_AmulBdivC_U16_rnd(void)
{
    U8 c;
    U16 a, b, div, ret;
    U32 chk;

    // Check corner cases tabulated above
    for(c = 0; c < RECORDS_IN(AmulBdivC_U16Chks); c++)
        { TEST_ASSERT_TRUE( AmulBdivC_U16_rnd(AmulBdivC_U16Chks[c].a, AmulBdivC_U16Chks[c].b, AmulBdivC_U16Chks[c].c) == AmulBdivC_U16Chks[c].returns); }

    // Check 100 random numbers
    for( c = 0; c < 100; c++)
    {
        a = randU16(); b = randU16();
        div = randU16(); if(div == 0) {div = 1;}
        chk = ((U32)a * b + (div/2)) / div;

        ret = AmulBdivC_U16_rnd(a,b,div);

        if( (chk > MAX_U16 && ret != MAX_U16) ||
            (chk <= MAX_U16 && chk != ret) )
        {
            printf("test_AmulBdivC_U16() failed: (%u * %u / %u) expected %lu result %u\r\n",  a,b,div, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}



/* ------------------------------- test_AmulBdivC_S16_U8_U8 --------------------------------- */

typedef struct { S16 a; U8 b, c; S16 returns; } AmulBdivC_S16_U8_U8Chk;

PRIVATE AmulBdivC_S16_U8_U8Chk AmulBdivC_S16_U8_U8_Chks[] = {
    // a    b       c    return
    // --------------------------------

    // Div zero cases.
    {0,     0,      0,      0},
    {1,     0,      0,      0},
    {0,     1,      0,      0},
    {1,     1,      0,      MAX_S16},
    {-1,    1,      0,      MIN_S16},

    // Clipping & signs
    {500,    200,      1,      MAX_S16},
    {-500,   200,      1,      MIN_S16},

    // Mul zero
    {1004,   0,      72,     0},
    {0,      123,   16,      0},
};

void test_AmulBdivC_S16_U8_U8(void)
{
    U8 c;
    S16 a, ret;
    U8 b, div;
    S32 chk;

    // Check corner cases tabulated above
    for(c = 0; c < RECORDS_IN(AmulBdivC_S16_U8_U8_Chks); c++)
        { TEST_ASSERT_TRUE( AmulBdivC_S16_U8_U8(AmulBdivC_S16_U8_U8_Chks[c].a, AmulBdivC_S16_U8_U8_Chks[c].b, AmulBdivC_S16_U8_U8_Chks[c].c) == AmulBdivC_S16_U8_U8_Chks[c].returns); }

    // Check 100 random numbers
    for( c = 0; c < 100; c++)
    {
        a = randS16(); b = randU8();
        div = randU8(); if(div == 0) {div = 1;}
        chk = (S32)a * b / div;

        ret = AmulBdivC_S16_U8_U8(a,b,div);

        if( (chk > MAX_S16 && ret != MAX_S16) ||
            (chk < MIN_S16 && ret != MIN_S16) ||
            (chk < MAX_S16 && chk > MIN_S16 && chk != ret) )
        {
            printf("test_AmulBdivC_S16_U8_U8() failed: (%d * %d / %d) expected %ld result %d\r\n",  a,b,div, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}


/* ------------------------------- test_AmulBdivC_U8 --------------------------------- */

typedef struct { U8 a, b, c, returns; } test_AmulBdivC_U8Chk;

PRIVATE test_AmulBdivC_U8Chk test_AmulBdivC_U8_Chks[] = {
    // a    b       c    return
    // --------------------------------

    // Div zero cases.
    {0,     0,      0,      0},
    {1,     0,      0,      0},
    {0,     1,      0,      0},
    {1,     1,      0,      MAX_U8},

    // Clipping & signs
    {100,    100,      1,      MAX_U8},

    // Mul zero
    {23,   0,      72,     0},
    {0,    75,     16,      0},
};

void test_AmulBdivC_U8(void)
{
    U8 c;
    U8 a, b, div, ret;
    U16 chk;

    // Check corner cases tabulated above
    for(c = 0; c < RECORDS_IN(test_AmulBdivC_U8_Chks); c++)
        { TEST_ASSERT_TRUE( AmulBdivC_U8(test_AmulBdivC_U8_Chks[c].a, test_AmulBdivC_U8_Chks[c].b, test_AmulBdivC_U8_Chks[c].c) == test_AmulBdivC_U8_Chks[c].returns); }

    // Check 100 random numbers
    for( c = 0; c < 100; c++)
    {
        a = randU8(); b = randU8();
        div = randU8(); if(div == 0) {div = 1;}
        chk = (U16)a * b / div;

        ret = AmulBdivC_U8(a,b,div);

        if( (chk > MAX_U8 && ret != MAX_U8) ||
            (chk <= MAX_U8 && chk != ret) )
        {
            printf("test_AmulBdivC_U8() failed: (%d * %d / %d) expected %ld result %d\r\n",  a,b,div, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------- test_AmulBdivC_U8_rnd --------------------------------- */

void test_AmulBdivC_U8_rnd(void)
{
    U8 c;
    U8 a, b, div, ret;
    U16 chk;

    // Check corner cases tabulated above
    for(c = 0; c < RECORDS_IN(test_AmulBdivC_U8_Chks); c++)
        { TEST_ASSERT_TRUE( AmulBdivC_U8_rnd(test_AmulBdivC_U8_Chks[c].a, test_AmulBdivC_U8_Chks[c].b, test_AmulBdivC_U8_Chks[c].c) == test_AmulBdivC_U8_Chks[c].returns); }

    // Check 100 random numbers
    for( c = 0; c < 100; c++)
    {
        a = randU8(); b = randU8();
        div = randU8(); if(div == 0) {div = 1;}
        chk = (((U16)a * b) + (div/2)) / div;

        ret = AmulBdivC_U8_rnd(a,b,div);

        if( (chk > MAX_U8 && ret != MAX_U8) ||
            (chk <= MAX_U8 && chk != ret) )
        {
            printf("test_AmulBdivC_U8() failed: (%d * %d / %d) expected %ld result %d\r\n",  a,b,div, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------- test_AmulBdivC_S16_S8_S8 --------------------------------- */

typedef struct { S16 a; S8 b, c; S16 returns; } S_AmulBdivC_S16_S8_S8Chk;

PRIVATE S_AmulBdivC_S16_S8_S8Chk AmulBdivC_S16_S8_S8_Chks[] = {
    // a    b       c    return
    // --------------------------------

    // Div zero cases.
    {0,     0,      0,      0},
    {1,     0,      0,      0},
    {0,     1,      0,      0},
    {1,     1,      0,      MAX_S16},
    {-1,   -1,      0,      MAX_S16},
    {-1,   -1,      0,      MAX_S16},
    {-1,    1,      0,      MIN_S16},
    {1,    -1,      0,      MIN_S16},

    // Clipping & signs
    {500,    100,      1,      MAX_S16},
    {-500,  -100,      1,      MAX_S16},
    {-500,   100,      1,      MIN_S16},
    {500,   -100,      1,      MIN_S16},
    {500,    100,     -1,      MIN_S16},
    {-500,   100,     -1,      MAX_S16},

    // Mul zero
    {1004,   0,      83,      0},
    {0,      66,     19,      0},
};

void test_AmulBdivC_S16_S8_S8(void)
{
    U8 c;
    S16 a, ret;
    S8 b, div;
    S32 chk;

    // Check corner cases tabulated above
    for(c = 0; c < RECORDS_IN(AmulBdivC_S16_S8_S8_Chks); c++)
        { TEST_ASSERT_TRUE( AmulBdivC_S16_S8_S8(AmulBdivC_S16_S8_S8_Chks[c].a, AmulBdivC_S16_S8_S8_Chks[c].b, AmulBdivC_S16_S8_S8_Chks[c].c) == AmulBdivC_S16_S8_S8_Chks[c].returns); }

    // Check 100 random numbers
    for( c = 0; c < 100; c++)
    {
        a = randS16(); b = randS8();
        div = randS8(); if(div == 0) {div = 1;}
        chk = (S32)a * b / div;

        ret = AmulBdivC_S16_S8_S8(a,b,div);

        if( (chk > MAX_S16 && ret != MAX_S16) ||
            (chk < MIN_S16 && ret != MIN_S16) ||
            (chk < MAX_S16 && chk > MIN_S16 && chk != ret) )
        {
            printf("AmulBdivC_S16_S8_S8() failed: (%d * %d / %d) expected %ld result %d\r\n",  a,b,div, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* -------------------------------- test_DeadbandS16 ------------------------------------ */

void test_DeadbandS16(void)
{
   typedef struct {S16 in, lo, hi, out; } S_Tst;

   S_Tst const tsts[] = {
      // Zeros in -> zero out.
      {.in = 0,   .lo = 0,    .hi = 0,    .out = 0},

      // Deadband all the way up.
      {.in = 22,   .lo = MIN_S16,    .hi = MIN_S16,    .out =22},
      {.in = MIN_S16,   .lo = MIN_S16,    .hi = MIN_S16,    .out =MIN_S16},
      {.in = MIN_S16+1,   .lo = MIN_S16,    .hi = MIN_S16,    .out =MIN_S16+1},

      {.in = -18,   .lo = MAX_S16,    .hi = MAX_S16,    .out = -18},
      {.in = MAX_S16,   .lo = MAX_S16,    .hi = MAX_S16,    .out = MAX_S16},
      {.in = MAX_S16-1,   .lo = MAX_S16,    .hi = MAX_S16,    .out = MAX_S16-1},

      // Upside-down limits return 'in' unchanged.
      {.in = MAX_S16, .lo = 10,  .hi = -10,    .out = MAX_S16},
      {.in = MIN_S16, .lo = 10,  .hi = -10,    .out = MIN_S16},
      {.in = 0, .lo = 10,  .hi = -10,    .out = 0},

      // If 'in' at midpoint of dead-band then return 'hi.
      {.in = 0,   .lo = -10,  .hi = 10,    .out = 10},

      {.in = -11, .lo = -10,  .hi = 10,    .out = -11},
      {.in = -10, .lo = -10,  .hi = 10,    .out = -10},
      {.in = -9 , .lo = -10,  .hi = 10,    .out = -10},
      {.in = -8 , .lo = -10,  .hi = 10,    .out = -10},
      {.in = -2 , .lo = -10,  .hi = 10,    .out = -10},
      {.in = -1 , .lo = -10,  .hi = 10,    .out = -10},

      // If 'in' at midpoint of dead-band then return 'hi.
      {.in = 0,   .lo = -10,  .hi = 10,    .out = 10},

      {.in =  1,  .lo = -10,  .hi = 10,    .out = 10},
      {.in =  2,  .lo = -10,  .hi = 10,    .out = 10},
      {.in =  3,  .lo = -10,  .hi = 10,    .out = 10},
      {.in =  8,  .lo = -10,  .hi = 10,    .out = 10},
      {.in =  9,  .lo = -10,  .hi = 10,    .out = 10},
      {.in =  10, .lo = -10,  .hi = 10,    .out = 10},
      {.in =  11, .lo = -10,  .hi = 10,    .out = 11},

      // Deadbands at top and bottom of S16 range. i.e 'lo', 'hi' do not have to be oppositie sign.

      {.in = MAX_S16,     .lo = MAX_S16-3,    .hi = MAX_S16-1,    .out = MAX_S16},
      {.in = MAX_S16-1,   .lo = MAX_S16-3,    .hi = MAX_S16-1,    .out = MAX_S16-1},
      {.in = MAX_S16-2,   .lo = MAX_S16-3,    .hi = MAX_S16-1,    .out = MAX_S16-1},
      {.in = MAX_S16-3,   .lo = MAX_S16-3,    .hi = MAX_S16-1,    .out = MAX_S16-3},
      {.in = MAX_S16-4,   .lo = MAX_S16-3,    .hi = MAX_S16-1,    .out = MAX_S16-4},


      {.in = MIN_S16,       .lo = MIN_S16+1,    .hi = MIN_S16+3,    .out = MIN_S16},
      {.in = MIN_S16+1,     .lo = MIN_S16+1,    .hi = MIN_S16+3,  .out = MIN_S16+1},
      {.in = MIN_S16+2,     .lo = MIN_S16+1,    .hi = MIN_S16+3,  .out = MIN_S16+3},
      {.in = MIN_S16+3,     .lo = MIN_S16+1,    .hi = MIN_S16+3,  .out = MIN_S16+3},
      {.in = MIN_S16+4,     .lo = MIN_S16+1,    .hi = MIN_S16+3,  .out = MIN_S16+4},
   };

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      S16 ret = DeadbandS16(t->in, t->lo, t->hi);

      C8 b0[100];
      sprintf(b0, "DeabandS16() tst #%d failed:  in %d, [lo %d, hi %d] -> %d; expected %d", i, t->in, t->lo, t->hi, ret, t->out);
      TEST_ASSERT_TRUE_MESSAGE(t->out == ret, b0);
   }
}

/* ------------------------------- test_Median3_U8 ------------------------------------- */

typedef struct {U8 a, b, c, res;} S_Median3_U8_Chk;

PRIVATE S_Median3_U8_Chk const median3_U8_Chks[] = {
    {1,2,3, 2},
    {2,3,1, 2},
    {3,1,2, 2},
    {3,2,1, 2},
    {1,3,2, 2},
    {2,1,3, 2},

    {3,2,2, 2},
    {2,2,3, 2},
    {2,3,2, 2},

    {3,3,3, 3},

    {0,0,0, 0},
    {MAX_U8,MAX_U8,MAX_U8, MAX_U8},
    {MAX_U8,0,0, 0},
};

void test_Median3_U8(void)
{
    U8 i, res;

    for( i = 0; i < RECORDS_IN(median3_U8_Chks); i++ )
    {
        res = Median3_U8(median3_U8_Chks[i].a, median3_U8_Chks[i].b, median3_U8_Chks[i].c );

        if( res != median3_U8_Chks[i].res )
        {
            printf("Median3_U8() failed: %u %u %u -> expected %u got %u\r\n",
                median3_U8_Chks[i].a, median3_U8_Chks[i].b, median3_U8_Chks[i].c, median3_U8_Chks[i].res, res);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------- test_Span3_U8 ------------------------------------- */

typedef struct {U8 a, b, c, res; } S_Span3_U8_Chk;

PRIVATE S_Span3_U8_Chk const span3_U8_Chks[] = {
    {1,2,3, 2},
    {2,3,1, 2},
    {3,1,2, 2},
    {3,2,1, 2},
    {1,3,2, 2},
    {2,1,3, 2},

    {3,2,2, 1},
    {2,2,3, 1},
    {2,3,2, 1},

    {3,3,3, 0},

    {0,0,0, 0},
    {MAX_U8,MAX_U8,MAX_U8, 0},
    {MAX_U8,0,0, MAX_U8},
};

void test_Span3_U8(void)
{
    U8 i, res;

    for( i = 0; i < RECORDS_IN(span3_U8_Chks); i++ )
    {
        res = Span3_U8(span3_U8_Chks[i].a, span3_U8_Chks[i].b, span3_U8_Chks[i].c );

        if( res != span3_U8_Chks[i].res )
        {
            printf("Span3_U8() failed: %u %u %u -> expected %u got %u\r\n",
                span3_U8_Chks[i].a, span3_U8_Chks[i].b, span3_U8_Chks[i].c, span3_U8_Chks[i].res, res);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}


/* ------------------------------- test_Span4_U8 ------------------------------------- */

typedef struct {U8 a, b, c, d, res; } S_Span4_U8_Chk;

PRIVATE S_Span4_U8_Chk const span4_U8_Chks[] = {
    {1,2,3,4, 3},
    {1,2,4,3, 3},
    {1,4,2,3, 3},
    {4,1,2,3, 3},
    {3,1,2,4, 3},
    {3,1,4,2, 3},
    {3,4,1,2, 3},
    {4,3,1,2, 3},
    {2,3,1,4, 3},
    {2,3,4,1, 3},
    {2,4,3,1, 3},
    {4,2,3,1, 3},

    {1,2,3,4, 3},
    {1,4,3,2, 3},
    {3,4,1,2, 3},
    {3,2,1,4, 3},

    {3,3,3,3, 0},

    {0,0,0,0, 0},

    {MAX_U8,MAX_U8,MAX_U8,MAX_U8, 0},
    {MAX_U8,0,0,0, MAX_U8},
};

void test_Span4_U8(void)
{
    U8 i, res;

    for( i = 0; i < RECORDS_IN(span4_U8_Chks); i++ )
    {
        res = Span4_U8(span4_U8_Chks[i].a, span4_U8_Chks[i].b, span4_U8_Chks[i].c, span4_U8_Chks[i].d );

        if( res != span4_U8_Chks[i].res )
        {
            printf("Span4_U8() failed: %u %u %u %u -> expected %u got %u\r\n",
                span4_U8_Chks[i].a, span4_U8_Chks[i].b, span4_U8_Chks[i].c, span4_U8_Chks[i].d, span4_U8_Chks[i].res, res);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}


/* -------------------------------- test_SqU8 --------------------------------------- */

void test_SqU8(void)
{
    U8 n;

    TEST_ASSERT_TRUE(SqU8(0) == 0);
    TEST_ASSERT_TRUE(SqU8(MAX_U8) == MAX_U8 * (U16)MAX_U8);
    n = randU8();
    TEST_ASSERT_TRUE(SqU8(n) == n * (U16)n);
}

/* -------------------------------- test_SqU16 --------------------------------------- */

void test_SqU16(void)
{
    U16 n;

    TEST_ASSERT_TRUE(SqU16(0) == 0);
    TEST_ASSERT_TRUE(SqU16(MAX_U16) == MAX_U16 * (U32)MAX_U16);
    n = randU16();
    TEST_ASSERT_TRUE(SqU16(n) == n * (U32)n);
}

/* -------------------------------- test_SqS16 --------------------------------------- */

void test_SqS16(void)
{
    S16 n;

    TEST_ASSERT_TRUE(SqS16(0) == 0);
    TEST_ASSERT_TRUE(SqS16(MAX_S16) == MAX_S16 * (S32)MAX_S16);
    TEST_ASSERT_TRUE(SqS16(MIN_S16) == MIN_S16 * (S32)MIN_S16);
    n = randS16();
    TEST_ASSERT_TRUE(SqS16(n) == n * (S32)n);
}


/* -------------------------------- test_MixU8 ----------------------------------------- */

void test_MixU8(void)
{
    U8 c, a, b, m, res;
    float chk, maxDNL;

    #define _MixU8Float(a,b,m) \
        (( (MAX_U8-(float)(m))*a  +  (float)m*b + (MAX_U8/2) + ((float)(a)/2) + ((float)(b)/2)) / 256.0)

    // Corner cases. Must nail these.
    TEST_ASSERT_TRUE(MixU8(0,0,0) == 0);
    TEST_ASSERT_TRUE(MixU8(MAX_U8,MAX_U8,MAX_U8) == MAX_U8);

    TEST_ASSERT_TRUE(MixU8(0,0,MAX_U8) == 0);
    TEST_ASSERT_TRUE(MixU8(MAX_U8,MAX_U8,0) == MAX_U8);

    TEST_ASSERT_TRUE(MixU8(0,MAX_U8,0) == 0);
    TEST_ASSERT_TRUE(MixU8(MAX_U8,0,MAX_U8) == 0);

    TEST_ASSERT_TRUE(MixU8(MAX_U8,0,0) == MAX_U8);
    TEST_ASSERT_TRUE(MixU8(0,MAX_U8,MAX_U8) == MAX_U8);

    // Try random points.
    maxDNL = 1.0;

    for(c = 0; c < 100; c++)
    {
        a = randU8(); b = randU8(); m = randU8();
        res = MixU8(a,b,m);
        chk = _MixU8Float(a,b,m);

        if(res > chk+maxDNL || res < chk-maxDNL)
        {
            printf("MixU8() failed: (%d %d %d) -> %d lims = %4.2f %4.2f\r\n", a,b,m,res, chk+maxDNL, chk-maxDNL);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

}


/* -------------------------------- test_MixU16 ----------------------------------------- */

void test_MixU16(void)
{
    U8 m;
    U16 c, a, b, res;
    float chk, maxErr;
    double errSum;

    #define _MixU16Float(a,b,m) \
        (( (MAX_U8-(float)(m))*a  +  (float)m*b + (MAX_U16/2) + ((float)(a)/2) + ((float)(b)/2)) / 256.0)

    // Corner cases. Must nail these.
    TEST_ASSERT_TRUE(MixU16(0,0,0) == 0);
    TEST_ASSERT_TRUE(MixU16(MAX_U16,MAX_U16,MAX_U8) == MAX_U16);

    TEST_ASSERT_TRUE(MixU16(0,0,MAX_U8) == 0);
    TEST_ASSERT_TRUE(MixU16(MAX_U16,MAX_U16,0) == MAX_U16);

    TEST_ASSERT_TRUE(MixU16(0,MAX_U16,0) == 0);
    TEST_ASSERT_TRUE(MixU16(MAX_U16,0,MAX_U8) == 0);

    TEST_ASSERT_TRUE(MixU16(MAX_U16,0,0) == MAX_U16);
    TEST_ASSERT_TRUE(MixU16(0,MAX_U16,MAX_U8) == MAX_U16);

    // Try random points.
    maxErr = 300;

    for(c = 0, errSum = 0.0; c < 10000; c++)
    {
        a = randU16(); b = randU16(); m = randU8();
        res = MixU16(a,b,m);
        chk = _MixU16Float(a,b,m);

        errSum += (res > chk ? (res-chk) : (chk-res));

        if(res > chk+maxErr || res < chk-maxErr)
        {
            printf("MixU16() failed: (%d %d %d) -> %d lims = %4.2f %4.2f\r\n", a,b,m,res, chk+maxErr, chk-maxErr);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
    //printf("Avg err %4.3f%%\r\n", 100.9*errSum/c/MAX_U16);
}


/* --------------------------------- test_DecrU8_NowZero ------------------------------------- */

void test_DecrU8_NowZero(void)
{
    U8 n, p; BIT res;
    n = MAX_U8;
    res = DecrU8_NowZero(&n);
    TEST_ASSERT_TRUE(n == MAX_U8-1 && res == 0);

    n = randU8();
    n = n <= 1 ? n+2 : n;           // 2..MAX_U8.
    p = n;
    res = DecrU8_NowZero(&n);
    TEST_ASSERT_TRUE(n == p-1 && res == 0);

    n = 1;
    res = DecrU8_NowZero(&n);
    TEST_ASSERT_TRUE(n == 0 && res == 1);

    n = 0;
    res = DecrU8_NowZero(&n);
    TEST_ASSERT_TRUE(n == 0 && res == 1);
}

/* --------------------------------- test_DecrU8_Was1_NowZero ------------------------------------- */

void test_DecrU8_Was1_NowZero(void)
{
    U8 n, p; BIT res;
    n = MAX_U8;
    res = DecrU8_Was1_NowZero(&n);
    TEST_ASSERT_TRUE(n == MAX_U8-1 && res == 0);

    n = randU8();
    n = n <= 1 ? n+2 : n;           // 2..MAX_U8.
    p = n;
    res = DecrU8_Was1_NowZero(&n);
    TEST_ASSERT_TRUE(n == p-1 && res == 0);

    n = 1;
    res = DecrU8_Was1_NowZero(&n);
    TEST_ASSERT_TRUE(n == 0 && res == 1);

    n = 0;
    res = DecrU8_Was1_NowZero(&n);
    TEST_ASSERT_TRUE(n == 0 && res == 0);
}

/* ------------------------------ test_RankU8_UpTo8 --------------------------------------- */

typedef struct {
    U8 buf[8],
       size,
       rank,
       chk;
} S_RankU8_UpTo8_Chk;

PRIVATE S_RankU8_UpTo8_Chk const rankU8_UpTo8_Chks[] = {

    //  Buffer             size  rank  result
    // ---------------------------------------

    // 'Illegal' parms must be handled gracefully
    // Zero buffer size always returns zero; regardless of buffer or rank.
    { {0,0,0,0,0,0,0,0},    0,    0,    0},
    { {3,3,3,3,3,3,3,3},    0,    0,    0},
    { {3,3,3,3,3,3,3,3},    0,    5,    0},

    // A buffer with just one member
    { {3,0,0,0,0,0,0,0},    1,    0,    3},

    // Rank must be clipped to within buffer.
    { {3,0,0,0,0,0,0,0},    1,    1,    3},     //
    { {3,0,0,0,0,0,0,0},    1,  MAX_U8, 3},     //

    { {3,4,5,2,1,0,0,0},    5,    0,    5},
    { {3,4,5,2,1,0,0,0},    5,    1,    4},

    { {3,4,5,2,1,8,6,7},    8,    0,    8},
    { {3,7,5,2,1,8,6,4},    8,    1,    7},
    { {3,5,2,1,8,6,4,7},    8,    2,    6},
    { {3,2,1,8,6,4,7,5},    8,    3,    5},
    { {3,2,1,8,6,7,5,4},    8,    4,    4},
    { {2,1,8,6,7,5,4,3},    8,    5,    3},
    { {2,5,1,8,6,7,4,3},    8,    6,    2},
    { {2,5,8,6,7,1,4,3},    8,    7,    1},

    // Ranks exceeding buffer size must be clipped to within buffer.
    { {2,8,6,7,5,1,4,3},    8,    8,    1},
    { {2,8,6,7,5,1,4,3},    8, MAX_U8,  1},

    // With some values equal
    { {1,1,2,2,2,3,3,3},    8,    0,    3},
    { {1,1,2,2,2,3,3,3},    8,    1,    3},
    { {1,1,2,2,2,3,3,3},    8,    2,    3},
    { {1,1,2,2,2,3,3,3},    8,    3,    2},
    { {1,1,2,2,2,3,3,3},    8,    4,    2},
    { {1,1,2,2,2,3,3,3},    8,    5,    2},
    { {1,1,2,2,2,3,3,3},    8,    6,    1},
    { {1,1,2,2,2,3,3,3},    8,    7,    1},


    { {MAX_U8, MAX_U8-2, MAX_U8-1,0,0,0,0,0}, 3, 0,  MAX_U8},
    { {MAX_U8, MAX_U8-2, MAX_U8-1,0,0,0,0,0}, 3, 1,  MAX_U8-1},
    { {MAX_U8-1, MAX_U8-2, MAX_U8-1,0,0,0,0,0}, 3, 2,  MAX_U8-2},
};

PRIVATE void printU8s(U8 const *buf, U8 cnt)
{
    U8 c;
    for( c = 0; c < cnt; c++)
        { printf(" %d", buf[c]); }
}

void test_RankU8_UpTo8(void)
{
    U8 c, result;

    #define _chks rankU8_UpTo8_Chks

    for( c = 0; c < RECORDS_IN(rankU8_UpTo8_Chks); c++ )
    {
        result = RankU8_UpTo8(_chks[c].buf, _chks[c].size, _chks[c].rank);

        if( result != _chks[c].chk )
        {
            printf("RankU8_UpTo8() failed: (");
            printU8s(_chks[c].buf, _chks[c].size);
            printf(") %dth-> %d expected %d\r\n", _chks[c].rank, result, _chks[c].chk);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}


/* -------------------------------- test_IncrU8 --------------------------------- */

void test_IncrU8(void)
{
   typedef struct {U8 in; U8 rtn;} S_Tst;

   S_Tst const tsts[] = {
      {.in = 0,         .rtn = 1},
      {.in = 34,        .rtn = 35},
      {.in = MAX_U8-1,  .rtn = MAX_U8},
      {.in = MAX_U8,    .rtn = MAX_U8},
   };

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      U8 in[2];
      in[0] = t->in;
      in[1] = 0x5A;     // Prefill to check for output buffer overrange.

      U8 rtn = IncrU8(in);

      BOOL fail = FALSE;

      if(in[1] != 0x5A)
      {
         printf("IncrU8() failed: Outbuffer overrun");
         fail = TRUE;
      }
      if(in[0] != t->rtn || rtn != t->rtn)
      {
         printf("IncrU8() failed: expected %u+1->%u; got %u<-IncrcU8(%u<-)\r\n", t->in, t->rtn, rtn, in[0]);
         fail = TRUE;

      }
      TEST_ASSERT_TRUE(fail == FALSE);
   }
}

/* -------------------------------- test_IncrU16 --------------------------------- */

void test_IncrU16(void)
{
   typedef struct {U16 in; U16 rtn;} S_Tst;

   S_Tst const tsts[] = {
      {.in = 0,         .rtn = 1},
      {.in = 34,        .rtn = 35},
      {.in = MAX_U16-1,  .rtn = MAX_U16},
      {.in = MAX_U16,    .rtn = MAX_U16},
   };

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      U16 in[2];
      in[0] = t->in;
      in[1] = 0x5A5A;     // Prefill to check for output buffer overrange.

      U16 rtn = IncrU16(in);

      BOOL fail = FALSE;

      if(in[1] != 0x5A5A)
      {
         printf("IncrU16() failed: Outbuffer overrun");
         fail = TRUE;
      }
      if(in[0] != t->rtn || rtn != t->rtn)
      {
         printf("IncrU16() failed: expected %u+1->%u; got %u<-IncrcU16(%u<-)\r\n", t->in, t->rtn, rtn, in[0]);
         fail = TRUE;

      }
      TEST_ASSERT_TRUE(fail == FALSE);
   }
}

/* -------------------------------- test_IncrU32 --------------------------------- */

void test_IncrU32(void)
{
   typedef struct {U32 in; U32 rtn;} S_Tst;

   S_Tst const tsts[] = {
      {.in = 0,         .rtn = 1},
      {.in = 12345678,  .rtn = 12345679},
      {.in = MAX_U32-1, .rtn = MAX_U32},
      {.in = MAX_U32,   .rtn = MAX_U32},
   };

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      U32 in[2];
      in[0] = t->in;
      in[1] = 0x5A5A5A5A;     // Prefill to check for output buffer overrange.

      U32 rtn = IncrU32(in);

      BOOL fail = FALSE;

      if(in[1] != 0x5A5A5A5A)
      {
         printf("IncrU32() failed: Outbuffer overrun");
         fail = TRUE;
      }
      if(in[0] != t->rtn || rtn != t->rtn)
      {
         printf("IncrU32() failed: expected %lu+1->%lu; got %lu<-IncrcU32(%lu<-)\r\n", t->in, t->rtn, rtn, in[0]);
         fail = TRUE;

      }
      TEST_ASSERT_TRUE(fail == FALSE);
   }
}

/* ------------------------------------ test_AplusBS64 ------------------------------------ */

void test_AplusBS64(void)
{
   typedef struct {S64 a, b, rtn;} S_Tst;

   S_Tst const tsts[] = {
      {.a = 0,       .b = 0,        .rtn = 0},
      {.a = 1,       .b = 2,        .rtn = 3},
      {.a = 2,       .b = 1,        .rtn = 3},
      {.a = -1,      .b = -2,       .rtn = -3},
      {.a = -2,      .b = -1,       .rtn = -3},

      // Corner cases
      {.a = MAX_S64, .b = 0,        .rtn = MAX_S64},
      {.a = 0,       .b = MAX_S64,  .rtn = MAX_S64},
      {.a = MIN_S64, .b = 0,        .rtn = MIN_S64},
      {.a = 0,       .b = MIN_S64,  .rtn = MIN_S64},

      {.a = MAX_S64, .b = MIN_S64,  .rtn = -1},
      {.a = MIN_S64, .b = MAX_S64,  .rtn = -1},

      {.a = MAX_S64,   .b = MIN_S64+1, .rtn = 0},
      {.a = MIN_S64+1, .b = MAX_S64,   .rtn = 0},

      // Overrange is clipped.
      {.a = MAX_S64, .b = 1,        .rtn = MAX_S64},
      {.a = 1,       .b = MAX_S64,  .rtn = MAX_S64},
      {.a = MAX_S64, .b = MAX_S64,  .rtn = MAX_S64},

      {.a = MIN_S64, .b = -1,       .rtn = MIN_S64},
      {.a = -1,      .b = MIN_S64,  .rtn = MIN_S64},
      {.a = MIN_S64, .b = MIN_S64,  .rtn = MIN_S64},

      // Just inside overrange... is not cliped.
      {.a = MAX_S64-2,  .b = 1,           .rtn = MAX_S64-1},
      {.a = 1,          .b = MAX_S64-2,   .rtn = MAX_S64-1},
      {.a = MIN_S64+2,  .b = -1,          .rtn = MIN_S64+1},
      {.a = -1,         .b = MIN_S64+2,   .rtn = MIN_S64+1},
   };

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      S64 rtn = AplusBS64(t->a, t->b);

      if(rtn != t->rtn)
      {
         printf("AplusBS64() #%d failed: expected %lld + %lld -> %lld; got %lld\r\n", i, t->a, t->b, t->rtn, rtn);
         TEST_FAIL();
      }
   }

   // 200 tests random inputs.
   for(U8 i = 0; i < 200; i++)
   {
      S64 a = randS64(); S64 b = randS64();
      S64 rtn = AplusBS64(a,b);

      // Use double to check for overrange. Double is 48bit vs 64bit so will miss a few numbers
      // near the edge but OK for a test.
      S64 chkOverflow(S64 a, S64 b) {
         double sum = (double)a + (double)b;
         return
            sum >= (double)MAX_S64
               ? MAX_S64
               : (sum <= (double)MIN_S64
                  ? MIN_S64
                  : a+b );

      }

      S64 chk = chkOverflow(a,b);

      if( chk != rtn )
      {
         printf("AplusBS64() failed #%d: expected %llxh + %llxh -> %llxh; got %llxh\r\n", i, a, b, chk, rtn);
         TEST_ASSERT_TRUE(FALSE);
      }
   }
}

/* ------------------------------------ test_AminusBS64 ------------------------------------ */

void test_AminusBS64(void)
{
   typedef struct {S64 a, b, rtn;} S_Tst;

   S_Tst const tsts[] = {
      {.a = 0,       .b = 0,        .rtn = 0},
      {.a = 1,       .b = 2,        .rtn = -1},
      {.a = 2,       .b = 1,        .rtn = 1},
      {.a = -1,      .b = -2,       .rtn = 1},
      {.a = -2,      .b = -1,       .rtn = -1},

      // Corner cases
      {.a = MAX_S64, .b = 0,        .rtn = MAX_S64},
      {.a = 0,       .b = MAX_S64,  .rtn = -MAX_S64},
      {.a = MIN_S64, .b = 0,        .rtn = MIN_S64},
      // is clipped MAX_S64 = (-MIN_S64)-1
      {.a = 0,       .b = MIN_S64,  .rtn = MAX_S64},

      {.a = MAX_S64, .b = 1,        .rtn = MAX_S64-1},
      {.a = MIN_S64, .b = -1,       .rtn = MIN_S64+1},

      {.a = MAX_S64, .b = MAX_S64,  .rtn = 0},
      {.a = MIN_S64, .b = MIN_S64,  .rtn = 0},

      {.a = MAX_S64, .b = MIN_S64,  .rtn = MAX_S64},
      {.a = MIN_S64, .b = MAX_S64,  .rtn = MIN_S64},


      // Overrange is clipped.
      {.a = -1,      .b = MAX_S64,  .rtn = MIN_S64},
      {.a = -2,      .b = MAX_S64,  .rtn = MIN_S64},

      {.a = -1,      .b = MIN_S64,  .rtn = MAX_S64},

      // At or just inside overrange... is not cliped.
      {.a = 0,       .b = MAX_S64,   .rtn = MIN_S64+1},
      {.a = 0,       .b = MIN_S64+2, .rtn = MAX_S64-1},
      {.a = 0,       .b = MIN_S64+1, .rtn = MAX_S64},
   };

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      S64 rtn = AminusBS64(t->a, t->b);

      if(rtn != t->rtn)
      {
         printf("AminusBS64() #%d failed: expected %llxh + %llxh -> %llxh; got %llxh\r\n", i, t->a, t->b, t->rtn, rtn);
         TEST_FAIL();
      }
   }

   // 200 tests random inputs.
   for(U8 i = 0; i < 200; i++)
   {
      S64 a = randU64(); S64 b = randU64();
      S64 rtn = AminusBS64(a,b);

      // Use double to check for overrange. Double is 48bit vs 64bit so will miss a few numbers
      // near the edge but OK for a test.
      S64 chkOverflow(S64 a, S64 b) {
         double diff = (double)a - (double)b;
         return
            diff >= (double)MAX_S64
               ? MAX_S64
               : (diff <= (double)MIN_S64
                  ? MIN_S64
                  : a-b ); }

      S64 chk = chkOverflow(a,b);

      if( chk != rtn )
      {
         printf("AminusBS64() failed #%d: expected %llxh + %llxh -> %llxh; got %llxh\r\n", i, a, b, chk, rtn);
         TEST_ASSERT_TRUE(FALSE);
      }
   }
}

/* ------------------------------------ test_AplusBU64 ------------------------------------ */

void test_AplusBU64(void)
{
   typedef struct {U64 a, b, rtn;} S_Tst;

   S_Tst const tsts[] = {
      {.a = 0,       .b = 0,        .rtn = 0},
      {.a = 1,       .b = 2,        .rtn = 3},
      {.a = 2,       .b = 1,        .rtn = 3},

      // Corner cases
      {.a = MAX_U64, .b = 0,        .rtn = MAX_U64},
      {.a = 0,       .b = MAX_U64,  .rtn = MAX_U64},

      // Overrange is clipped.
      {.a = MAX_U64, .b = 1,        .rtn = MAX_U64},
      {.a = 1,       .b = MAX_U64,  .rtn = MAX_U64},
      {.a = MAX_S64, .b = MAX_U64,  .rtn = MAX_U64},

      // Just inside overrange... is not cliped.
      {.a = MAX_U64-2,  .b = 1,           .rtn = MAX_U64-1},
      {.a = 1,          .b = MAX_U64-2,   .rtn = MAX_U64-1},
   };

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      U64 rtn = AplusBU64(t->a, t->b);

      if(rtn != t->rtn)
      {
         printf("AplusBU64() #%d failed: expected %llxh + %llxh -> %llxh; got %llxh\r\n", i, t->a, t->b, t->rtn, rtn);
         TEST_FAIL();
      }
   }

   // 200 tests random inputs.
   for(U8 i = 0; i < 200; i++)
   {
      U64 a = randU64(); U64 b = randU64();
      U64 rtn = AplusBU64(a,b);

      // Use double to check for overrange. Double is 48bit vs 64bit so will miss a few numbers
      // near the edge but OK for a test.
      U64 chkOverflow(U64 a, U64 b) {
         double sum = (double)a + (double)b;
         return
            sum >= (double)MAX_U64
               ? MAX_U64
               : (sum <= (double)MIN_U64
                  ? MIN_U64
                  : a+b );

      }

      U64 chk = chkOverflow(a,b);

      if( chk != rtn )
      {
         printf("AplusBU64() failed #%d: expected %llxh + %llxh -> %llxh; got %llxh\r\n", i, a, b, chk, rtn);
         TEST_ASSERT_TRUE(FALSE);
      }
   }
}

/* ------------------------------------ test_AminusBU64 ------------------------------------ */

void test_AminusBU64(void)
{
   typedef struct {U64 a, b, rtn;} S_Tst;

   S_Tst const tsts[] = {
      {.a = 0,       .b = 0,        .rtn = 0},
      {.a = MAX_U64, .b = MAX_U64,  .rtn = 0},

      {.a = 2,       .b = 1,        .rtn = 1},
      {.a = MAX_U64, .b = 1,        .rtn = MAX_U64-1},
      {.a = MAX_U64, .b = 0,        .rtn = MAX_U64},


      // Overrange is clipped.
      {.a = 0,       .b = MAX_U64,  .rtn = 0},
      {.a = 1,       .b = 2,        .rtn = 0},
   };

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      U64 rtn = AminusBU64(t->a, t->b);

      if(rtn != t->rtn)
      {
         printf("AminusBU64() #%d failed: expected %llxh - %llxh -> %llxh; got %llxh\r\n", i, t->a, t->b, t->rtn, rtn);
         TEST_FAIL();
      }
   }

   // 200 tests random inputs.
   for(U8 i = 0; i < 200; i++)
   {
      U64 a = randU64(); U64 b = randU64();
      U64 rtn = AminusBU64(a,b);

      U64 chk = b > a ? 0 : a-b;

      if( chk != rtn )
      {
         printf("AminusBU64() failed #%d: expected %llxh - %llxh -> %llxh; got %llxh\r\n", i, a, b, chk, rtn);
         TEST_ASSERT_TRUE(FALSE);
      }
   }
}

/* ----------------------------------------test_ClipU64 --------------------------------------- */

void test_ClipU64(void)
{
    U8 c;
    U64 n, l, u, ret, chk;

    // If limits are crossed, returns the mean of upper and lower.
    #define _GoodClip(n,l,u)            \
        ((u) < (l))                     \
            ? ((u >> 1) + (l >> 1) )    \
            : ((n) < (l)                \
                ? (l)                   \
                : ((n) > (u)            \
                    ? (u)               \
                    : (n)))

    for( c = 0; c < 20; c++ )
    {
        n = randU64(); l = randU64(), u = randU64();
        ret =  ClipU64(n,l,u);
        chk = _GoodClip(n,l,u);

        if( ret != chk)
        {
            printf("ClipU64() failed n = %lld l = %lld u = %ld  expected %lld got %lld\r\n", n, l, u, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    #undef _GoodClip

    // Corner cases
    TEST_ASSERT_TRUE( ClipU64(0,0,0) == 0 );
    TEST_ASSERT_TRUE( ClipU64(MAX_U64, 0, MAX_U64) == MAX_U64 );
}

/* ------------------------------------ test_ClipS64 ------------------------------------- */

void test_ClipS64(void)
{
    U8 c;
    S64 n, l, u, ret, chk;

    #define _GoodClip(n,l,u)            \
        ((u) < (l))                     \
            ? ((u >> 1) + (l >> 1) )    \
            : ((n) < (l)                \
                ? (l)                   \
                : ((n) > (u)            \
                    ? (u)               \
                    : (n)))

    for( c = 0; c < 20; c++ )
    {
        n = randS64(); l = randS64(), u = randS64();
        ret =  ClipS64(n,l,u);
        chk = _GoodClip(n,l,u);

        if( ret != chk)
        {
            printf("ClipS64() failed n = %ld l = %ld u = %ld  expected %ld got %ld\r\n", n, l, u, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    #undef _GoodClip

    // Corner cases
    TEST_ASSERT_TRUE( ClipS64(0,0,0) == 0 );
    TEST_ASSERT_TRUE( ClipS64(MAX_S64, 0, MAX_S64) == MAX_S64 );
    TEST_ASSERT_TRUE( ClipS64(MIN_S64, MIN_S64, 0) == MIN_S64 );
}


// ----------------------------------------- eof --------------------------------------------
