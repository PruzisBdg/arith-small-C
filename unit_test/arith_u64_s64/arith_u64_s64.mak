# ------------------------------------------------------------------
#
# TDD makefile for Basic Integer lib
#
# ---------------------------------------------------------------------

# Defs common to the arithmetic.
include ../arith_common_pre.mak

TARGET_BASE = arith_u64_s64

SRC_FILES := $(SRC_FILES) $(UNITYDIR)unity.c $(DUT_SRC_FULLPATH) $(HARNESS_TESTS_SRC) $(HARNESS_MAIN_SRC)

# Clean and build
include ../arith_common_build.mak

# ------------------------------- eof ------------------------------------

