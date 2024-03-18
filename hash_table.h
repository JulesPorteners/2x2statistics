#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "types.h"
#include "cube.h"

#define STATES 3674160
#define HASH_TABLE_SIZE (2 * STATES)

struct hash_table_cell{
    u64 key;
    u64 index;
};

struct hash_table_cell hash_table[HASH_TABLE_SIZE];

u64 id(struct cube* c){
    u64 sum = 0;
    u64 base = 1;
    for (u64 x = 0; x < 2; x++){
        for (u64 y = 0; y < 2; y++){
            for (u64 z = 0; z < 2; z++){
                for (u64 d = 0; d < 3; d++){
                    sum += ((u64) c->stickers[x][y][z][d]) * base;
                    base *= 6;
                }
            }
        }
    }
    return sum;
}

u64 hash_table_hash(u64 key){ 
    key = (key ^ (key >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    key = (key ^ (key >> 27)) * UINT64_C(0x94d049bb133111eb);
    key = key ^ (key >> 31);
    return key % HASH_TABLE_SIZE; 
}

void hash_table_put(struct cube* c, u64 index){
    u64 key = id(c);
    u64 h = hash_table_hash(key);
    while (hash_table[h].key != 0 && hash_table[h].key != key){ //this only works because key is never 0
        h++;
        if (h >= HASH_TABLE_SIZE){
            h = 0;
        }
    }
    hash_table[h].key = key;
    hash_table[h].index = index;
}

struct hash_table_cell* hash_table_get(struct cube* c){
    u64 key = id(c);
    u64 h = hash_table_hash(key);
    while (hash_table[h].key != 0 && hash_table[h].key != key){ //this only works because key is never 0
        h++;
        if (h >= HASH_TABLE_SIZE){
            h = 0;
        }
    }
    if (hash_table[h].key == key){
        return &hash_table[h];
    }
    return NULL;
}

#endif