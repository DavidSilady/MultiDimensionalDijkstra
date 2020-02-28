//
// Created by david on 12/4/2019.
//

#ifndef POPOLVAR_DIJKSTRA_H
#define POPOLVAR_DIJKSTRA_H

#include "node.h"
#include "min_heap.h"

typedef struct World {
    char ** map;
    short num_princesses;
    short *num_portals;
    short width;
    short height;
    NodeField *nodeField;
    Heap *heap;
    short **princesses;
    short ***portals;
} World;

int *zachran_princezne(char **mapa, int n, int m, int t, int *dlzka_cesty);

#endif //POPOLVAR_DIJKSTRA_H
