#!/bin/bash
 g++ -o fibonacci main.cpp fibonacci.cpp

index=1
while [ $index -le 9 ]
do
  infile="in/input${index}.txt"
  echo "---------- Test "$infile"  ----------"
  outfile="out/output${index}.txt"
  echo "---------- Test "$outfile"  ----------"
  ./fibonacci ${infile} >${outfile}
  index=$(( $index + 1 ))
done

rm -rf fibonacci