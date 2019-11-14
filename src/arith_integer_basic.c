/* -----------------------------------------------------------------
|
|              Basic Integer Arithmetic
|
--------------------------------------------------------------------- */

#include "GenericTypeDefs.h"
#include "libs_support.h"
#include "arith.h"



// ============================= PRIVATE ====================================

PRIVATE S16 AmulBdivC_S16_Raw(S16 a, S16 b, S16 c)
    { return ClipS32toS16(a * (S32)b / c); }

// =============================== end: PRIVATE ==============================


PUBLIC S16 ClipS32toS16(S32 n)
    { return (n > MAX_S16) ? MAX_S16 : (n < MIN_S16 ? MIN_S16 : n); }

PUBLIC U16 ClipS32toU16(S32 n)
    { return (n > MAX_U16) ? MAX_U16 : (n < 0 ? 0 : n); }

PUBLIC U16 ClipU32toU16(U32 n)
    { return (n > MAX_U16) ? MAX_U16 : n; }

PUBLIC U8 ClipS16toU8(S16 n)
    { return (n > MAX_U8) ? MAX_U8 : (n < 0 ? 0 : n); }

PUBLIC S8 ClipS16toS8(S16 n)
    { return (n > MAX_S8) ? MAX_S8 : (n < MIN_S8 ? MIN_S8 : n); }

PUBLIC U8 ClipU16toU8(U16 n)
    { return n > MAX_U8 ? MAX_U8 : n; }

PUBLIC S32 ClipU32toS32(U32 n)
	{ return n > MAX_S32 ? MAX_S32 : n; }

PUBLIC S16 ClipS16(S16 n, S16 min, S16 max)
{
    return
        min > max                                       // Limits are crossed?
            ? ((min >> 1) + (max >> 1))                 // then return mean of limits
            : (n > max ? max : (n < min ? min : n));    // else clip 'n' to limits.
}

PUBLIC S32 ClipS32(S32 n, S32 min, S32 max)
{
    return
        min > max                                       // Limits are crossed?
            ? ((min >> 1) + (max >> 1))                 // then return mean of limits
            : (n > max ? max : (n < min ? min : n));    // else clip 'n' to limits.
}

PUBLIC U16 ClipU16(U16 n, U16 min, U16 max)
{
    return
        min > max                                       // Limits are crossed?
            ? ((min >> 1) + (max >> 1))                 // then return mean of limits
            : (n > max ? max : (n < min ? min : n));    // else clip 'n' to limits.
}

PUBLIC U32 ClipU32(U32 n, U32 min, U32 max)
{
    return
        min > max                                       // Limits are crossed?
            ? ((min >> 1) + (max >> 1))                 // then return mean of limits
            : (n > max ? max : (n < min ? min : n));    // else clip 'n' to limits.
}

PUBLIC U8 ClipU8(U8 n, U8 min, U8 max)
{
    return
        min > max
            ? ((min >> 1) + (max >> 1))
            : (n > max ? max : (n < min ? min : n));
}

PUBLIC S8 ClipS8(S8 n, S8 min, S8 max)
{
    return
        min > max
            ? ((min/2) + (max/2))
            : (n > max ? max : (n < min ? min : n));
}

PUBLIC S16 MinS16(S16 a, S16 b)
    { return a < b ? a : b; }

PUBLIC S16 MaxS16(S16 a, S16 b)
    { return a > b ? a : b; }

PUBLIC S8 MinS8(S8 a, S8 b)
    { return a < b ? a : b; }

PUBLIC S8 MaxS8(S8 a, S8 b)
    { return a > b ? a : b; }

PUBLIC U16 MinU16(U16 a, U16 b)
    { return a < b ? a : b; }

PUBLIC U16 MaxU16(U16 a, U16 b)
    { return a > b ? a : b; }

PUBLIC U8 MinU8(U8 a, U8 b)
    { return a < b ? a : b; }

PUBLIC U8 MaxU8(U8 a, U8 b)
    { return a > b ? a : b; }

PUBLIC U32 MinU32(U32 a, U32 b)
    { return a < b ? a : b; }

PUBLIC U32 MaxU32(U32 a, U32 b)
    { return a > b ? a : b; }


PUBLIC S16 AplusBS16(S16 a, S16 b)
    { return ClipS32toS16(a + (S32)b); }

PUBLIC U16 AplusB_U16(U16 a, U16 b)
    { return ClipU32toU16(a + (U32)b); }

PUBLIC U16 U16plusS16_toU16(U16 a, S16 b)
   { return ClipS32((S32)a + b, MIN_U16, MAX_U16); }

PUBLIC U32 AplusBU32(U32 a, U32 b)
{
    return
        (U32)(a + b) < a || (U32)(a + b) < b || (a+b) > MAX_U32
            ? MAX_U32
            : a + b;
}

PUBLIC U32 U32plusS16(U32 a, S16 b)
{
	return
		b > 0
			? AplusBU32(a, b)
			: AminusBU32(a, -b);
}

PUBLIC U32 U32plusS32_toU32(U32 a, S32 b)
{
	return
		b > 0
			? AplusBU32(a, b)
			: AminusBU32(a, -b);
}

PUBLIC S32 AplusBS32(S32 a, S32 b)
{
    return
        (a > 0 && b > 0 && (a+b) < 0)
            ? MAX_S32
            : ((a < 0 && b < 0 && (a+b) > 0)
                    ? MIN_S32
                    : a + b );
}


PUBLIC BOOL SignEqualsS16(S16 a, S16 b)
    { return _SignEqualsS16(a,b); }

PUBLIC S32 MulS16(S16 a, S16 b) { return b * (S32)a; }

PUBLIC S16 AmulBdivC_S16(S16 a, S16 b, S16 c)
{
    return
        c == 0                                  // divisor == 0?
            ? (a == 0 || b == 0                 // AND either multiplicand == 0
                ? 0                             // then <- 0
                : ( _SignEqualsS16(a,b)         // else both multiplcands are non-zero. Multiplicands have same sign?
                    ? MAX_S16                   // then <- maximum positive
                    : MIN_S16 ))                // else multiplicands have oppositie signs; <- max negative
            : ClipS32toS16(a * (S32)b / c);     // else a,b,c are non-zero. Get a*b/c; clip result to S16.
}

PUBLIC U16 AmulBdivC_U16(U16 a, U16 b, U16 c)
{
    return
        c == 0
            ? (a == 0 || b ==0
                ? 0
                : MAX_U16)
            : ClipU32toU16(a * (U32)b / c);
}

PUBLIC U16 AmulBdivC_U16_rnd(U16 a, U16 b, U16 c)
{
    return
        c == 0
            ? (a == 0 || b ==0
                ? 0
                : MAX_U16)
            : ClipU32toU16( ((a * (U32)b) + (c/2)) / c);
}


PUBLIC S16 AmulBdivC_S16_U8_U8(S16 a, U8 b, U8 c)
{
    /* This function is often used for taking simple fractions e.g b = 3, c = 16. So check
       if 32 bit arithmetic is need. Stay with faster 16bit if it's not.
    */
    return
        c == 0
            ? (a == 0 || b == 0
                ? 0
                : (a > 0 ? MAX_S16 : MIN_S16))
            : (
            ((a < 4096 && a > -4096) && (b < 8)) ||         // a * b fits inside 16bit int? OR
            ((a < 1024 && a > -1024) && (b < 32))           // a * b fits this way
                ? a * b / c                                 // then do 16 bit arithmetic
                : ClipS32toS16(a * (S32)b / c));             // else fall back to a 32bit product.

}

PUBLIC U8 AmulBdivC_U8(U8 a, U8 b, U8 c)
{
    return
        a == 0 || b == 0
        ? 0
        : ( c == 0
            ? MAX_U8
            : ClipU16toU8(a * (U16)b / c));
}

PUBLIC U8 AmulBdivC_U8_rnd(U8 a, U8 b, U8 c)
{
    return
        a == 0 || b == 0
            ? 0
            : ( c == 0
                ? MAX_U8
                : ClipU16toU8( ((a * (U16)b) + (c/2)) / c));
}

PUBLIC S16 AmulBdivC_S16_S8_S8(S16 a, S8 b, S8 c)
    { return AmulBdivC_S16(a,b,c); }

PUBLIC S16 DeadbandS16(S16 n, S16 lo, S16 hi) {
   S16 mid = Mean2_S16(lo, hi);
   return
      lo > hi                             // Limits upside down?
         ? n                              // then <- 'n'
         : (n > hi || n < lo              // Outside band
            ? n                           // then <- just 'n'
            : (n < mid                    // else in-band.. Below mid?
               ? lo                       // then <- 'lo'
               : hi)); }                 // else <- 'hi'

PUBLIC S16 Mean2_S16(S16 a, S16 b)
    { return (a + (S32)b) / 2; }

PUBLIC U8 Mean2_U8(U8 a, U8 b)
    { return (a + (S16)b) / 2; }

PUBLIC U8 Mean3_U8(U8 a, U8 b, U8 c)
    { return (a + (S16)b + (S16)c + 1) / 3; }

PUBLIC U8 Mean4_U8(U8 a, U8 b, U8 c, U8 d)
    { return (a + (S16)b + (S16)c + (S16)d + 2) / 4; }

PUBLIC BIT Inside_U8(U8 a, U8 min, U8 max)
    { return a > min && a < max; }

PUBLIC BIT Inside_U16(U16 a, U16 min, U16 max)
    { return a > min && a < max; }

PUBLIC BIT Inside_S16(S16 a, S16 min, S16 max)
    { return a > min && a < max; }

PUBLIC BIT InsideEq_U32(U32 a, U32 min, U32 max)
    { return a >= min && a <= max; }

PUBLIC S16 AbsS16(S16 n)
{
    return
        n == MIN_S16        // Gotta watch that sign inversion!
            ? MAX_S16
            : (n < 0 ? -n : n);
}

PUBLIC U8 AbsDiffU8(U8 a, U8 b)
    {return a > b ? a - b : b - a; }

PUBLIC U16 AbsDiffU16(U16 a, U16 b)
    {return a > b ? a - b : b - a; }

PUBLIC U16 AbsDiffS16(S16 a, S16 b)
    {return (U16)(a > b ? (S32)a - b : (S32)b - a); }

PUBLIC U32 AbsDiffU32(U32 a, U32 b)
    { return a > b ? a - b : b - a; }

PUBLIC S32 MinusS32(S32 n)
	{ return n == MIN_S32 ? MAX_S32 : -n; }		// Negative of the most negative signed int is not defined.

PUBLIC U8 AminusBU8(U8 a, U8 b)
    { return a > b ? a - b : 0; }

PUBLIC U16 AminusBU16(U16 a, U16 b)
    { return a > b ? a - b : 0; }

PUBLIC U32 AminusBU32(U32 a, U32 b)
    { return a > b ? a - b : 0; }

PUBLIC S32 AminusBU32toS32(U32 a, U32 b)
    { return a > b ? ClipU32toS32(a - b) : (b - a > MAX_S32 ? MIN_S32 : -(S32)(b - a)); }

PUBLIC U32 AminusBS32toU32(S32 a, S32 b) {
   return
      a > b
         ? (
            b > 0
               ? a-b
               : (a - (b+MAX_S32) + MAX_S32) )
         : 0; }

PUBLIC S16 AminusBU16ToS16(U16 a, U16 b)
    { return ClipS32toS16((S32)a - (S32)b); }

PUBLIC S16 AminusBS16(S16 a, S16 b)
    { return ClipS32toS16((S32)a - (S32)b); }

PUBLIC U8 AminusB_PtrToU8(U8 const *a, U8 const *b) {
   return
      a <= b
         ? 0
         : ( (a - b) > 0xFF
            ? 0xFF
            : a - b); }



PUBLIC U8 AplusBU8(U8 a, U8 b)
    { return a + (U16)b > MAX_U8 ? MAX_U8 : a + b; }

PUBLIC U8 Span3_U8(U8 a, U8 b, U8 c)
{
    return
        a > b
            ? (b > c
                ? (a-c)
                : (a > c
                    ? a-b
                    : c-b))
            : (b > c
                ? (c > a
                    ? b-a
                    : b-c)
                : ( b> a
                    ? c-a
                    : c-b));     // Mmmph!
}

PUBLIC U8 Median3_U8(U8 a, U8 b, U8 c)
{
    return a > b
        ? (b > c
            ? b
            : (a > c ? c : a))
        : (a > c
            ? a
            : (b > c ? c : b));     // Uuurgh!!
}

PUBLIC U8 Span4_U8(U8 a, U8 b, U8 c, U8 d)
{
    return
        MaxU8(a, MaxU8(b, MaxU8(c,d))) - MinU8(a, MinU8(b, MinU8(c,d)));
}

PUBLIC U16 SqU8(U8 a) { return (U16)a * a; }

PUBLIC U32 SqU16(U16 n) { return (U32)n * n; }

PUBLIC S32 SqS16(S16 n) { return (S32)n * n; }

PUBLIC U8 MixU8(U8 a, U8 b, U8 m)
    { return ( (MAX_U8-m)*(U16)a  +  m*(U16)b + (MAX_U8/2) + (a/2) + (b/2) + 1) >> 8; }

PUBLIC U16 MixU16(U16 a, U16 b, U8 m)
{
    return
        ((a == 0 && m == 0) || (b == 0 && m == MAX_U8))                         // Wiper all at an end which is zero?
            ? 0                                                                 // then return 0
            : ( ((a == MAX_U16 && m == 0) || (b == MAX_U16 && m == MAX_U8))     // Wiper at and end which is max
                ? MAX_U16                                                       // then return MAX_U16
                                                                                // otherwise interpolate
                : (( (MAX_U8-m)*(U32)a  +  m*(U32)b + (MAX_U8/2) + (a/2) + (b/2) +1) >> 8) );
}


/* ----------------------------------------------------------------
|
|  Decrement 'a', but not below zero. Return 1 if 'a' was zero or
|  is zero after the operation.
|
-------------------------------------------------------------------*/

PUBLIC BIT DecrU8_NowZero(U8 * a)
{
   if( *a <= 1 )
   {
      *a = 0;
      return 1;
   }
   else
   {
      if(*a) (*a)--;
      return 0;
   }
}

/* ----------------------------------------------------------------
|
|  Decrement 'a', but not below zero. Return 1 if 'a' was '1' before
|  being decremented (and is now zero).
|
-------------------------------------------------------------------*/

PUBLIC BIT DecrU8_Was1_NowZero(U8 * a)
{
   if( *a == 0 )
   {
      return 0;
   }
   else if( *a == 1 )
   {
      *a = 0;
      return 1;
   }
   else
   {
      if(*a) (*a)--;
      return 0;
   }
}

/* -------------------------- RankU8_UpTo8 --------------------------------------

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



// --------------------------- eof -----------------------------------


