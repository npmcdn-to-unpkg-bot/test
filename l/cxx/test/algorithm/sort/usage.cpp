#include <algorithm> // std::sort
#include <iostream>
#include <random>	// random methods
#include <functional> // std::bind

// g++ --std=c++11 usage.cpp

std::vector<int> get_random_vector() {
	std::vector<int> res;

	auto dice = std::bind(std::uniform_int_distribution<int>(1,20) ,std::default_random_engine());
	for (int i = 0; i < 10; i++) {
		res.push_back(dice());
	}
	return res;
}

void print_array(const char* msg, const std::vector<int>& array) {
	std::cout << "-------" << msg << "---------\n";
	for (const auto& entry : array) {
		std::cout << entry << " " ;
	}
	std::cout << std::endl;
}

// sort compare
bool compare(int a, int b) {
	return a > b;
}

// functor
struct compare_functor {
	bool operator()(int a, int b) {
		return a < b;
	}
};

int main(int argc, char* argv[]) {
	auto v = get_random_vector();
	print_array("orginal array", v);
	sort(v.begin(), v.end());
	print_array("default sort", v);

	sort(v.begin(), v.end(), compare);
	print_array("sort with function", v);

	sort(v.begin(), v.end(), compare_functor());
	print_array("sort with functor", v);

	sort(v.begin(), v.end(), [](int a, int b){ return a > b;});
	print_array("sort with lambda", v);

}