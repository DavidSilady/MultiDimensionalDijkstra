//
// Created by david on 12/4/2019.
//

#include "dijkstra.h"
#include "node.h"
#include "min_heap.h"


void scan_map(World *world);

World *init_world(char **map, short width, short height) {
    World *world = malloc(sizeof(World));
    world->map = map;
    world->height = height;
    world->width = width;
    world->num_princesses = 5;
    world->heap = init_heap(width * height * 100);
    world->nodeField = init_node_field(width, height, world->num_princesses);
    world->princesses = NULL;
    world->portals = NULL;
    scan_map(world);
    return world;
}

short length_from_map(char **map, short x, short y) {
    if(map[x][y] == 'N') {
        return 0x7f; //max value
    }
    if(map[x][y] == 'C' || map[x][y] == 'D' || map[x][y] == 'P' || map[x][y] == 'G') {
        return 1;
    }
    if(map[x][y] > 47 && map[x][y] < 58) { //port
        return 1;
    }
    if(map[x][y] == 'H') {
        return 2;
    }
    printf("------ UNKNOWN CHAR ------");
    return 1;
}

int check_node(World *world, Node *node, Node *parent) {
    if(node == NULL) {
        return 0;
    }
    if(world->map[node->x][node->y] == 'N') {
        return 0;
    }
    int new_value = length_from_map(world->map, node->x, node->y) + parent->value;
    if (node->value < 0 || new_value < node->value) {
        node->state = parent->state;
        node->value = (short) new_value;
        node->parent = parent;
        heap_insert(world->heap, node);
        return 1;
    }
    return 0;
}

void update_state(World *world, Node *node, short x, short y) {
    if(!generator_on(node)) {
        if(world->map[x][y] == 'G') {
            Node *new_state_node;
            if (dragon_slayed(node)) {
                new_state_node = world->nodeField->field[x][y][3][num_saved(node)];
            } else {
                new_state_node = world->nodeField->field[x][y][1][num_saved(node)];
            }
            printf("Generator on!\n");
            new_state_node->state = node->state;
            new_state_node->state |= 0x40u;
            check_node(world, new_state_node, node);
        }
    }
    if(!dragon_slayed(node)) {
        if(world->map[x][y] == 'D') {
            Node *new_state_node;
            if (generator_on(node)) {
                new_state_node = world->nodeField->field[x][y][3][num_saved(node)];
            } else {
                new_state_node = world->nodeField->field[x][y][2][num_saved(node)];
                printf("Dragon dead!\n");
            }
            new_state_node->state = node->state;
            new_state_node->state |= 0x20u;
            check_node(world, new_state_node, node);
        }
    }

}

void check_portals(World *world, Node *node, short x, short y) {
    if(generator_on(node)) {
        if(world->map[x][y] > 47 && world->map[x][y] < 58) {
            short port_id = (short) (world->map[x][y] - 48);
            for (int i = 0; i < world->num_portals[port_id]; ++i) {
                //printf("Using portal --");
                short portal_x = world->portals[port_id][i][0];
                short portal_y = world->portals[port_id][i][1];
                Node *portal = filtered_by_state(world->nodeField, node, portal_x, portal_y);
                portal->state = node->state;
                if(check_node(world, portal, node)) {
                    portal->value -= 1;
                }
            }
        }
    }

}

void check_princesses(World *world, Node *node, short x, short y) {
    if(dragon_slayed(node)) {
        if(world->map[x][y] == 'P') {
            for (unsigned short i = 0; i < world->num_princesses; ++i) {
                if(x == world->princesses[i][0] && y == world->princesses[i][1]){
                    printf("Princess %d found at %d %d!\n", i, x, y);
                    node->state |= 0x01u << i;
                    check_node(world, filtered_by_state(world->nodeField, node, x, y), node);
                }
            }
        }
    }
}

//returns length of the path
void spread_node(World *world, Node *node) {
    /*printf("Spreading %d %d. . .", node->x , node->y);
    if(dragon_slayed(node)) {
        printf("With dragon dead. . .");
    }
    printf("\n");*/
    update_state(world, node, node->x, node->y);
    check_portals(world, node, node->x, node->y);
    check_princesses(world, node, node->x, node->y);
    check_node(world, right_node(world->nodeField, node), node);
    check_node(world, left_node(world->nodeField, node), node);
    check_node(world, upper_node(world->nodeField, node), node);
    check_node(world, lower_node(world->nodeField, node), node);
    //printf("\n");
}

void scan_map(World *world) {
    //printf("Width %d | Height: %d\n", world->height, world->width);
    short num_portals = 100;
    short **princesses = malloc(world->num_princesses * sizeof(short));
    for (int j = 0; j < world->num_princesses; ++j) {
        princesses[j] = malloc(2 * sizeof(short));
    }
    short ***portals = malloc(10 * sizeof(short **));
    for (int i = 0; i < 10; ++i) {
        portals[i] = malloc(num_portals * sizeof(short *));
        for (int j = 0; j < num_portals; ++j) {
            portals[i][j] = malloc(2 * sizeof(short));
        }
    }

    short *portal_count = calloc(10, sizeof(short));
    short princess_count = 0;
    for (short x = 0; x < world->height; ++x) {
        for (short y = 0; y < world->width; ++y) {

            if(world->map[x][y] == 'P') {
                princesses[princess_count][0] = x;
                princesses[princess_count][1] = y;
                princess_count++;
            }
            printf("%c", world->map[x][y]);
            if(world->map[x][y] > 47 && world->map[x][y] < 58) { //port
                short port_id = (short) (world->map[x][y] - 48);
                portals[port_id][portal_count[port_id]][0] = x;
                portals[port_id][portal_count[port_id]][1] = y;
                portal_count[port_id]++;
            }
        }
        printf("\n");
    }

    world->princesses = princesses;
    world->num_princesses = princess_count;

    world->portals = portals;
    world->num_portals = portal_count;
}



Node *dijkstra(World *world) {
    Node *node = world->nodeField->field[0][0][0][0]; //starting node
    Node *finish = NULL;
    while (1) {
        spread_node(world, node);

        if(num_saved(node) >= world->num_princesses) {
            if(finish == NULL || node->value < finish->value) {
                printf("-- All saved, not finished, yet! --\n");
                finish = node;
            }
            if(heap_empty(world->heap) || heap_first(world->heap)->value > node->value) {
                printf("-- All saved. --\n");
                break;
            }
        }

        if (heap_empty(world->heap)) {
            printf("Empty heap\n");
            finish = node;
            break;
        }

        node = heap_extract(world->heap);
    }
    return finish;
}

int *reverse(int *path, int size) {
    size *= 2;
    int *reverse = malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        reverse[i] = path[size - i - 1];
    }

    free(path);
    return reverse;
}

int *zachran_princezne(char **mapa, int n, int m, int t, int *dlzka_cesty) {
    //n = height
    //m = width
    World *world = init_world(mapa, (short) m, (short) n);
    world->nodeField->field[0][0][0][0]->value = 1;

    Node *finish = dijkstra(world);

    int *path = malloc(finish->value * 3 * sizeof(int));

    printf("Length: %d\n", finish->value);
    //short x = 0, y = 0;
    //get_coordinates(world->nodeField, finish, &x, &y);
    printf("Coordinates:\n");
    *dlzka_cesty = 0;
    while(1){
        printf("%d %d", finish->x, finish->y);
        path[*dlzka_cesty * 2] = finish->x;
        path[*dlzka_cesty * 2 + 1] = finish->y;

        //finish = back_track(world, finish);
        finish = finish->parent;
        if(finish->x == path[*dlzka_cesty * 2] && path[*dlzka_cesty* 2 + 1] == finish->y) {
            finish = finish->parent;
        }
        printf(" -- prev: %d %d\n", finish->x, finish->y);
        *dlzka_cesty += 1;
        if(finish->parent == NULL) {
            path[*dlzka_cesty * 2] = finish->x;
            path[*dlzka_cesty * 2 + 1] = finish->y;
            *dlzka_cesty += 1;
            break;
        }
    }

    printf("-- final -- dlzka cesty %d --\n", *dlzka_cesty);
    path = reverse(path, *dlzka_cesty);
    printf("Reverse:\n");
    for (int k = 0; k < *dlzka_cesty; ++k) {
        printf("%d %d\n", path[k * 2], path[k * 2 + 1]);
    }
    return path;
}