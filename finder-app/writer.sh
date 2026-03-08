#!/bin/bash

# Check number of arguments
if [ $# -ne 2 ]; then
    echo "Error: Two arguments required."
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

writefile=$1
writestr=$2

# Extract directory path
dirpath=$(dirname "$writefile")

# Create directory path if it does not exist
mkdir -p "$dirpath"

# Write string to file (overwrite if exists)
echo "$writestr" > "$writefile"

# Check if file was created successfully
if [ $? -ne 0 ]; then
    echo "Error: Could not create file $writefile"
    exit 1
fi

