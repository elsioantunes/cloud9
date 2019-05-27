#include <map>
#include <regex>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    
    std::ifstream input(argv[1]);
    const std::regex title_regex("title=(\\d+)");
    std::smatch matcher;
    std::map<int,std::string> sorted_titles;

    std::string video;
    while (std::getline(input, video)) {

        if (std::regex_search(video, matcher, title_regex)) {
            int no = std::stoi(matcher[1].str());
            sorted_titles[no] = video;
        }
    }

    std::cout << "Valores ordenados" << std::endl;
    for (auto pair : sorted_titles) {
        std::cout << pair.first << std::endl;
    }
}