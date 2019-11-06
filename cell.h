//
// Created by max on 2/11/2019.
//

#ifndef GOL_SFML_CELL_H
#define GOL_SFML_CELL_H

typedef unsigned char uc;
struct position {
    int x;
    int y;
};

class cell {
    position coords;
    uc content;

public:
    cell();
    cell(int, int);
    ~cell();

    void set_content(uc);
    void change_content();
    void clear_content();
    uc get_content();
    position get_coords();

    void draw_cell(bool);
};


#endif //GOL_SFML_CELL_H
