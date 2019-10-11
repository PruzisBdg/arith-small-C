/* */

#include "unity.h"
#include "arith.h"
#include <stdlib.h>
#include <time.h>
#include "tdd_common.h"
#include <limits.h>
#include <float.h>

// =============================== Tests start here ==================================


/* -------------------------------------- setUp ------------------------------------------- */

void setUp(void) {
    srand(time(NULL));     // Random seed for scrambling stimuli
}

/* -------------------------------------- tearDown ------------------------------------------- */

void tearDown(void) {
}

/* ------------------------------------- test_FloatsEqual -------------------------------------- */

void test_FloatsEqual(void)
{
   TEST_ASSERT_EQUAL_UINT8( TRUE, FloatsEqual(0.0, 0.0, 0.0) );
   TEST_ASSERT_EQUAL_UINT8( TRUE, FloatsEqual(FLT_MIN, FLT_MIN, 0.0) );
   TEST_ASSERT_EQUAL_UINT8( TRUE, FloatsEqual(FLT_MAX, FLT_MAX, 0.0) );

   TEST_ASSERT_EQUAL_UINT8( TRUE, FloatsEqual(0.0, 0.0, 0.001) );

   TEST_ASSERT_EQUAL_UINT8( FALSE, FloatsEqual(0.1, 0.0, 0.0) );
   TEST_ASSERT_EQUAL_UINT8( FALSE, FloatsEqual(0.0, 1E-10, 0.0) );

   TEST_ASSERT_EQUAL_UINT8( FALSE, FloatsEqual(0.0, 1E-10, 2.E-10) );
   TEST_ASSERT_EQUAL_UINT8( FALSE, FloatsEqual(0.0, 1E-10, 9E-11) );

   TEST_ASSERT_EQUAL_UINT8( TRUE,  FloatsEqual(1E-10, 1E-10, 0.0) );

   TEST_ASSERT_EQUAL_UINT8( FALSE, FloatsEqual(1.0, 1.000001, 4E-7) );
   TEST_ASSERT_EQUAL_UINT8( TRUE,  FloatsEqual(1.0, 1.000001, 5.1E-7) );

   TEST_ASSERT_EQUAL_UINT8( FALSE,  FloatsEqual(100000.0, 100000.1, 4E-7) );
   TEST_ASSERT_EQUAL_UINT8( TRUE,  FloatsEqual(100000.0, 100000.1, 5.1E-7) );
}


// ----------------------------------------- eof --------------------------------------------
