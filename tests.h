#ifndef TESTS_H
#define TESTS_H

#include "types.h"
#include "cube.h"
#include "hash_table.h"
#include "cubes_and_graph.h"

#define TESTS 26
u64 distances[TESTS][STATES];
u64 statistics[TESTS][12];
char description_tests[TESTS][70] = {
    "solved",
    "cll yellow",
    "cll colour neutral",
    "eg yellow",
    "eg colour neutral",
    "dr white yellow",
    "dr colour neutral",
    "tcll (including cll) yellow",
    "tcll (including cll) colour neutral",
    "teg (including eg) yellow",
    "teg (including eg) colour neutral",
    "ls (including tcll and cll) yellow",
    "ls (including tcll and cll) colour neutral",
    "CBL or TCBL yellow",
    "CBL or TCBL colour neutral",
    "eg or tcll yellow",
    "eg or tcll colour neutral",
    "teg1 (excluding eg1) colour neutral",
    "teg1 (excluding eg1) only bars colour neutral",
    "eg1ls (excluding teg1 and eg1) colour neutral",
    "eg1ls (excluding teg1 and eg1) only bars colour neutral",
    "egls (including teg and eg) colour neutral",
    "solid bar",
    "pseudo eg colour neutral",
    "pseudo cbl or tcbl colour neutral",
    "permutation only",
};

#define FILTERS 4
char description_filters[FILTERS][50] = {
    "all",
    "bar",
    "nobar",
    "solid bar",
};

#define INFINITY 37

void generate_distances(bool (*pred)(struct cube*), u64 t){
    for (u64 i = 0; i < STATES; i++){
        if ((*pred)(&cubes[i])){
            distances[t][i] = 0;
        }
        else{
            distances[t][i] = INFINITY;
        }
    }
    for (u64 j = 0; j < GOD; j++){
        bool change = false;
        for (u64 i = 0; i < STATES; i++){
            for (u64 m = 0; m < 9; m++){
                if (distances[t][i] + 1 < distances[t][graph[i][m]]){
                    distances[t][graph[i][m]] = distances[t][i] + 1;
                    change = true;
                }
            }
        }
        if (!change){
            break;
        }
    }
}

bool pred_solved(struct cube* c){
    struct cube x;
    cube_constructor(&x);
    return id(&x) == id(c);
}

bool pred_face_colourneutral(struct cube* c){ 
    for (u64 x = 0; x < 6; x++){
        bool l = c->stickers[0][0][0][0] == x && c->stickers[0][0][1][0] == x && c->stickers[0][1][0][0] == x && c->stickers[0][1][1][0] == x;
        bool r = c->stickers[1][0][0][0] == x && c->stickers[1][0][1][0] == x && c->stickers[1][1][0][0] == x && c->stickers[1][1][1][0] == x;
        bool d = c->stickers[0][0][0][1] == x && c->stickers[0][0][1][1] == x && c->stickers[1][0][0][1] == x && c->stickers[1][0][1][1] == x;
        bool u = c->stickers[0][1][0][1] == x && c->stickers[0][1][1][1] == x && c->stickers[1][1][0][1] == x && c->stickers[1][1][1][1] == x;
        bool b = c->stickers[0][0][0][2] == x && c->stickers[0][1][0][2] == x && c->stickers[1][0][0][2] == x && c->stickers[1][1][0][2] == x;
        bool f = c->stickers[0][0][1][2] == x && c->stickers[0][1][1][2] == x && c->stickers[1][0][1][2] == x && c->stickers[1][1][1][2] == x;
        if (l || r || d || u || b || f){
            return true;
        }
    }
    return false;
}

bool pred_face_yellow(struct cube* c){ 
    u64 x = YELLOW;
    bool l = c->stickers[0][0][0][0] == x && c->stickers[0][0][1][0] == x && c->stickers[0][1][0][0] == x && c->stickers[0][1][1][0] == x;
    bool r = c->stickers[1][0][0][0] == x && c->stickers[1][0][1][0] == x && c->stickers[1][1][0][0] == x && c->stickers[1][1][1][0] == x;
    bool d = c->stickers[0][0][0][1] == x && c->stickers[0][0][1][1] == x && c->stickers[1][0][0][1] == x && c->stickers[1][0][1][1] == x;
    bool u = c->stickers[0][1][0][1] == x && c->stickers[0][1][1][1] == x && c->stickers[1][1][0][1] == x && c->stickers[1][1][1][1] == x;
    bool b = c->stickers[0][0][0][2] == x && c->stickers[0][1][0][2] == x && c->stickers[1][0][0][2] == x && c->stickers[1][1][0][2] == x;
    bool f = c->stickers[0][0][1][2] == x && c->stickers[0][1][1][2] == x && c->stickers[1][0][1][2] == x && c->stickers[1][1][1][2] == x;
    return l || r || d || u || b || f;
    /*
    bool yellow = c->stickers[0][0][0][1] == YELLOW && c->stickers[0][0][1][1] == YELLOW && c->stickers[1][0][0][1] == YELLOW && c->stickers[1][0][1][1] == YELLOW;
    return yellow;*/
}

bool pred_dr_lr(struct cube* c){ 
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                if (c->stickers[x][y][z][0] != ORANGE && c->stickers[x][y][z][0] != RED){
                    return false;
                }
            }
        }
    }
    return true;
}

bool pred_dr_du(struct cube* c){ 
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                if (c->stickers[x][y][z][1] != YELLOW && c->stickers[x][y][z][1] != WHITE){
                    return false;
                }
            }
        }
    }
    return true;
}

bool pred_dr_bf(struct cube* c){ 
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                if (c->stickers[x][y][z][2] != BLUE && c->stickers[x][y][z][2] != GREEN){
                    return false;
                }
            }
        }
    }
    return true;
}

bool pred_dr(struct cube* c){ 
    return pred_dr_lr(c) || pred_dr_du(c) || pred_dr_bf(c);
}

bool filter_all(struct cube* c){
    return true;
}

bool filter_bar(struct cube* c){ 
    bool l = c->stickers[0][0][0][0] == c->stickers[0][0][1][0] ||
             c->stickers[0][0][1][0] == c->stickers[0][1][1][0] ||
             c->stickers[0][1][1][0] == c->stickers[0][1][0][0] ||
             c->stickers[0][1][0][0] == c->stickers[0][0][0][0];
    bool r = c->stickers[1][0][0][0] == c->stickers[1][0][1][0] ||
             c->stickers[1][0][1][0] == c->stickers[1][1][1][0] ||
             c->stickers[1][1][1][0] == c->stickers[1][1][0][0] ||
             c->stickers[1][1][0][0] == c->stickers[1][0][0][0];
    bool d = c->stickers[0][0][0][1] == c->stickers[0][0][1][1] ||
             c->stickers[0][0][1][1] == c->stickers[1][0][1][1] ||
             c->stickers[1][0][1][1] == c->stickers[1][0][0][1] ||
             c->stickers[1][0][0][1] == c->stickers[0][0][0][1];
    bool u = c->stickers[0][1][0][1] == c->stickers[0][1][1][1] ||
             c->stickers[0][1][1][1] == c->stickers[1][1][1][1] ||
             c->stickers[1][1][1][1] == c->stickers[1][1][0][1] ||
             c->stickers[1][1][0][1] == c->stickers[0][1][0][1];
    bool b = c->stickers[0][0][0][2] == c->stickers[0][1][0][2] ||
             c->stickers[0][1][0][2] == c->stickers[1][1][0][2] ||
             c->stickers[1][1][0][2] == c->stickers[1][0][0][2] ||
             c->stickers[1][0][0][2] == c->stickers[0][0][0][2];
    bool f = c->stickers[0][0][1][2] == c->stickers[0][1][1][2] ||
             c->stickers[0][1][1][2] == c->stickers[1][1][1][2] ||
             c->stickers[1][1][1][2] == c->stickers[1][0][1][2] ||
             c->stickers[1][0][1][2] == c->stickers[0][0][1][2];
    return l || r || d || u || b || f;
}

bool pred_CBL_or_TCBL_colour_neutral(struct cube* c){ 
    for (u64 colour = 0; colour < 6; colour += 2){  
        bool l = (c->stickers[0][0][0][0] == colour || c->stickers[0][0][0][1] == colour || c->stickers[0][0][0][2] == colour) &&
                 (c->stickers[0][0][1][0] == colour || c->stickers[0][0][1][1] == colour || c->stickers[0][0][1][2] == colour) &&
                 (c->stickers[0][1][0][0] == colour || c->stickers[0][1][0][1] == colour || c->stickers[0][1][0][2] == colour) &&
                 (c->stickers[0][1][1][0] == colour || c->stickers[0][1][1][1] == colour || c->stickers[0][1][1][2] == colour);

        bool d = (c->stickers[0][0][0][0] == colour || c->stickers[0][0][0][1] == colour || c->stickers[0][0][0][2] == colour) &&
                 (c->stickers[0][0][1][0] == colour || c->stickers[0][0][1][1] == colour || c->stickers[0][0][1][2] == colour) &&
                 (c->stickers[1][0][0][0] == colour || c->stickers[1][0][0][1] == colour || c->stickers[1][0][0][2] == colour) &&
                 (c->stickers[1][0][1][0] == colour || c->stickers[1][0][1][1] == colour || c->stickers[1][0][1][2] == colour); 

        bool b = (c->stickers[0][0][0][0] == colour || c->stickers[0][0][0][1] == colour || c->stickers[0][0][0][2] == colour) &&
                 (c->stickers[0][1][0][0] == colour || c->stickers[0][1][0][1] == colour || c->stickers[0][1][0][2] == colour) &&
                 (c->stickers[1][0][0][0] == colour || c->stickers[1][0][0][1] == colour || c->stickers[1][0][0][2] == colour) &&
                 (c->stickers[1][1][0][0] == colour || c->stickers[1][1][0][1] == colour || c->stickers[1][1][0][2] == colour); 
        if (l || d || b){
            return true;
        }
    }
    return false;
}

bool pred_CBL_or_TCBL_yellow(struct cube* c){ 
    u64 colour = YELLOW;
    bool l = (c->stickers[0][0][0][0] == colour || c->stickers[0][0][0][1] == colour || c->stickers[0][0][0][2] == colour) &&
                (c->stickers[0][0][1][0] == colour || c->stickers[0][0][1][1] == colour || c->stickers[0][0][1][2] == colour) &&
                (c->stickers[0][1][0][0] == colour || c->stickers[0][1][0][1] == colour || c->stickers[0][1][0][2] == colour) &&
                (c->stickers[0][1][1][0] == colour || c->stickers[0][1][1][1] == colour || c->stickers[0][1][1][2] == colour);
    bool d = (c->stickers[0][0][0][0] == colour || c->stickers[0][0][0][1] == colour || c->stickers[0][0][0][2] == colour) &&
                (c->stickers[0][0][1][0] == colour || c->stickers[0][0][1][1] == colour || c->stickers[0][0][1][2] == colour) &&
                (c->stickers[1][0][0][0] == colour || c->stickers[1][0][0][1] == colour || c->stickers[1][0][0][2] == colour) &&
                (c->stickers[1][0][1][0] == colour || c->stickers[1][0][1][1] == colour || c->stickers[1][0][1][2] == colour); 
    bool b = (c->stickers[0][0][0][0] == colour || c->stickers[0][0][0][1] == colour || c->stickers[0][0][0][2] == colour) &&
                (c->stickers[0][1][0][0] == colour || c->stickers[0][1][0][1] == colour || c->stickers[0][1][0][2] == colour) &&
                (c->stickers[1][0][0][0] == colour || c->stickers[1][0][0][1] == colour || c->stickers[1][0][0][2] == colour) &&
                (c->stickers[1][1][0][0] == colour || c->stickers[1][1][0][1] == colour || c->stickers[1][1][0][2] == colour); 
    return (l || d || b);
}

bool pred_cll_yellow(struct cube* c){
    u8 x = YELLOW;
    bool l = c->stickers[0][0][0][0] == x && c->stickers[0][0][1][0] == x && c->stickers[0][1][0][0] == x && c->stickers[0][1][1][0] == x
                && c->stickers[0][0][0][1] == c->stickers[0][0][1][1] && c->stickers[0][0][0][2] == c->stickers[0][1][0][2];
    bool r = c->stickers[1][0][0][0] == x && c->stickers[1][0][1][0] == x && c->stickers[1][1][0][0] == x && c->stickers[1][1][1][0] == x
                && c->stickers[1][0][0][1] == c->stickers[1][0][1][1] && c->stickers[1][0][0][2] == c->stickers[1][1][0][2];
    bool d = c->stickers[0][0][0][1] == x && c->stickers[0][0][1][1] == x && c->stickers[1][0][0][1] == x && c->stickers[1][0][1][1] == x
                && c->stickers[0][0][0][0] == c->stickers[0][0][1][0] && c->stickers[0][0][0][2] == c->stickers[1][0][0][2];
    bool u = c->stickers[0][1][0][1] == x && c->stickers[0][1][1][1] == x && c->stickers[1][1][0][1] == x && c->stickers[1][1][1][1] == x
                && c->stickers[0][1][0][0] == c->stickers[0][1][1][0] && c->stickers[0][1][0][2] == c->stickers[1][1][0][2];        
    bool b = c->stickers[0][0][0][2] == x && c->stickers[0][1][0][2] == x && c->stickers[1][0][0][2] == x && c->stickers[1][1][0][2] == x
                && c->stickers[0][0][0][0] == c->stickers[0][1][0][0] && c->stickers[0][0][0][1] == c->stickers[1][0][0][1];          
    bool f = c->stickers[0][0][1][2] == x && c->stickers[0][1][1][2] == x && c->stickers[1][0][1][2] == x && c->stickers[1][1][1][2] == x
                && c->stickers[0][0][1][0] == c->stickers[0][1][1][0] && c->stickers[0][0][1][1] == c->stickers[1][0][1][1]; 
    return l || r || d || u || b || f;
}

bool pred_cll_colour_neutral(struct cube* c){
    for (u8 x = 0; x < COLOURS; x++){
        bool l = c->stickers[0][0][0][0] == x && c->stickers[0][0][1][0] == x && c->stickers[0][1][0][0] == x && c->stickers[0][1][1][0] == x
                 && c->stickers[0][0][0][1] == c->stickers[0][0][1][1] && c->stickers[0][0][0][2] == c->stickers[0][1][0][2];
        bool r = c->stickers[1][0][0][0] == x && c->stickers[1][0][1][0] == x && c->stickers[1][1][0][0] == x && c->stickers[1][1][1][0] == x
                 && c->stickers[1][0][0][1] == c->stickers[1][0][1][1] && c->stickers[1][0][0][2] == c->stickers[1][1][0][2];
        bool d = c->stickers[0][0][0][1] == x && c->stickers[0][0][1][1] == x && c->stickers[1][0][0][1] == x && c->stickers[1][0][1][1] == x
                 && c->stickers[0][0][0][0] == c->stickers[0][0][1][0] && c->stickers[0][0][0][2] == c->stickers[1][0][0][2];
        bool u = c->stickers[0][1][0][1] == x && c->stickers[0][1][1][1] == x && c->stickers[1][1][0][1] == x && c->stickers[1][1][1][1] == x
                 && c->stickers[0][1][0][0] == c->stickers[0][1][1][0] && c->stickers[0][1][0][2] == c->stickers[1][1][0][2];        
        bool b = c->stickers[0][0][0][2] == x && c->stickers[0][1][0][2] == x && c->stickers[1][0][0][2] == x && c->stickers[1][1][0][2] == x
                 && c->stickers[0][0][0][0] == c->stickers[0][1][0][0] && c->stickers[0][0][0][1] == c->stickers[1][0][0][1];          
        bool f = c->stickers[0][0][1][2] == x && c->stickers[0][1][1][2] == x && c->stickers[1][0][1][2] == x && c->stickers[1][1][1][2] == x
                 && c->stickers[0][0][1][0] == c->stickers[0][1][1][0] && c->stickers[0][0][1][1] == c->stickers[1][0][1][1]; 
        if (l || r || d || u || b || f){
            return true;
        }
    }
    return false;
}

void twist(struct cube* c, u64 x, u64 y, u64 z){
    u8 temp = c->stickers[x][y][z][0];
    c->stickers[x][y][z][0] = c->stickers[x][y][z][1];
    c->stickers[x][y][z][1] = c->stickers[x][y][z][2];
    c->stickers[x][y][z][2] = temp;
}

bool pred_teg_including_eg_colour_neutral(struct cube* c){
    struct cube cc = *c;
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                for (u64 i = 0; i < 3; i++){
                    twist(&cc, x, y, z);
                    if (pred_face_colourneutral(&cc)){
                        return true;
                    }
                } 
            }
        }
    }
    return false;
}

bool pred_teg_including_eg_yellow(struct cube* c){
    struct cube cc = *c;
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                for (u64 i = 0; i < 3; i++){
                    twist(&cc, x, y, z);
                    if (pred_face_yellow(&cc)){
                        return true;
                    }
                } 
            }
        }
    }
    return false;
}

bool pred_tcll_including_cll_colour_neutral(struct cube* c){
    struct cube cc = *c;
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                for (u64 i = 0; i < 3; i++){
                    twist(&cc, x, y, z);
                    if (pred_cll_colour_neutral(&cc)){
                        return true;
                    }
                } 
            }
        }
    }
    return false;
}

bool pred_tcll_including_cll_yellow(struct cube* c){
    struct cube cc = *c;
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                for (u64 i = 0; i < 3; i++){
                    twist(&cc, x, y, z);
                    if (pred_cll_yellow(&cc)){
                        return true;
                    }
                } 
            }
        }
    }
    return false;
}

bool pred_ls_including_tcll_and_cll_colour_neutral(struct cube* c){
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                u64 count = 0;
                if (c->stickers[x][y][z][1] == c->stickers[1 - x][y][z][1] && c->stickers[x][y][z][2] == c->stickers[1 - x][y][z][2]){
                    count++;
                }
                if (c->stickers[x][y][z][0] == c->stickers[x][1 - y][z][0] && c->stickers[x][y][z][2] == c->stickers[x][1 - y][z][2]){
                    count++;
                }
                if (c->stickers[x][y][z][0] == c->stickers[x][y][1 - z][0] && c->stickers[x][y][z][1] == c->stickers[x][y][1 - z][1]){
                    count++;
                }
                if (count >= 2){
                    return true;
                }
            }
        }
    }
    return false;
}

bool pred_ls_including_tcll_and_cll_yellow(struct cube* c){
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                u64 count = 0;
                if (c->stickers[x][y][z][1] == c->stickers[1 - x][y][z][1] && c->stickers[x][y][z][2] == c->stickers[1 - x][y][z][2] && (c->stickers[x][y][z][1] == YELLOW || c->stickers[x][y][z][2] == YELLOW)){
                    count++;
                }
                if (c->stickers[x][y][z][0] == c->stickers[x][1 - y][z][0] && c->stickers[x][y][z][2] == c->stickers[x][1 - y][z][2] && (c->stickers[x][y][z][0] == YELLOW || c->stickers[x][y][z][2] == YELLOW)){
                    count++;
                }
                if (c->stickers[x][y][z][0] == c->stickers[x][y][1 - z][0] && c->stickers[x][y][z][1] == c->stickers[x][y][1 - z][1] && (c->stickers[x][y][z][0] == YELLOW || c->stickers[x][y][z][1] == YELLOW)){
                    count++;
                }
                if (count >= 2){
                    return true;
                }
            }
        }
    }
    return false;
}

bool pred_tcll_or_eg_yellow(struct cube* c){
    return pred_tcll_including_cll_yellow(c) || pred_face_yellow(c);
}

bool pred_tcll_or_eg_colour_neutral(struct cube* c){
    return pred_tcll_including_cll_colour_neutral(c) || pred_face_colourneutral(c);
}

bool filter_nobar(struct cube* c){
    return !filter_bar(c);
}

bool filter_solid_bar(struct cube* c){
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                u64 count = 0;
                if (c->stickers[x][y][z][1] == c->stickers[1 - x][y][z][1] && c->stickers[x][y][z][2] == c->stickers[1 - x][y][z][2]){
                    count++;
                }
                if (c->stickers[x][y][z][0] == c->stickers[x][1 - y][z][0] && c->stickers[x][y][z][2] == c->stickers[x][1 - y][z][2]){
                    count++;
                }
                if (c->stickers[x][y][z][0] == c->stickers[x][y][1 - z][0] && c->stickers[x][y][z][1] == c->stickers[x][y][1 - z][1]){
                    count++;
                }
                if (count >= 1){
                    return true;
                }
            }
        }
    }
    return false;
}

bool colours_same(u8 x, u8 y){
    return x == y;
}

bool colours_opposite(u8 x, u8 y){
    if (x == ORANGE && y == RED){
        return true;
    }
    if (x == RED && y == ORANGE){
        return true;
    }
    if (x == YELLOW && y == WHITE){
        return true;
    }
    if (x == WHITE && y == YELLOW){
        return true;
    }
    if (x == BLUE && y == GREEN){
        return true;
    }
    if (x == GREEN && y == BLUE){
        return true;
    }  
    return false;
}

bool colours_adjacent(u8 x, u8 y){
    return !(colours_same(x,y) || colours_opposite(x,y));
}

bool pred_teg1_excluding_eg1_colour_neutral(struct cube* c){
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                //for eg1 we want: same adj | opp adj
                u64 count = 0;
                //change xy. that means layer on z
                if (c->stickers[x][y][z][2] == c->stickers[1 - x][y][z][2] &&
                    c->stickers[x][y][z][2] == c->stickers[x][1 - y][z][2] && 
                    (   c->stickers[x][y][z][2] == c->stickers[1 - x][1 - y][z][0] 
                    || 
                        c->stickers[x][y][z][2] == c->stickers[1 - x][1 - y][z][1]) 
                    &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_same(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            ) 
                        ||
                            (
                                    colours_opposite(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_opposite(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            ) 
                    ) 
                    ){
                    return true;
                }
                //change xz. that means layer on y
                if (c->stickers[x][y][z][1] == c->stickers[1 - x][y][z][1] &&
                    c->stickers[x][y][z][1] == c->stickers[x][y][1 - z][1] && 
                    (   c->stickers[x][y][z][1] == c->stickers[1 - x][y][1 - z][0] 
                    || 
                        c->stickers[x][y][z][1] == c->stickers[1 - x][y][1 - z][2]) 
                    &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_same(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                        ||
                            (
                                    colours_opposite(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_opposite(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                    ) 
                    ){
                    return true;
                }
                //change yz. that means layer on x
                if (c->stickers[x][y][z][0] == c->stickers[x][1 - y][z][0] &&
                    c->stickers[x][y][z][0] == c->stickers[x][y][1 - z][0] && 
                    (   c->stickers[x][y][z][0] == c->stickers[x][1 - y][1 - z][1] 
                    || 
                        c->stickers[x][y][z][0] == c->stickers[x][1 - y][1 - z][2]) 
                    &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_same(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                        ||
                            (
                                    colours_opposite(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_opposite(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                    ) 
                    ){
                    return true;
                }
            }
        }
    }
    return false;
}

bool pred_teg1_excluding_eg1_only_bars_colour_neutral(struct cube* c){
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                //for eg1 we want: same adj | opp adj
                u64 count = 0;
                //change xy. that means layer on z
                if (c->stickers[x][y][z][2] == c->stickers[1 - x][y][z][2] &&
                    c->stickers[x][y][z][2] == c->stickers[x][1 - y][z][2] && 
                    (   c->stickers[x][y][z][2] == c->stickers[1 - x][1 - y][z][0] 
                    || 
                        c->stickers[x][y][z][2] == c->stickers[1 - x][1 - y][z][1]) 
                    &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_same(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            )  
                    ) 
                    ){
                    return true;
                }
                //change xz. that means layer on y
                if (c->stickers[x][y][z][1] == c->stickers[1 - x][y][z][1] &&
                    c->stickers[x][y][z][1] == c->stickers[x][y][1 - z][1] && 
                    (   c->stickers[x][y][z][1] == c->stickers[1 - x][y][1 - z][0] 
                    || 
                        c->stickers[x][y][z][1] == c->stickers[1 - x][y][1 - z][2]) 
                    &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_same(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                    ) 
                    ){
                    return true;
                }
                //change yz. that means layer on x
                if (c->stickers[x][y][z][0] == c->stickers[x][1 - y][z][0] &&
                    c->stickers[x][y][z][0] == c->stickers[x][y][1 - z][0] && 
                    (   c->stickers[x][y][z][0] == c->stickers[x][1 - y][1 - z][1] 
                    || 
                        c->stickers[x][y][z][0] == c->stickers[x][1 - y][1 - z][2]) 
                    &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_same(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                    ) 
                    ){
                    return true;
                }
            }
        }
    }
    return false;
}

bool pred_eg1ls_excluding_teg1_and_eg1_colour_neutral(struct cube* c){
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                //for eg1 we want: same adj | opp adj
                u64 count = 0;
                //change xy. that means layer on z
                if (c->stickers[x][y][z][2] == c->stickers[1 - x][y][z][2] &&
                    c->stickers[x][y][z][2] == c->stickers[x][1 - y][z][2] && 
                    c->stickers[x][y][z][2] != c->stickers[1 - x][1 - y][z][0] &&
                    c->stickers[x][y][z][2] != c->stickers[1 - x][1 - y][z][1] &&
                    c->stickers[x][y][z][2] != c->stickers[1 - x][1 - y][z][2] &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_same(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            ) 
                        ||
                            (
                                    colours_opposite(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_opposite(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            ) 
                    ) 
                    ){
                    return true;
                }
                //change xz. that means layer on y
                if (c->stickers[x][y][z][1] == c->stickers[1 - x][y][z][1] &&
                    c->stickers[x][y][z][1] == c->stickers[x][y][1 - z][1] && 
                    c->stickers[x][y][z][1] != c->stickers[1 - x][y][1 - z][0] &&
                    c->stickers[x][y][z][1] != c->stickers[1 - x][y][1 - z][1] &&
                    c->stickers[x][y][z][1] != c->stickers[1 - x][y][1 - z][2] &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_same(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                        ||
                            (
                                    colours_opposite(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_opposite(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                    ) 
                    ){
                    return true;
                }
                //change yz. that means layer on x
                if (c->stickers[x][y][z][0] == c->stickers[x][1 - y][z][0] &&
                    c->stickers[x][y][z][0] == c->stickers[x][y][1 - z][0] && 
                    c->stickers[x][y][z][0] != c->stickers[x][1 - y][1 - z][0] &&
                    c->stickers[x][y][z][0] != c->stickers[x][1 - y][1 - z][1] &&
                    c->stickers[x][y][z][0] != c->stickers[x][1 - y][1 - z][2] &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_same(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                        ||
                            (
                                    colours_opposite(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_opposite(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                    ) 
                    ){
                    return true;
                }
            }
        }
    }
    return false;
}

bool pred_eg1ls_excluding_teg1_and_eg1_only_bars_colour_neutral(struct cube* c){
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                //for eg1 we want: same adj | opp adj
                u64 count = 0;
                //change xy. that means layer on z
                if (c->stickers[x][y][z][2] == c->stickers[1 - x][y][z][2] &&
                    c->stickers[x][y][z][2] == c->stickers[x][1 - y][z][2] && 
                    c->stickers[x][y][z][2] != c->stickers[1 - x][1 - y][z][0] &&
                    c->stickers[x][y][z][2] != c->stickers[1 - x][1 - y][z][1] &&
                    c->stickers[x][y][z][2] != c->stickers[1 - x][1 - y][z][2] &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[1 - x][y][z][1])
                                && 
                                    colours_same(c->stickers[x][y][z][0], c->stickers[x][1 - y][z][0])
                            )  
                    ) 
                    ){
                    return true;
                }
                //change xz. that means layer on y
                if (c->stickers[x][y][z][1] == c->stickers[1 - x][y][z][1] &&
                    c->stickers[x][y][z][1] == c->stickers[x][y][1 - z][1] && 
                    c->stickers[x][y][z][1] != c->stickers[1 - x][y][1 - z][0] &&
                    c->stickers[x][y][z][1] != c->stickers[1 - x][y][1 - z][1] &&
                    c->stickers[x][y][z][1] != c->stickers[1 - x][y][1 - z][2] &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[1 - x][y][z][2])
                                && 
                                    colours_same(c->stickers[x][y][z][0], c->stickers[x][y][1 - z][0])
                            ) 
                    ) 
                    ){
                    return true;
                }
                //change yz. that means layer on x
                if (c->stickers[x][y][z][0] == c->stickers[x][1 - y][z][0] &&
                    c->stickers[x][y][z][0] == c->stickers[x][y][1 - z][0] && 
                    c->stickers[x][y][z][0] == c->stickers[x][y][1 - z][0] && 
                    c->stickers[x][y][z][0] != c->stickers[x][1 - y][1 - z][0] &&
                    c->stickers[x][y][z][0] != c->stickers[x][1 - y][1 - z][1] &&
                    c->stickers[x][y][z][0] != c->stickers[x][1 - y][1 - z][2] &&
                    (
                            (
                                    colours_same(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_adjacent(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                        ||
                            (
                                    colours_adjacent(c->stickers[x][y][z][2], c->stickers[x][1 - y][z][2])
                                && 
                                    colours_same(c->stickers[x][y][z][1], c->stickers[x][y][1 - z][1])
                            ) 
                    ) 
                    ){
                    return true;
                }
            }
        }
    }
    return false;
}

bool pred_egls_including_teg_and_eg_colour_neutral(struct cube* c){
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                //for eg1 we want: same adj | opp adj
                u64 count = 0;
                //change xy. that means layer on z
                if (c->stickers[x][y][z][2] == c->stickers[1 - x][y][z][2] &&
                    c->stickers[x][y][z][2] == c->stickers[x][1 - y][z][2]
                    ){
                    return true;
                }
                //change xz. that means layer on y
                if (c->stickers[x][y][z][1] == c->stickers[1 - x][y][z][1] &&
                    c->stickers[x][y][z][1] == c->stickers[x][y][1 - z][1]
                    ){
                    return true;
                }
                //change yz. that means layer on x
                if (c->stickers[x][y][z][0] == c->stickers[x][1 - y][z][0] &&
                    c->stickers[x][y][z][0] == c->stickers[x][y][1 - z][0]
                    ){
                    return true;
                }
            }
        }
    }
    return false;
}

struct cube cube_inverse(struct cube* c){
    struct cube s;
    cube_constructor(&s);
    struct cube r;
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                u64 xd;
                u64 yd;
                u64 zd;
                u64 d0;
                u64 d1;
                u64 d2;
                for (u64 d = 0; d < 3; d++){
                    switch (c->stickers[x][y][z][d]){
                        case ORANGE:
                            xd = 0;
                            break;
                        case RED:
                            xd = 1;
                            break;
                        case YELLOW:
                            yd = 0;
                            break;
                        case WHITE:
                            yd = 1;
                            break;
                        case BLUE:
                            zd = 0;
                            break;
                        case GREEN:
                            zd = 1;
                            break;
                    }
                    switch (d){
                        case 0: d0 = c->stickers[x][y][z][d] / 2; break;
                        case 1: d1 = c->stickers[x][y][z][d] / 2; break;
                        case 2: d2 = c->stickers[x][y][z][d] / 2; break;
                    } 
                }
                r.stickers[xd][yd][zd][d0] = s.stickers[x][y][z][0];
                r.stickers[xd][yd][zd][d1] = s.stickers[x][y][z][1];
                r.stickers[xd][yd][zd][d2] = s.stickers[x][y][z][2];
                
            }
        }
    }
    return r;
}

bool pred_pseudo(bool (*pred)(struct cube*), struct cube* c){
    //being able to do exactly 1 move on the inverse and go to a certain set
    struct cube i = cube_inverse(c);
    for (u64 m = 0; m < MOVES; m++){
        cube_move(&i, m);
        if ((*pred)(&i)){
            return true;
        }
        switch (m % 3){
            case 0:
                cube_move(&i, m + 1);
                break;
            case 1:
                cube_move(&i, m - 1);
                break;
            case 2:
                cube_move(&i, m);
                break;
        }
    }
    return false;
}

bool pred_pseudo_eg_colourneutral(struct cube* c){
    return pred_pseudo(pred_face_colourneutral, c);
}

bool pred_pseudo_cbl_or_tcbl_colourneutral(struct cube* c){
    return pred_pseudo(pred_CBL_or_TCBL_colour_neutral, c);
}

bool pred_permutation_only(struct cube* c){
    struct cube s;
    cube_constructor(&s);
    struct cube cc = *c;
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                bool stop = true;
                for (u64 i = 0; i < 3; i++){
                    twist(&cc, x, y, z);
                    if (cc.stickers[x][y][z][0] != s.stickers[x][y][z][0]){
                        continue;
                    }
                    if (cc.stickers[x][y][z][1] != s.stickers[x][y][z][1]){
                        continue;
                    }
                    if (cc.stickers[x][y][z][2] != s.stickers[x][y][z][2]){
                        continue;
                    }
                    stop = false;
                }
                if (stop){
                    return false;
                } 
            }
        }
    }
    return true;
}


bool (*tests[TESTS])(struct cube*) = {
    pred_solved,
    pred_cll_yellow,
    pred_cll_colour_neutral,
    pred_face_yellow,
    pred_face_colourneutral,
    pred_dr_du,
    pred_dr,
    pred_tcll_including_cll_yellow,
    pred_tcll_including_cll_colour_neutral,
    pred_teg_including_eg_yellow,
    pred_teg_including_eg_colour_neutral,
    pred_ls_including_tcll_and_cll_yellow,
    pred_ls_including_tcll_and_cll_colour_neutral,
    pred_CBL_or_TCBL_yellow,
    pred_CBL_or_TCBL_colour_neutral,
    pred_tcll_or_eg_yellow,
    pred_tcll_or_eg_colour_neutral,
    pred_teg1_excluding_eg1_colour_neutral,
    pred_teg1_excluding_eg1_only_bars_colour_neutral,
    pred_eg1ls_excluding_teg1_and_eg1_colour_neutral,
    pred_eg1ls_excluding_teg1_and_eg1_only_bars_colour_neutral,
    pred_egls_including_teg_and_eg_colour_neutral,
    filter_solid_bar,
    pred_pseudo_eg_colourneutral,
    pred_pseudo_cbl_or_tcbl_colourneutral,
    pred_permutation_only,
};

bool (*filters[FILTERS])(struct cube*) = {
    filter_all,
    filter_bar,
    filter_nobar,
    filter_solid_bar,
};

#endif