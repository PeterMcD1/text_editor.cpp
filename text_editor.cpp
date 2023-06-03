#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Function to get user input
int get_option(){
    std::string user_input;
    int user_input_int;
    std::getline(std::cin, user_input);
    user_input_int = std::stoi(user_input);
    return user_input_int;
}

//get new string to add to file
std::string get_user_input(){
    std::string user_input;
    std::cout << "Enter text you want to save: ";
    std::getline(std::cin, user_input);
    return user_input;
}

// function to save user input to file
void save_user_input(std::string user_input){
    std::cout << "saving '" << user_input << "' to file \n";
    std::cout << "what should the file name be? \n";
    std::string filename;
    std::getline(std::cin, filename);
    std::ofstream out(filename);
    out << user_input;
    out.close();
    return;
}

// function to read file contents
void read_file(std::string filename){
    std::ifstream in(filename);
    if (in.is_open()){
        std::string filecontents;
        std::cout << std::endl;
        int i = 1;
        while(std::getline(in, filecontents)){
            std::cout << i << ". " << filecontents << std::endl;
            i++;
        }
        std::cout << std::endl;
    }
    return;
}

// function to replace a specific line with a new line from user input
void replace_line(std::string filename, size_t linenumber, std::string newtext){
    std::fstream in(filename);
    std::vector<std::string> lines;
    std::string line;
    while(getline(in, line)) lines.push_back(line);
    in.close();

    if(linenumber >= lines.size()){
        std::cout << "Line " << linenumber << " not in file. \n";
        return;
    }

    std::ofstream out(filename);

    for (size_t i = 0; i < lines.size(); i++){
        if (i != linenumber)
            out << lines[i] << std::endl;
        else
            out << newtext << std::endl;
    }
    out.close();
}

// function to delete a specific line
void delete_line(std::string filename, size_t linenumber){
    std::fstream in(filename);
    std::vector<std::string> lines;
    std::string line;
    while(getline(in, line)) lines.push_back(line);
    in.close();

    if(linenumber >= lines.size()){
        std::cout << "Line " << linenumber << " not in file. \n";
        return;
    }

    std::ofstream out(filename);
    for (size_t i = 0; i < lines.size(); i++){
        if (i == linenumber)
            continue;
        else 
            out << lines[i] << std::endl;
    }
    out.close();

}

//function to edit file contents
void edit_file(std::string filename){
    read_file(filename);
    std::cout << "What do you want to do?\n";
    std::cout << "1. replace a line\n";
    std::cout << "2. add a new line\n";
    std::cout << "3. delete a line\n";
    int option = get_option();
    switch(option){
        case 1: {
            std::cout << "what line do you want to replace?(numerical): ";
            int linenumber = get_option();
            linenumber--;
            std::cout << "what text do you want to replace this line?\n";
            std::string newtext;
            std::getline(std::cin, newtext);
            replace_line(filename, linenumber, newtext);
            break;
        }
        case 2: {
            std::cout << "What should the text be for the new line\n";
            std::string newtext;
            std::getline(std::cin, newtext);
            std::ofstream out;
            out.open(filename, std::ios_base::app);
            out << newtext;
            out.close();
            break;
        }
        case 3: {
            std::cout << "What line do you want to delete?(numerical): ";
            int linenumber = get_option();
            linenumber--;
            delete_line(filename, linenumber);
            break;
        }
    }
}

int main(){
    while(true){
        std::cout << "Enter your option: \n";
        std::cout << "1. read file\n";
        std::cout << "2. input text to new file\n";
        std::cout << "3. edit file\n";
        std::cout << "0. to exit\n";
        int option = get_option();
        switch(option){
            case 0: { return 0; }
            case 1: {
                std::string filename;
                std::cout << "What file do you want to read?\n";
                std::getline(std::cin, filename);
                read_file(filename);
                break;
            }
            case 2: {
                std::string user_input;
                user_input = get_user_input();
                save_user_input(user_input);
                break;
            }
            case 3: {
                std::string filename;
                std::cout << "What file do you want to edit?\n";
                std::getline(std::cin, filename);
                edit_file(filename);
                break;
            }
            default: {
                std::cout << "ERROR: give a valid option\n\n";
            }
        }
    }
    return 0;
}