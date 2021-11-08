index=1
g++ -std=c++17 Card.cpp Vehicle.cpp ParkSystem.cpp main.cpp
while [ $index -le 10 ]
do
  infile="in/input${index}.txt"
  outfile="out/output${index}.txt"
  ./a.out < ${infile} > ${outfile}
  index=$(( $index + 1 ))
done
#index=1;
#while [ $index -le 10 ]
#do
#   infile="in/input${index}.txt"
#   echo $index > ${infile}
#   index=$(( $index + 1 ))
#done