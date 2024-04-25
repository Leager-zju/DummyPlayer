cd protoc
protoc -I=. --cpp_out=../src/proto ./info.proto
cd ../build
cmake ..
make clean
make -j8