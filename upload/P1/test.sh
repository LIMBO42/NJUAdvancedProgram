#!/bin/bash
 g++ -o List main.cpp List.cpp

index=1




# while [ $index -le 20 ]
# do
#   realfile="real/output${index}.txt"
#   outfile="out/output${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   diff ${realfile} ${outfile}
#   index=$(( $index + 1 ))
# done

while [ $index -le 20 ]
do
  infile="in/input${index}.txt"
  outfile="out/output${index}.txt"
  echo "---------- Test "$outfile"  ----------"
  ./List <${infile} >${outfile}
  index=$(( $index + 1 ))
done


# rm -rf in/*.txt
# rm -rf out/*.txt
# rm -rf real/*.txt


# while [ $index -le 1 ]
# do
#   outfile="in/input${index}.txt"
#   realout="real/output${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10 1 ${outfile} >${realout}
#   index=$(( $index + 1 ))
# done

# while [ $index -le 2 ]
# do
#   outfile="in/input${index}.txt"
#   realout="real/output${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10 2 ${outfile} >${realout}
#   index=$(( $index + 1 ))
# done

# while [ $index -le 3 ]
# do
#   outfile="in/input${index}.txt"
#   realout="real/output${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10 3 ${outfile} >${realout}
#   index=$(( $index + 1 ))
# done

# while [ $index -le 4 ]
# do
#   outfile="in/input${index}.txt"
#   realout="real/output${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10 4 ${outfile} >${realout}
#   index=$(( $index + 1 ))
# done

# while [ $index -le 7 ]
# do
#   outfile="in/input${index}.txt"
#   realout="real/output${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10000 1 ${outfile} >${realout}
#   index=$(( $index + 1 ))
# done
# while [ $index -le 10 ]
# do
#   outfile="in/input${index}.txt"
#   realout="real/output${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10000 2 ${outfile} >${realout}
#   index=$(( $index + 1 ))
# done
# while [ $index -le 18 ]
# do
#   outfile="in/input${index}.txt"
#   realout="real/output${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10000 3 ${outfile} >${realout}
#   index=$(( $index + 1 ))
# done
# while [ $index -le 20 ]
# do
#   outfile="in/input${index}.txt"
#   realout="real/output${index}.txt"
#   echo "---------- Test "$outfile"  ----------"
#   ./List 10000 4 ${outfile} >${realout}
#   index=$(( $index + 1 ))
# done


rm -rf List