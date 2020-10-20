#include <ncurses.h>
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <vector>
namespace fs = std::experimental::filesystem;

std::vector<std::string> get_files(std::string path) {
	std::vector<std::string> files;
	for (auto &p : fs::recursive_directory_iterator(path)){
        files.push_back(p.path().stem().string());
    }
	return files;
}

int main(){
	std::string path = "/home/user/bin/zos/";
	std::vector<std::string> files = get_files(path);
	int index = -1;
    initscr();
	for(int i = 0; i < files.size(); i++) {
		printw("%s\n", files[i].c_str());
		refresh();
	}
	while(index < 0 || index > files.size()) {
		printw("Which file to open? (0 - %d) ", files.size() - 1);
		refresh();
		char input[32];
		getstr(input);
		index = std::stoi(input);
	}
	printw("You opened: %s", (path + files[index]).c_str());
	refresh();
    endwin();
	system((path + files[index]).c_str());
    return 0;
}