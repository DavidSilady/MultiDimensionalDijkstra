//
// Created by david on 12/3/2019.
//

#ifndef POPOLVAR_NODE_H
#define POPOLVAR_NODE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    unsigned char state;         // [empty][generator_on][dragon_slayed][princess4][princess3][princess2][princess1][princess0]
    short x;
    short y;
    struct Node *parent;
    short value;
} Node;

typedef struct NodeField {
    unsigned short width;
    unsigned short height;
    Node *****field;
} NodeField;

//Node *get_parent(NodeField *node_field, Node *node);
unsigned char dragon_slayed(Node *node);
unsigned char generator_on(Node *node);
Node *init_node(int state, short x, short y);
NodeField *init_node_field(short width, short height, short num_princesses);
void get_coordinates(NodeField *node_field, Node *node, short *x, short *y);
unsigned char num_saved(Node *node);
Node *filtered_by_state(NodeField *node_field, Node *node, short x, short y);

Node *right_node(NodeField *node_field, Node* node);
Node *left_node(NodeField *node_field, Node* node);
Node *upper_node(NodeField *node_field, Node* node);
Node *lower_node(NodeField *node_field, Node* node);

#endif //POPOLVAR_NODE_H
