#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024
#define REGION_MAX 50

char presents[6][8][3][4];
int variant_count[6] = {0};
int shape_area[6] = {0};

void rotate(char original[3][4], char shape[3][4]) {
  memset(shape, 0, 3 * 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      shape[i][j] = original[2 - j][i];
    }
  }
}

void horizontal(char original[3][4], char shape[3][4]) {
  memset(shape, 0, 12);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      shape[i][j] = original[i][2 - j];
    }
  }
}

int exist(char (*shape)[4], char (*existing)[3][4], int count) {
  for (int existing_i = 0; existing_i < count; existing_i++) {
    if (0 == memcmp(shape, existing[existing_i], 3 * 4)) {
      return 1;
    }
  }
  return 0;
}

void variant() {
  for (int i = 0; i < 6; i++) {
    int next = 1;
    char(*original)[4] = presents[i][0];

    char shape[3][4];
    char current[3][4];
    memcpy(current, original, sizeof(current));
    for (int _ = 0; _ < 3; _++) {
      rotate(current, shape);
      if (!exist(shape, presents[i], next)) {
        memcpy(presents[i][next], shape, sizeof(shape));
        next++;
      }
      memcpy(current, shape, sizeof(current));
    }
    horizontal(original, current);
    for (int _ = 0; _ < 4; _++) {
      rotate(current, shape);
      if (!exist(shape, presents[i], next)) {
        memcpy(presents[i][next], shape, sizeof(shape));
        next++;
      }
      memcpy(current, shape, sizeof(current));
    }

    variant_count[i] = next;
  }
}

int put(char present[3][4], int region[REGION_MAX][REGION_MAX], int row,
        int col, int max_row, int max_col) {
  // test it first, if can not put, do not edit
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (row + i >= max_row) {
        return 0;
      }
      if (col + j >= max_col) {
        return 0;
      }

      if (present[i][j] == '#' && region[row + i][col + j] == 1) {
        return 0;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (present[i][j] == '#') {
        region[row + i][col + j] = 1;
      }
    }
  }
  return 1;
}

int recover(char present[3][4], int region[REGION_MAX][REGION_MAX], int row,
            int col) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (present[i][j] == '#') {
        region[row + i][col + j] = 0;
      }
    }
  }

  return 1;
}

int possible_fit(int *num, int region[REGION_MAX][REGION_MAX], int max_row,
                 int max_col) {
  int empty = 0;
  for (int r = 0; r < max_row; r++)
    for (int c = 0; c < max_col; c++)
      if (region[r][c] == 0)
        empty++;

  int need = 0;
  for (int i = 0; i < 6; i++)
    need += num[i] * shape_area[i];

  if (need > empty)
    return 0;

  // for i-th present
  for (int i = 0; i < 6; i++) {
    if (num[i] == 0) {
      if (i == 5 && num[i] == 0) {
        // all done!
        return 1;
      }
      continue;
    }

    // for every variant
    for (int v = 0; v < variant_count[i]; v++) {
      for (int row = 0; row < max_row; row++) {
        for (int col = 0; col < max_col; col++) {
          if (region[row][col] == 1)
            continue;
          int can_put = put(presents[i][v], region, row, col, max_row, max_col);
          if (!can_put) {
            continue;
          }

          *(num + i) -= 1;
          if (possible_fit(num, region, max_row, max_col)) {
            return 1;
          }

          recover(presents[i][v], region, row, col);
          *(num + i) += 1;
        }
      }
    }
    return 0;
  }
  return 0;
}

int fit(char *target) {
  char *token = strtok(target, ": ");
  printf("region: %s ==> ", token);
  int present_num[6] = {0};
  for (int i = 0; i < 6; i++) {
    char *ntoken = strtok(NULL, " ");
    int x = atoi(ntoken);
    present_num[i] = x;
    printf("%d ", present_num[i]);
  }

  int row = 0;
  int col = 0;
  token = strtok(token, "x");
  row = atoi(token);
  token = strtok(NULL, "x");
  col = atoi(token);
  printf("row=%d col=%d\n", row, col);
  printf("\n");

  int region[REGION_MAX][REGION_MAX] = {0};
  return possible_fit(present_num, region, row, col);
}

int compute(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen");
    return 1;
  }
  char buffer[LINE_BUFFER_SIZE];
  int loaded_presents = 0;
  int loading_present_line = 0;

  char cases[1000][100] = {0};
  int total_case = 0;

  while (fgets(buffer, sizeof(buffer), fp)) {
    buffer[strcspn(buffer, "\n")] = '\0';
    if (!strlen(buffer) || strlen(buffer) == 2)
      continue;

    if (loaded_presents < 6) {
      memcpy(presents[loaded_presents][0][loading_present_line], buffer, 4);
      loading_present_line++;

      for (int i = 0; i < 3; i++)
        shape_area[loaded_presents] += (buffer[i] == '#');

      if (loading_present_line == 3) {
        loading_present_line = 0;
        loaded_presents++;
      }
    } else {
      printf("test the case: %s\n", buffer);
      memcpy(&cases[total_case++], buffer, strlen(buffer) + 1);
    }
  }

  for (int i = 0; i < 6; i++) {
    printf("%d shape area: %d\n", i, shape_area[i]);
  }
  variant();

  for (int i = 0; i < 6; i++) {
    printf("%dth present:\n", i);
    for (int j = 0; j < 3; j++) {
      for (int v_i = 0; v_i < variant_count[i]; v_i++) {
        printf("%s   ", presents[i][v_i][j]);
      }
      printf("\n");
    }
  }

  int fit_case = 0;
  for (int case_i = 0; case_i < total_case; case_i++) {
    printf("case %d", case_i);
    int f = fit(cases[case_i]);
    printf("fix? %d\n", f);
    fit_case += f;
  }
  printf("total cases: %d\n", fit_case);
  return 0;
}

int main() {
  /* compute("sample.txt"); */
  compute("input.txt");
  return 0;
}
