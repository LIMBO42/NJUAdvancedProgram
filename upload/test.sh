index=1
g++ -std=c++17 test.cpp
while [ $index -le 10 ]
do
  infile="in/input${index}.txt"
  outfile="out/output${index}.txt"
  ./a.out < ${infile} > ${outfile}
  index=$(( $index + 1 ))
done
# while [ $index -le 10 ]
# do
#   infile="in/input${index}.txt"
#   echo $index > ${infile}
#   index=$(( $index + 1 ))
# done