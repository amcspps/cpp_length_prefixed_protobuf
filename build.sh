if [ -d "build" ]; then
    cd build
else
    mkdir "build"
    cd build
fi


cmake ..

if [[ $? -eq 0 ]]
then
	make
fi
mv protobuf_parser ..
mv  test/message_test ..
#rm -rf CMakeFiles cmake_install.cmake CMakeCache.txt Makefile src CTestTestfile.cmake test/