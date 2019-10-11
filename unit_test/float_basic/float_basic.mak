# ------------------------------------------------------------------
#
# TDD makefile for Basic Integer lib
#
# ---------------------------------------------------------------------

# Defs common to the arithmetic.
include ../arith_common_pre.mak

TARGET_BASE = float_basic

SRC_FILES := $(SRC_FILES) $(UNITYDIR)unity.c $(INTEGER_BASIC_FULLPATH) $(DUT_SRC_FULLPATH) $(HARNESS_TESTS_SRC) $(HARNESS_MAIN_SRC)

# Clean and build
include ../arith_common_build.mak

# ------------------------------- eof ------------------------------------

