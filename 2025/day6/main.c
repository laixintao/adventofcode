#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 10240

int compute(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen");
    return 1;
  }
  char buffer[10][LINE_BUFFER_SIZE];
  int col = 0;
  int row = 0;

  while (fgets(buffer[row], sizeof(buffer), fp)) {
    buffer[row][strcspn(buffer[row], "\n")] = '\0';
    row++;
  }

  col = strlen(buffer[0]);
  long long ans = 0;

  char symbol = 0;
  long long m = 1;
  long long s = 0;
  for (int i = col - 1; i >= 0; i--) {
    long long num = 0;
    for (int j = 0; j < row; j++) {
      if (buffer[j][i] == '*') {
        symbol = '*';
        break;
      }
      if (buffer[j][i] == '+') {
        symbol = '+';
        break;
      }
      int c = buffer[j][i] - '0';
      if (c > 9 || c < 0) {
        continue;
      }
      num = num * 10 + (buffer[j][i] - '0');
    }
    if (num == 0)
      continue;

    m *= num;
    s += num;

    printf("num=%lld m=%lld s=%lld \n", num, m, s);

    if (symbol == '*') {
      ans += m;
      printf("ans + %lld = %lld \n", m, ans);
      m = 1;
      s = 0;
      symbol = 0;
    }
    if (symbol == '+') {
      ans += s;
      printf("ans + %lld = %lld \n", s, ans);
      m = 1;
      s = 0;
      symbol = 0;
    }
  }
  printf("ans=%lld \n", ans);
  return 0;
}

int main() {
  /* compute("sample.txt"); */
  compute("input.txt");
  return 0;
}
