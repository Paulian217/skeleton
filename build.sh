if [ -e build ]; then
cd build
cmake .. && make -j16
else
mkdir build
cd build
cmake .. && make -j16 
fi

