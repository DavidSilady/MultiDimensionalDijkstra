#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main() {
    int width = 5;
    int height = 5;
    int time = 0;
    scanf("%d %d %d", &height, &width, &time);
    char **map = malloc(height * sizeof(char *));
    for (int i = 0; i < height; ++i) {
        map[i] = malloc(width * sizeof(char));
        for (int j = 0; j < width; ++j) {
            map[i][j] = 0;
            scanf(" %c", &map[i][j]);
        }
    }

/*
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {

        }
    }
*/
    printf("\n\n");
    /* for(int i = 0; i < width; i++) {
         for(int j = 0; j < height; j++) {
             printf("%c ", map[j][i]);
         }
         printf("\n");
     }*/
    int length = 0;


    int *path = zachran_princezne(map, height, width, 30, &length);
    free(path);
    /*for (int k = 0; k < length; ++k) {
        printf("%d %d\n", path[k * 2], path[k * 2 + 1]);
    }*/
    return 0;
}