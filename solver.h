#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>

#include "types.h"
#include "cube.h"
#include "hash_table.h"
#include "cubes_and_graph.h"
#include "tests.h"



void dfs(u64 n, u64* moves, u64* moves_size){
    if (distances[0][n] == 0){
        for (u64 i = 0; i < *moves_size; i++){ 
            switch (moves[i]){
                case 0: printf("R "); break;
                case 1: printf("R' "); break;
                case 2: printf("R2 "); break;
                case 3: printf("U "); break;
                case 4: printf("U' "); break;
                case 5: printf("U2 "); break;
                case 6: printf("F "); break;
                case 7: printf("F' "); break;
                case 8: printf("F2 "); break;
            }
        }
        printf("\n");
    }
    else{
        for (u64 i = 0; i < 9; i++){ 
            if (distances[0][graph[n][i]] < distances[0][n]){
                moves[*moves_size] = i;
                (*moves_size)++;
                dfs(graph[n][i], moves, moves_size);
                (*moves_size)--;
            }
        }
    }
}

void solve(struct cube* c){
    u64 moves[GOD];
    u64 moves_size = 0;
    u64 n = hash_table_get(c)->index;
    dfs(n, moves, &moves_size);
}

#endif