/* */

#include "unity.h"
#include "arith.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

// --------------------------- Support --------------------------------------------

PUBLIC U8  randU8(void)  { return (U8)((float)rand() * MAX_U8 / RAND_MAX); }
PUBLIC U16 randU16(void) { return (U16)((float)rand() * MAX_U16 / RAND_MAX); }
PUBLIC U32 randU32(void) { return (U32)((float)rand() * MAX_U32 / RAND_MAX); }
PUBLIC U64 randU64(void) { return (U64)((float)rand() * MAX_U64 / RAND_MAX); }

PUBLIC S8  randS8(void)  { return (S8)(  2.0 * ((float)rand() - (RAND_MAX/2)) * MAX_S8 / RAND_MAX); }
PUBLIC S16 randS16(void) { return (S16)( 2.0 * ((float)rand() - (RAND_MAX/2)) * MAX_S16 / RAND_MAX); }
PUBLIC S64 randS64(void) { return (S64)( 2.0 * ((float)rand() - (RAND_MAX/2)) * MAX_S64 / RAND_MAX); }


// =============================== Tests start here ==================================


/* -------------------------------------- setUp ------------------------------------------- */

void setUp(void) {
    srand(time(NULL));     // Random seed for scrambling stimuli
}

/* -------------------------------------- tearDown ------------------------------------------- */

void tearDown(void) {
}

/* -------------------------------------- test_SqrtU16 ------------------------------------------- */

void test_SqrtU16(void)
{
    U8 c;
    U16 n, r;

    // All exact roots must be correct.
    for(c = 0; c < MAX_U8; c++)
    {
        n = (U16)c * c;
        r = SqrtU16(n);

        if(r != c)
        {
            printf("SqrtU16() failed %u -> %u:\r\n", n, r);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // All (other) roots must binned for minmum DNL
    for(n = 0; n < MAX_U16; n++)
    {
        r = SqrtU16(n);

        if( (r == 0 && n != 0) ||                       // Sqrt(0) != 0?
            (
                r > 0 &&                                // for all n > 0
                (                                       // Fails minimum DNL? i.e.
                    n < (r-1) * r ||                    // n is binned too low?
                    n > ((r+1) * (r == 255 ? 256 : r))  // n binned too high? (there's no 1/2-bin above 255; that's the top)
                )
           ))
        {
            printf("SqrtU16() failed %u -> %u:\r\n", n, r);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* -------------------------------------- test_SqrtU32 ------------------------------------------- */

void test_SqrtU32(void)
{
    U32 c;
    U32 n, r;

    // All exact roots must be correct.
    for(c = 0; c < MAX_U16; c++)
    {
        n = (U32)c * c;
        r = SqrtU32(n);

        if(r != c)
        {
            printf("SqrtU32() failed %lu -> %u:\r\n", n, r);
            TEST_ASSERT_TRUE(FALSE);
        }
    }

    // Test a decent sample of inexact roots. Which must be binned for minimum DNL.
    for(c = 0; c < 100000; c++)
    {
        n = randU32();
        r = SqrtU32(n);

        if( (r == 0 && n != 0) ||                       // Sqrt(0) != 0?
            (
                r > 0 &&                                // for all n > 0
                (                                       // Fails minimum DNL? i.e.
                    n < (r-1) * r ||                    // n is binned too low? OR
                    (r != MAX_U16
                        ? (n > (r * (r+1)))             // 'n' binned too high?
                        : FALSE)                        // except if root is MAX_U16, when top bin goes all way to MAX_U32.
                )
           ))
        {
            printf("SqrtU32() failed %lu -> %u:\r\n", n, r);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------- test_RootSumSqU8 ------------------------------------ */

void test_RootSumSqU8(void)
{
    U16 c;
    U8 a,b,rss;
    float chk, tol;

    // Corner cases.
    TEST_ASSERT_TRUE( RootSumSqU8(0,0) == 0);
    TEST_ASSERT_TRUE( RootSumSqU8(MAX_U8,MAX_U8) == MAX_U8);

    // Must nail all exact roots on either side.
    for( c = 0; c < MAX_U8; c++)
    {
        TEST_ASSERT_TRUE(RootSumSqU8(c,0) == c);
        TEST_ASSERT_TRUE(RootSumSqU8(0,c) == c);
    }

    // Check a sample of others
    for( c = 0, tol = 1.0; c < 1000; c++ )
    {
        a = randU8(); b = randU8();
        rss = RootSumSqU8(a,b);
        chk = sqrt(a*(float)a + b*(float)b);

        if( (chk < 255.0 && (rss > chk+tol || rss < chk-tol)) ||
            (chk >= 255.0 && rss != MAX_U8) )                       // RSS >= MAX_U8, then result must be MAX_U8
        {
            printf("RootSumSqU8() failed: (%d,%d) -> %d  limits %4.2f %4.2f\r\n", a, b, rss, chk-tol, chk+tol);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ------------------------------- test_RootSumSqU16 ------------------------------------ */

void test_RootSumSqU16(void)
{
    U16 c,a,b,rss;
    float chk, tol;

    // Corner cases.
    TEST_ASSERT_TRUE( RootSumSqU16(0,0) == 0);
    TEST_ASSERT_TRUE( RootSumSqU16(MAX_U16,MAX_U16) == MAX_U16);

    // Must nail all exact roots on either side.
    for( c = 0; c < MAX_U16; c++)
    {
        TEST_ASSERT_TRUE(RootSumSqU16(c,0) == c);
        TEST_ASSERT_TRUE(RootSumSqU16(0,c) == c);
    }

    // Check a sample of others
    for( c = 0, tol = 1.0; c < 1000; c++ )
    {
        a = randU16(); b = randU16();
        rss = RootSumSqU16(a,b);
        chk = sqrt(a*(float)a + b*(float)b);

        if( (chk < 65535.0 && (rss > chk+tol || rss < chk-tol)) ||
            (chk >= 65535.0 && rss != MAX_U16) )                       // RSS >= MAX_U16, then result must be MAX_U16
        {
            printf("RootSumSqU16() failed: (%d,%d) -> %d  limits %4.2f %4.2f\r\n", a, b, rss, chk-tol, chk+tol);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}


/* ------------------------------- test_RootSumSqS16 ------------------------------------ */

void test_RootSumSqS16(void)
{
    U16 c, rss;
    S16 a,b;
    float chk, tol;

    // Corner cases.
    TEST_ASSERT_TRUE( RootSumSqS16(0,0) == 0);
    TEST_ASSERT_TRUE( RootSumSqS16(MAX_S16,MAX_S16) >= 46339 || RootSumSqS16(MAX_S16,MAX_S16) <= 46341 );  // sqrt(2 * 32768^2) = 46340.95
    TEST_ASSERT_TRUE( RootSumSqS16(MIN_S16,MIN_S16) >= 46339 || RootSumSqS16(MIN_S16,MIN_S16) <= 46341 );  // sqrt(2 * -32767^2) = 46339.54

    // Must nail all exact roots on either side.
    for( c = MIN_S16; c < MAX_S16; c++)
    {
        TEST_ASSERT_TRUE(RootSumSqS16(c,0) == c);
        TEST_ASSERT_TRUE(RootSumSqS16(0,c) == c);
    }

    // Check a sample of others
    for( c = 0, tol = 1.0; c < 1000; c++ )
    {
        a = randS16(); b = randS16();
        rss = RootSumSqS16(a,b);
        chk = sqrt(a*(float)a + b*(float)b);

        if( (chk < 65535.0 && (rss > chk+tol || rss < chk-tol)) ||
            (chk >= 65535.0 && rss != MAX_U16) )                       // RSS >= MAX_U16, then result must be MAX_U16
        {
            printf("RootSumSqS16() failed: (%d,%d) -> %d  limits %4.2f %4.2f\r\n", a, b, rss, chk-tol, chk+tol);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}


/* ------------------------------- test_SigmaSqU8 ------------------------------------ */

void test_SigmaSqU8(void)
{
    U8 c, ssq, prev;
    U16 accLo, accHi;
    float hiDivLo;

    // Must join at ends.
    TEST_ASSERT_TRUE(SigmaSqU8(0) == 0);
    TEST_ASSERT_TRUE(SigmaSqU8(MAX_U8) == MAX_U8);

    // Must pass through midpoint exactly.
    TEST_ASSERT_TRUE(SigmaSqU8(128) == 128);

    for(c = 0, accHi = 0, accLo = 0, prev = SigmaSqU8(0); c < MAX_U8; c++)
    {
        ssq = SigmaSqU8(c);

        // Must be monotonic.
        TEST_ASSERT_TRUE(ssq >= prev);
        prev = ssq;

        // Left of midpoint, must be below y=x; otherwise above.
        if(c < 128)
        {
            TEST_ASSERT_TRUE(ssq <= c);
            accLo += (c - ssq);
        }
        else
        {
            TEST_ASSERT_TRUE(ssq >= c);
            accHi += (ssq - c);
        }
    }

    // Must be symmetric within 2%.
    hiDivLo = (float)accHi/accLo;
    TEST_ASSERT_TRUE(hiDivLo > 0.95);
    TEST_ASSERT_TRUE(hiDivLo < 1.05);

    // Otherwise we rely on the function body as written.
    // If it also passes the above tests, then it must be what we intend.
}


// ----------------------------------------- eof --------------------------------------------
