/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Test Runner Used To Run Each Test Below=====*/
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT()) \
  { \
    tearDown(); \
  } \
  UnityConcludeTest(); \
}

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include <setjmp.h>
#include <stdio.h>
#include "arith.h"
#include "tdd_common.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_Limits(void);
extern void test_ClipS32toS16(void);
extern void test_ClipU32toU16(void);
extern void test_ClipS32toU16(void);
extern void test_ClipS16toU8(void);
extern void test_ClipU16toU8(void);
extern void test_ClipU32toS32(void);
extern void test_MinS8(void);
extern void test_MaxS8(void);
extern void test_MinS16(void);
extern void test_MaxS16(void);
extern void test_ClipS32(void);
extern void test_ClipU32(void);
extern void test_ClipS16(void);
extern void test_ClipU16(void);
extern void test_ClipU8(void);
extern void test_ClipS8(void);
extern void test_MinU8(void);
extern void test_MaxU8(void);
extern void test_MinU16(void);
extern void test_MaxU16(void);
extern void test_MinU32(void);
extern void test_MaxU32(void);
extern void test_AplusBU8(void);
extern void test_AplusBS16(void);
extern void test_AplusBU16(void);
extern void test_U16plusS16_toU16(void);
extern void test_AplusBU32(void);
extern void test_AplusBS32(void);
extern void test_U32plusS16(void);
extern void test_U32plusS32_toU32(void);
extern void test_SignEqualsS16(void);
extern void test_AminusBU8(void);
extern void test_AminusBU16(void);
extern void test_AminusBS16(void);
extern void test_AminusBU32(void);
extern void test_AminusBU16ToS16(void);
extern void test_AminusBU32toS32(void);
extern void test_AminusBS32toU32(void);
extern void test_AbsS16(void);
extern void test_AbsDiffU8(void);
extern void test_AbsDiffU16(void);
extern void test_AbsDiffS16(void);
extern void test_AbsDiffU32(void);
extern void test_MinusS32(void);
extern void test_Inside_U8(void);
extern void test_Inside_U16(void);
extern void test_Inside_S16(void);
extern void test_InsideEq_U32(void);
extern void test_Mean2_U8(void);
extern void test_Mean3_U8(void);
extern void test_Mean4_U8(void);
extern void test_AmulBdivC_S16(void);
extern void test_AmulBdivC_U16(void);
extern void test_AmulBdivC_U16_rnd(void);
extern void test_AmulBdivC_S16_U8_U8(void);
extern void test_AmulBdivC_U8(void);
extern void test_AmulBdivC_U8_rnd(void);
extern void test_AmulBdivC_S16_S8_S8(void);
extern void test_DeadbandS16(void);
extern void test_Median3_U8(void);
extern void test_Span3_U8(void);
extern void test_Span4_U8(void);
extern void test_SqU8(void);
extern void test_SqU16(void);
extern void test_SqS16(void);
extern void test_MixU8(void);
extern void test_MixU16(void);
extern void test_DecrU8_NowZero(void);
extern void test_DecrU8_Was1_NowZero(void);
extern void test_RankU8_UpTo8(void);


/*=======Test Reset Option=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  setUp();
}


/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test-arith_integer_basic.c");
  RUN_TEST(test_Limits, 24);
  RUN_TEST(test_ClipS32toS16, 47);
  RUN_TEST(test_ClipU32toU16, 72);
  RUN_TEST(test_ClipS32toU16, 83);
  RUN_TEST(test_ClipS16toU8, 95);
  RUN_TEST(test_ClipU16toU8, 109);
  RUN_TEST(test_ClipU32toS32, 120);
  RUN_TEST(test_MinS8, 130);
  RUN_TEST(test_MaxS8, 162);
  RUN_TEST(test_MinS16, 192);
  RUN_TEST(test_MaxS16, 222);
  RUN_TEST(test_ClipS32, 251);
  RUN_TEST(test_ClipU32, 288);
  RUN_TEST(test_ClipS16, 325);
  RUN_TEST(test_ClipU16, 363);
  RUN_TEST(test_ClipU8, 401);
  RUN_TEST(test_ClipS8, 439);
  RUN_TEST(test_MinU8, 479);
  RUN_TEST(test_MaxU8, 509);
  RUN_TEST(test_MinU16, 538);
  RUN_TEST(test_MaxU16, 568);
  RUN_TEST(test_MinU32, 598);
  RUN_TEST(test_MaxU32, 628);
  RUN_TEST(test_AplusBU8, 659);
  RUN_TEST(test_AplusBS16, 671);
  RUN_TEST(test_AplusBU16, 701);
  RUN_TEST(test_U16plusS16_toU16, 730);
  RUN_TEST(test_AplusBU32, 764);
  RUN_TEST(test_AplusBS32, 793);
  RUN_TEST(test_U32plusS16, 824);
  RUN_TEST(test_U32plusS32_toU32, 858);
  RUN_TEST(test_SignEqualsS16, 891);
  RUN_TEST(test_AminusBU8, 933);
  RUN_TEST(test_AminusBU16, 944);
  RUN_TEST(test_AminusBS16, 955);
  RUN_TEST(test_AminusBU32, 969);
  RUN_TEST(test_AminusBU16ToS16, 981);
  RUN_TEST(test_AminusBU32toS32, 1015);
  RUN_TEST(test_AminusBS32toU32, 1054);
  RUN_TEST(test_AbsS16, 1087);
  RUN_TEST(test_AbsDiffU8, 1096);
  RUN_TEST(test_AbsDiffU16, 1112);
  RUN_TEST(test_AbsDiffS16, 1127);
  RUN_TEST(test_AbsDiffU32, 1162);
  RUN_TEST(test_MinusS32, 1177);
  RUN_TEST(test_Inside_U8, 1191);
  RUN_TEST(test_Inside_U16, 1217);
  RUN_TEST(test_Inside_S16, 1243);
  RUN_TEST(test_InsideEq_U32, 1272);
  RUN_TEST(test_Mean2_U8, 1301);
  RUN_TEST(test_Mean3_U8, 1325);
  RUN_TEST(test_Mean4_U8, 1351);
  RUN_TEST(test_AmulBdivC_S16, 1380);
  RUN_TEST(test_AmulBdivC_U16, 1440);
  RUN_TEST(test_AmulBdivC_U16_rnd, 1490);
  RUN_TEST(test_AmulBdivC_S16_U8_U8, 1522);
  RUN_TEST(test_AmulBdivC_U8, 1577);
  RUN_TEST(test_AmulBdivC_U8_rnd, 1627);
  RUN_TEST(test_AmulBdivC_S16_S8_S8, 1657);
  RUN_TEST(test_DeadbandS16, 1718);
  RUN_TEST(test_Median3_U8, 1791);
  RUN_TEST(test_Span3_U8, 1831);
  RUN_TEST(test_Span4_U8, 1872);
  RUN_TEST(test_SqU8, 1921);
  RUN_TEST(test_SqU16, 1933);
  RUN_TEST(test_SqS16, 1945);
  RUN_TEST(test_MixU8, 1959);
  RUN_TEST(test_MixU16, 2001);
  RUN_TEST(test_DecrU8_NowZero, 2047);
  RUN_TEST(test_DecrU8_Was1_NowZero, 2071);
  RUN_TEST(test_RankU8_UpTo8, 2095);

  return (UnityEnd());
}
