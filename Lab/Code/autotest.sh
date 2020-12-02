#!/bin/bash
for file in ../Tests/*.cmm; do
    echo $file
    ./parser $file "$file.output"
done