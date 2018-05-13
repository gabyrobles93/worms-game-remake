#!bin/bash

rm -fr build
mkdir build
cd build
cmake ..
make
cd ..
touch run.sh
chmod +x run.sh
echo "./build/client" > run.sh
