#!/bin/bash


echo -n > c
for i in {1..100}; do
    EXPECT=$(cat "./file$i" | head -n 1)
    if [[ "$EXPECT" =~ "ERRO" ]]; then
        echo -n "."
    else
        cp ../in/file$i lol
    fi
done

