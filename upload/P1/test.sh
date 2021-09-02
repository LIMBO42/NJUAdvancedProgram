#!/bin/bash
 g++ -o List main.cpp List.cpp

index=1

while [ $index -le 200 ]
do
  infile="in/input${index}.txt"
  outfile="out/output${index}.txt"
  echo "---------- Test "$outfile"  ----------"
  ./List <${infile} >${outfile}
  index=$(( $index + 1 ))
done
# while [ $index -le 15 ]
# do
#   outfile="in/input${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10000 1 >${outfile}
#   index=$(( $index + 1 ))
# done
# while [ $index -le 150 ]
# do
#   outfile="in/input${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10000 2 >${outfile}
#   index=$(( $index + 1 ))
# done
# while [ $index -le 190 ]
# do
#   outfile="in/input${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10000 3 >${outfile}
#   index=$(( $index + 1 ))
# done
# while [ $index -le 200 ]
# do
#   outfile="in/input${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10000 4 >${outfile}
#   index=$(( $index + 1 ))
# done
rm -rf List