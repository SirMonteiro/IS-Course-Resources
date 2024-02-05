#!/bin/env bash
for folder in */; do
    cd "$folder"
    for file in *.png; do
        ../png_to_txt "$file" "${file%.png}.txt"
    done
    cd ..
done
