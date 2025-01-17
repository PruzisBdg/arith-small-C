/* -----------------------------------------------------------------
|
|    Sorts, ranks and non-linear filters.
|
--------------------------------------------------------------------- */

#include "spj_stdint.h"
#include "arith.h"


/* -------------------------- RankU8_UpTo8/16 --------------------------------------

   Returns the 'rank'th number in 'buf' of 'size'. 'rank' = 0 returns the largest.

   ********* 'size' can be up to 8, limited by the uchars which hold flags. You
   can rebuild for 16 (word) or 32 (dword). Likewise you can sort ints or longs.

   Runs 'rank' passes through buf, tagging the largest or smallest on each pass,
   to be skipped on subsequent passes. The answer is number tagged after the
   'rank'th pass.

   The code searches from the quickest end, i.e if searching for median or higher
   it will pick off largest downwards; otherwise will pick off smallest upwards.

   This is an N^2 algorithmn but for small 'N' is faster than others because
   codes compactly. On 8-bit load/store MCU's much better than anything fancier.
   Also doesn't need buffers, malloc() etc to sort.
*/

PUBLIC U8 RankU8_UpTo8( U8 const *buf, U8 size, U8 rank )
{
   U8 s, r, maxIdx;
   U8 tags, mask;
   U8       rankNum;
   BIT      up;

   maxIdx = 0;                                      // Unecessary, but keeps compiler from complaining

   if(size == 0)                                    // Zero-buffer
   {
       return 0;                                    // then quit gracefully.
   }
   else                                             // else buffer has at least 1 element.
   {
       size = MinU8(size,8);                        // Make sure 'size' is <= 8
       rank = MinU8(size-1, rank);                  // Make sure 'rank' is within the size of the buffer.

       if(rank < size/2)                            // searching for median or higher
       {
          up = 1;                                   // then will search and tag from largest downwards
       }
       else
       {
          up = 0;
          rank = size-rank-1;                       // else will search and tag from smallest upwards
       }

       tags = 0;                                    // no numbers tagged yet
       r = rank;                                    // 'rank' == 0 means will do one pass and find min/max

       while(1)
       {
          mask = 1;                                 // lsb of mask is 1st number compared.
          s = size;                                 // start index at array size; will predecrement to index last number

          if(up)                                    // searching from smallest up?
             { rankNum = MIN_U8; }                  // then any number will be larger
          else
             { rankNum = MAX_U8; }                  // else any number will be smaller

          do                                        // do for each number in array
          {
             s--;
             if(!(tags & mask) )                    // number wasn't tagged on last pass?
             {
                if( (up && buf[s] >= rankNum) ||    // from smallest up AND is largest so far OR
                    (!up && buf[s] <= rankNum))     // from largest down AND is smallest so far
                {
                   rankNum = buf[s];                // then cache min/max
                   maxIdx = s;                      // and cache its idx to be added to tags
                }
             }
             mask <<= 1;                            // advance mask
          }
          while(s);

          if(!r)                                    // no more passes?
          {
             return rankNum;                        // then done, return min/max from this pass
          }
          else                                      // else more passes to do
          {
             r--;                                   // one less pass remaining
             tags |= (1 << (size - maxIdx - 1));    // tag min/max this pass, to be ignored on subsequent ones
          }                                         // Mask is shifted left so subtract 'maxIdx' to tag correct bit
       }
   }
   return 0;    // So compiler doesn't complain.
}


// -------------------------- RankU8_UpTo8/16 --------------------------------------

PUBLIC U8 RankU8_UpTo16( U8 const *buf, U8 size, U8 rank )
{
   U8   s, r, maxIdx;
   U16  tags, mask;
   U8   rankNum;
   BIT  up;

   maxIdx = 0;                                      // Unecessary, but keeps compiler from complaining

   if(size == 0)                                    // Zero-buffer
   {
       return 0;                                    // then quit gracefully.
   }
   else                                             // else buffer has at least 1 element.
   {
       size = MinU8(size,16);                       // Make sure 'size' is <= 8
       rank = MinU8(size-1, rank);                  // Make sure 'rank' is within the size of the buffer.

       if(rank < size/2)                            // searching for median or higher
       {
          up = 1;                                   // then will search and tag from largest downwards
       }
       else
       {
          up = 0;
          rank = size-rank-1;                       // else will search and tag from smallest upwards
       }

       tags = 0;                                    // no numbers tagged yet
       r = rank;                                    // 'rank' == 0 means will do one pass and find min/max

       while(1)
       {
          mask = 1;                                 // lsb of mask is 1st number compared.
          s = size;                                 // start index at array size; will predecrement to index last number

          if(up)                                    // searching from smallest up?
             { rankNum = MIN_U8; }                  // then any number will be larger
          else
             { rankNum = MAX_U8; }                  // else any number will be smaller

          do                                        // do for each number in array
          {
             s--;
             if(!(tags & mask) )                    // number wasn't tagged on last pass?
             {
                if( (up && buf[s] >= rankNum) ||    // from smallest up AND is largest so far OR
                    (!up && buf[s] <= rankNum))     // from largest down AND is smallest so far
                {
                   rankNum = buf[s];                // then cache min/max
                   maxIdx = s;                      // and cache its idx to be added to tags
                }
             }
             mask <<= 1;                            // advance mask
          }
          while(s);

          if(!r)                                    // no more passes?
          {
             return rankNum;                        // then done, return min/max from this pass
          }
          else                                      // else more passes to do
          {
             r--;                                   // one less pass remaining
             tags |= (1 << (size - maxIdx - 1));    // tag min/max this pass, to be ignored on subsequent ones
          }                                         // Mask is shifted left so subtract 'maxIdx' to tag correct bit
       }
   }
   return 0;    // So compiler doesn't complain.
}


// ====================================== EOF ===========================================================
