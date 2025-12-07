#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024
#define MAX 1024

int cmp(const void *a, const void *b) {
  const long long *x = (const long long *)a;
  const long long *y = (const long long *)b;

  if (x[0] < y[0])
    return -1;
  if (x[0] > y[0])
    return 1;
  return 0;
}

int compute(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen");
    return 1;
  }
  char buffer[LINE_BUFFER_SIZE];
  long long range[MAX][2];
  int len = 0;
  while (fgets(buffer, sizeof(buffer), fp)) {
    buffer[strcspn(buffer, "\n")] = '\0';
    if (!strlen(buffer)) {
      break;
    }
    long long start = 0;
    long long end = 0;
    int i = 0;

    for (; buffer[i] != '-'; i++) {
      start = start * 10 + buffer[i] - '0';
    }
    i++;
    for (; buffer[i] != '\0'; i++) {
      end = end * 10 + buffer[i] - '0';
    }

    range[len][0] = start;
    range[len++][1] = end;
  }

  qsort(range, len, sizeof(range[0]), cmp);

  for (int i = 0; i < len; i++) {
    printf("%lld, %lld \n", range[i][0], range[i][1]);
  }

  long long counter = 0;
  long long current = 0;
  for (int i = 0; i < len; i++) {
    if (range[i][0] > current)
      current = range[i][0];
    long long add = (range[i][1] - current + 1);
    if (add < 0)
      continue;
    counter += add;
    current = range[i][1] + 1;
    printf("to add: %lld, %lld - %lld, =%lld\n", add, current, range[i][1],
           counter);
  }
  printf("%lld\n", counter);
  return 0;
}

int main() {
  compute("sample.txt");
  compute("input.txt");
  return 0;
}
