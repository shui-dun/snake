#include <curses.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define MAX_N_TRAP 255
#define MAX_N_BOMB 20

typedef struct Axis {
    uint8_t x;
    uint8_t y;
} Axis;

typedef struct Node {
    Axis axis;
    struct Node *pre;
} Node;

char EMPTY = ' ';
char BORDER = '+';
char HEAD = 'O';
char BODY = 'o';
char TRAP = '+';
char BOMB = 'x';
char FOOD = '@';
bool god_mode;
pthread_t thread_input, thread_bomb;
Node *head, *tail;
char **map;
Axis food;
Axis *bombs;
uint8_t speed = 2;
int delay[] = {25000, 50000, 75000, 100000, 125000};
uint16_t len = 5;
uint8_t additional;
uint8_t n_trap = 30;
uint8_t n_bomb = 5;
uint8_t direction;
int8_t directs[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
char input_ch;

void destructor() {
    free(bombs);
    for (uint8_t i = 0; i < COLS; i++) free(map[i]);
    free(map);
    Node *cur = head, *temp = head;
    while (cur) {
        temp = temp->pre;
        free(cur);
        cur = temp;
    }
}

void game_over() {
    if (god_mode) return;
    move(LINES / 2 - 1, (COLS - 10) / 2);
    printw("Game Over!");
    move(LINES / 2, (COLS - 23) / 2);
    printw("Your Fianl Score is %d", len + additional);
    destructor();
    refresh();
    sleep(5);
    endwin();
    exit(0);
}

void update_map(char ch, int x, int y) {
    mvaddch(y, x, ch);
    map[x][y] = ch;
}

Axis next_pos(Axis axis, int direct) {
    return (Axis){axis.x + directs[direct][0], axis.y + directs[direct][1]};
}

Axis random_posion() {
    Axis ret;
    do {
        ret.y = rand() % (LINES - 2) + 1;
        ret.x = rand() % (COLS - 2) + 1;
    } while (map[ret.x][ret.y] != EMPTY);
    return ret;
}

bool is_circle() {
    int count = 0;
    for (uint8_t i = 0; i < 4; i++) {
        Axis axis = next_pos(head->axis, i);
        if (map[axis.x][axis.y] == BODY) {
            ++count;
            if (count >= 2) return true;
        }
    }
    return false;
}

bool far_from_head(Axis axis) {
    if (axis.x == 0) return true;
    return axis.x - head->axis.x > 10 || axis.x - head->axis.x < -10 ||
           axis.y - head->axis.y > 5 || axis.y - head->axis.y < -5;
}

bool search_snake(Axis axis, int direct) {
    uint8_t search_len = direct > 1 ? 10 : 5;
    Axis pre = axis, new_pos;
    for (uint8_t i = 0; i < search_len; i++) {
        new_pos = next_pos(pre, direct);
        if (map[new_pos.x][new_pos.y] == BORDER) return false;
        if (map[new_pos.x][new_pos.y] == BODY ||
            map[new_pos.x][new_pos.y] == HEAD)
            return true;
        pre = new_pos;
    }
    return false;
}

bool inside_snake(Axis axis) {
    for (uint8_t x = 0; x < 4; x++)
        if (!search_snake(axis, x)) return false;
    return true;
}

void destroy_bomb() {
    if (is_circle()) {
        for (uint8_t i = 0; i < n_bomb; i++) {
            if (far_from_head(bombs[i])) continue;
            if (inside_snake(bombs[i])) {
                update_map(TRAP, bombs[i].x, bombs[i].y);
                additional += 2;
                mvprintw(0, 0, "Score\t%d", len + additional);
                bombs[i].x = 0;
            }
        }
    }
}

void *move_bomb(void *parm) {
    bombs = (Axis *)malloc(sizeof(Axis) * n_bomb);
    for (uint8_t i = 0; i < n_bomb; i++) {
        bombs[i] = random_posion();
        update_map(BOMB, bombs[i].x, bombs[i].y);
    }
    while (1) {
        for (uint8_t i = 0; i < n_bomb; i++) {
            if (bombs[i].x == 0) continue;
            int random_direct = rand() % 4;
            Axis new_pos = next_pos(bombs[i], random_direct);
            uint8_t x = new_pos.x, y = new_pos.y;
            if (map[x][y] == EMPTY) {
                update_map(EMPTY, bombs[i].x, bombs[i].y);
                update_map(BOMB, x, y);
                bombs[i] = new_pos;
            }
        }
        sleep(1);
    }
}

void alloc_map() {
    map = (char **)malloc(COLS * sizeof(char *));
    for (uint8_t i = 0; i < COLS; i++)
        map[i] = (char *)malloc(LINES * sizeof(char));
    for (uint8_t x = 0; x < COLS; x++)
        for (uint8_t y = 0; y < LINES; y++) map[x][y] = EMPTY;
}

void draw_wall() {
    for (uint8_t i = 0; i < COLS; i++) {
        update_map(BORDER, i, 0);
        update_map(BORDER, i, LINES - 1);
    }
    for (uint8_t i = 1; i < LINES - 1; i++) {
        update_map(BORDER, 0, i);
        update_map(BORDER, COLS - 1, i);
    }
    mvprintw(0, 0, "Score\t%d", len + additional);
}

bool is_coincide(Axis a, Axis b) { return a.x == b.x && a.y == b.y; }

void random_food() {
    food = random_posion();
    update_map(FOOD, food.x, food.y);
}

Node *create_node(Axis axis, Node *pre) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->axis = axis;
    node->pre = pre;
    return node;
}

void init_snake() {
    head = create_node((Axis){len + 1, 2}, NULL);
    Node *pre = head;
    for (uint8_t i = len; i >= 2; i--) {
        tail = create_node((Axis){i, 2}, pre);
        pre = tail;
    }
    update_map(HEAD, head->axis.x, head->axis.y);
    for (Node *node = tail; node != head; node = node->pre)
        update_map(BODY, node->axis.x, node->axis.y);
}

void random_trap() {
    for (uint8_t i = 0; i < n_trap; i++) {
        Axis trap = random_posion();
        update_map(TRAP, trap.x, trap.y);
    }
}

void init() {
    srand((unsigned)time(NULL));
    noecho();
    curs_set(0);
    alloc_map();
    init_snake();
    draw_wall();
    random_trap();
    random_food();
}

void *wait_input(void *para) {
    while (1) {
        input_ch = getch();
    }
}

void gluttonous_snake() {
    while (1) {
        switch (input_ch) {
            case 'w':
            case 'W':
                direction = 0;
                break;
            case 's':
            case 'S':
                direction = 1;
                break;
            case 'a':
            case 'A':
                direction = 2;
                break;
            case 'd':
            case 'D':
            case 0:
                direction = 3;
                break;
        }
        Axis new_axis = next_pos(head->axis, direction);
        if (is_coincide(new_axis, food)) {
            len++;
            update_map(HEAD, food.x, food.y);
            update_map(BODY, head->axis.x, head->axis.y);
            Node *node = create_node(food, NULL);
            head->pre = node;
            head = node;
            mvprintw(0, 0, "Score\t%d", len + additional);
            random_food();
        } else if (map[new_axis.x][new_axis.y] != EMPTY) {
            game_over();
        } else {
            update_map(EMPTY, tail->axis.x, tail->axis.y);
            update_map(BODY, head->axis.x, head->axis.y);
            update_map(HEAD, new_axis.x, new_axis.y);
            Node *node = tail->pre;
            head->pre = tail;
            tail->pre = NULL;
            head = tail;
            head->axis = new_axis;
            tail = node;
        }
        destroy_bomb();
        refresh();
        if (direction == 1 || direction == 0)
            usleep(2 * delay[speed]);
        else
            usleep(delay[speed]);
    }
}

void parse_param(int argc, char **argv) {
    initscr();
    int opt, tmp, mlen;
    while ((opt = getopt(argc, argv, "s:h:o:t:b:l:g")) != -1) {
        switch (opt) {
            case 's':
                tmp = atoi(optarg);
                speed = tmp >= 0 ? (tmp > 4 ? 4 : tmp) : 0;
                break;
            case 'h':
                HEAD = *optarg;
                break;
            case 'o':
                BODY = *optarg;
                break;
            case 't':
                tmp = atoi(optarg);
                n_trap = tmp >= 0 ? (tmp > MAX_N_TRAP ? MAX_N_TRAP : tmp) : 0;
                break;
            case 'b':
                tmp = atoi(optarg);
                n_bomb = tmp >= 0 ? (tmp > MAX_N_BOMB ? MAX_N_BOMB : tmp) : 0;
                break;
            case 'l':
                mlen = COLS / 2;
                tmp = atoi(optarg);
                len = tmp >= 0 ? (tmp > mlen ? mlen : tmp) : 2;
                break;
            case 'g':
                god_mode = true;
                break;
        }
    }
}

int main(int argc, char **argv) {
    parse_param(argc, argv);
    init();
    pthread_create(&thread_input, NULL, wait_input, NULL);
    pthread_create(&thread_bomb, NULL, move_bomb, NULL);
    gluttonous_snake();
    return 0;
}
