# ------------------------------------------------------------------
#
# TDD makefile for Integer Interpolation Lib.
#
# ---------------------------------------------------------------------

# Defs common to the arithmetic.
include ../arith_common_pre.mak

# This is our harness.
TARGET_BASE = interp_integer

# Link these files.
SRC_FILES = $(UNITYDIR)unity.c $(DUT_SRC_FULLPATH) $(INTEGER_BASIC_FULLPATH) $(HARNESS_TESTS_SRC) $(HARNESS_MAIN_SRC)

# Clean and build
include ../arith_common_build.mak

# ------------------------------- eof ------------------------------------

