cd protoc
protoc -I=. --cpp_out=../src ./info.proto
cd ../build
cmake ..
make -j8