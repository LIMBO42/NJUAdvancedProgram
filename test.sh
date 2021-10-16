index=1
while [ $index -le 14 ]
do
  infile="upload/in/input${index}.txt"
  
  echo $index > ${infile} 
  index=$(( $index + 1 ))
done