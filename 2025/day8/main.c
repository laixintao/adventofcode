#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024
#define MEMBER 1000

int cmp_int(const void *a, const void *b) {
  int x = *(const int *)a;
  int y = *(const int *)b;
  return y - x;
}

struct Distance {
  long *start;
  long *end;
  int start_index;
  int end_index;
  double distance;
};

typedef struct {
  struct Distance **data;
  int size;
  int capacity;
} MinHeap;

MinHeap *heap_new(int capacity) {
  MinHeap *h = malloc(sizeof(MinHeap));
  h->data = malloc(sizeof(struct Distance *) * (capacity + 1)); // 1-based
  h->size = 0;
  h->capacity = capacity;
  return h;
}

void heap_push(MinHeap *h, struct Distance *val) {
  if (h->size >= h->capacity)
    return;

  int i = ++h->size;
  h->data[i] = val;

  while (i > 1) {
    int parent = i / 2;
    if (h->data[parent]->distance <= h->data[i]->distance)
      break;

    struct Distance *tmp = h->data[parent];
    h->data[parent] = h->data[i];
    h->data[i] = tmp;

    i = parent;
  }
}

struct Distance *heap_pop(MinHeap *h) {
  if (h->size == 0)
    return NULL;

  struct Distance *minv = h->data[1];
  h->data[1] = h->data[h->size--];

  int i = 1;
  while (1) {
    int left = i * 2;
    int right = i * 2 + 1;
    int smallest = i;

    if (left <= h->size &&
        h->data[left]->distance < h->data[smallest]->distance)
      smallest = left;

    if (right <= h->size &&
        h->data[right]->distance < h->data[smallest]->distance)
      smallest = right;

    if (smallest == i)
      break;

    struct Distance *tmp = h->data[i];
    h->data[i] = h->data[smallest];
    h->data[smallest] = tmp;

    i = smallest;
  }

  return minv;
}

struct Distance *heap_top(MinHeap *h) { return h->size ? h->data[1] : NULL; }

int compute(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen");
    return 1;
  }
  char buffer[LINE_BUFFER_SIZE];
  long points[1000][3];
  int row = 0;
  while (fgets(buffer, sizeof(buffer), fp)) {
    buffer[strcspn(buffer, "\n")] = '\0';
    int i = 0;
    char *token = strtok(buffer, ",");
    while (token != NULL) {
      points[row][i++] = strtol(token, NULL, 10);
      token = strtok(NULL, ",");
    }
    row++;
  }

  MinHeap *hp = heap_new(1000 * 1000);

  for (int i = 0; i < row; i++) {
    for (int j = i + 1; j < row; j++) {
      double dis = sqrt(pow(points[j][0] - points[i][0], 2) +
                        pow(points[j][1] - points[i][1], 2) +
                        pow(points[j][2] - points[i][2], 2));
      struct Distance *d = malloc(sizeof(struct Distance));
      d->start = points[i];
      d->end = points[j];
      d->distance = dis;
      d->start_index = i;
      d->end_index = j;

      heap_push(hp, d);
    }
  }

  long point_groups[1000] = {0};
  int group_members[1000000] = {0};
  int unused_group = 1;

  for (int i = 0;; i++) {
    struct Distance *d = heap_pop(hp);
    if (!d)
      break;

    for (int x = 0; x < 20; x++) {
      printf("%d ", group_members[x]);
    }
    printf("\n");
    printf("last: %ld, from %ld * %ld  \n", (d->start[0]) * (d->end[0]),
           d->start[0], d->end[0]);
    int belong_group = unused_group;

    if (point_groups[d->start_index] != 0 && point_groups[d->end_index] != 0) {
      if (point_groups[d->start_index] == point_groups[d->end_index]) {
        continue;
      }
      long old_group = point_groups[d->start_index];
      long new_group = point_groups[d->end_index];
      for (int i = 0; i < 1000; i++) {
        if (point_groups[i] == old_group)
          point_groups[i] = new_group;
      }
      group_members[new_group] += group_members[old_group];
      group_members[old_group] = 0;

      if (group_members[new_group] == MEMBER)
        break;

      continue;
    }

    if (point_groups[d->start_index] != 0) {
      point_groups[d->end_index] = point_groups[d->start_index];
      group_members[point_groups[d->start_index]]++;
      if (group_members[point_groups[d->start_index]] == MEMBER)
        break;
      continue;
    }

    if (point_groups[d->end_index] != 0) {
      point_groups[d->start_index] = point_groups[d->end_index];
      group_members[point_groups[d->end_index]]++;
      if (group_members[point_groups[d->end_index]] == MEMBER)
        break;
      continue;
    }

    point_groups[d->start_index] = point_groups[d->end_index] = unused_group;
    group_members[unused_group] += 2;
    if (group_members[unused_group] == MEMBER)
      break;
    unused_group++;

  }

  return 0;
}

int main() {
  /* compute("sample.txt"); */
  compute("input.txt");
  return 0;
}
