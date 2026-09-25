#include "../include/utils.h"

#include <algorithm>

int main() {

	std::vector<int> sequence = project::read_sequence(std::cin);

	std::sort(sequence.begin(), sequence.end());

	project::print_sequence(sequence, std::cout);

	std::vector<int> evens = project::filter_even(sequence);

	project::print_sequence(evens, std::cout);

	return 0;
}