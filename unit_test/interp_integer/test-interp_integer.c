/* */

#include "unity.h"
#include "arith.h"
#include <stdlib.h>
#include <time.h>
#include "tdd_common.h"

// =============================== Tests start here ==================================


/* -------------------------------------- setUp ------------------------------------------- */

void setUp(void) {
    srand(time(NULL));     // Random seed for scrambling stimuli
}

/* -------------------------------------- tearDown ------------------------------------------- */

void tearDown(void) {
}

/* ----------------------- test_LinterpFromU8Tbl ------------------------------------------- */

typedef struct {
    S_ConstTblU8 *tbl;
    U8 in, min, max;
} S_ChkU8;

PRIVATE U8 const raws1[] = {0, 80, 0};
PRIVATE S_ConstTblU8 tbl1 = { raws1, RECORDS_IN(raws1)-1 };

#define _x(n)  (U8)(_LinterpTblU8_Step * (n))

PRIVATE S_ChkU8 const chksU8[] = {
    { &tbl1, _x(0.0), 0,  0 },
    { &tbl1, _x(0.5), 40, 40 },
    { &tbl1, _x(1.0), 80, 80 },
    { &tbl1, _x(1.5), 40, 40 },
    { &tbl1, _x(2.0), 0,  0 },
    { &tbl1, _x(2.1), 0,  0 },
    
    { &tbl1, MAX_U8, 0,  0 },
};

#undef _x

void test_LinterpFromU8Tbl(void)
{
    U8 n,c, res;

    for(c = 0; c < RECORDS_IN(chksU8); c++)
    {
        res = LinterpFromU8Tbl(chksU8[c].tbl, chksU8[c].in);

        if(res < chksU8[c].min || res > chksU8[c].max )
        {
            printf("LinterpFromU8Tbl() failed: %d -> %d limits (%d,%d)\r\n", chksU8[c].in, res, chksU8[c].min, chksU8[c].max);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}

/* ----------------------- test_LinterpFromS16Tbl ------------------------------------------- */

typedef struct {
    S_ConstTblS16 *tbl;
    S16 in, min, max;
} S_ChkS16;

PRIVATE S16 const raws2[] = {0, 80, 0, -80, 0};
PRIVATE S_ConstTblS16 tblS16 = { raws2, RECORDS_IN(raws2)-1 };

#define _x(n)  (S16)(_LinterpTblS16_Step * (n))

PRIVATE S_ChkS16 const chksS16[] = {
    { &tblS16, _x(0.0),  0,  0 },
    { &tblS16, _x(0.5),  40, 40 },
    { &tblS16, _x(1.0), 80, 80 },
    { &tblS16, _x(1.5), 40, 40 },
    { &tblS16, _x(2.0), 0,  0 },
    { &tblS16, _x(2.5), -40,  -40 },
    { &tblS16, _x(3.0), -80,  -80 },
    { &tblS16, _x(3.5), -40,  -40 },
    { &tblS16, _x(4.0), 0,  0 },
    { &tblS16, _x(4.1), 0,  0 },
    
    { &tblS16, MAX_S16, 0,  0 },
};

#undef _x

void test_LinterpFromS16Tbl(void)
{
    U8 c;
    S16 n,res;

    for(c = 0; c < RECORDS_IN(chksS16); c++)
    {
        res = LinterpFromS16Tbl(chksS16[c].tbl, chksS16[c].in);

        if(res < chksS16[c].min || res > chksS16[c].max )
        {
            printf("LinterpFromS16Tbl() failed: %d -> %d limits (%d,%d)\r\n", chksS16[c].in, res, chksS16[c].min, chksS16[c].max);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
}



// ----------------------------------------- eof --------------------------------------------