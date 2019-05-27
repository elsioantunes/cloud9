#!/bin/bash

TDIR=/tmp/test
rm -rf $TDIR 2> /dev/null
mkdir $TDIR

TOTAL=0
GRADE=0
for i in {00..99}
do
    TOTAL=$((TOTAL+1))
    $@ < ./in/file$i > $TDIR/file$i
    D=$(diff -w $TDIR/file$i ./out/file$i)
    if [[ "$D" == "" ]]; then
	GRADE=$((GRADE+1))
	echo "$i ok"
    else
	echo "$i not ok"
    fi
done

NOTA=$(echo "scale=2; 10*$GRADE/$TOTAL" | bc)
echo "Nota $NOTA de 10.00"
