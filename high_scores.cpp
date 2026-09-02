#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>

// Функция дозаписывает в файл результатов строку с именем и значением очков, если передаваемое количество попыток больше 0, и печатает таблицу результатов.
// При нулевом значении количества попыток функция только печатает таблицу результатов.
int high_scores(const int attempts_count, const std::string user_name="") {

	const std::string high_scores_filename = "high_scores.txt";
    std::unordered_map<std::string, int> hs_table;
    std::string username;
    int high_score = 0;
	// Write new high score to the records table
	if (attempts_count > 0)	{
        if(std::filesystem::exists(high_scores_filename)){
            // Если файл существует, читаем таблицу результатов и записываем в map
            std::ifstream hs_file{high_scores_filename};
            if (!hs_file.is_open()) {
                std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
                return -1;
            }
            while (true) {
                // Read the username first
                hs_file >> username;
                // Read the high score next
                hs_file >> high_score;
                // Ignore the end of line symbol
                hs_file.ignore();
                hs_table[username] = high_score;

                if (hs_file.fail()) {
                    break;
                }
            }
            // Если пользователь уже есть в таблице, перезаписываем результат, если он меньше
            if (hs_table.count(user_name)) {
                if(hs_table[user_name] > attempts_count) hs_table[user_name] = attempts_count;
            } else {
                // Иначе добавляем новый результат
                hs_table[user_name] = attempts_count;
            }
        } else {
            // При отсутствии файла просто добавляем новый результат
            hs_table[user_name] = attempts_count;
        }
		// We should open the output file in the append mode - we don't want
		// to erase previous results.
        std::ofstream out_file{high_scores_filename, std::ios_base::out};

		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

        // Write results to the table:
        for (const auto& pair : hs_table) {
            out_file << pair.first << " " << pair.second << std::endl;
        }
	} // end of score here just to mark end of the logic block of code

	// Read the high score file and print all results
	{
		std::ifstream in_file{high_scores_filename};
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		std::cout << "High scores table:" << std::endl;

        hs_table.clear();
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
