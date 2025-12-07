#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024

long long get_joltage(char *line) {
  const int d = 12;
  long long num = 0;
  int start = 0;

  for (int current = 0; current < d; current++) {
    int digit = 0;
    int max_end = strlen(line) - (12 - 1 - current);
    for (int i = start; i < max_end; i++) {
      if (digit < line[i] - '0') {
        digit = line[i] - '0';
        start = i + 1;
      }
    }
    num = num * 10 + digit;
  }
  return num;
}

int compute(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen");
    return 1;
  }
  char buffer[LINE_BUFFER_SIZE];
  long long sum = 0;
  while (fgets(buffer, sizeof(buffer), fp)) {
    buffer[strcspn(buffer, "\n")] = '\0';
    // here!
    long long max = get_joltage(buffer);
    printf("line: %s, max %lld\n", buffer, max);
    sum += max;
  }
  printf("sum is: %lld\n", sum);
  return sum;
}

int main() {
  compute("sample.txt");
  compute("input.txt");
  return 0;
}
