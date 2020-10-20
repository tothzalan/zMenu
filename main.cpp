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

int main() {  
    std::string path = "/bin/zos/";
	std::vector<std::string> list = get_files(path);
    WINDOW *w;
    char item[list.size()];
    int ch, i = 0;
    bool canbreak = false;
 
    initscr();

    int x,y;
    getmaxyx(stdscr, x, y);

    w = newwin( x-1, y-1, 1, 1 );
    box( w, 0, 0 );
     
    for( i=0; i<list.size(); i++ ) {
        if( i == 0 ) 
            wattron( w, A_STANDOUT );
        else
            wattroff( w, A_STANDOUT );
        sprintf(item, "%s",  list[i].c_str());
        mvwprintw( w, i+1, 2, "%s", item );
    }
 
    wrefresh( w );
 
    i = 0;
    noecho();
    keypad( w, TRUE );
    curs_set( 0 );

    while(( ch = wgetch(w)) != 'q' && !canbreak){ 
         
            sprintf(item, "%s",  list[i].c_str()); 
            mvwprintw( w, i+1, 2, "%s", item ); 
            switch( ch ) {
                case KEY_UP:
                    i--;
                    i = ( i < 0 ) ? list.size()-1 : i;
                    break;
                case KEY_DOWN:
                    i++;
                    i = ( i > list.size()-1 ) ? 0 : i;
                    break;
                case KEY_RIGHT:
                    canbreak = true;
                    break;
            }
                wattron( w, A_STANDOUT );

                sprintf(item, "%s",  list[i].c_str());
                mvwprintw( w, i+1, 2, "%s", item);

                wattroff( w, A_STANDOUT );
    }
    delwin( w );
    endwin();
    system((path + list[i]).c_str());
}