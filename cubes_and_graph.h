#ifndef CUBES_AND_GRAPH_H
#define CUBES_AND_GRAPH_H

#include "types.h"
#include "cube.h"
#include "hash_table.h"

struct cube cubes[STATES];
u64 graph[STATES][9];

void cubes_generator(){
    cube_constructor(&cubes[0]);
    hash_table_put(&cubes[0], 0);
    u64 cubes_size = 1;
    u64 cubes_queue_front = 0;
    while (cubes_queue_front != cubes_size){
        struct cube u = cubes[cubes_queue_front];
        cubes_queue_front++;
        for (u64 m = 0; m < 9; m++){
            struct cube v = u;
            cube_move(&v, m);
            if (hash_table_get(&v) == NULL){
                cubes[cubes_size] = v;
                hash_table_put(&v, cubes_size);
                cubes_size++;   
            }
        }
    }
}

void graph_generator(){
    for (u64 i = 0; i < STATES; i++){
        struct cube u = cubes[i];
        for (u64 m = 0; m < 9; m++){
            struct cube v = cubes[i];
            cube_move(&v, m);
            graph[i][m] = hash_table_get(&v)->index;
        }
    }
}

#endif