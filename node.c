//
// Created by david on 12/3/2019.
//

#include "node.h"


#define NUM_STATES 4
//generator 0, dragon 0 | generator 1, dragon 0 | generator 0, dragon 1 | generator 1, dragon 1


Node *****create_node_field(short width, short height, short num_princesses);


Node *init_node(int state, short x, short y) {
    Node *node = malloc(sizeof(Node));
    node->x = x;
    node->y = y;
    node->value = -1;
    node->state = 0;
    node->parent = NULL;
    if(state == 1) {//generator
        node->state |= 0x40u;
    }
    if(state == 2) { //dragon
        node->state |= 0x20u;
    }
    if(state == 3) { //dragon + generator
        node->state |= 0x20u;
        node->state |= 0x40u;
    }
    return node;
}

NodeField *init_node_field(short width, short height, short num_princesses) {
    NodeField *field = malloc(sizeof(NodeField));
    field->width = width;
    field->height = height;
    field->field = create_node_field(width, height, num_princesses);
    return field;
}

Node *****create_node_field(short width, short height, short num_princesses) {
    num_princesses++; //include the state with 0 saved
    unsigned short num_dimensions = 0x01u << (unsigned) num_princesses;
    unsigned short depth = NUM_STATES;
    Node *****field = malloc(height * sizeof(Node ****));
    for (short x = 0; x < height; ++x) {
        field[x] = malloc(width * sizeof(Node ***));
        for (short y = 0; y < width; ++y) {
            field[x][y] = malloc(depth * sizeof(Node **));
            for (unsigned short k = 0; k < depth - 2; ++k) { //dragon alive
                field[x][y][k] = malloc(sizeof(Node *));
                field[x][y][k][0] = init_node(k, x, y);
            }
            for (int k = depth - 2; k < depth; ++k) { //dragon dead
                field[x][y][k] = malloc(num_dimensions * sizeof(Node *));
                for (int l = 0; l < num_dimensions; ++l) {
                    field[x][y][k][l] = init_node(k, x, y);
                }
            }
        }
    }
    return field;
}

unsigned char dragon_slayed(Node *node) {
    return node->state & 0x20u;
}

unsigned char generator_on(Node *node) {
    return node->state & 0x40u;
}

Node *filtered_by_state(NodeField *node_field, Node *node, short x, short y) {
    if(x < 0 || x >= node_field->height || y < 0 || y >= node_field->width) {
        return NULL;
    }
    unsigned short dimension_id = (unsigned) node->state & 0x1Fu;
    if(dragon_slayed(node) && generator_on(node)) {
        return node_field->field[x][y][3][dimension_id];
    }
    if(dragon_slayed(node)) {
        return node_field->field[x][y][2][dimension_id];
    }
    if(generator_on(node)) {
        return node_field->field[x][y][1][dimension_id];
    }
    return node_field->field[x][y][0][dimension_id];
}

Node *right_node(NodeField *node_field, Node* node) {
    short x = (short) (node->x + 1);
    if(x > node_field->height) {
        return NULL;
    }
    return filtered_by_state(node_field, node, x, node->y);
}

Node *left_node(NodeField *node_field, Node* node) {
    short x = (short) (node->x - 1);
    if(x < 0) {
        return NULL;
    }
    return filtered_by_state(node_field, node, x, node->y);
}

Node *upper_node(NodeField *node_field, Node* node) {
    short y = (short) (node->y - 1);
    if(y < 0) {
        return NULL;
    }
    return filtered_by_state(node_field, node, node->x, y);
}

Node *lower_node(NodeField *node_field, Node* node) {
    short y = (short) (node->y + 1);
    if(y > node_field->width) {
        return NULL;
    }
    return filtered_by_state(node_field, node, node->x, y);
}

unsigned char num_saved(Node *node) {
    unsigned char sum = 0;
    for (unsigned short i = 0; i < 5; ++i) {
        unsigned char princess = node->state >> i;
        sum += princess & 0x01u;
    }
    return sum;
}