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

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_ClipS32toS16(void);
extern void test_ClipU32toU16(void);
extern void test_ClipS16toU8(void);
extern void test_ClipU16toU8(void);
extern void test_ClipU32toS32(void);
extern void test_MinS8(void);
extern void test_MaxS8(void);
extern void test_MinS16(void);
extern void test_MaxS16(void);
extern void test_ClipS32(void);
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
extern void test_Median3_U8(void);
extern void test_Span3_U8(void);
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
  RUN_TEST(test_ClipS32toS16, 23);
  RUN_TEST(test_ClipU32toU16, 46);
  RUN_TEST(test_ClipS16toU8, 57);
  RUN_TEST(test_ClipU16toU8, 71);
  RUN_TEST(test_ClipU32toS32, 82);
  RUN_TEST(test_MinS8, 92);
  RUN_TEST(test_MaxS8, 124);
  RUN_TEST(test_MinS16, 154);
  RUN_TEST(test_MaxS16, 184);
  RUN_TEST(test_ClipS32, 213);
  RUN_TEST(test_ClipS16, 250);
  RUN_TEST(test_ClipU16, 288);
  RUN_TEST(test_ClipU8, 326);
  RUN_TEST(test_ClipS8, 364);
  RUN_TEST(test_MinU8, 404);
  RUN_TEST(test_MaxU8, 434);
  RUN_TEST(test_MinU16, 463);
  RUN_TEST(test_MaxU16, 493);
  RUN_TEST(test_MinU32, 523);
  RUN_TEST(test_MaxU32, 553);
  RUN_TEST(test_AplusBU8, 584);
  RUN_TEST(test_AplusBS16, 596);
  RUN_TEST(test_AplusBU16, 626);
  RUN_TEST(test_U16plusS16_toU16, 655);
  RUN_TEST(test_AplusBU32, 689);
  RUN_TEST(test_AplusBS32, 718);
  RUN_TEST(test_U32plusS16, 749);
  RUN_TEST(test_U32plusS32_toU32, 783);
  RUN_TEST(test_SignEqualsS16, 816);
  RUN_TEST(test_AminusBU8, 858);
  RUN_TEST(test_AminusBU16, 869);
  RUN_TEST(test_AminusBS16, 880);
  RUN_TEST(test_AminusBU32, 894);
  RUN_TEST(test_AminusBU16ToS16, 906);
  RUN_TEST(test_AminusBU32toS32, 940);
  RUN_TEST(test_AbsS16, 979);
  RUN_TEST(test_AbsDiffU8, 988);
  RUN_TEST(test_AbsDiffU16, 1004);
  RUN_TEST(test_AbsDiffS16, 1019);
  RUN_TEST(test_AbsDiffU32, 1054);
  RUN_TEST(test_MinusS32, 1069);
  RUN_TEST(test_Inside_U8, 1083);
  RUN_TEST(test_Inside_U16, 1109);
  RUN_TEST(test_Inside_S16, 1135);
  RUN_TEST(test_InsideEq_U32, 1164);
  RUN_TEST(test_Mean2_U8, 1193);
  RUN_TEST(test_Mean3_U8, 1217);
  RUN_TEST(test_Mean4_U8, 1243);
  RUN_TEST(test_AmulBdivC_S16, 1272);
  RUN_TEST(test_AmulBdivC_U16, 1332);
  RUN_TEST(test_AmulBdivC_U16_rnd, 1382);
  RUN_TEST(test_AmulBdivC_S16_U8_U8, 1414);
  RUN_TEST(test_AmulBdivC_U8, 1469);
  RUN_TEST(test_AmulBdivC_U8_rnd, 1519);
  RUN_TEST(test_AmulBdivC_S16_S8_S8, 1549);
  RUN_TEST(test_Median3_U8, 1611);
  RUN_TEST(test_Span3_U8, 1651);
  RUN_TEST(test_SqU8, 1692);
  RUN_TEST(test_SqU16, 1704);
  RUN_TEST(test_SqS16, 1716);
  RUN_TEST(test_MixU8, 1730);
  RUN_TEST(test_MixU16, 1772);
  RUN_TEST(test_DecrU8_NowZero, 1818);
  RUN_TEST(test_DecrU8_Was1_NowZero, 1842);
  RUN_TEST(test_RankU8_UpTo8, 1866);

  return (UnityEnd());
}
