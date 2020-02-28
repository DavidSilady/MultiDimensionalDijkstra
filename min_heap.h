//
// Created by david on 12/3/2019.
//

#ifndef POPOLVAR_MIN_HEAP_H
#define POPOLVAR_MIN_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

typedef struct Heap {
    int max_length;
    int size;
    Node **nodes;
} Heap;

int heap_empty(Heap *heap);
Node *heap_first(Heap *heap);
void heap_insert(Heap *heap, Node *node);
Heap *init_heap(int length);
Node *heap_extract(Heap *heap);

#endif //POPOLVAR_MIN_HEAP_H
