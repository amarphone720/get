#!/bin/bash

# Check if a file is provided as an argument
if [ -z "$1" ]; then
    echo "Usage: $0 filename"
    exit 1
fi

# Read and print the file line by line
while IFS= read -r line; do
    ./path "$line"
done < "$1"
