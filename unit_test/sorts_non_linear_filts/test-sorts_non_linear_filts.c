/* */

#include "unity.h"
#include "arith.h"
#include <stdlib.h>
#include <time.h>

// --------------------------- Support --------------------------------------------

PUBLIC U8  randU8(void)  { return (U8)((float)rand() * MAX_U8 / RAND_MAX); }
PUBLIC U16 randU16(void) { return (U16)((float)rand() * MAX_U16 / RAND_MAX); }
PUBLIC U16 randU32(void) { return (U32)((float)rand() * MAX_U32 / RAND_MAX); }
PUBLIC S16 randS16(void) { return (S16)( 2.0 * ((float)rand() - (RAND_MAX/2)) * MAX_S16 / RAND_MAX); }
PUBLIC S8  randS8(void)  { return (S8)( 2.0 * ((float)rand() - (RAND_MAX/2)) * MAX_S8 / RAND_MAX); }


// =============================== Tests start here ==================================


/* -------------------------------------- setUp ------------------------------------------- */

void setUp(void) {
    srand(time(NULL));     // Random seed for scrambling stimuli
}

/* -------------------------------------- tearDown ------------------------------------------- */

void tearDown(void) {
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
    #undef _chks
}


/* ------------------------------ test_RankU8_UpTo16 --------------------------------------- */

typedef struct {
    U8 buf[16],
       size,
       rank,
       chk;
} S_RankU8_UpTo16_Chk;

PRIVATE S_RankU8_UpTo16_Chk const rankU8_UpTo16_Chks[] = {

    //  Buffer             size  rank  result
    // ---------------------------------------

    // 'Illegal' parms must be handled gracefully
    // Zero buffer size always returns zero; regardless of buffer or rank.
    { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},    0,    0,    0},
    { {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},    0,    0,    0},
    { {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},    0,    5,    0},

    // A buffer with just one member
    { {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},    1,    0,    3},

    // Rank must be clipped to within buffer.
    { {3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0},    1,    1,    3},     //
    { {3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0},    1,  MAX_U8, 3},     //

    { {3,4,5,2,1,9,9,9,3,4,5,2,1,0,0,0},    5,    0,    5},
    { {3,4,5,2,1,9,9,9,3,4,5,2,1,0,0,0},    5,    1,    4},

    { {3,4,5,2,1,8,6,7,13,14,15,12,11,18,16,17},   16,    0,    18},
    { {3,7,5,2,1,8,6,4,3,7,5,2,1,8,6,4},    16,    1,    8},
    { {3,5,2,1,8,6,4,7,13,14,15,12,11,18,16,17},   16,    2,    16},
    { {3,2,1,8,6,4,7,5,2,5,8,6,7,1,4,3},    16,    3,    7},
    { {3,2,1,8,6,7,5,4,2,5,1,8,6,7,4,3},    16,    4,    6},
    { {2,1,8,6,7,5,4,3,2,1,8,6,7,5,4,3},    16,    5,    6},
    { {2,5,1,8,6,7,4,3,13,14,15,12,11,18,16,17},   16,    6,    12},
    { {2,5,8,6,7,1,4,3,3,2,1,8,6,4,7,5},    16,    7,    5},

    // Ranks exceeding buffer size must be clipped to within buffer.
    { {2,8,6,7,5,1,4,3,12,18,16,17,15,11,14,13},    8,    8,    1},
    { {2,8,6,7,5,1,4,3,12,18,16,17,15,11,14,13},    8, MAX_U8,  1},

    // With some values equal
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    0,    3},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    1,    3},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    2,    3},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    3,    3},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    4,    3},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    5,    3},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    6,    2},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    7,    2},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    8,    2},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    9,    2},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    10,   2},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    11,   2},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    12,   1},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    13,   1},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    14,   1},
    { {1,1,2,2,2,3,3,3,1,1,2,2,2,3,3,3},    16,    15,   1},


    { {MAX_U8, MAX_U8-2, MAX_U8-1,0,0,0,0,0,0,0,0,0,0,0,0,0}, 3, 0,  MAX_U8},
    { {MAX_U8, MAX_U8-2, MAX_U8-1,0,0,0,0,0,0,0,0,0,0,0,0,0}, 3, 1,  MAX_U8-1},
    { {MAX_U8-1, MAX_U8-2, MAX_U8-1,0,0,0,0,0,0,0,0,0,0,0,0,0}, 3, 2,  MAX_U8-2},
};

void test_RankU8_UpTo16(void)
{
    U8 c, result;

    #define _chks rankU8_UpTo16_Chks

    for( c = 0; c < RECORDS_IN(rankU8_UpTo16_Chks); c++ )
    {
        result = RankU8_UpTo16(_chks[c].buf, _chks[c].size, _chks[c].rank);

        if( result != _chks[c].chk )
        {
            printf("RankU8_UpTo16() failed: (");
            printU8s(_chks[c].buf, _chks[c].size);
            printf(") %dth-> %d expected %d\r\n", _chks[c].rank, result, _chks[c].chk);
            TEST_ASSERT_TRUE(FALSE);
        }
    }
    #undef _chks
}



// ----------------------------------------- eof --------------------------------------------
