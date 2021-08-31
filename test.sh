gcc main.cpp fibonacci.h


for filename in in/*.txt;do
  echo "---------- Test "$filename"  ----------"
  ./a.out $filename > out/

rm -rf *.o