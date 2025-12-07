#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024

int compute(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen");
    return 1;
  }
  char buffer[200][LINE_BUFFER_SIZE];
  int col = 0, row = 0;
  int split = 0;

  while (fgets(buffer[row], sizeof(buffer), fp)) {
    buffer[row][strcspn(buffer[row], "\n")] = '\0';
    char *line = buffer[row];
    col = strlen(line);
    for (int i = 0; line[i] != '\0'; i++) {
      if (line[i] == '.' && row - 1 >= 0 &&
          (buffer[row - 1][i] == 'S' || buffer[row - 1][i] == '|')) {
        line[i] = '|';
      }
      if (line[i] == '^' && (buffer[row - 1][i] == '|')) {
        split++;
        if (i - 1 >= 0)
          line[i - 1] = '|';
        if (i + 1 < col)
          line[i + 1] = '|';
      }
    }
    printf("line: %s\n", line);

    row++;
  }

  printf("split: %d\n", split);
  return 0;
}

int main() {
  compute("sample.txt");
  compute("input.txt");
  return 0;
}
