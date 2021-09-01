#!/bin/bash
 g++ -o List main.cpp List.cpp

index=1
while [ $index -le 9 ]
do
  outfile="in/input${index}.txt"
  echo "---------- Test "$outfile"  ----------"
  ./List 10000 1 >${outfile}
  index=$(( $index + 1 ))
done

rm -rf List