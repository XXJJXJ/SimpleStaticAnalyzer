#!/bin/bash

# Get the directory of the script
script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Change to the script's directory
cd "$script_dir"

echo "working directory: $(pwd)"

echo "========= Running cmake ============"

mkdir -p Team03/Code03/build
cd Team03/Code03/build && cmake .. &> $script_dir/cmake_output.out && make -j4 &> $script_dir/build_output.out

echo "========= Running tests ============"

cd ../tests && ../build/src/autotester/autotester Sample_source.txt Sample_queries.txt out.xml > $script_dir/test_results.out
