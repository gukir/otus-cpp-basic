#include <algorithm>
#include <iostream>
#include <vector>

// Takes a numeric sequence from the stdin
// Makes a sorting
// Prints the result
// Makes a filter for even
// Prints the result


int main() {

	// Take from the stdin
	std::vector<int> values;
	int v = 0;
	while (std::cin >> v) {
		values.push_back(v);
	}

	// Makes a sorting
	std::sort(values.begin(), values.end());

	// Print the sorted result to the stdout
	for (size_t i = 0; i < values.size(); ++i) {
		if (i != 0) std::cout << ' ';
		std::cout << values[i];
	}
	std::cout << std::endl;

	// Make a filter for even
	std::vector<int> evens;
	for (size_t i = 0; i < values.size(); ++i) {
		if (values[i] % 2 == 0) {
			evens.push_back(values[i]);
		}
	}

	// Print evens to the screen
	for (size_t i = 0; i < evens.size(); ++i) {
		if (i != 0) std::cout << ' ';
		std::cout << evens[i];
	}
	std::cout << std::endl;

	return 0;
}