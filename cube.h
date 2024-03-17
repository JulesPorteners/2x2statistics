#ifndef CUBE_H
#define CUBE_H

#include "types.h"

#define ORANGE 0
#define RED 1
#define YELLOW 2
#define WHITE 3
#define BLUE 4
#define GREEN 5

struct cube{
    //u64 stickers[x coordinate][y coordinate][z coordinate][direction (0 = x, 1 = y, 2 = z)];
    u64 stickers[2][2][2][3];
};

void cube_constructor(struct cube* c){
    c->stickers[0][0][0][0] = ORANGE;
    c->stickers[0][0][1][0] = ORANGE;
    c->stickers[0][1][0][0] = ORANGE;
    c->stickers[0][1][1][0] = ORANGE;
    c->stickers[1][0][0][0] = RED;
    c->stickers[1][0][1][0] = RED;
    c->stickers[1][1][0][0] = RED;
    c->stickers[1][1][1][0] = RED;
    c->stickers[0][0][0][1] = YELLOW;
    c->stickers[0][0][1][1] = YELLOW;
    c->stickers[1][0][0][1] = YELLOW;
    c->stickers[1][0][1][1] = YELLOW;
    c->stickers[0][1][0][1] = WHITE;
    c->stickers[0][1][1][1] = WHITE;
    c->stickers[1][1][0][1] = WHITE;
    c->stickers[1][1][1][1] = WHITE;
    c->stickers[0][0][0][2] = BLUE;
    c->stickers[0][1][0][2] = BLUE;
    c->stickers[1][0][0][2] = BLUE;
    c->stickers[1][1][0][2] = BLUE;
    c->stickers[0][0][1][2] = GREEN;
    c->stickers[0][1][1][2] = GREEN;
    c->stickers[1][0][1][2] = GREEN;
    c->stickers[1][1][1][2] = GREEN;
}

void cube_move_R_normal(struct cube* c){
    u64 temp;
    temp = c->stickers[1][0][0][1];
    c->stickers[1][0][0][1] = c->stickers[1][1][0][2];
    c->stickers[1][1][0][2] = c->stickers[1][1][1][1];
    c->stickers[1][1][1][1] = c->stickers[1][0][1][2];
    c->stickers[1][0][1][2] = temp;
    temp = c->stickers[1][0][0][2];
    c->stickers[1][0][0][2] = c->stickers[1][1][0][1];
    c->stickers[1][1][0][1] = c->stickers[1][1][1][2];
    c->stickers[1][1][1][2] = c->stickers[1][0][1][1];
    c->stickers[1][0][1][1] = temp;
    temp = c->stickers[1][0][1][0];
    c->stickers[1][0][1][0] = c->stickers[1][0][0][0];
    c->stickers[1][0][0][0] = c->stickers[1][1][0][0];
    c->stickers[1][1][0][0] = c->stickers[1][1][1][0];
    c->stickers[1][1][1][0] = temp;
}

void cube_move_R_inverse(struct cube* c){
    u64 temp;
    temp = c->stickers[1][0][0][1];
    c->stickers[1][0][0][1] = c->stickers[1][0][1][2];
    c->stickers[1][0][1][2] = c->stickers[1][1][1][1];
    c->stickers[1][1][1][1] = c->stickers[1][1][0][2];
    c->stickers[1][1][0][2] = temp;
    temp = c->stickers[1][0][0][2];
    c->stickers[1][0][0][2] = c->stickers[1][0][1][1];
    c->stickers[1][0][1][1] = c->stickers[1][1][1][2];
    c->stickers[1][1][1][2] = c->stickers[1][1][0][1];
    c->stickers[1][1][0][1] = temp;
    temp = c->stickers[1][0][1][0];
    c->stickers[1][0][1][0] = c->stickers[1][1][1][0];
    c->stickers[1][1][1][0] = c->stickers[1][1][0][0];
    c->stickers[1][1][0][0] = c->stickers[1][0][0][0];
    c->stickers[1][0][0][0] = temp;
}

void cube_move_R_double(struct cube* c){
    u64 temp;
    temp = c->stickers[1][0][0][1];
    c->stickers[1][0][0][1] = c->stickers[1][1][1][1];
    c->stickers[1][1][1][1] = temp;
    temp = c->stickers[1][0][0][2];
    c->stickers[1][0][0][2] = c->stickers[1][1][1][2];
    c->stickers[1][1][1][2] = temp;
    temp = c->stickers[1][0][1][0];
    c->stickers[1][0][1][0] = c->stickers[1][1][0][0];
    c->stickers[1][1][0][0] = temp;
    temp = c->stickers[1][0][1][1];
    c->stickers[1][0][1][1] = c->stickers[1][1][0][1];
    c->stickers[1][1][0][1] = temp;
    temp = c->stickers[1][0][1][2];
    c->stickers[1][0][1][2] = c->stickers[1][1][0][2];
    c->stickers[1][1][0][2] = temp;
    temp = c->stickers[1][1][1][0];
    c->stickers[1][1][1][0] = c->stickers[1][0][0][0];
    c->stickers[1][0][0][0] = temp;
}

void cube_move_U_normal(struct cube* c){
    u64 temp;
    temp = c->stickers[0][1][0][1];
    c->stickers[0][1][0][1] = c->stickers[0][1][1][1];
    c->stickers[0][1][1][1] = c->stickers[1][1][1][1];
    c->stickers[1][1][1][1] = c->stickers[1][1][0][1];
    c->stickers[1][1][0][1] = temp;
    temp = c->stickers[0][1][0][2];
    c->stickers[0][1][0][2] = c->stickers[0][1][1][0];
    c->stickers[0][1][1][0] = c->stickers[1][1][1][2];
    c->stickers[1][1][1][2] = c->stickers[1][1][0][0];
    c->stickers[1][1][0][0] = temp;
    temp = c->stickers[0][1][1][2];
    c->stickers[0][1][1][2] = c->stickers[1][1][1][0];
    c->stickers[1][1][1][0] = c->stickers[1][1][0][2];
    c->stickers[1][1][0][2] = c->stickers[0][1][0][0];
    c->stickers[0][1][0][0] = temp;
}

void cube_move_U_inverse(struct cube* c){
    u64 temp;
    temp = c->stickers[0][1][0][1];
    c->stickers[0][1][0][1] = c->stickers[1][1][0][1];
    c->stickers[1][1][0][1] = c->stickers[1][1][1][1];
    c->stickers[1][1][1][1] = c->stickers[0][1][1][1];
    c->stickers[0][1][1][1] = temp;
    temp = c->stickers[0][1][0][2];
    c->stickers[0][1][0][2] = c->stickers[1][1][0][0];
    c->stickers[1][1][0][0] = c->stickers[1][1][1][2];
    c->stickers[1][1][1][2] = c->stickers[0][1][1][0];
    c->stickers[0][1][1][0] = temp;
    temp = c->stickers[0][1][1][2];
    c->stickers[0][1][1][2] = c->stickers[0][1][0][0];
    c->stickers[0][1][0][0] = c->stickers[1][1][0][2];
    c->stickers[1][1][0][2] = c->stickers[1][1][1][0];
    c->stickers[1][1][1][0] = temp;
}

void cube_move_U_double(struct cube* c){
    u64 temp;
    temp = c->stickers[0][1][0][1];
    c->stickers[0][1][0][1] = c->stickers[1][1][1][1];
    c->stickers[1][1][1][1] = temp;
    temp = c->stickers[0][1][0][2];
    c->stickers[0][1][0][2] = c->stickers[1][1][1][2];
    c->stickers[1][1][1][2] = temp;
    temp = c->stickers[0][1][1][0];
    c->stickers[0][1][1][0] = c->stickers[1][1][0][0];
    c->stickers[1][1][0][0] = temp;
    temp = c->stickers[0][1][1][1];
    c->stickers[0][1][1][1] = c->stickers[1][1][0][1];
    c->stickers[1][1][0][1] = temp;
    temp = c->stickers[0][1][1][2];
    c->stickers[0][1][1][2] = c->stickers[1][1][0][2];
    c->stickers[1][1][0][2] = temp;
    temp = c->stickers[1][1][1][0];
    c->stickers[1][1][1][0] = c->stickers[0][1][0][0];
    c->stickers[0][1][0][0] = temp;
}

void cube_move_F_normal(struct cube* c){
    u64 temp;
    temp = c->stickers[0][0][1][1];
    c->stickers[0][0][1][1] = c->stickers[1][0][1][0];
    c->stickers[1][0][1][0] = c->stickers[1][1][1][1];
    c->stickers[1][1][1][1] = c->stickers[0][1][1][0];
    c->stickers[0][1][1][0] = temp;
    temp = c->stickers[0][0][1][2];
    c->stickers[0][0][1][2] = c->stickers[1][0][1][2];
    c->stickers[1][0][1][2] = c->stickers[1][1][1][2];
    c->stickers[1][1][1][2] = c->stickers[0][1][1][2];
    c->stickers[0][1][1][2] = temp;
    temp = c->stickers[0][1][1][1];
    c->stickers[0][1][1][1] = c->stickers[0][0][1][0];
    c->stickers[0][0][1][0] = c->stickers[1][0][1][1];
    c->stickers[1][0][1][1] = c->stickers[1][1][1][0];
    c->stickers[1][1][1][0] = temp;
}

void cube_move_F_inverse(struct cube* c){
    u64 temp;
    temp = c->stickers[0][0][1][1];
    c->stickers[0][0][1][1] = c->stickers[0][1][1][0];
    c->stickers[0][1][1][0] = c->stickers[1][1][1][1];
    c->stickers[1][1][1][1] = c->stickers[1][0][1][0];
    c->stickers[1][0][1][0] = temp;
    temp = c->stickers[0][0][1][2];
    c->stickers[0][0][1][2] = c->stickers[0][1][1][2];
    c->stickers[0][1][1][2] = c->stickers[1][1][1][2];
    c->stickers[1][1][1][2] = c->stickers[1][0][1][2];
    c->stickers[1][0][1][2] = temp;
    temp = c->stickers[0][1][1][1];
    c->stickers[0][1][1][1] = c->stickers[1][1][1][0];
    c->stickers[1][1][1][0] = c->stickers[1][0][1][1];
    c->stickers[1][0][1][1] = c->stickers[0][0][1][0];
    c->stickers[0][0][1][0] = temp;
}

void cube_move_F_double(struct cube* c){
    u64 temp;
    temp = c->stickers[0][0][1][1];
    c->stickers[0][0][1][1] = c->stickers[1][1][1][1];
    c->stickers[1][1][1][1] = temp;
    temp = c->stickers[0][0][1][2];
    c->stickers[0][0][1][2] = c->stickers[1][1][1][2];
    c->stickers[1][1][1][2] = temp;
    temp = c->stickers[0][1][1][0];
    c->stickers[0][1][1][0] = c->stickers[1][0][1][0];
    c->stickers[1][0][1][0] = temp;
    temp = c->stickers[0][1][1][1];
    c->stickers[0][1][1][1] = c->stickers[1][0][1][1];
    c->stickers[1][0][1][1] = temp;
    temp = c->stickers[0][1][1][2];
    c->stickers[0][1][1][2] = c->stickers[1][0][1][2];
    c->stickers[1][0][1][2] = temp;
    temp = c->stickers[1][1][1][0];
    c->stickers[1][1][1][0] = c->stickers[0][0][1][0];
    c->stickers[0][0][1][0] = temp;
}

void cube_move(struct cube* c, u64 m){
    switch(m){
        case 0: cube_move_R_normal(c); break;
        case 1: cube_move_R_inverse(c); break;
        case 2: cube_move_R_double(c); break;
        case 3: cube_move_U_normal(c); break;
        case 4: cube_move_U_inverse(c); break;
        case 5: cube_move_U_double(c); break;
        case 6: cube_move_F_normal(c); break;
        case 7: cube_move_F_inverse(c); break;
        case 8: cube_move_F_double(c); break;
    }
}

#endif