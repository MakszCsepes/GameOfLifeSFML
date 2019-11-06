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
//    content == life ? content = not_life : content = life;
//}
//
//void cell::draw_cell(bool is_selected) {
//    sf::RectangleShape cage(sf::Vector2f(cell_size, cell_size));
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