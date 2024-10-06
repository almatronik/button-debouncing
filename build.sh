mkdir -p ./build
g++ -c ./lib/button/button.cpp -I./test/test_button -DDEVENV --coverage -o ./build/button.o
g++ -c ./test/unity/unity.cpp -DDEVENV -o ./build/unity.o
g++ -c ./test/test_button/bsp.cpp -DDEVENV -o ./build/bsp.o
g++ -c ./test/test_button/test.cpp -DDEVENV -I./lib/button -I./test/test_button -o ./build/test.o
g++ ./build/test.o ./build/button.o ./build/unity.o ./build/bsp.o --coverage -o ./build/test.exe

./build/test.exe; gcovr -r . --html-details -o ./build/index.html