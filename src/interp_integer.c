/* -----------------------------------------------------------------
|
|              Integer Interpolation
|
--------------------------------------------------------------------- */

#include "spj_stdint.h"
#include "arith.h"

/* --------------------------- LinterpFromU8Tbl ----------------------------

   Linear interpolate 'x' onto 'tbl[]'. 'tbl' has up to 17 elements. 'x' is 16
   counts per table step; x: 0->255 spans a 17 element table (i.e 16 steps)

*/
PRIVATE U8 interp(U8 const *tbl, U8 x)
{
    return
        tbl[x >> 4] +
        (
            (
                (
                    (x & 0x0F) *
                    ( tbl[(x >> 4)+1] - tbl[x >> 4] )
                )
                + (1<<3)            // Add 1/2 lsb to cancel round-down.
            )
            >> 4
        );
}

PUBLIC U8 LinterpFromU8Tbl(S_ConstTblU8 const *tbl, U8 x)
{
    if((x >> 4) >= tbl->tblSize)
    {
        return tbl->theTbl[tbl->tblSize];
    }
    else
    {
        return interp(tbl->theTbl, x);
    }
}


/* --------------------------- linterpFromS16Tbl ----------------------------

   Linear interpolate 'x' onto 'tbl[]'. 'tbl' has up to 17 elements. 'x' is 256
   counts per table step; x: 0->4096 spans a 17 element table (i.e 16 steps)
*/
PUBLIC S16 LinterpFromS16Tbl_naked(S16 const *tbl, S16 x)
{
    return
        tbl[x >> 8] +
        (
            (
                (
                    (x & 0x00FF) *
                    (S32)( tbl[(x >> 8)+1] - tbl[x >> 8] )
                )
                + (1<<7)        // Add 1/2 lsb to cancel round-down.
            )
            >> 8
        );
}

PUBLIC S16 LinterpFromS16Tbl(S_ConstTblS16 const *tbl, S16 x)
{
    return LinterpFromS16Tbl_naked(tbl->theTbl, MinS16(x,  (tbl->tblSize << 8) - 1));
}





// ------------------------------------ eof ---------------------------------------------
