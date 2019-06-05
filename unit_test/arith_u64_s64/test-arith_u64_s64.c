/* */
#define UNITY_SUPPORT_64

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

/* ------------------------------------ test_64bit_Limits ------------------------------------- */

void test_64bit_Limits(void)
{
    TEST_ASSERT_TRUE( MAX_S64 == LONG_LONG_MAX );
    TEST_ASSERT_TRUE( MIN_S64 == LONG_LONG_MIN );
    TEST_ASSERT_TRUE( MAX_U64 == ULONG_LONG_MAX );
}

/* ------------------------------------ test_AplusBS64 ------------------------------------- */

void test_AplusBS64(void)
{
    TEST_ASSERT_EQUAL_INT64(0, AplusBS64(0,0) );

    // Try some numbers
    S64 a, b;

    for(U8 i = 0; i < 20; i++)
    {
        a = randU16() * (S64)randS32();
        b = randU16() * (S64)randS32();
        TEST_ASSERT_TRUE( a + b == AplusBS64(a,b) );
    }

    // Overflow
    TEST_ASSERT_TRUE( MAX_S64 == AplusBS64(MAX_S64, 0) );
    TEST_ASSERT_TRUE( MAX_S64 == AplusBS64(MAX_S64, 1) );
    TEST_ASSERT_TRUE( MAX_S64 == AplusBS64(MAX_S64, MAX_S64) );

    // Underflow
    TEST_ASSERT_TRUE( MIN_S64 == AplusBS64(MIN_S64, 0) );
    TEST_ASSERT_TRUE( MIN_S64 == AplusBS64(MIN_S64, -1) );
    TEST_ASSERT_TRUE( MIN_S64 == AplusBS64(MIN_S64, MIN_S64) );
}


/* ------------------------------------ test_AminusBS64 ------------------------------------- */

void test_AminusBS64(void)
{
    TEST_ASSERT_EQUAL_INT64(0, AminusBS64(0,0) );

    // Try some numbers
    S64 a, b;

    for(U8 i = 0; i < 20; i++)
    {
        a = randU16() * (S64)randS32();
        b = randU16() * (S64)randS32();
        TEST_ASSERT_TRUE( a - b == AminusBS64(a,b) );
    }

    // Overflow
    TEST_ASSERT_TRUE( MAX_S64 == AminusBS64(MAX_S64, 0) );
    TEST_ASSERT_TRUE( MAX_S64 == AminusBS64(MAX_S64, -1) );
    TEST_ASSERT_TRUE( MAX_S64 == AminusBS64(MAX_S64, MIN_S64) );

    // Underflow
    TEST_ASSERT_TRUE( MIN_S64 == AminusBS64(MIN_S64, 0) );
    TEST_ASSERT_TRUE( MIN_S64 == AminusBS64(MIN_S64, 1) );
    TEST_ASSERT_TRUE( MIN_S64 == AminusBS64(MIN_S64, MAX_S64) );
}

/* ------------------------------------ test_AminusBU64 ------------------------------------- */

void test_AminusBU64(void)
{
    TEST_ASSERT_EQUAL_UINT64(0, AminusBU64(0,0) );

    // Try some numbers
    U64 a, b;

    for(U8 i = 0; i < 20; i++)
    {
        a = randU16() * (U64)randU32();
        b = randU16() * (U64)randU32();

        if(a > b)
            { TEST_ASSERT_TRUE( a - b == AminusBU64(a,b) ); }
        else
            { TEST_ASSERT_TRUE( b - a == AminusBU64(b,a) ); }
    }

    // Underflow
    TEST_ASSERT_TRUE( 0 == AminusBU64(0, 1) );
    TEST_ASSERT_TRUE( 0 == AminusBU64(MAX_U64, MAX_U64) );
    TEST_ASSERT_TRUE( 0 == AminusBU64 (0, MAX_U64) );
}

/* ------------------------------------ test_AplusBU64 ------------------------------------- */

void test_AplusBU64(void)
{
    TEST_ASSERT_EQUAL_UINT64(0, AplusBU64(0,0) );

    // Try some numbers
    U64 a, b;

    for(U8 i = 0; i < 20; i++)
    {
        a = randU16() * (U64)randU32();
        b = randU16() * (U64)randU32();

        TEST_ASSERT_TRUE( a + b == AplusBU64(a,b) );
    }

    // Overflow
    TEST_ASSERT_TRUE( MAX_U64 == AplusBU64(MAX_U64, 1) );
    TEST_ASSERT_TRUE( MAX_U64 == AplusBU64(1, MAX_U64) );
    TEST_ASSERT_TRUE( MAX_U64 == AplusBU64 (MAX_U64, MAX_U64) );
}

/* ------------------------------------ test_ClipU64 ------------------------------------- */

void test_ClipU64(void)
{
    TEST_ASSERT_TRUE( 0       == ClipU64(0, 0, 0) );
    TEST_ASSERT_TRUE( 0       == ClipU64(MAX_U64, 0, 0) );
    TEST_ASSERT_TRUE( MAX_U64 == ClipU64(0, MAX_U64, MAX_U64) );
    TEST_ASSERT_TRUE( 100     == ClipU64(200, 0, 100) );
    TEST_ASSERT_TRUE( 200     == ClipU64(200, 100, 300) );
    TEST_ASSERT_TRUE( 500     == ClipU64(10, 500, 1000) );

    // Try some numbers
    U64 a, b, c, d;

    for(U8 i = 0; i < 20; i++)
    {
        a = randU16() * (U64)randU32();
        b = a + randU16() * (U64)randU32();     // a > b

        c = randU16() * (U64)randU32();
        d = c > b ? b : (c < a ? a : c);        // d <- c, clipped.

        TEST_ASSERT_TRUE( d == ClipU64(c, a, b) );
    }

    // Crossed limits return mean of limits.
    TEST_ASSERT_TRUE( 750     == ClipU64(0, 1000, 500) );
}

/* ------------------------------------ test_ClipS64 ------------------------------------- */

void test_ClipS64(void)
{
    TEST_ASSERT_TRUE( 0       == ClipS64(0, 0, 0) );
    TEST_ASSERT_TRUE( 0       == ClipS64(MAX_S64, 0, 0) );
    TEST_ASSERT_TRUE( 0       == ClipS64(MIN_S64, 0, 0) );
    TEST_ASSERT_TRUE( MAX_S64 == ClipS64(0, MAX_S64, MAX_S64) );
    TEST_ASSERT_TRUE( MIN_S64 == ClipS64(0, MIN_S64, MIN_S64) );
    TEST_ASSERT_TRUE( 100     == ClipS64(200, 0, 100) );
    TEST_ASSERT_TRUE( 200     == ClipS64(200, 100, 300) );
    TEST_ASSERT_TRUE( 500     == ClipS64(10, 500, 1000) );

    // Try some numbers
    S64 a, b, c, d;

    for(U8 i = 0; i < 20; i++)
    {
        a = randS16() * (S64)randS32();
        b = a + randU16() * (S64)randU32();     // a > b

        c = randS16() * (S64)randS32();
        d = c > b ? b : (c < a ? a : c);        // d <- c, clipped.

        TEST_ASSERT_TRUE( d == ClipS64(c, a, b) );
    }

    // Crossed limits return mean of limits.
    TEST_ASSERT_TRUE( 750     == ClipS64(0, 1000, 500) );
    TEST_ASSERT_TRUE( -1     == ClipS64(MIN_S64, MAX_S64, MIN_S64) );
}

/* ------------------------------------ test_MaxS64 ------------------------------------- */

void test_MaxS64(void)
{
   TEST_ASSERT_TRUE( 0 == MaxS64(0, MIN_S64) );
   TEST_ASSERT_TRUE( 0 == MaxS64(MIN_S64, 0) );
   TEST_ASSERT_TRUE( MAX_S64 == MaxS64(0, MAX_S64) );
   TEST_ASSERT_TRUE( MAX_S64 == MaxS64(MAX_S64, 0) );
   TEST_ASSERT_TRUE( MAX_S64 == MaxS64(MAX_S64, MAX_S64) );
   TEST_ASSERT_TRUE( MIN_S64 == MaxS64(MIN_S64, MIN_S64) );
}

/* ------------------------------------ test_MaxU64 ------------------------------------- */

void test_MaxU64(void)
{
   TEST_ASSERT_TRUE( 0 == MaxU64(0, 0) );
   TEST_ASSERT_TRUE( MAX_U64 == MaxU64(0, MAX_U64) );
   TEST_ASSERT_TRUE( MAX_U64 == MaxU64(MAX_U64, 0) );
   TEST_ASSERT_TRUE( MAX_U64 == MaxU64(MAX_U64, MAX_U64) );
}

/* ------------------------------------ test_MinS64 ------------------------------------- */

void test_MinS64(void)
{
   TEST_ASSERT_TRUE( MIN_S64 == MinS64(0, MIN_S64) );
   TEST_ASSERT_TRUE( MIN_S64 == MinS64(MIN_S64, 0) );
   TEST_ASSERT_TRUE( 0 == MinS64(0, MAX_S64) );
   TEST_ASSERT_TRUE( 0 == MinS64(MAX_S64, 0) );
   TEST_ASSERT_TRUE( MAX_S64 == MinS64(MAX_S64, MAX_S64) );
   TEST_ASSERT_TRUE( MIN_S64 == MinS64(MIN_S64, MIN_S64) );
}

/* ------------------------------------ test_MinU64 ------------------------------------- */

void test_MinU64(void)
{
   TEST_ASSERT_TRUE( 0 == MinU64(0, 0) );
   TEST_ASSERT_TRUE( 0 == MinU64(0, MAX_U64) );
   TEST_ASSERT_TRUE( 0 == MinU64(MAX_U64, 0) );
   TEST_ASSERT_TRUE( MAX_U64 == MinU64(MAX_U64, MAX_U64) );
}

/* ------------------------------------ test_ClipU64toU32 ------------------------------------- */

void test_ClipU64toU32(void)
{
   TEST_ASSERT_TRUE( 0 == ClipU64toU32(0) );
   TEST_ASSERT_TRUE( MAX_U32 == ClipU64toU32(MAX_U32+1) );
   TEST_ASSERT_TRUE( MAX_U32 == ClipU64toU32(MAX_U32) );
   TEST_ASSERT_TRUE( MAX_U32-1 == ClipU64toU32(MAX_U32-1) );
   TEST_ASSERT_TRUE( MAX_U32 == ClipU64toU32(MAX_U64) );
}



 // ----------------------------------------- eof --------------------------------------------
