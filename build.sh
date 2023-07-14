if [ -e build ]; then
cd build
cmake .. && make -j16 && ./utm_client
else
mkdir build
cd build
cmake .. && make -j16 && ./utm_client
fi

