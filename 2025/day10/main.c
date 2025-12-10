#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define MAX_DIM 16
#define MAX_BUTTONS 64
#define MAX_LINE 4096

// ---------------- Priority Queue (Min-Heap) -----------------

typedef struct {
    int dist;
    int state[MAX_DIM];
} Node;

#define HEAP_MAX 2000000
static Node heap_arr[HEAP_MAX];
static int heap_size = 0;

#define SWAP(a,b) do { Node tmp=a; a=b; b=tmp; } while(0)

static inline void heap_push(Node nd) {
    int i = heap_size++;
    heap_arr[i] = nd;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap_arr[p].dist <= heap_arr[i].dist) break;
        SWAP(heap_arr[p], heap_arr[i]);
        i = p;
    }
}

static inline Node heap_pop() {
    Node ret = heap_arr[0];
    heap_arr[0] = heap_arr[--heap_size];

    int i = 0;
    while (1) {
        int l = i * 2 + 1;
        int r = l + 1;
        int s = i;
        if (l < heap_size && heap_arr[l].dist < heap_arr[s].dist) s = l;
        if (r < heap_size && heap_arr[r].dist < heap_arr[s].dist) s = r;
        if (s == i) break;
        SWAP(heap_arr[s], heap_arr[i]);
        i = s;
    }
    return ret;
}

// ----------------- Hash table (Chained!) ---------------------

typedef struct HNode {
    uint64_t key;
    int value;
    struct HNode *next;
} HNode;

#define HSIZE (1<<20)  // 1M buckets
static HNode **htable;

static inline uint64_t hash_state(const int *s, int dim) {
    uint64_t h = 0x9e3779b97f4a7c15ULL;
    for (int i = 0; i < dim; i++) {
        h ^= (uint64_t)s[i] + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
    }
    return h;
}

static inline int hash_query(uint64_t key) {
    HNode *p = htable[key & (HSIZE-1)];
    while (p) {
        if (p->key == key) return p->value;
        p = p->next;
    }
    return INT_MAX;  // not found
}

static inline void hash_update(uint64_t key, int val) {
    uint64_t idx = key & (HSIZE-1);
    HNode *p = htable[idx];
    while (p) {
        if (p->key == key) {
            if (val < p->value) p->value = val;
            return;
        }
        p = p->next;
    }
    // insert new node
    HNode *n = malloc(sizeof(HNode));
    n->key = key;
    n->value = val;
    n->next = htable[idx];
    htable[idx] = n;
}

// ---------------- Machine Struct ---------------------

typedef struct {
    int dim;
    int target[MAX_DIM];
    int button_count;
    int button[MAX_BUTTONS][MAX_DIM];
} Machine;

// ---------------- Dijkstra ---------------------------

int solve_machine(const Machine *m) {
    int dim = m->dim;

    // reset heap
    heap_size = 0;

    // reset hash table
    for (int i = 0; i < HSIZE; i++) htable[i] = NULL;

    Node start;
    start.dist = 0;
    memset(start.state, 0, sizeof(int) * dim);
    heap_push(start);

    uint64_t target_key = hash_state(m->target, dim);

    while (heap_size > 0) {
        Node cur = heap_pop();
        uint64_t k = hash_state(cur.state, dim);

        int old = hash_query(k);
        if (old <= cur.dist) continue;

        hash_update(k, cur.dist);

        if (k == target_key) {
            return cur.dist;
        }

        for (int b = 0; b < m->button_count; b++) {
            Node nxt;
            nxt.dist = cur.dist + 1;

            int valid = 1;
            for (int i = 0; i < dim; i++) {
                int nv = cur.state[i] + m->button[b][i];
                if (nv > m->target[i]) { valid = 0; break; }
                nxt.state[i] = nv;
            }
            if (!valid) continue;

            heap_push(nxt);
        }
    }

    return -1;
}

// ---------------- Parsing --------------------------

void parse_buttons(char *p, Machine *m) {
    int idx = 0;

    while (*p) {
        if (*p == '(') {
            memset(m->button[idx], 0, sizeof(int)*MAX_DIM);
            p++;
            while (*p != ')' && *p) {
                if (*p >= '0' && *p <= '9') {
                    int x = atoi(p);
                    if (x >= 0 && x < m->dim) {
                        m->button[idx][x] = 1;
                    }
                    while (*p >= '0' && *p <= '9') p++;
                } else {
                    p++;
                }
            }
            idx++;
        }
        p++;
    }
    m->button_count = idx;
}

void parse_target(char *p, Machine *m) {
    int idx = 0;
    while (*p) {
        if ((*p >= '0' && *p <= '9') || *p=='-') {
            m->target[idx++] = atoi(p);
            while ((*p >= '0' && *p <= '9')) p++;
        }
        else p++;
    }
    m->dim = idx;
}

// ---------------- Main -----------------------------

int main() {
    htable = malloc(sizeof(HNode *) * HSIZE);
    for (int i = 0; i < HSIZE; i++) htable[i] = NULL;

    char line[MAX_LINE];
    long long total = 0;

    while (fgets(line, sizeof(line), stdin)) {
        // Skip blank lines
        if (strlen(line) < 5) continue;

        Machine m;
        memset(&m, 0, sizeof(m));

        // parse dim from indicator lights between [...]
        char *L = strchr(line, '[');
        char *R = strchr(line, ']');

        if (!L || !R) continue;
        m.dim = (int)(R - L - 1);

        // parse buttons
        parse_buttons(line, &m);

        // parse target { ... }
        char *curly = strchr(line, '{');
        parse_target(curly, &m);

        int ans = solve_machine(&m);
        total += ans;
    }

    printf("Part 2 Total = %lld\n", total);
    return 0;
}
