index=1
g++ -std=c++17 main.cpp
while [ $index -le 13 ]
do
  infile="in/input${index}.txt"
  outfile="out/output${index}.txt"
  ./a.out < ${infile} > ${outfile}
  index=$(( $index + 1 ))
done