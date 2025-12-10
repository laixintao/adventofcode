#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024

int output_target(int target[], int len) {
  printf("target: ");
  for (int i = 0; i < len; i++) {
    printf("%d ", target[i]);
  }
  return 1;
}

int all_set(int target[], int len) {
  for (int i = 0; i < len; i++) {
    if (target[i] != -1) {
      return 0;
    }
  }
  return 1;
}

int try_press(int target[], int target_len, int button[][100], int button_index,
              int button_len) {

  output_target(target, target_len);
  if (all_set(target, target_len)) {
    printf("match \n");
    return 0;
  } else if (button_index + 1 == button_len) {
    printf("no match\n");
    return 99999;
  }
  printf("\n%*s", 3 * button_index, " ");
  printf("N%d ", button_index);
  // not press;
  int total =
      try_press(target, target_len, button, button_index + 1, button_len);

  // press
  int *new_target = malloc(target_len * sizeof(int));
  memcpy(new_target, target, target_len * sizeof(*new_target));

  for (int i = 0; button[button_index][i] != -1; i++) {
    int idx = button[button_index][i];
    new_target[idx] *= -1;
  }
  printf("%*s", 3 * button_index, " ");
  printf("Y%d ", button_index);
  int press_total = 1 + try_press(new_target, target_len, button,
                                  button_index + 1, button_len);
  return press_total > total ? total : press_total;
}

void store_buttons(char *pointer, int *button_seq) {
  char *saveptr;
  pointer++;
  char *token = strtok_r(pointer, ",)", &saveptr);
  while (token != NULL) {
    *button_seq = atoi(token);
    button_seq++;
    token = strtok_r(NULL, ",)", &saveptr);
  }
}

int compute(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen");
    return 1;
  }
  char buffer[LINE_BUFFER_SIZE];
  int ans = 0;
  while (fgets(buffer, sizeof(buffer), fp)) {
    buffer[strcspn(buffer, "\n")] = '\0';

    printf("buffer: %s\n", buffer);
    int target[100] = {'\0'};
    int button[100][100];
    memset(button, -1, sizeof(button));
    char *pointer = buffer + 1;

    int i = 0;
    while (*pointer != ']') {
      if (*pointer == '#') {
        target[i++] = 1;
      } else {
        target[i++] = -1;
      }
      pointer++;
    }
    pointer++;

    int button_index = 0;
    pointer = strtok(pointer, " ");
    while (*pointer != '{') {
      store_buttons(pointer, button[button_index++]);
      pointer = strtok(NULL, " ");
    }
    button_index++;

    int total = try_press(target, i, button, 0, button_index);
    printf("total: %d\n", total);

    ans += total;
    for (int i = 0; i < button_index; i++) {
      for (int j = 0; j < 10; j++) {
        printf("%d ", button[i][j]);
      }
      printf("\n");
    }
  }
  printf("ans=%d\n", ans);
  return 0;
}

int main() {
  compute("sample.txt");
  compute("input.txt");
  return 0;
}
