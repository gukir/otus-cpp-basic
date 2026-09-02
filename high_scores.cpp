#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

// Функция дозаписывает в файл результатов строку с именем и значением очков, если передаваемое количество попыток больше 0, и печатает таблицу результатов.
// При нулевом значении количества попыток функция только печатает таблицу результатов.
int high_scores(const int attempts_count, const std::string user_name="") {

	const std::string high_scores_filename = "high_scores.txt";

	// Write new high score to the records table
	if (attempts_count > 0)	{
		// We should open the output file in the append mode - we don't want
		// to erase previous results.
		std::ofstream out_file{high_scores_filename, std::ios_base::app};
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		// Append new results to the table:
		out_file << user_name << ' ';
		out_file << attempts_count;
		out_file << std::endl;
	} // end of score here just to mark end of the logic block of code

	// Read the high score file and print all results
	{
		std::ifstream in_file{high_scores_filename};
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		std::cout << "High scores table:" << std::endl;

        std::unordered_map<std::string, int> hs_table;
		std::string username;
		int high_score = 0;
		while (true) {
			// Read the username first
			in_file >> username;
			// Read the high score next
			in_file >> high_score;
			// Ignore the end of line symbol
			in_file.ignore();
            if (hs_table.count(username)) {
                if(hs_table[username] > high_score) hs_table[username] = high_score;
            } else {
                hs_table[username] = high_score;
            }


			if (in_file.fail()) {
				break;
			}
		}
        for (const auto& pair : hs_table) {
            std::cout << pair.first << "\t" << pair.second << std::endl;
        }
	}

	return 0;
}
