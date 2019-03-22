/* -----------------------------------------------------------------
|
|              Basic Floating Point
|
--------------------------------------------------------------------- */

#include "GenericTypeDefs.h"
#include <math.h>
#include "arith.h"

/* ---------------------------------- MinFloat ------------------------------- */

PUBLIC float MinFloat(float a, float b) { return a < b ? a : b; }

/* ---------------------------------- MaxFloat ------------------------------- */

PUBLIC float MaxFloat(float a, float b) { return a > b ? a : b; }


/* ---------------------------------- ClipFloatToLong ------------------------------- */

PUBLIC S32 ClipFloatToLong(float f)
{
   if( f < (float)MIN_S32 )
      return MIN_S32;
   else if( f > (float)MAX_S32 )
      return MAX_S32;
   else
      return (S32)f;
}

/* ---------------------------------- ClipFloatToU32 ------------------------------- */

PUBLIC U32 ClipFloatToU32(float f)
{
   if( f <= (float)0.0 )
      return 0;
   else if( f >= (float)MAX_U32 )
      return MAX_U32;
   else
      return (U32)f;
}

/* ---------------------------------- ClipFloatToInt ------------------------------- */

PUBLIC S16 ClipFloatToInt(float f)
{
   return ClipS32toS16(ClipFloatToLong(f));
}

/* ----------------------------------- InsideEq_Float --------------------------------- */

PUBLIC BOOL InsideEq_Float(float n, float min, float max)
    { return n >= min && n <= max; }




/*-----------------------------------------------------------------------------------
|
|  GetPwr10Float
|
|  Return 10^exp for 'exp', which may be anywhere in the legal range for floats
|  or doubles.
|
|  The table lookup method avoids using pow() (<math> power function) which is
|  slow. The function walks down the table an converges on 'exp' in at most a
|  few cycles.
|
--------------------------------------------------------------------------------------*/

typedef struct
{
   S16   exp;        // an exponent
   float num;        // 10^exp
} S_Pwr10FloatMapping;

PRIVATE S_Pwr10FloatMapping const Pwr10FloatTbl[] =
{
   {16,  1E16 },
   {8,   1E8  },
   {4,   1E4  },
   {2,   1E2  },
   {1,   10.0 }
};

PUBLIC float GetPwr10Float(S16 exp)
{
   U8    c;
   BIT   negExp;
   float f;

   if( exp == 0 )                            // 10^0?
   {
      return 1.0;                            // equals 1.0
   }
   else                                      // else must use Pwr10FloatTbl[]
   {
      /* Table is for positive exponents. Handle negative ones by flipping the
         exponent and then returning reciprocal of result from table.
      */
      if( exp < 0 )                          // Negative exponent?
      {
         negExp = 1;                         // then mark that is so
         exp = -exp;                         // and flip it.
      }
      else
         { negExp = 0; }

      for( c = 0, f = 1.0; exp; c++)            // From 1.0, and from table bottom (largest numbers)
      {
         while( exp >= Pwr10FloatTbl[c].exp )   // While remainder of exponent > this table entry
         {
            f *= Pwr10FloatTbl[c].num;          // then multiply 'f' by tables 10^exp
            exp -= Pwr10FloatTbl[c].exp;        // and consume the exponent
         }                                      // and on to try next (smaller) table entry
      }                                         // continue until 'exp' has been eaten

      // Return with 10^exp
      if( negExp )                              // Exponent was negative?
         { return 1.0f/f; }                     // then flip the table result
      else
         { return f; }                          // else return result unchanged
   }
}


/*-----------------------------------------------------------------------------------
|
|  Mod_Float
|
|  Returns 'n' mod 'd'.
|
--------------------------------------------------------------------------------------*/

PUBLIC float Mod_Float(float n, float d)
{
    float m;

    if(d == 0.0f)
    {
        return 0.0;
    }
    else
    {
        m = floor(n/d);
        return MinFloat(n-(m*d), (d * (m+1)) - n);
    }
}



// ------------------------------------ eof ------------------------------------------------------
