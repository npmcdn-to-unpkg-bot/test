#include <algorithm>
#include <iostream>

// g++ --std=c++11 usage.cpp

int main(int argc, char** argv) {
	// 可以直接计算出结果
	std::cout << [](int i, int j){ return i + j; }(10, 10) << std::endl;
}