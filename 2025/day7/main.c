#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024

int total_row = 0;
long long cache[2000][1000];

long long count_timeline(char (*arr)[LINE_BUFFER_SIZE], int row, int i) {
  if (row == total_row - 2) {
    return 1;
  }

  if (cache[row][i] != -1) {
    return cache[row][i];
  }

  char *line = arr[row + 2];

  long long timeline = 0;

  if (line[i] == '^') {
    timeline += count_timeline(arr, row + 2, i - 1);
    timeline += count_timeline(arr, row + 2, i + 1);
  } else {
    timeline += count_timeline(arr, row + 2, i);
  }
  printf("%*s", row, "");
  printf("row = %d, i=%d, total=%lld\n", row, i, timeline);
  cache[row][i] = timeline;

  return timeline;
}

int compute(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen");
    return 1;
  }
  char buffer[200][LINE_BUFFER_SIZE];
  int row = 0;
  int split = 0;

  while (fgets(buffer[row], sizeof(buffer), fp)) {
    total_row += 1;
    buffer[row][strcspn(buffer[row], "\n")] = '\0';
    row++;
  }
  printf("total rows: %d \n", total_row);

  memset(cache, -1, sizeof(cache));

  long long timeline = 0;
  for (int i = 0; i < strlen(buffer[0]); i++) {
    if (buffer[0][i] == 'S') {
      timeline += count_timeline(buffer, 0, i);
    }
  }
  printf("timeline: %lld\n", timeline);
  return 0;
}

int main() {
  compute("sample.txt");
  compute("input.txt");
  return 0;
}
