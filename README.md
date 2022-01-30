
# Environment

## Operating System
MacOS Monterey
## IDE
CLion
## Build Tools
CMake, ninja

# Build Steps and Binary

The preconfigured build steps should run in CLion and (repository is a CLion project). \
It is recommended to reload the project and build cache before development. See [CLion Development](#clion-development)

The binary will be found in debug or release directory. [//]: # (Where?)

# Autotester Execution

Run binary which takes in a set of 3 file paths:

## User Inputs
1. Source script in SIMPLE (.simple)
2. Queries in PQL and its expected results (.pql)
User Inputs are placed in a common directory ```./tests/inputs```.

## SPA Outputs
3. Target output stores test result. (.xml)

Output Folder: ```./tests/spa_logs```.  See [Viewing Test Result](#viewing-test-result). \
Outputs will not be persistently stored in the repository. Run execution to obtain fresh logs.

For simplicity file names in each set should have the same name and differentiated by its file extension.

## Example - Execution

```
#!/bin/bash
# Include input sets here.
SET_NAMES=("001")

# Paths

# Path - Binary
BINARY_PATH="./cmake-build-debug/src/autotester/autotester"
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
done

```

# Test Tool

## Running Multiple Executions

```./run_test.sh``` Include set names to test in the array ```SET_NAMES```

[//]: # (Run multiple executions step)

## Viewing Test Result

If python is installed, run a simple local server in the wd. \
analysis.xml is required in the same parent directory of test result file for nice formatting.

- Run server (Default url should be localhost:8000) \
``` python3 -m http.server ```

# CLion Development

## Using command line

It is recommended to open the project in Clion.

## In Clion, Adding new cpp and header files
Right click the project > Reload CMake Project 