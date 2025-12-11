#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 2048
#define MAX_EDGES 8192

// 图：邻接表
int head[MAX_NODES];
int to[MAX_EDGES];
int next_edge[MAX_EDGES];
int edge_cnt = 0;

// 名字映射
char names[MAX_NODES][4]; // 三个字母 + '\0'
int node_cnt = 0;

// 记忆化 DP
long long memo1[MAX_NODES];        // Part 1: you -> out
long long memo2[MAX_NODES][2][2];  // Part 2: svr -> out, with dac/fft flags

// 这些 id 在读完输入后通过 get_id("xxx") 拿
int id_you = -1;
int id_svr = -1;
int id_out = -1;
int id_dac = -1;
int id_fft = -1;

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    next_edge[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

// 找到名字对应的 id，不存在则创建
int get_id(const char *name) {
    for (int i = 0; i < node_cnt; i++) {
        if (strcmp(names[i], name) == 0) {
            return i;
        }
    }
    if (node_cnt >= MAX_NODES) {
        fprintf(stderr, "Too many nodes\n");
        exit(1);
    }
    strncpy(names[node_cnt], name, 3);
    names[node_cnt][3] = '\0';
    return node_cnt++;
}

// Part 1: 从 node 到 out 的路径数量
long long dfs1(int node) {
    if (node == id_out) {
        return 1;
    }
    if (memo1[node] != -1) {
        return memo1[node];
    }
    long long total = 0;
    for (int e = head[node]; e != -1; e = next_edge[e]) {
        int v = to[e];
        total += dfs1(v);
    }
    memo1[node] = total;
    return total;
}

// Part 2: 从 node 到 out 的路径数量，当前已是否见过 dac/fft
long long dfs2(int node, int has_dac, int has_fft) {
    // 当前节点可能就是 dac / fft
    if (node == id_dac) has_dac = 1;
    if (node == id_fft) has_fft = 1;

    if (memo2[node][has_dac][has_fft] != -1) {
        return memo2[node][has_dac][has_fft];
    }

    if (node == id_out) {
        long long res = (has_dac && has_fft) ? 1 : 0;
        memo2[node][has_dac][has_fft] = res;
        return res;
    }

    long long total = 0;
    for (int e = head[node]; e != -1; e = next_edge[e]) {
        int v = to[e];
        total += dfs2(v, has_dac, has_fft);
    }
    memo2[node][has_dac][has_fft] = total;
    return total;
}

int main(void) {
    // 初始化 head 和 memo
    for (int i = 0; i < MAX_NODES; i++) {
        head[i] = -1;
        memo1[i] = -1;
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                memo2[i][a][b] = -1;
            }
        }
    }

    FILE *fp = fopen("input", "r");
    if (!fp) {
        perror("fopen input");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        // 跳过空行
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        // 找到冒号
        char *colon = strchr(line, ':');
        if (!colon) continue;

        *colon = '\0'; // 把左边单独截出来

        // 左边是起点名字
        char start_name[4];
        // 名字都是 3 个字母，前面可能有空格
        if (sscanf(line, " %3s", start_name) != 1) {
            continue;
        }
        int u = get_id(start_name);

        // 右边是终点列表
        char *rest = colon + 1;
        char *token = strtok(rest, " \t\n");
        while (token) {
            // token 也是 3 个字母名字
            if (strlen(token) >= 1) {
                // 去掉末尾的换行之类
                char name[4] = {0};
                strncpy(name, token, 3);
                name[3] = '\0';
                int v = get_id(name);
                add_edge(u, v);
            }
            token = strtok(NULL, " \t\n");
        }
    }
    fclose(fp);

    // 获取各个关键节点的 id
    id_you = get_id("you");
    id_svr = get_id("svr");
    id_out = get_id("out");
    id_dac = get_id("dac");
    id_fft = get_id("fft");

    // Part 1: from "you" to "out"
    long long ans1 = dfs1(id_you);
    printf("Part 1: paths from you to out = %lld\n", ans1);

    // Part 2: from "svr" to "out", must pass dac and fft
    long long ans2 = dfs2(id_svr, 0, 0);
    printf("Part 2: paths from svr to out that visit dac and fft = %lld\n", ans2);

    return 0;
}
