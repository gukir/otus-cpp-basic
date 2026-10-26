// console_template.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>



struct Command
{
    std::string name;
    bool(*cmd_impl)(std::vector<std::string>&);
};

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

bool ExecuteAboutCommand(std::vector<std::string>& args)
{
    std::cout << "COMMAND EXECUTOR PROGRAM" << std::endl;

    return true;
}

std::vector<std::string> ParseCommand(std::string& command, char split_token)
{
    std::vector<std::string> result;

    /*for (int i = 0; i < command.size(); ++i) {
        command[i];
    }*/
     
    for (auto it = command.begin(); it < command.end(); it++) {

        if (*it != split_token) {
            std::string tmp;
            std::string::iterator j = it;

            while (j < command.end() && *j != split_token) {
                tmp += *j;
                j++;
                //char demo = *j;
            }
            
            result.push_back(tmp);
            it = j;

            if (it >= command.end())
                return result;

        }

    }

    return result;
}

bool ExecuteSumCommand(std::vector<std::string>& args)
{
    // sum 2 2
    
    if (args.size() < 3) {
        std::cout << "Invalid arguments count" << std::endl;
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

Command commands[] =
{
    {"about",ExecuteAboutCommand},
    {"sum",ExecuteSumCommand}
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
    

    //
    // sum 20 20 или sum 5 5 5 5
    // history    
    //while(true)
    //while(1)
    std::string command;
    for (;;) {
        std::getline(std::cin, command);

        std::vector<std::string> parsed = ParseCommand(command, ' ');

        Command* cmd = FindCommand(*parsed.begin());
        //Command* cmd = FindCommand(parsed[0]);

        //cmd == 0;
        if (cmd == nullptr) {
            std::cout << "Command not found" << std::endl;
            continue;
        }

        bool result = cmd->cmd_impl(parsed);

        //if(result ==false)
        if (!result) {
            std::cout << "Failed to execute command!" << std::endl;
            continue;
        }

        if (!SaveCommandToHistory(command)) {
            std::cout << "Error saving command to history" << std::endl;
        }

               
    }



    

    
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
