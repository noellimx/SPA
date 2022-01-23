#!/bin/bash
# Include input sets here.
SET_NAMES=("001")




# Build
BINARY_PATH="./cmake-build-debug/src/autotester/autotester"

rm -f "${BINARY_PATH}"
# Build Debug (Some magic here that needs deeper look)
cmake --build ./cmake-build-debug --target all

if [ ! -f "${BINARY_PATH}" ]; then
  echo "ERROR: Binary not found"
  exit 1
fi

# Path - Test Inputs and Test Outputs
DIRECTORY_TEST="./tests"

SUBDIRECTORY_INPUTS="/inputs"
SUBDIRECTORY_OUTPUTS="/spa_logs"

DIRECTORY_TEST_INPUT="${DIRECTORY_TEST}${SUBDIRECTORY_INPUTS}"
DIRECTORY_TEST_OUTPUT="${DIRECTORY_TEST}${SUBDIRECTORY_OUTPUTS}"

# Run autotest on input sets

for t in "${SET_NAMES[@]}"; do
  eval "${BINARY_PATH} ${DIRECTORY_TEST_INPUT}/${t}.simple ${DIRECTORY_TEST_INPUT}/${t}.pql ${DIRECTORY_TEST_OUTPUT}/${t}.xml"
  ## TO DO: Raise Failing Tests
done
