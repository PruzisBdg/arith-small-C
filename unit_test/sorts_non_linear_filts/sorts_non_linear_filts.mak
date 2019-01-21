# ------------------------------------------------------------------
#
# TDD makefile for Sorts and non-linear filters
#
# ---------------------------------------------------------------------

# Defs common to the arithmetic.
include ../arith_common_pre.mak

TARGET_BASE = sorts_non_linear_filts

SRC_FILES = $(UNITYDIR)unity.c $(DUT_SRC_FULLPATH) $(HARNESS_TESTS_SRC) $(HARNESS_MAIN_SRC) $(INTEGER_BASIC_FULLPATH)

# Clean and build
include ../arith_common_build.mak

# ------------------------------- eof ------------------------------------

