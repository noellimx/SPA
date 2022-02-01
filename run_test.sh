#!/bin/bash
# Include input sets here.
#SET_NAMES=("001")

SET_NAMES=("001") # // TODO. for now no autotest test yet. implementing autotester.

# Setup: binaries.

# Build paths
BINARY_PATH_AUTOTESTER="./cmake-build-debug/src/autotester/autotester"
BINARY_PATH_UNIT_TESTING="./cmake-build-debug/src/unit_testing/unit_testing"

rm -f "${BINARY_PATH_AUTOTESTER}"
rm -f "${BINARY_PATH_UNIT_TESTING}"

# Build Debug (Some magic here that needs deeper look)
cmake --build ./cmake-build-debug --target all

if [ ! -f "${BINARY_PATH_AUTOTESTER}" ]; then
  echo "ERROR: BINARY_PATH_AUTOTESTER not found"
  exit 1
fi

if [ ! -f "${BINARY_PATH_UNIT_TESTING}" ]; then
  echo "ERROR: BINARY_PATH_UNIT_TESTING not found"
  exit 1
fi

# Setup - unit testing

# Run: unit_testing

eval "${BINARY_PATH_UNIT_TESTING}"

# Setup: autotester inputs

# Paths - Test Inputs and Test Outputs
DIRECTORY_TEST="./tests"

SUBDIRECTORY_INPUTS="/inputs"
SUBDIRECTORY_OUTPUTS="/spa_logs"

DIRECTORY_TEST_INPUT="${DIRECTORY_TEST}${SUBDIRECTORY_INPUTS}"
DIRECTORY_TEST_OUTPUT="${DIRECTORY_TEST}${SUBDIRECTORY_OUTPUTS}"

# Run autotester

for t in "${SET_NAMES[@]}"; do
  eval "${BINARY_PATH_AUTOTESTER} ${DIRECTORY_TEST_INPUT}/${t}.simple ${DIRECTORY_TEST_INPUT}/${t}.pql ${DIRECTORY_TEST_OUTPUT}/${t}.xml"
  ## TO DO: Raise Failing Tests
done
