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

/* ------------------------------------- test_MinFloat -------------------------------------- */

void test_MinFloat(void) {
   TEST_ASSERT_EQUAL_FLOAT(0.0,     MinFloat(0.0, 0.0));
   TEST_ASSERT_EQUAL_FLOAT(0.0,     MinFloat(1.1, 0.0));
   TEST_ASSERT_EQUAL_FLOAT(0.0,     MinFloat(0.0, 1.23));
   TEST_ASSERT_EQUAL_FLOAT(-0.22,   MinFloat(-0.22, 0.0));
   TEST_ASSERT_EQUAL_FLOAT(-4.7,    MinFloat(-0.22, -4.7));

   // Invalid comparision always returns NAN
   TEST_ASSERT_EQUAL_FLOAT(NAN,    MinFloat(NAN, -4.5));
   TEST_ASSERT_EQUAL_FLOAT(NAN,    MinFloat(-3, NAN));
   TEST_ASSERT_EQUAL_FLOAT(NAN,    MinFloat(NAN, NAN));
}


/* ------------------------------------- test_MaxFloat -------------------------------------- */

void test_MaxFloat(void)
{
   TEST_ASSERT_EQUAL_FLOAT(0.0,     MaxFloat(0.0, 0.0));
   TEST_ASSERT_EQUAL_FLOAT(1.1,     MaxFloat(1.1, 0.0));
   TEST_ASSERT_EQUAL_FLOAT(1.23,    MaxFloat(0.0, 1.23));
   TEST_ASSERT_EQUAL_FLOAT(-0.0,    MaxFloat(-0.22, 0.0));
   TEST_ASSERT_EQUAL_FLOAT(-0.22,   MaxFloat(-0.22, -4.7));

   // Invalid comparision always returns NAN
   TEST_ASSERT_EQUAL_FLOAT(NAN,    MaxFloat(NAN, -4.5));
   TEST_ASSERT_EQUAL_FLOAT(NAN,    MaxFloat(-3, NAN));
   TEST_ASSERT_EQUAL_FLOAT(NAN,    MaxFloat(NAN, NAN));
}

/* ----------------------------------- test_ClipFloatToLong ----------------------------------- */

void test_ClipFloatToLong(void)
{
   TEST_ASSERT_EQUAL_INT32(0,          ClipFloatToLong(0.0) );
   TEST_ASSERT_EQUAL_INT32(1,          ClipFloatToLong(1.0) );
   TEST_ASSERT_EQUAL_INT32(-1,         ClipFloatToLong(-1.0) );

   /* (S32)(float)MAX_S32 -> MAX_S32.
      The 32bit number is truncated to a 24bit mantissa, so C does not strictly define the
      exact output.
   */
   TEST_ASSERT_EQUAL_INT32(MAX_S32,             ClipFloatToLong(MAX_S32 ) );
   TEST_ASSERT_EQUAL_INT32(MIN_S32,             ClipFloatToLong(MIN_S32) );

   // Check logic for FLT_MAX/MIN; because no floats greater/less than these.
   TEST_ASSERT_EQUAL_INT32(MAX_S32,             ClipFloatToLong(FLT_MAX) );
   TEST_ASSERT_EQUAL_INT32(MIN_S32,             ClipFloatToLong(FLT_MIN) );

   // NaN must become zero.
   TEST_ASSERT_EQUAL_INT32(0,             ClipFloatToLong(NAN) );
}

/* ----------------------------------- test_ClipDoubleToS64 ----------------------------------- */

void test_ClipDoubleToS64(void)
{
   TEST_ASSERT_EQUAL_INT64(0,          ClipDoubleToS64(0.0) );
   TEST_ASSERT_EQUAL_INT64(1,          ClipDoubleToS64(1.0) );
   TEST_ASSERT_EQUAL_INT64(-1,         ClipDoubleToS64(-1.0) );

   /* (S64)(float)MAX_S64 -> MAX_S64.
      The 64bit number is truncated to a 24bit mantissa, so C does not strictly define the
      exact output.
   */
   TEST_ASSERT_EQUAL_INT64(MAX_S64,             ClipDoubleToS64(MAX_S64 ) );
   TEST_ASSERT_EQUAL_INT64(MIN_S64,             ClipDoubleToS64(MIN_S64) );

   // Check logic for FLT_MAX/MIN; because no floats greater/less than these.
   TEST_ASSERT_EQUAL_INT64(MAX_S64,             ClipDoubleToS64(DBL_MAX) );
   TEST_ASSERT_EQUAL_INT64(MIN_S64,             ClipDoubleToS64(DBL_MIN) );

   // NaN must become zero.
   TEST_ASSERT_EQUAL_INT64(0,             ClipDoubleToS64(NAN) );
}


/* ----------------------------------- test_ClipFloatToU32 ----------------------------------- */

void test_ClipFloatToU32(void)
{
   TEST_ASSERT_EQUAL_UINT32(0,          ClipFloatToU32(0.0) );
   TEST_ASSERT_EQUAL_UINT32(1,          ClipFloatToU32(1.0) );

   /* (U32)(float)MAX_U32 -> MAX_U32.
      The 32bit number is truncated to a 24bit mantissa, so C does not strictly define the
      exact output.
   */
   TEST_ASSERT_EQUAL_UINT32(MAX_U32,             ClipFloatToU32(MAX_U32 ) );
   TEST_ASSERT_EQUAL_UINT32(MIN_U32,             ClipFloatToU32(MIN_U32) );

   // Check logic for FLT_MAX/MIN; because no floats greater/less than these.
   TEST_ASSERT_EQUAL_UINT32(MAX_U32,             ClipFloatToU32(FLT_MAX) );
   TEST_ASSERT_EQUAL_UINT32(MIN_U32,             ClipFloatToU32(FLT_MIN) );

   // NaN must become zero.
   TEST_ASSERT_EQUAL_UINT32(0,             ClipFloatToU32(NAN) );
}

/* ----------------------------------- test_ClipFloatToU16 ----------------------------------- */

void test_ClipFloatToU16(void)
{
   TEST_ASSERT_EQUAL_UINT16(0,          ClipFloatToU16(0.0) );
   TEST_ASSERT_EQUAL_UINT16(1,          ClipFloatToU16(1.0) );

   /* (U16)(float)MAX_U16 -> MAX_U16.
      The 32bit number is truncated to a 24bit mantissa, so C does not strictly define the
      exact output.
   */
   TEST_ASSERT_EQUAL_UINT16(MAX_U16,             ClipFloatToU16(MAX_U16 ) );
   TEST_ASSERT_EQUAL_UINT16(MIN_U16,             ClipFloatToU16(MIN_U16) );

   // Check logic for FLT_MAX/MIN; because no floats greater/less than these.
   TEST_ASSERT_EQUAL_UINT16(MAX_U16,             ClipFloatToU16(FLT_MAX) );
   TEST_ASSERT_EQUAL_UINT16(MIN_U16,             ClipFloatToU16(FLT_MIN) );

   // NaN must become zero.
   TEST_ASSERT_EQUAL_UINT16(0,             ClipFloatToU16(NAN) );
}

/* ----------------------------------- test_ClipFloatToInt ----------------------------------- */

void test_ClipFloatToInt(void)
{
   TEST_ASSERT_EQUAL_INT16(0,          ClipFloatToInt(0.0) );
   TEST_ASSERT_EQUAL_INT16(1,          ClipFloatToInt(1.0) );
   TEST_ASSERT_EQUAL_INT16(-1,         ClipFloatToInt(-1.0) );

   /* (S16)(float)MAX_S16 -> MAX_S16.
      The 32bit number is truncated to a 24bit mantissa, so C does not strictly define the
      exact output.
   */
   TEST_ASSERT_EQUAL_INT16(MAX_S16,             ClipFloatToInt(MAX_S16 ) );
   TEST_ASSERT_EQUAL_INT16(MIN_S16,             ClipFloatToInt(MIN_S16) );

   // Check logic for FLT_MAX/MIN; because no floats greater/less than these.
   TEST_ASSERT_EQUAL_INT16(MAX_S16,             ClipFloatToInt(FLT_MAX) );
   TEST_ASSERT_EQUAL_INT16(MIN_S16,             ClipFloatToInt(FLT_MIN) );

   // NaN must become zero.
   TEST_ASSERT_EQUAL_INT16(0,             ClipFloatToInt(NAN) );
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

   // NaNs always -> FALSE
   TEST_ASSERT_EQUAL_UINT8( FALSE,  FloatsEqual(NAN, 0.0, 0.0) );
   TEST_ASSERT_EQUAL_UINT8( FALSE,  FloatsEqual(0.0, NAN, 0.0) );
   TEST_ASSERT_EQUAL_UINT8( FALSE,  FloatsEqual(0.0, 0.0, NAN) );
}

/* ------------------------------------- test_InsideEq_Float ----------------------------------- */

void test_InsideEq_Float(void)
{
   TEST_ASSERT_EQUAL_UINT8(TRUE,  InsideEq_Float(1.5, 1.0, 2.0) );
   TEST_ASSERT_EQUAL_UINT8(TRUE,  InsideEq_Float(1.0, 1.0, 2.0) );
   TEST_ASSERT_EQUAL_UINT8(TRUE,  InsideEq_Float(2.0, 1.0, 2.0) );

   TEST_ASSERT_EQUAL_UINT8(FALSE,  InsideEq_Float(2.5, 1.0, 2.0) );
   TEST_ASSERT_EQUAL_UINT8(FALSE,  InsideEq_Float(0.5, 1.0, 2.0) );

   /* Although FLT_EPSILON is the difference between 1.0 and the first float which is >1.0. it is
      not the smallest number you can add to 1.0 to get the next float. But for what we're testing inside
      it's the same thing.
   */
   TEST_ASSERT_EQUAL_UINT8(FALSE,  InsideEq_Float(1.0+FLT_EPSILON, 0.5, 1.0) );
   TEST_ASSERT_EQUAL_UINT8(FALSE,  InsideEq_Float(-1.0-FLT_EPSILON, -1.0, 1) );

   // All NaN's must eval -> FALSE.
   TEST_ASSERT_EQUAL_UINT8(FALSE, InsideEq_Float(NAN, 1.0, 2.0) );
   TEST_ASSERT_EQUAL_UINT8(FALSE, InsideEq_Float(1.0, NAN, 2.0) );
   TEST_ASSERT_EQUAL_UINT8(FALSE, InsideEq_Float(1.0, 1.0, NAN) );
   TEST_ASSERT_EQUAL_UINT8(FALSE, InsideEq_Float(NAN, NAN, NAN) );
}


/* ------------------------------------- test_GetPwr10Float ------------------------------------- */

void test_GetPwr10Float(void)
{
   typedef struct { S16 exp; float res; } S_Tst;

      S_Tst const tsts[] = {
         // 10^0 -> 1.0
         { .exp = 0,    .res = 1.0 },


         // Some other positive and negative indices.
         { .exp = 1,    .res = 10.0 },
         { .exp = -1,   .res = 0.1 },
         { .exp = 3,    .res = 1E3 },
         { .exp = 15,   .res = 1E15 },
         { .exp = 23,   .res = 1E23 },
         { .exp = -17,  .res = 1E-17 },

         // 10^38, 10^-37
         { .exp = FLT_MAX_10_EXP,    .res = XCAT(1.0E, FLT_MAX_10_EXP) },
         { .exp = FLT_MIN_10_EXP,    .res = 1.0E-37 },      // Can't construct const from (-37) (has brackets)

         // Overrange exponents are clipped to float min/max.
         { .exp = FLT_MAX_10_EXP+1,    .res = FLT_MAX },
         { .exp = FLT_MIN_10_EXP-1,    .res = FLT_MIN },
      };

   bool fail = false;

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      float got = GetPwr10Float(t->exp);
      float err = t->res - got;

      #define _MaxRelErr (1.5E-7)

      if(fabs(err / t->res) > _MaxRelErr)
      {
         printf("tst #%d: %d -> %.3e err %.4e relerr %.3e (limit +/-1E-7)\r\n", i, t->exp, got, err, err/t->res);
         fail = true;
      }

   }
   if(fail == true) {
      TEST_FAIL();  }

   #undef _MaxRelErr
}


/* ------------------------------------- test_GetPwr10Double ------------------------------------- */

void test_GetPwr10Double(void)
{
   typedef struct { S16 exp; double res; } S_Tst;

      S_Tst const tsts[] = {
         // 10^0 -> 1.0
         { .exp = 0,    .res = 1.0 },

         // Some other positive and negative indices.
         { .exp = 1,    .res = 10.0    },
         { .exp = -1,   .res = 0.1     },
         { .exp = 3,    .res = 1E3     },
         { .exp = 15,   .res = 1E15    },
         { .exp = 23,   .res = 1E23    },
         { .exp = -17,  .res = 1E-17   },
         { .exp = -30,  .res = 1E-30   },
         { .exp = 140,  .res = 1E140   },
         { .exp = -270, .res = 1E-270  },

         // 10^38, 10^-37
         { .exp = DBL_MAX_10_EXP,    .res = XCAT(1.0E, DBL_MAX_10_EXP) },
         { .exp = DBL_MIN_10_EXP,    .res = 1.0E-307 },

         // Overrange exponents are clipped to float min/max.
         { .exp = DBL_MAX_10_EXP+1,    .res = DBL_MAX },
         { .exp = DBL_MIN_10_EXP-1,    .res = DBL_MIN },
      };

   bool fail = false;

   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
   {
      S_Tst const *t = &tsts[i];

      double got = GetPwr10Double(t->exp);
      double err = t->res - got;

      #define _MaxRelErr (1E-15)

      if(fabs(err / t->res) > _MaxRelErr)
      {
         printf("tst #%d: %d -> %.3e err %.4e relerr %.3e (limit +/-1E-15)\r\n", i, t->exp, got, err, err/t->res);
         fail = true;
      }
   }

   if(fail == true) {
      TEST_FAIL();  }

   #undef _MaxRelErr

}


/* ------------------------------- test_Mod_Float ------------------------------------------- */

void test_Mod_Float(void)
{
   // Mod is to the nearest, above or below.
   TEST_ASSERT_EQUAL_FLOAT(0.3, Mod_Float(1.3, 1.0));
   TEST_ASSERT_EQUAL_FLOAT(0.3, Mod_Float(1.7, 1.0));

   TEST_ASSERT_EQUAL_FLOAT(0.0, Mod_Float(100.0, 10.0));

   // Zero returns zero.
   TEST_ASSERT_EQUAL_FLOAT(0.0, Mod_Float(100.0, 0.0));

   // NaN's return NaN.
   TEST_ASSERT_EQUAL_FLOAT(NAN, Mod_Float(NAN, 1.0));
   TEST_ASSERT_EQUAL_FLOAT(NAN, Mod_Float(1.7, NAN));
}

/* ---------------------------------- test_DecSizeFloat --------------------------------------- */

void test_DecSizeFloat(void)
{
   // Zero returns MIN_S16; satisfies DecSizeFloat(0.0) < DecSizeFloat(any_non_zero_float)
   TEST_ASSERT_EQUAL_INT16(MIN_S16,   DecSizeFloat(0.0));

   TEST_ASSERT_EQUAL_INT16(0,   DecSizeFloat(1.0));
   TEST_ASSERT_EQUAL_INT16(1,   DecSizeFloat(10.0));
   TEST_ASSERT_EQUAL_INT16(7,   DecSizeFloat(1E7));
   TEST_ASSERT_EQUAL_INT16(-1,  DecSizeFloat(0.1));
   TEST_ASSERT_EQUAL_INT16(-7,  DecSizeFloat(1E-7));

   // Sign does not change result.
   TEST_ASSERT_EQUAL_INT16(0,   DecSizeFloat(-1.0));
   TEST_ASSERT_EQUAL_INT16(1,   DecSizeFloat(-10.0));
   TEST_ASSERT_EQUAL_INT16(7,   DecSizeFloat(-1E7));
   TEST_ASSERT_EQUAL_INT16(-1,  DecSizeFloat(-0.1));
   TEST_ASSERT_EQUAL_INT16(-7,  DecSizeFloat(-1E-7));

   // float 10^38 ... 10^-38.
   TEST_ASSERT_EQUAL_INT16(FLT_MAX_10_EXP,  DecSizeFloat(FLT_MAX));
   TEST_ASSERT_EQUAL_INT16(FLT_MIN_10_EXP,  DecSizeFloat(FLT_MIN));

   // NaN -> zero
   TEST_ASSERT_EQUAL_INT16(0,   DecSizeFloat(NAN));
}

/* ---------------------------------- test_DecSizeDouble --------------------------------------- */

void test_DecSizeDouble(void)
{
   // Zero returns MIN_S16; satisfies DecSizeDouble(0.0) < DecSizeDouble(any_non_zero_double)
   TEST_ASSERT_EQUAL_INT16(MIN_S16,   DecSizeDouble(0.0));

   TEST_ASSERT_EQUAL_INT16(0,   DecSizeDouble(1.0));
   TEST_ASSERT_EQUAL_INT16(1,   DecSizeDouble(10.0));
   TEST_ASSERT_EQUAL_INT16(7,   DecSizeDouble(1E7));
   TEST_ASSERT_EQUAL_INT16(-1,  DecSizeDouble(0.1));
   TEST_ASSERT_EQUAL_INT16(-7,  DecSizeDouble(1E-7));

   // Sign does not change result.
   TEST_ASSERT_EQUAL_INT16(0,   DecSizeDouble(-1.0));
   TEST_ASSERT_EQUAL_INT16(1,   DecSizeDouble(-10.0));
   TEST_ASSERT_EQUAL_INT16(7,   DecSizeDouble(-1E7));
   TEST_ASSERT_EQUAL_INT16(-1,  DecSizeDouble(-0.1));
   TEST_ASSERT_EQUAL_INT16(-7,  DecSizeDouble(-1E-7));

   // float 10^38 ... 10^-38.
   TEST_ASSERT_EQUAL_INT16(DBL_MAX_10_EXP,  DecSizeDouble(DBL_MAX));
   TEST_ASSERT_EQUAL_INT16(DBL_MIN_10_EXP,  DecSizeDouble(DBL_MIN));

   // NaN -> zero
   TEST_ASSERT_EQUAL_INT16(0,   DecSizeDouble(NAN));
}

/* ------------------------------------- test_GetPwr10Double ------------------------------------- */

//void test_GetPwr10Double(void)
//{
//   typedef struct { S16 exp; double res; } S_Tst;
//
//      S_Tst const tsts[] = {
//         // 10^0 -> 1.0
//         { .exp = 0,    .res = 1.0 },
//
//         // Some other positive and negative indices.
//         { .exp = 1,    .res = 10.0 },
//         { .exp = -1,   .res = 0.1 },
//         { .exp = 3,    .res = 1E3 },
//         { .exp = 15,   .res = 1E15 },
//         { .exp = 23,   .res = 1E23 },
//         { .exp = -17,  .res = 1E-17 },
//         { .exp = 64,   .res = 1E64 },
//         { .exp = -55,   .res = 1E-55 },
//
//         // 10^38, 10^-37
//         { .exp = DBL_MAX_10_EXP,    .res = XCAT(1.0E, DBL_MAX_10_EXP) },
//         { .exp = DBL_MIN_10_EXP,    .res = 1.0E-307 },      // Can't construct const from (-37) (has brackets)
//
//         // Overrange exponents are clipped to float min/max.
//         { .exp = DBL_MAX_10_EXP+1,    .res = DBL_MAX },
//         { .exp = DBL_MIN_10_EXP-1,    .res = DBL_MIN },
//      };
//
//   for(U8 i = 0; i < RECORDS_IN(tsts); i++)
//   {
//      S_Tst const *t = &tsts[i];
//
//      double res = GetPwr10Double(t->exp);
//
//      C8 b0[100];
//      sprintf(b0, "10^%d -> %.15e diff %e", t->exp, res, t->res-res);
//      TEST_ASSERT_EQUAL_DOUBLE_MESSAGE( t->res, res, b0);
//   }
//}






// ----------------------------------------- eof --------------------------------------------
