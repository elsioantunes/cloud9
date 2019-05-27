#!/bin/bash

TESTDIR=/tmp/test
mkdir -p $TESTDIR

START=$(date +%s)
TOTAL=10026
GRADE=0
for i in {1..100}; do
    #echo -n "."
    OUTPUT=$(timeout 2s python gram.py < "./in/file$i" | head -n 1)
    EXPECT=$(cat "./out/file$i" | head -n 1)
    CURRENT=$(date +%s)
    if (( CURRENT - START > 60 )); then
	    echo "Time limit exceeded (60s)."
	    break
    fi

    echo -n "file$i  ::$OUTPUT:: "  
    
    if [[ "$EXPECT" =~ "CORRETO" ]]; then
		if [[ "$OUTPUT" =~ "CORRETO" ]]; then
		    GRADE=$((GRADE+80))
		    #echo -n "CORRETO : " 
		else 
			echo -n "devia ter dito correto "
		fi
		
		
		if [[ "$OUTPUT" == "$EXPECT" ]]; then
		    GRADE=$((GRADE+48))
		    #echo class certa!
		    echo
		else
		    echo "class errada --> $EXPECT"
		fi
		
	else
		if [[ "$OUTPUT" == "ERRO" ]]; then
		    GRADE=$((GRADE+80))
		    #echo erro certo!
		    echo
		else
		    echo ERROoooooooooooooooooooooooooooooooou
		fi
    fi
done

NTOTAL=$(echo "scale=2; 10*$GRADE/$TOTAL" | bc)
echo ""
echo "Comment :=>> Nota do projeto: $NTOTAL de 10.00"
echo "Grade :=>> $NTOTAL"
