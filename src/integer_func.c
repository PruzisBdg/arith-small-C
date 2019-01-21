/* -----------------------------------------------------------------
|
|               Godzilla Front,  Integer Functions
|
--------------------------------------------------------------------- */

#include "GenericTypeDefs.h"
#include "arith.h"

/* ----------------------------- SqrtU16 ---------------------------------------

   Returns the square root of the ABSOLUTE value of 'n'. Uses successive aproximation.
   Will terminate in 8 loops or less. Much faster than any method conventionally used with
   real numbers.

   This root-finder has minimum DNL; meaning the crossover between integer root
   r and r+1 is mid-way between r^2 and (r+1)^2.
*/
PUBLIC U8 SqrtU16(U16 n)
{
   U16   u;
   U8  root, step;

   if( n == 0 )
      { return 0; }
   else
   {
      for( root = 128U, step = 64U, u = 128U*128U; step > 0; step >>= 1 ) {

         root = u > n
                    ? root - step
                    : root + step;
         
         u = root * (U16)root;
         }

      // Adjust SAR result for equi-sized bins, centered on exact root.
      return
        n > u + root && root != MAX_U8  // Bin-up? (except 255 we are already at top)
            ? root+1
            : (n < u - root             // Bin down?
                ? root-1
                : root);                // else already correctly binned; leaver unchanged.
   }
}

/* ----------------------------- SqrtU32 ---------------------------------------

   Returns the square root of the absolute value of 'n'. Uses successive aproximation.
   Will terminate in 16 loops or less.
*/
PUBLIC U16 SqrtU32(U32 n)
{

   U32   u;
   U16   root, step;

   if( n == 0 ) return 0;

   for( root = 32768U, step = 16384U, u = 32768LU * 32768LU; step > 0; step >>= 1 ) {
        root = u > n
                ? root - step
                : root + step;

        u = root * (U32)root;
        }
  // Adjust SAR result for equi-sized bins, centered on exact root.
  return
    n > u + root && root != MAX_U16 // Bin-up? (except 65535 we are already at top)
        ? root+1
        : (n < u - root             // Bin down?
            ? root-1
            : root);                // else already correctly binned; leaver unchanged.
}




PUBLIC U16 RootSumSqU16(U16 a, U16 b)
{
    return SqrtU32(AplusBU32((U32)a*a, (U32)b*b));
}

PUBLIC U16 RootSumSqS16(S16 a, S16 b)
{
    return SqrtU32(AplusBU32( (U32)(a*(S32)a), (U32)(b*(S32)b) ));
}



PUBLIC U8 RootSumSqU8(U8 a, U8 b)
{
    return SqrtU16(AplusB_U16(a*(U16)a, b*(U16)b));
}

/* -------------------------- SigmaSqU8 --------------------------------------------

   Quadratic approximation of the sigma function.
*/

PUBLIC U8 SigmaSqU8(U8 n)
{
    return
        n < 128
            ? SqU8(n) >> 7
            : 255 - ((SqU8(255 - n) + 255 - n) >> 7);
}





// ---------------------------- eof ---------------------------------------