//
// Created by max on 2/11/2019.
//

#ifndef GOL_SFML_BOARD_H

#define GOL_SFML_BOARD_H
#endif //GOL_SFML_BOARD_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "cell.h"
#include <iostream>
#include <fstream>

using namespace std;
const int height_of_map = 1000;
const int width_of_map = 1000;

const int cells_in_row = 25;
const int cells_in_column = 25;

const int frame_size = 26;
const int cell_size = 24;

const int life = 1;
const int not_life = 0;

const int board_offset = 200;
typedef unsigned char uc;

sf::RenderWindow window(sf::VideoMode(height_of_map, width_of_map), "Game of Life");
sf::SoundBuffer buffer;
sf::Sound action_sound;

//Logic---------------------------------------------------------
void create_board(cell **array) {
    for(int i = 0 ; i < cells_in_row; i++) {
        array[i] = new cell[cells_in_column];
        for(int j = 0 ; j < cells_in_column ; j++) {
            array[i][j] = cell(j, i);
        }
    }
}
void delete_board(cell **board) {
    for(int i = 0 ; i < cells_in_row ; i++) {
        delete[] board[i];
    }

    delete(board);
}
void **clear_board (cell **board) {
    for(int i = 0 ; i < cells_in_row ; i++) {
        for(int j = 0 ; j < cells_in_column ; j++) {

            board[i][j].clear_content();
        }
    }
}
void save_game (cell **board) {

    ofstream fout;
    uc cell_content;
    fout.open("life.bin", ios_base::trunc | ios_base::binary);

    if (fout.is_open()) {

        for (int i = 0 ; i < cells_in_row ; i++) {
            for (int j = 0 ; j < cells_in_column ; j++) {
                cell_content = board[i][j].get_content();
                fout.write((char *) &cell_content , sizeof(unsigned char));
            }
        }

        fout.close();
    }
}

void load_game (cell **board) {
    ifstream fin("life.bin" , std::ios::binary);
    uc cell_content;
    for (int i = 0 ; i < cells_in_row ; i++) {

        for (int j = 0 ; j < cells_in_column ; j++) {
            fin.read((char *)&cell_content , sizeof(unsigned char));
            board[i][j].set_content(cell_content);
        }

    }

    fin.close();

}
int check_neighbours_up(cell **board, int j, int i) {
    int counter = 0;

    if (j == 0) {
        // board[-1][-1]
        if (board[cells_in_row - 1][cells_in_column - 1].get_content()) {
            counter++;
        }
        // board[-1][0]
        if (board[cells_in_row - 1][0].get_content()) {
            counter++;
        }
        // board[-1][1]
        if (board[cells_in_row - 1][1].get_content()) {
            counter++;
        }
        // board[0][-1]
        if (board[0][cells_in_column - 1].get_content()) {
            counter++;
        }
        // board[0][+1]
        if (board[0][1].get_content()) {
            counter++;
        }
        // board[+1][-1]
        if (board[1][cells_in_column - 1].get_content()) {
            counter++;
        }
        // board[+1][0]
        if (board[1][0].get_content()) {
            counter++;
        }
        // board[+1][+1]
        if (board[1][1].get_content()) {
            counter++;
        }
    } else if (j == (cells_in_column - 1)) {
        // board[-1][-1]
        if (board[cells_in_row - 1][cells_in_column - 2].get_content()) {
            counter++;
        }
        // board[-1][0]
        if (board[cells_in_row - 1][cells_in_column - 1].get_content()) {
            counter++;
        }
        // board[-1][1]
        if (board[cells_in_row - 1][0].get_content()) {
            counter++;
        }
        // board[0][-1]
        if (board[0][cells_in_column - 2].get_content()) {
            counter++;
        }
        // board[0][+1]
        if (board[0][0].get_content()) {
            counter++;
        }
        // board[+1][-1]
        if (board[1][cells_in_column - 2].get_content()) {
            counter++;
        }
        // board[+1][0]
        if ( board[1][cells_in_column - 1].get_content()) {
            counter++;
        }
        // board[+1][+1]
        if (board[1][0].get_content()) {
            counter++;
        }
    } else {
        // board[-1][-1]
        if (board[cells_in_row - 1][j - 1].get_content()) {
            counter++;
        }
        // board[-1][0]
        if (board[cells_in_row - 1][j].get_content()) {
            counter++;
        }
        // board[-1][+1]
        if (board[cells_in_row - 1] [j + 1].get_content()) {
            counter++;
        }
        // board[0][-1]
        if (board[i][j - 1].get_content()) {
            counter++;
        }
        // board[0][+1]
        if (board[i][j + 1].get_content()) {
            counter++;
        }
        // board[+1][-1]
        if (board[i + 1][j - 1].get_content()) {
            counter++;
        }
        // board[+1][0]
        if (board[i + 1][j].get_content()) {
            counter++;
        }
        // board[+1][+1]
        if (board[i + 1][j + 1].get_content()) {
            counter++;
        }
    }

    return counter;
}
int check_neighbours_left(cell **board, int j, int i) {
    int counter = 0;

    // board[-1][-1]
    if (board[i - 1][cells_in_column - 1].get_content()) {
        counter++;
    }
    // board[-1][0]
    if (board[i - 1][j].get_content()) {
        counter++;
    }
    // board[-1][+1]
    if (board[i - 1][j + 1].get_content()) {
        counter++;
    }
    // board[0][-1]
    if (board[i][cells_in_column - 1].get_content()) {
        counter++;
    }
    // board[0][+1]
    if (board[i][j + 1].get_content()) {
        counter++;
    }
    // board[+1][-1]
    if (board[i + 1][cells_in_column - 1].get_content()) {
        counter++;
    }
    // board[+1][0]
    if (board[i + 1][j].get_content()) {
        counter++;
    }
    // board[+1][+1]
    if (board[i + 1][j + 1].get_content()) {
        counter++;
    }

    return counter;
}
int check_neighbours_down(cell **board, int j, int i) {
    int counter = 0;

    if ( j == 0 ) {
        // board[-1][-1]
        if (board[cells_in_row - 2][cells_in_column - 1].get_content()) {
            counter++;
        }
        // board[-1][0]
        if (board[i - 1][j].get_content()) {
            counter++;
        }
        // board[-1][+1]
        if (board[i - 1] [j + 1].get_content()) {
            counter++;
        }
        // board[0][-1]
        if (board[cells_in_row - 1][cells_in_column - 1].get_content()) {
            counter++;
        }
        // board[0][+1]
        if (board[i][j + 1].get_content()) {
            counter++;
        }
        // board[+1][-1]
        if (board[0][cells_in_column - 1].get_content()) {
            counter++;
        }
        // board[+1][0]
        if (board[0][0].get_content()) {
            counter++;
        }
        // board[+1][+1]
        if (board[0][1].get_content()) {
            counter++;
        }
    } else if ( j == (cells_in_column - 1) ) {
        // board[-1][-1]
        if (board[cells_in_row - 2][cells_in_column - 2].get_content()) {
            counter++;
        }
        // board[-1][0]
        if (board[i - 1][j].get_content()) {
            counter++;
        }
        // board[-1][+1]
        if (board[cells_in_row - 2][0].get_content()) {
            counter++;
        }
        // board[0][-1]
        if (board[cells_in_row - 1][cells_in_column - 2].get_content()) {
            counter++;
        }
        // board[0][+1]
        if (board[cells_in_row - 1][0].get_content()) {
            counter++;
        }
        // board[+1][-1]
        if (board[0][cells_in_column - 2].get_content()) {
            counter++;
        }
        // board[+1][0]
        if (board[cells_in_row - 1][cells_in_column - 1].get_content()) {
            counter++;
        }
        // board[+1][+1]
        if (board[0][0].get_content()) {
            counter++;
        }
    } else {
        // board[-1][-1]
        if (board[i - 1][j - 1].get_content()) {
            counter++;
        }
        // board[-1][0]
        if (board[i - 1][j].get_content()) {
            counter++;
        }
        // board[-1][+1]
        if (board[i - 1][j + 1].get_content()) {
            counter++;
        }
        // board[0][-1]
        if (board[i][j - 1].get_content()) {
            counter++;
        }
        // board[0][+1]
        if (board[i][j + 1].get_content()) {
            counter++;
        }
        // board[+1][-1]
        if (board[0][j - 1].get_content()) {
            counter++;
        }
        // board[+1][0]
        if (board[0][j].get_content()) {
            counter++;
        }
        // board[+1][+1]
        if (board[0][j + 1].get_content()) {
            counter++;
        }
    }

    return counter;
}


int check_neighbours_right(cell **board, int j, int i) {
    int counter = 0;

    // board[-1][-1]
    if (board[i - 1][j - 1].get_content()) {
        counter++;
    }
    // board[-1][0]
    if (board[i - 1][j].get_content()) {
        counter++;
    }
    // board[-1][+1]
    if (board[i - 1][0].get_content()) {
        counter++;
    }
    // board[0][-1]
    if (board[i][j - 1].get_content()) {
        counter++;
    }
    // board[0][+1]
    if (board[i][0].get_content()) {
        counter++;
    }
    // board[+1][-1]
    if (board[i + 1][j - 1].get_content()) {
        counter++;
    }
    // board[+1][0]
    if (board[i + 1][j].get_content()) {
        counter++;
    }
    // board[+1][+1]
    if (board[i + 1][0].get_content()) {
        counter++;
    }

    return counter;
}

int check_neighbours_inside(cell **board, int j, int i) {
    int counter = 0;
    // board[-1][-1]
    if (board[i - 1][j - 1].get_content()) {
        counter++;
    }
    // board[-1][0]
    if (board[i - 1][j].get_content()) {
        counter++;
    }
    // board[-1][+1]
    if (board[i - 1][j + 1].get_content()) {
        counter++;
    }
    // board[0][-1]
    if (board[i][j - 1].get_content()) {
        counter++;
    }
    // board[0][+1]
    if (board[i][j + 1].get_content()) {
        counter++;
    }
    // board[+1][-1]
    if (board[i + 1][j - 1].get_content()) {
        counter++;
    }
    // board[+1][0]
    if (board[i + 1][j].get_content()) {
        counter++;
    }
    // board[+1][+1]
    if (board[i + 1][j + 1].get_content()) {
        counter++;
    }

    return counter;
}
int get_counter(cell **board, int i, int j) {
    int count = 0;

    if (i == 0) {
        count = check_neighbours_up(board, j, i);
    } else if (j == 0 && i != (cells_in_row - 1) ) {
        count = check_neighbours_left(board, j, i);
    } else if (i == cells_in_row - 1) {
        count = check_neighbours_down(board, j, i);
    } else if (j == cells_in_column - 1) {
        count = check_neighbours_right(board, j, i);
    } else {
        count = check_neighbours_inside(board, j, i);
    }

    return count;
}
cell **get_new_board (cell **board) {
    cell **new_map = new cell*[cells_in_row];
    int count = 0;

    create_board(new_map);

    for (int i = 0; i < cells_in_row; i++) {
        for (int j = 0; j < cells_in_column; j++) {

            count = get_counter(board, i , j);

            if (count == 3) {
                if (board[i][j].get_content() > 0) {
                    if (board[i][j].get_content() < 250) {
                        new_map[i][j].set_content(board[i][j].get_content() + 1);
                    } else {
                        new_map[i][j].set_content(250);
                    }
                } else {
                    new_map[i][j].set_content(life);
                }
            }
            if (board[i][j].get_content() > 0 && count == 2) {
                if (board[i][j].get_content() > 0) {
                    if (board[i][j].get_content() < 250) {
                        new_map[i][j].set_content(board[i][j].get_content() + 1);
                    } else {
                        new_map[i][j].set_content(250);
                    }
                } else {
                    new_map[i][j].set_content(life);
                }
            }

        }
    }

    delete_board(board);

    return new_map;
}

//Drawing-------------------------------------------------------

void draw_board(cell **board,int cursor_column, int cursor_row) {
    window.clear(sf::Color::Transparent);

    for (int i = 0 ; i < cells_in_row; i++) {
        for (int j = 0 ; j < cells_in_column; j++) {
            board[i][j].draw_cell(i == cursor_row && j == cursor_column ? true : false);
        }
    }
    window.display();
}
//Class-------------------------------------------------------

cell::cell() {
    content = not_life;
    coords.x = 0;
    coords.y = 0;
}
cell::cell(int x, int y) {
    content = not_life;
    coords.x = x;
    coords.y = y;
}
cell::~cell() {
}

position cell::get_coords() {
    return coords;
}
uc cell::get_content() {
    return content;
}
void cell::set_content(uc value) {
    content = value;
}
void cell::change_content() {
    content >= life ? content = not_life : content = life;
}
void cell::clear_content() {
    content = not_life;
}
void cell::draw_cell(bool is_selected) {
    sf::RectangleShape cage(sf::Vector2f(cell_size, cell_size));

    if (this->get_content() > 0) {
        int Color = std::min(5*this->get_content(), 255);

        cage.setFillColor(sf::Color(Color, 0 , 0));
    } else {
        cage.setFillColor(sf::Color::White);
    }
    position pos = this->get_coords();

//    cage.setFillColor(content >= life ? sf::Color::Black : sf::Color::White);

    cage.setPosition(board_offset + pos.x * (cell_size + 2), board_offset + pos.y * (cell_size + 2));

    if (is_selected) {
        cage.setOutlineThickness(2);
        cage.setOutlineColor(sf::Color::Red);
    }
    window.draw(cage);
}