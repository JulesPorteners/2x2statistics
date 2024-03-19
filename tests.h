#ifndef TESTS_H
#define TESTS_H

#include "types.h"
#include "cube.h"
#include "hash_table.h"
#include "cubes_and_graph.h"

#define TESTS 11
u64 distances[TESTS][STATES];
u64 statistics[TESTS][12];
char description_tests[TESTS][50] = {
    "solved",
    "cll yellow",
    "cll colour neutral",
    "eg yellow",
    "eg colour neutral",
    "dr white yellow",
    "dr colour neutral",
    "CBL or TCBL colour neutral",
    "teg (including eg) colour neutral",
    "pred_teg_including_eg_colour_neutral_part_two",
    "pred_teg_including_eg_colour_neutral again"
};

#define FILTERS 3
char description_filters[FILTERS][50] = {
    "all",
    "bar",
    "nobar",
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
    for (u64 j = 0; j < 12 - 1; j++){
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
    bool yellow = c->stickers[0][0][0][1] == YELLOW && c->stickers[0][0][1][1] == YELLOW && c->stickers[1][0][0][1] == YELLOW && c->stickers[1][0][1][1] == YELLOW;
    return yellow;
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

bool pred_cll_yellow(struct cube* c){
    bool yellow = c->stickers[0][0][0][1] == YELLOW && c->stickers[0][0][1][1] == YELLOW && c->stickers[1][0][0][1] == YELLOW && c->stickers[1][0][1][1] == YELLOW;
    bool ring = c->stickers[0][0][0][2] == BLUE && c->stickers[1][0][0][2] == BLUE && c->stickers[0][0][0][0] == ORANGE && c->stickers[0][0][1][0] == ORANGE ;
    bool ring2 = c->stickers[0][0][1][2] == GREEN && c->stickers[1][0][1][2] == GREEN && c->stickers[1][0][0][0] == RED && c->stickers[1][0][1][0] == RED ;
    return yellow && ring && ring2;
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

bool pred_teg_including_eg_colour_neutral(struct cube* c){
    for (u64 x = 0; x < 6; x++){
        bool l1 = (c->stickers[0][0][0][0] == x || c->stickers[0][0][0][1] == x || c->stickers[0][0][0][2] == x) && c->stickers[0][0][1][0] == x && c->stickers[0][1][0][0] == x && c->stickers[0][1][1][0] == x;
        bool l2 = c->stickers[0][0][0][0] == x && (c->stickers[0][0][1][0] == x || c->stickers[0][0][1][1] == x || c->stickers[0][0][1][2] == x) && c->stickers[0][1][0][0] == x && c->stickers[0][1][1][0] == x;
        bool l3 = c->stickers[0][0][0][0] == x && c->stickers[0][0][1][0] == x && (c->stickers[0][1][0][0] == x || c->stickers[0][1][0][1] == x || c->stickers[0][1][0][2] == x) && c->stickers[0][1][1][0] == x;
        bool l4 = c->stickers[0][0][0][0] == x && c->stickers[0][0][1][0] == x && c->stickers[0][1][0][0] == x && (c->stickers[0][1][1][0] == x || c->stickers[0][1][1][1] == x || c->stickers[0][1][1][2] == x);
        
        bool r1 = (c->stickers[1][0][0][0] == x || c->stickers[1][0][0][1] == x || c->stickers[1][0][0][2] == x) && c->stickers[1][0][1][0] == x && c->stickers[1][1][0][0] == x && c->stickers[1][1][1][0] == x;
        bool r2 = c->stickers[1][0][0][0] == x && (c->stickers[1][0][1][0] == x || c->stickers[1][0][1][1] == x || c->stickers[1][0][1][2] == x) && c->stickers[1][1][0][0] == x && c->stickers[1][1][1][0] == x;
        bool r3 = c->stickers[1][0][0][0] == x && c->stickers[1][0][1][0] == x && (c->stickers[1][1][0][0] == x || c->stickers[1][1][0][1] == x || c->stickers[1][1][0][2] == x) && c->stickers[1][1][1][0] == x;
        bool r4 = c->stickers[1][0][0][0] == x && c->stickers[1][0][1][0] == x && c->stickers[1][1][0][0] == x && (c->stickers[1][1][1][0] == x || c->stickers[1][1][1][1] == x || c->stickers[1][1][1][2] == x);

        bool d1 = (c->stickers[0][0][0][1] == x || c->stickers[0][0][0][0] == x || c->stickers[0][0][0][2] == x) && c->stickers[0][0][1][1] == x && c->stickers[1][0][0][1] == x && c->stickers[1][0][1][1] == x;
        bool d2 = c->stickers[0][0][0][1] == x && (c->stickers[0][0][1][1] == x || c->stickers[0][0][1][0] == x || c->stickers[0][0][1][2] == x) && c->stickers[1][0][0][1] == x && c->stickers[1][0][1][1] == x;
        bool d3 = c->stickers[0][0][0][1] == x && c->stickers[0][0][1][1] == x && (c->stickers[1][0][0][1] == x || c->stickers[1][0][0][0] == x || c->stickers[1][0][0][2] == x) && c->stickers[1][0][1][1] == x;
        bool d4 = c->stickers[0][0][0][1] == x && c->stickers[0][0][1][1] == x && c->stickers[1][0][0][1] == x && (c->stickers[1][0][1][1] == x || c->stickers[1][0][1][0] == x || c->stickers[1][0][1][2] == x);
        
        bool u1 = (c->stickers[0][1][0][0] == x || c->stickers[0][1][0][1] == x || c->stickers[0][1][0][2] == x) && c->stickers[0][1][1][1] == x && c->stickers[1][1][0][1] == x && c->stickers[1][1][1][1] == x;
        bool u2 = c->stickers[0][1][0][1] == x && (c->stickers[0][1][1][0] == x || c->stickers[0][1][1][1] == x || c->stickers[0][1][1][2] == x) && c->stickers[1][1][0][1] == x && c->stickers[1][1][1][1] == x;
        bool u3 = c->stickers[0][1][0][1] == x && c->stickers[0][1][1][1] == x && (c->stickers[1][1][0][0] == x || c->stickers[1][1][0][1] == x || c->stickers[1][1][0][2] == x) && c->stickers[1][1][1][1] == x;
        bool u4 = c->stickers[0][1][0][1] == x && c->stickers[0][1][1][1] == x && c->stickers[1][1][0][1] == x && (c->stickers[1][1][1][0] == x || c->stickers[1][1][1][1] == x || c->stickers[1][1][1][2] == x);
        
        bool b1 = (c->stickers[0][0][0][0] == x || c->stickers[0][0][0][1] == x || c->stickers[0][0][0][2] == x) && c->stickers[0][1][0][2] == x && c->stickers[1][0][0][2] == x && c->stickers[1][1][0][2] == x;
        bool b2 = c->stickers[0][0][0][2] == x && (c->stickers[0][1][0][0] == x || c->stickers[0][1][0][1] == x || c->stickers[0][1][0][2] == x) && c->stickers[1][0][0][2] == x && c->stickers[1][1][0][2] == x;
        bool b3 = c->stickers[0][0][0][2] == x && c->stickers[0][1][0][2] == x && (c->stickers[1][0][0][0] == x || c->stickers[1][0][0][1] == x || c->stickers[1][0][0][2] == x) && c->stickers[1][1][0][2] == x;
        bool b4 = c->stickers[0][0][0][2] == x && c->stickers[0][1][0][2] == x && c->stickers[1][0][0][2] == x && (c->stickers[1][1][0][0] == x || c->stickers[1][1][0][1] == x || c->stickers[1][1][0][2] == x);

        bool f1 = (c->stickers[0][0][1][0] == x || c->stickers[0][0][1][1] == x || c->stickers[0][0][1][2] == x) && c->stickers[0][1][1][2] == x && c->stickers[1][0][1][2] == x && c->stickers[1][1][1][2] == x;
        bool f2 = c->stickers[0][0][1][2] == x && (c->stickers[0][1][1][0] == x || c->stickers[0][0][1][1] == x || c->stickers[0][0][1][2] == x) && c->stickers[1][0][1][2] == x && c->stickers[1][1][1][2] == x;
        bool f3 = c->stickers[0][0][1][2] == x && c->stickers[0][1][1][2] == x && (c->stickers[1][0][1][0] == x || c->stickers[0][0][1][1] == x || c->stickers[0][0][1][2] == x) && c->stickers[1][1][1][2] == x;
        bool f4 = c->stickers[0][0][1][2] == x && c->stickers[0][1][1][2] == x && c->stickers[1][0][1][2] == x && (c->stickers[1][1][1][0] == x || c->stickers[0][0][1][1] == x || c->stickers[0][0][1][2] == x);
        if (l1 || l2 || l3 || l4 || r1 || r2 || r3 || r4 || d1 || d2 || d3 || d4 || u1 || u2 || u3 || u4 || b1 || b2 || b3 || b4 || f1 || f2 || f3 || f4){
            return true;
        }
    }
    return false;
}

void twist(struct cube* c, u64 x, u64 y, u64 z, u64 n){
    while (n != 0){
        u8 temp = c->stickers[x][y][z][0];
        c->stickers[x][y][z][0] = c->stickers[x][y][z][1];
        c->stickers[x][y][z][1] = c->stickers[x][y][z][2];
        c->stickers[x][y][z][2] = temp;
        n--;
    }
}
//pred_face_colourneutral

bool pred_teg_including_eg_colour_neutral_part_two(struct cube* c){
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                //no copying of the cube cuz why not 
                for (u64 i = 0; i < 3; i++){
                    twist(c, x, y, z, 1);
                    if (pred_face_colourneutral(c)){
                        return true;
                    }
                }
                
            }
        }
    }
    return false;
}

/*
bool pred_tcll_including_cll_colour_neutral(struct cube* c){
    for (u64 x = 0; x < 6; x++){
        bool l1 = (c->stickers[0][0][0][0] == x || c->stickers[0][0][0][1] == x || c->stickers[0][0][0][2] == x) && c->stickers[0][0][1][0] == x && c->stickers[0][1][0][0] == x && c->stickers[0][1][1][0] == x;
        bool l2 = c->stickers[0][0][0][0] == x && (c->stickers[0][0][1][0] == x || c->stickers[0][0][1][1] == x || c->stickers[0][0][1][2] == x) && c->stickers[0][1][0][0] == x && c->stickers[0][1][1][0] == x;
        bool l3 = c->stickers[0][0][0][0] == x && c->stickers[0][0][1][0] == x && (c->stickers[0][1][0][0] == x || c->stickers[0][1][0][1] == x || c->stickers[0][1][0][2] == x) && c->stickers[0][1][1][0] == x;
        bool l4 = c->stickers[0][0][0][0] == x && c->stickers[0][0][1][0] == x && c->stickers[0][1][0][0] == x && (c->stickers[0][1][1][0] == x || c->stickers[0][1][1][1] == x || c->stickers[0][1][1][2] == x);
        
        bool r1 = (c->stickers[1][0][0][0] == x || c->stickers[1][0][0][1] == x || c->stickers[1][0][0][2] == x) && c->stickers[1][0][1][0] == x && c->stickers[1][1][0][0] == x && c->stickers[1][1][1][0] == x;
        bool r2 = c->stickers[1][0][0][0] == x && (c->stickers[1][0][1][0] == x || c->stickers[1][0][1][1] == x || c->stickers[1][0][1][2] == x) && c->stickers[1][1][0][0] == x && c->stickers[1][1][1][0] == x;
        bool r3 = c->stickers[1][0][0][0] == x && c->stickers[1][0][1][0] == x && (c->stickers[1][1][0][0] == x || c->stickers[1][1][0][1] == x || c->stickers[1][1][0][2] == x) && c->stickers[1][1][1][0] == x;
        bool r4 = c->stickers[1][0][0][0] == x && c->stickers[1][0][1][0] == x && c->stickers[1][1][0][0] == x && (c->stickers[1][1][1][0] == x || c->stickers[1][1][1][1] == x || c->stickers[1][1][1][2] == x);

        bool d1 = (c->stickers[0][0][0][1] == x || c->stickers[0][0][0][0] == x || c->stickers[0][0][0][2] == x) && c->stickers[0][0][1][1] == x && c->stickers[1][0][0][1] == x && c->stickers[1][0][1][1] == x;
        bool d2 = c->stickers[0][0][0][1] == x && (c->stickers[0][0][1][1] == x || c->stickers[0][0][1][0] == x || c->stickers[0][0][1][2] == x) && c->stickers[1][0][0][1] == x && c->stickers[1][0][1][1] == x;
        bool d3 = c->stickers[0][0][0][1] == x && c->stickers[0][0][1][1] == x && (c->stickers[1][0][0][1] == x || c->stickers[1][0][0][0] == x || c->stickers[1][0][0][2] == x) && c->stickers[1][0][1][1] == x;
        bool d4 = c->stickers[0][0][0][1] == x && c->stickers[0][0][1][1] == x && c->stickers[1][0][0][1] == x && (c->stickers[1][0][1][1] == x || c->stickers[1][0][1][0] == x || c->stickers[1][0][1][2] == x);
        
        bool u1 = (c->stickers[0][1][0][0] == x || c->stickers[0][1][0][1] == x || c->stickers[0][1][0][2] == x) && c->stickers[0][1][1][1] == x && c->stickers[1][1][0][1] == x && c->stickers[1][1][1][1] == x;
        bool u2 = c->stickers[0][1][0][1] == x && (c->stickers[0][1][1][0] == x || c->stickers[0][1][1][1] == x || c->stickers[0][1][1][2] == x) && c->stickers[1][1][0][1] == x && c->stickers[1][1][1][1] == x;
        bool u3 = c->stickers[0][1][0][1] == x && c->stickers[0][1][1][1] == x && (c->stickers[1][1][0][0] == x || c->stickers[1][1][0][1] == x || c->stickers[1][1][0][2] == x) && c->stickers[1][1][1][1] == x;
        bool u4 = c->stickers[0][1][0][1] == x && c->stickers[0][1][1][1] == x && c->stickers[1][1][0][1] == x && (c->stickers[1][1][1][0] == x || c->stickers[1][1][1][1] == x || c->stickers[1][1][1][2] == x);
        
        bool b1 = (c->stickers[0][0][0][0] == x || c->stickers[0][0][0][1] == x || c->stickers[0][0][0][2] == x) && c->stickers[0][1][0][2] == x && c->stickers[1][0][0][2] == x && c->stickers[1][1][0][2] == x;
        bool b2 = c->stickers[0][0][0][2] == x && (c->stickers[0][1][0][0] == x || c->stickers[0][1][0][1] == x || c->stickers[0][1][0][2] == x) && c->stickers[1][0][0][2] == x && c->stickers[1][1][0][2] == x;
        bool b3 = c->stickers[0][0][0][2] == x && c->stickers[0][1][0][2] == x && (c->stickers[1][0][0][0] == x || c->stickers[1][0][0][1] == x || c->stickers[1][0][0][2] == x) && c->stickers[1][1][0][2] == x;
        bool b4 = c->stickers[0][0][0][2] == x && c->stickers[0][1][0][2] == x && c->stickers[1][0][0][2] == x && (c->stickers[1][1][0][0] == x || c->stickers[1][1][0][1] == x || c->stickers[1][1][0][2] == x);

        bool f1 = (c->stickers[0][0][1][0] == x || c->stickers[0][0][1][1] == x || c->stickers[0][0][1][2] == x) && c->stickers[0][1][1][2] == x && c->stickers[1][0][1][2] == x && c->stickers[1][1][1][2] == x;
        bool f2 = c->stickers[0][0][1][2] == x && (c->stickers[0][1][1][0] == x || c->stickers[0][0][1][1] == x || c->stickers[0][0][1][2] == x) && c->stickers[1][0][1][2] == x && c->stickers[1][1][1][2] == x;
        bool f3 = c->stickers[0][0][1][2] == x && c->stickers[0][1][1][2] == x && (c->stickers[1][0][1][0] == x || c->stickers[0][0][1][1] == x || c->stickers[0][0][1][2] == x) && c->stickers[1][1][1][2] == x;
        bool f4 = c->stickers[0][0][1][2] == x && c->stickers[0][1][1][2] == x && c->stickers[1][0][1][2] == x && (c->stickers[1][1][1][0] == x || c->stickers[0][0][1][1] == x || c->stickers[0][0][1][2] == x);
        if (l1 || l2 || l3 || l4 || r1 || r2 || r3 || r4 || d1 || d2 || d3 || d4 || u1 || u2 || u3 || u4 || b1 || b2 || b3 || b4 || f1 || f2 || f3 || f4){
            return true;
        }
    }
    return false;
}

*/



bool filter_nobar(struct cube* c){
    return !filter_bar(c);
}

bool (*tests[TESTS])(struct cube*) = {
    pred_solved,
    pred_cll_yellow,
    pred_cll_colour_neutral,
    pred_face_yellow,
    pred_face_colourneutral,
    pred_dr_du,
    pred_dr,
    pred_CBL_or_TCBL_colour_neutral,
    pred_teg_including_eg_colour_neutral,
    pred_teg_including_eg_colour_neutral_part_two,
    pred_teg_including_eg_colour_neutral,
};

bool (*filters[FILTERS])(struct cube*) = {
    filter_all,
    filter_bar,
    filter_nobar,
};

#endif