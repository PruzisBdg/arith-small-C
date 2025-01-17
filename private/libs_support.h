#ifndef LIBS_SUPPORT_H
#define LIBS_SUPPORT_H

#include "spj_stdint.h"

#define TOOL_CC430   1
#define TOOL_GCC_ARM 2
#define TOOL_GCC_X86 3

#ifdef __TOOL_IS_CC430
   #define _TOOL_IS TOOL_CC430
#else
   #ifdef __TOOL_IS_GCC_ARM
      #define _TOOL_IS TOOL_GCC_ARM
   #else
      #ifdef __TOOL_IS_GCC_X86
         #define _TOOL_IS TOOL_GCC_X86
      #else
         #error "_TOOL_IS must be defined"
      #endif
   #endif
#endif

#endif // LIBS_SUPPORT_H
