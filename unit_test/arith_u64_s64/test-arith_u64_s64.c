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
   TEST_ASSERT_TRUE( MAX_U32 == ClipU64toU32((U64)MAX_U32+1) );
   TEST_ASSERT_TRUE( MAX_U32 == ClipU64toU32(MAX_U32) );
   TEST_ASSERT_TRUE( MAX_U32-1 == ClipU64toU32(MAX_U32-1) );
   TEST_ASSERT_TRUE( MAX_U32 == ClipU64toU32(MAX_U64) );
}

/* ------------------------------------ test_ClipS64toU32 ------------------------------------- */

void test_ClipS64toU32(void)
{
   TEST_ASSERT_TRUE( MAX_U32 == ClipS64toU32((S64)MAX_U32+1) );
   TEST_ASSERT_TRUE( MAX_U32 == ClipS64toU32(MAX_U32) );
   TEST_ASSERT_TRUE( MAX_U32-1 == ClipS64toU32(MAX_U32-1) );
   TEST_ASSERT_TRUE( MAX_U32 == ClipS64toU32(MAX_S64) );

   TEST_ASSERT_TRUE( 0 == ClipS64toU32(0) );
   TEST_ASSERT_TRUE( 0 == ClipS64toU32(-1) );
   TEST_ASSERT_TRUE( 1 == ClipS64toU32(1) );
   TEST_ASSERT_TRUE( 0 == ClipS64toU32(MIN_S64) );
}

/* ------------------------------------ test_ClipS64toS32 ------------------------------------- */

void test_ClipS64toS32(void)
{
   TEST_ASSERT_TRUE( 0 == ClipS64toS32(0) );

   TEST_ASSERT_TRUE( MAX_S32 == ClipS64toS32((S64)MAX_S32+1) );
   TEST_ASSERT_TRUE( MAX_S32 == ClipS64toS32(MAX_S32) );
   TEST_ASSERT_TRUE( MAX_S32-1 == ClipS64toS32(MAX_S32-1) );
   TEST_ASSERT_TRUE( MAX_S32 == ClipS64toS32(MAX_S64) );

   TEST_ASSERT_TRUE( MIN_S32 == ClipS64toS32((S64)MIN_S32-1) );
   TEST_ASSERT_TRUE( MIN_S32 == ClipS64toS32(MIN_S32) );
   TEST_ASSERT_TRUE( MIN_S32+1 == ClipS64toS32(MIN_S32+1) );
   TEST_ASSERT_TRUE( MIN_S32 == ClipS64toS32(MIN_S64) );
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

    // Check corner cases tabulated above
    for(c = 0; c < RECORDS_IN(AmulBdivC_U32Chks); c++) {
         S_AmulBdivC_U32Chk const *ck = &AmulBdivC_U32Chks[c];

         if( (ret = AmulBdivC_U32(ck->a, ck->b, ck->c)) != ck->returns) {
            printf("test_AmulBdivC_U32() #%d failed: (%u * %u / %u) expected %lu result %u\r\n",  c, ck->a, ck->b, ck->c, ck->returns, ret);
            TEST_ASSERT_TRUE(FALSE);
         }
    }

    U64 chk;

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
            printf("test_AmulBdivC_U32() failed: (%u * %u / %u) expected %lu result %u\r\n",  a,b,div, chk, ret);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
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



 // ----------------------------------------- eof --------------------------------------------
