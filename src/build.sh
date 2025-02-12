#!/bin/bash

CC="gcc"
CFLAGS="-Wall -Wextra -O2 -fopenmp"

for file in tutorial/*.c challenges/*.c; do
    if [[ -f "$file" ]]; then
        output_file="${file%.c}.out"
        echo "Compiling $file -> $output_file"
        $CC $CFLAGS "$file" -o "$output_file"
        if [[ $? -ne 0 ]]; then
            echo "Failed to compile: $file"
        fi
    fi
done
