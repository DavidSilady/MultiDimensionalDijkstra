//
// Created by david on 12/3/2019.
//

#include "min_heap.h"

Heap *init_heap(int length) {
    Heap *heap = malloc(sizeof(Heap));
    heap->max_length = length;
    heap->size = 0;
    heap->nodes = calloc(length, sizeof(Node*));
    return heap;
}

int heap_empty(Heap *heap) {
    if(heap_first(heap) == NULL) {
        return 1;
    }
    return 0;
}

Node *heap_first(Heap *heap) {
    return heap->nodes[0];
}

void swap_nodes(Node **a, Node **b) {
    Node *tmp = *a;
    *a = *b;
    *b = tmp;
}

void balance(Heap *heap, int index) {
    if(index <= 0) {
        return;
    }

    if(heap->nodes[index]->value < heap->nodes[(index - 1) / 2]->value) {
        swap_nodes(&heap->nodes[index], &heap->nodes[(index - 1) / 2]);
        balance(heap, (index - 1) / 2);
    }
}

void heap_insert(Heap *heap, Node *node) {
    heap->nodes[heap->size] = node;
    balance(heap, heap->size);
    heap->size++;
}

int min_node(Node *a, Node *b) {
    if (a->value < b->value)
        return 1;
    else
        return 2;
}

void heapify(Heap *heap, int index) {
    if ((index * 2) + 2 >= heap->size) {
        if((index * 2) + 2 == heap->size) {
            if (heap->nodes[index]->value > heap->nodes[(2 * index) + 1]->value) {
                swap_nodes(&heap->nodes[index], &heap->nodes[(2 * index) + 1]);
            }
        }
        return;
    }

    int max_offset = min_node(heap->nodes[(2 * index) + 1], heap->nodes[(2 * index) + 2]);
    if (heap->nodes[index]->value > heap->nodes[(2 * index) + max_offset]->value) {
        swap_nodes(&heap->nodes[index], &heap->nodes[(2 * index) + max_offset]);
        heapify(heap, (2 * index) + max_offset);
    }
}

Node *heap_extract(Heap *heap) {
    Node *extracted = heap->nodes[0];
    heap->size -= 1;
    swap_nodes(&heap->nodes[0], &heap->nodes[heap->size]);
    heap->nodes[heap->size] = NULL;
    heapify(heap, 0);
    return extracted;
}
