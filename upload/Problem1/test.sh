#!/bin/bash
 g++ -o Queue main.cpp Queue.cpp List.cpp

index=1


while [ $index -le 20 ]
do
  infile="in/input${index}.txt"
  outfile="now/output${index}.txt"
  echo "---------- Test "$outfile"  ----------"
 ./Queue <${infile} >${outfile}
  index=$(( $index + 1 ))
done

while [ $index -le 20 ]
do
  realfile="now/output${index}.txt"
  outfile="out/output${index}.txt"
  echo "---------- Test "$outfile"  ----------"
  diff ${realfile} ${outfile}
  index=$(( $index + 1 ))
done





# while [ $index -le 20 ]
# do
#   outfile="in/input${index}.txt"
#   realout="real/output${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./Queue 10000 6 ${outfile} >${realout}
#   index=$(( $index + 1 ))
# done
rm -rf Queue