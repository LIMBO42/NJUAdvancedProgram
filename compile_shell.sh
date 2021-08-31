C_OPTIONS_SHELL=$1
EXEFILE_SHELL=$2
PROBLEMPATH_SHELL=$3
USERNAME=$4
SUBMIT_NAME=$5

dos2unix fibonacci.h
dos2unix fibonacci.cpp

echo "==========fibonacci.h=============" >> $PROBLEMPATH_SHELL/$USERNAME/${SUBMIT_NAME}.cpp
cat fibonacci.h >> $PROBLEMPATH_SHELL/$USERNAME/${SUBMIT_NAME}.cpp
echo "==========fibonacci.cpp=============" >> $PROBLEMPATH_SHELL/$USERNAME/${SUBMIT_NAME}.cpp
cat fibonacci.cpp >>  $PROBLEMPATH_SHELL/$USERNAME/${SUBMIT_NAME}.cpp
echo >> $PROBLEMPATH_SHELL/$USERNAME/${SUBMIT_NAME}.cpp

cp $PROBLEMPATH_SHELL/main.cpp .

g++ -std=c++11 fibonacci.cpp  main.cpp -o $EXEFILE_SHELL