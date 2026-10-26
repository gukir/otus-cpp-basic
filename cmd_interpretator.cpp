#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>

struct Command
{
    std::string name;
    bool(*cmd_impl)(std::vector<std::string>&);
};


std::vector<std::string> ParseCommand(const char* command, int cmd_len, char split_token)
{
    std::vector<std::string> result;

    for (int i = 0; i < cmd_len; ++i) {
        if (command[i] != split_token) {
            std::string tmp;
            int j = i;

            while (j < cmd_len && command[j] != split_token) {
                tmp += command[j];
                j++;
            }

            result.push_back(tmp);

            i = j;
        }
    }

    return result;
}

std::vector<std::string> ParseCommand(std::string& command, char split_token)
{


    std::vector<std::string> result;

    for (auto it = command.begin(); it < command.end(); ++it) {
        if (*it != split_token) {

            std::string tmp;
            std::string::iterator j = it;

            while (j < command.end() && *j != split_token) {
                tmp += *j;
                j++;

            }

            result.push_back(tmp);
            it = j;

            if (it >= command.end())
                return result;




        }
    }

    return result;


}

template<typename T>
void PrintVector(std::vector<T>& v)
{
    std::cout << "====VEC INFO=====" << std::endl;
    std::cout << v.size() << std::endl;
    for (auto x : v) {
        std::cout << x << std::endl;
    }
}


bool SaveCommandToHistory(std::string& cmd)
{
    if (cmd == "history") return true;
    if (cmd == "about") return true;

    std::ofstream f;

    f.open("history.txt", std::ios_base::app);

    if (!f.is_open())
        return false;

    f << cmd << '\n';

    f.close();

    return true;

}

bool ReadHistory(std::list<std::string>& history)
{
    std::ifstream f;

    f.open("history.txt");

    if (!f.is_open()) {
        std::cout << "Unable to open history file" << std::endl;
        return false;
    }

    std::string tmp;

    while (std::getline(f, tmp)) {
        history.push_back(tmp);
    }

    f.close();

    return true;

}



void PrintHistory(std::list<std::string>& history)
{
    std::cout << "=======History==========" << std::endl;
    for (auto x : history) {
        std::cout << x << std::endl;
    }

    std::cout << "========================" << std::endl;
}

bool ExecuteAboutCommand(std::vector<std::string>& args)
{
    std::cout << "This is test command executor!" << std::endl;
    return true;
}

bool ExecuteSumCommand(std::vector<std::string>& args)
{
    if (args.size() < 3) {
        std::cout << "Invalid argumants count" << std::endl;
        return false;
    }

    int sum = 0;

    for (int i = 1; i < args.size(); ++i) {
        int val = std::stoi(args[i]);
        sum += val;
    }

    std::cout << "Sum is:" << sum << std::endl;

    return true;
}

bool ExecuteHistoryCommand(std::vector<std::string>& args)
{
    std::list<std::string> h;
    if (!ReadHistory(h)) {
        std::cout << "Error Reading history file" << std::endl;
        return false;
    }

    PrintHistory(h);

    return true;
}

Command commands[] =
{
    {"about",ExecuteAboutCommand},
    {"sum",ExecuteSumCommand},
    {"history",ExecuteHistoryCommand}
};

Command* FindCommand(std::string& command_name)
{
    size_t bytes = sizeof(commands);
    size_t data_size = sizeof(commands[0]);
    size_t elements = bytes / data_size;


    for (int i = 0; i < elements; ++i) {
        if (commands[i].name == command_name) {
            return &commands[i];
        }
    }

    return nullptr;
}

int main()
{
    std::string cmd;

    for (;;) {
        std::getline(std::cin, cmd);
        std::vector<std::string> parsed = ParseCommand(cmd, ' ');
        //std::vector<std::string> parsed = ParseCommand(cmd.c_str(),cmd.size(),' ');
        //PrintVector(parsed);
        if (parsed.size() < 1) {
            std::cout << "Empty command!" << std::endl;
            continue;
        }

        std::string parsed_cmd = parsed[0];

Command* current_command = FindCommand(parsed_cmd);

if (current_command == nullptr) {
    std::cout << "Command not found" << std::endl;
    continue;
}


bool result = current_command->cmd_impl(parsed);

if (!result) {
    std::cout << "Failed to execute command!" << std::endl;
    continue;
}

if (!SaveCommandToHistory(cmd)) {
    std::cout << "Error saving command to history" << std::endl;
}


    }






}