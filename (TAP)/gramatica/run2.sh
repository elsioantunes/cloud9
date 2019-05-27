#!/bin/bash

echo -n > c
for i in {1..100}; do
    echo  >> c
    echo -n "file$i: "  >> c
    python gram.py < "./in/file$i" >> c
    echo >> c
done

