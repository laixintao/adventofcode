#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024
#define MAX 1024

const int direction[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                             {0, 1},   {1, -1}, {1, 0},  {1, 1}};

int compute(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen");
    return 1;
  }
  char buffer[LINE_BUFFER_SIZE];
  char rolls[MAX][MAX] = {0};
  int line = 0;
  int roll = 0;
  while (fgets(buffer, sizeof(buffer), fp)) {
    buffer[strcspn(buffer, "\n")] = '\0';
    memcpy(rolls[line++], buffer, LINE_BUFFER_SIZE);
    for (int i = 0; i < LINE_BUFFER_SIZE; i++) {
      if (buffer[i] == '@') {
        roll++;
      }
    }
  }

  int width = strlen(rolls[0]);
  int height = line;
  int total_removed = 0;
  while (roll) {
    int counter = 0;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (rolls[i][j] != '@')
          continue;
        int blocks = 0;
        for (int d = 0; d < 8; d++) {
          int row = i + direction[d][0];
          if (row < 0 || row >= height)
            continue;

          int col = j + direction[d][1];
          if (col < 0 || col >= width)
            continue;

          if (rolls[row][col] == '@' || rolls[row][col] == 'x')
            blocks++;
        }
        if (blocks < 4) {
          counter++;
          rolls[i][j] = '.';
        }
      }
      printf("%s \n", rolls[i]);
    }
    roll -= counter;
    total_removed += counter;
    if (counter == 0) {
      break;
    }
  }
  printf("total removed: %d", total_removed);
  return 0;
}

int main() {
  compute("sample.txt");
  compute("input.txt");
  return 0;
}
