#!/bin/bash
for file in ../Tests/*.cmm; do
    echo $file
    ./parser $file "$file.ir"
done