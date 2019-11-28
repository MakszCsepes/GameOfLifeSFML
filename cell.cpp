//
// Created by max on 2/11/2019.
//

#include "cell.h"
//#include "board.h"
//
//position cell::get_coords() {
//    return coords;
//}
//
//int cell::get_content() {
//    return content;
//}
//
//void cell::set_content() {
//    content == LIFE ? content = NOT_LIFE : content = LIFE;
//}
//
//void cell::draw_cell(bool is_selected) {
//    sf::RectangleShape cage(sf::Vector2f(CELL_SIZE, CELL_SIZE));
//    position pos = this->get_coords();
//    cage.setFillColor(sf::Color::Yellow);
//
//    cage.setPosition(pos.x, pos.y);
//
//    if (is_selected) {
//        cage.setOutlineThickness(2);
//        cage.setOutlineColor(sf::Color::Red);
//    }
//    window.draw(cage);
//}