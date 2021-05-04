#include <iostream>
#include "board.h"

using namespace std;

int main() {
    if(!buffer.loadFromFile("../Audio/beep-3.wav")) {
        return -1;
    }
    action_sound.setBuffer(buffer);

    int cursor_row = 0;
    int cursor_column = 0;

    sf::Event event;

    cell **board = new cell*[CELLS_IN_ROW];
    create_board(board);

    while(window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:

                    switch(event.key.code) {
                        case sf::Keyboard::Right:
                            cursor_column == CELLS_IN_COLLUMN - 1 ? cursor_column = 0 : cursor_column++;
                            break;
                        case sf::Keyboard::Left:
                            cursor_column == 0 ? cursor_column = CELLS_IN_COLLUMN - 1 : cursor_column--;
                            break;
                        case sf::Keyboard::Up:
                            cursor_row == 0 ? cursor_row = CELLS_IN_ROW - 1 : cursor_row--;
                            break;
                        case sf::Keyboard::Down:
                            cursor_row == CELLS_IN_ROW - 1 ? cursor_row = 0 : cursor_row++;
                            break;
                        case sf::Keyboard::Space:
                            board[cursor_row][cursor_column].change_content();
                            action_sound.play();
                            break;
                        case sf::Keyboard::C:
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                                clear_board(board);
                            }
                            break;
                        case sf::Keyboard::S:
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
                                save_game(board);
                            }

                            break;
                        case sf::Keyboard::L:
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
                                load_game(board);
                            }
                            break;
                        case sf::Keyboard::Return:
                            board = get_new_board(board);
                            action_sound.play();
                            break;
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::KeyReleased:
                    break;
            }
            draw_board(board, cursor_column, cursor_row);
        }

    }

    return 0;
}
