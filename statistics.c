#include <stdio.h> 

#include "types.h"
#include "cube.h"
#include "hash_table.h"
#include "cubes_and_graph.h"
#include "tests.h"

void generate_statistics(){
    for (u64 t = 0; t < TESTS; t++){
        generate_distances(tests[t], t);
    }
    for (u64 t = 0; t < TESTS; t++){
        printf("%c = %s\n", (char) (t + 'A'), description_tests[t]);
    }
    printf("\n");
    for (u64 f = 0; f < FILTERS; f++){
        printf("--- %s ---\n\n", description_filters[f]);
        for (u64 t = 0; t < TESTS; t++){
            for (u64 i = 0; i < 12; i++){
                statistics[t][i] = 0;
            }
        }
        for (u64 t = 0; t < TESTS; t++){
            for (u64 i = 0; i < STATES; i++){
                if (distances[0][i] >= 4 && filters[f](&cubes[i])){
                    statistics[t][distances[t][i]]++;
                }  
            }
        }
        printf("moves");
        for (u64 t = 0; t < TESTS; t++){
            printf("%10c", (char) (t + 'A'));
        }  
        printf("\n");
        for (u64 i = 0; i < 12; i++){
            printf("%5" PRIu64, i);
            for (u64 t = 0; t < TESTS; t++){
                printf("%10" PRIu64, statistics[t][i]);
            }
            printf("\n");
        }
        printf("\navg  ");
        for (u64 t = 0; t < TESTS; t++){
            u64 sum = 0;
            u64 weighted_sum = 0;
            for (u64 i = 0; i < 12; i++){
                sum += statistics[t][i];
                weighted_sum += i * statistics[t][i];
            }
            printf("%10.2f", ((f64) weighted_sum) / ((f64) sum));
        }
        printf("\ntot  ");
        for (u64 t = 0; t < TESTS; t++){
            u64 sum = 0;
            for (u64 i = 0; i < 12; i++){
                sum += statistics[t][i];
            }
            printf("%10" PRIu64, sum);
        }
        printf("\n\n");
    }
}

int main(){
    printf("exploring all 2x2 states...\n\n");
    cubes_generator();
    graph_generator();
    generate_statistics();
    return 0;
}

