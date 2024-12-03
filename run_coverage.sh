#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define directories
BUILD_DIR="build"
COVERAGE_DIR="coverage"
COVERAGE_INFO="coverage.info"

# Clean and create build directory
rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR
cd $BUILD_DIR

# Run CMake with coverage flags
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage" -DCMAKE_EXE_LINKER_FLAGS="--coverage" ..

# Build the project
make

# Run the tests
./runUnitTests

# Capture coverage data
lcov --capture --directory . --output-file $COVERAGE_INFO --ignore-errors mismatch

# Remove external libraries from coverage data
lcov --remove $COVERAGE_INFO '/usr/*' --output-file $COVERAGE_INFO
lcov --remove $COVERAGE_INFO 'external/*' --output-file $COVERAGE_INFO

# Generate HTML report
genhtml $COVERAGE_INFO --output-directory $COVERAGE_DIR

# Open the coverage report in the default browser
xdg-open $COVERAGE_DIR/index.html