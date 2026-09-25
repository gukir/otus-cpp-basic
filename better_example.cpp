#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> read_sequence() {
	std::vector<int> values;
	int v = 0;
	while (std::cin >> v) {
		values.push_back(v);
	}
	return values;
}

void print_sequence(const std::vector<int> &seq) {
	for (size_t i = 0; i < seq.size(); ++i) {
		if (i != 0)
			std::cout << ' ';
		std::cout << seq[i];
	}
	std::cout << std::endl;
}

std::vector<int> filter_even(const std::vector<int>& seq) {
	std::vector<int> evens;
	for (size_t i = 0; i < seq.size(); ++i) {
		if (seq[i] % 2 == 0) {
			evens.push_back(seq[i]);
		}
	}
	return evens;
}

// Takes a numeric sequence from the stdin
// Makes a sorting
// Prints the result
// Makes a filter for even
// Prints the result

int main() {

	std::vector<int> sequence = read_sequence();

	std::sort(sequence.begin(), sequence.end());

	print_sequence(sequence);

	std::vector<int> evens = filter_even(sequence);

	print_sequence(evens);

	return 0;
}