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
const int HEIGHT_OF_MAP = 1000;
const int WIDTH_OF_MAP = 1000;

const int CELLS_IN_ROW = 25;
const int CELLS_IN_COLLUMN = 25;

const int FRAME_SIZE = 26;
const int CELL_SIZE = 24;

const int LIFE = 1;
const int NOT_LIFE = 0;

const int BOARD_OFFSET = 200;
typedef unsigned char uc;

sf::RenderWindow window(sf::VideoMode(HEIGHT_OF_MAP, WIDTH_OF_MAP), "Game of Life");
sf::SoundBuffer buffer;
sf::Sound action_sound;

//Logic---------------------------------------------------------
void create_board(cell **array) {
    for(int i = 0 ; i < CELLS_IN_ROW; i++) {
        array[i] = new cell[CELLS_IN_COLLUMN];
        for(int j = 0 ; j < CELLS_IN_COLLUMN ; j++) {
            array[i][j] = cell(j, i);
        }
    }
}
void delete_board(cell **board) {
    for(int i = 0 ; i < CELLS_IN_ROW ; i++) {
        delete[] board[i];
    }

    delete(board);
}
void **clear_board (cell **board) {
    for(int i = 0 ; i < CELLS_IN_ROW ; i++) {
        for(int j = 0 ; j < CELLS_IN_COLLUMN ; j++) {

            board[i][j].clear_content();
        }
    }
}
void save_game (cell **board) {

    ofstream fout;
    uc cell_content;
    fout.open("LIFE.bin", ios_base::trunc | ios_base::binary);

    if (fout.is_open()) {

        for (int i = 0 ; i < CELLS_IN_ROW ; i++) {
            for (int j = 0 ; j < CELLS_IN_COLLUMN ; j++) {
                cell_content = board[i][j].get_content();
                fout.write((char *) &cell_content , sizeof(unsigned char));
            }
        }

        fout.close();
    }
}

void load_game (cell **board) {
    ifstream fin("LIFE.bin" , std::ios::binary);
    uc cell_content;
    for (int i = 0 ; i < CELLS_IN_ROW ; i++) {

        for (int j = 0 ; j < CELLS_IN_COLLUMN ; j++) {
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
        if (board[CELLS_IN_ROW - 1][CELLS_IN_COLLUMN - 1].get_content()) {
            counter++;
        }
        // board[-1][0]
        if (board[CELLS_IN_ROW - 1][0].get_content()) {
            counter++;
        }
        // board[-1][1]
        if (board[CELLS_IN_ROW - 1][1].get_content()) {
            counter++;
        }
        // board[0][-1]
        if (board[0][CELLS_IN_COLLUMN - 1].get_content()) {
            counter++;
        }
        // board[0][+1]
        if (board[0][1].get_content()) {
            counter++;
        }
        // board[+1][-1]
        if (board[1][CELLS_IN_COLLUMN - 1].get_content()) {
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
    } else if (j == (CELLS_IN_COLLUMN - 1)) {
        // board[-1][-1]
        if (board[CELLS_IN_ROW - 1][CELLS_IN_COLLUMN - 2].get_content()) {
            counter++;
        }
        // board[-1][0]
        if (board[CELLS_IN_ROW - 1][CELLS_IN_COLLUMN - 1].get_content()) {
            counter++;
        }
        // board[-1][1]
        if (board[CELLS_IN_ROW - 1][0].get_content()) {
            counter++;
        }
        // board[0][-1]
        if (board[0][CELLS_IN_COLLUMN - 2].get_content()) {
            counter++;
        }
        // board[0][+1]
        if (board[0][0].get_content()) {
            counter++;
        }
        // board[+1][-1]
        if (board[1][CELLS_IN_COLLUMN - 2].get_content()) {
            counter++;
        }
        // board[+1][0]
        if ( board[1][CELLS_IN_COLLUMN - 1].get_content()) {
            counter++;
        }
        // board[+1][+1]
        if (board[1][0].get_content()) {
            counter++;
        }
    } else {
        // board[-1][-1]
        if (board[CELLS_IN_ROW - 1][j - 1].get_content()) {
            counter++;
        }
        // board[-1][0]
        if (board[CELLS_IN_ROW - 1][j].get_content()) {
            counter++;
        }
        // board[-1][+1]
        if (board[CELLS_IN_ROW - 1] [j + 1].get_content()) {
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
    if (board[i - 1][CELLS_IN_COLLUMN - 1].get_content()) {
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
    if (board[i][CELLS_IN_COLLUMN - 1].get_content()) {
        counter++;
    }
    // board[0][+1]
    if (board[i][j + 1].get_content()) {
        counter++;
    }
    // board[+1][-1]
    if (board[i + 1][CELLS_IN_COLLUMN - 1].get_content()) {
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
        if (board[CELLS_IN_ROW - 2][CELLS_IN_COLLUMN - 1].get_content()) {
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
        if (board[CELLS_IN_ROW - 1][CELLS_IN_COLLUMN - 1].get_content()) {
            counter++;
        }
        // board[0][+1]
        if (board[i][j + 1].get_content()) {
            counter++;
        }
        // board[+1][-1]
        if (board[0][CELLS_IN_COLLUMN - 1].get_content()) {
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
    } else if ( j == (CELLS_IN_COLLUMN - 1) ) {
        // board[-1][-1]
        if (board[CELLS_IN_ROW - 2][CELLS_IN_COLLUMN - 2].get_content()) {
            counter++;
        }
        // board[-1][0]
        if (board[i - 1][j].get_content()) {
            counter++;
        }
        // board[-1][+1]
        if (board[CELLS_IN_ROW - 2][0].get_content()) {
            counter++;
        }
        // board[0][-1]
        if (board[CELLS_IN_ROW - 1][CELLS_IN_COLLUMN - 2].get_content()) {
            counter++;
        }
        // board[0][+1]
        if (board[CELLS_IN_ROW - 1][0].get_content()) {
            counter++;
        }
        // board[+1][-1]
        if (board[0][CELLS_IN_COLLUMN - 2].get_content()) {
            counter++;
        }
        // board[+1][0]
        if (board[CELLS_IN_ROW - 1][CELLS_IN_COLLUMN - 1].get_content()) {
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
    } else if (j == 0 && i != (CELLS_IN_ROW - 1) ) {
        count = check_neighbours_left(board, j, i);
    } else if (i == CELLS_IN_ROW - 1) {
        count = check_neighbours_down(board, j, i);
    } else if (j == CELLS_IN_COLLUMN - 1) {
        count = check_neighbours_right(board, j, i);
    } else {
        count = check_neighbours_inside(board, j, i);
    }

    return count;
}
cell **get_new_board (cell **board) {
    cell **new_map = new cell*[CELLS_IN_ROW];
    int count = 0;

    create_board(new_map);

    for (int i = 0; i < CELLS_IN_ROW; i++) {
        for (int j = 0; j < CELLS_IN_COLLUMN; j++) {

            count = get_counter(board, i , j);

            if (count == 3) {
                if (board[i][j].get_content() > 0) {
                    if (board[i][j].get_content() < 250) {
                        new_map[i][j].set_content(board[i][j].get_content() + 1);
                    } else {
                        new_map[i][j].set_content(250);
                    }
                } else {
                    new_map[i][j].set_content(LIFE);
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
                    new_map[i][j].set_content(LIFE);
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

    for (int i = 0 ; i < CELLS_IN_ROW; i++) {
        for (int j = 0 ; j < CELLS_IN_COLLUMN; j++) {
            board[i][j].draw_cell(i == cursor_row && j == cursor_column ? true : false);
        }
    }
    window.display();
}
//Class-------------------------------------------------------

cell::cell() {
    content = NOT_LIFE;
    coords.x = 0;
    coords.y = 0;
}
cell::cell(int x, int y) {
    content = NOT_LIFE;
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
    content >= LIFE ? content = NOT_LIFE : content = LIFE;
}
void cell::clear_content() {
    content = NOT_LIFE;
}
void cell::draw_cell(bool is_selected) {
    sf::RectangleShape cage(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    if (this->get_content() > NOT_LIFE) {
        int Color = std::min(5*this->get_content(), 255);

        cage.setFillColor(sf::Color(Color, 0 , 0));
    } else {
        cage.setFillColor(sf::Color::White);
    }
    position pos = this->get_coords();

    cage.setPosition(BOARD_OFFSET + pos.x * (CELL_SIZE + 2), BOARD_OFFSET + pos.y * (CELL_SIZE + 2));

    if (is_selected) {
        cage.setOutlineThickness(2);
        cage.setOutlineColor(sf::Color::Red);
    }
    window.draw(cage);
}