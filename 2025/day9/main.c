#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024

int is_valid(long minx, long maxx, long miny, long maxy, long points[][2],
             int len) {
  int valid = 1;
  printf("check %ld, %ld -- %ld, %ld \n", minx, miny, maxx, maxy);
  for (long p = minx + 1; p < maxx; p += (maxx - minx - 2)) {
    for (long q = miny + 1; q < maxy; q++) {
      // if on the line?
      long x1 = points[len - 1][0];
      long y1 = points[len - 1][1];

      long x2 = 0;
      long y2 = 0;
      for (int i = 0; i < len; i++) {
        x2 = points[i][0];
        y2 = points[i][1];

        if (x1 == x2 && x1 == p) {
          if ((q >= y1 && q <= y2) || (q >= y2 && q <= y1)) {
            return 0;
          }
        }

        if (y1 == y2 && y1 == q) {
          if ((p >= x1 && p <= x2) || (p >= x2 && p <= x1)) {
            return 0;
          }
        }
        x1 = x2;
        y1 = y2;
      }
    }
    if (maxx - minx - 2 == 0)
      break;
  }
  for (long q = miny + 1; q < maxy; q += (maxy - miny - 2)) {
    for (long p = minx + 1; p < maxx; p++) {
      // if on the line?
      long x1 = points[len - 1][0];
      long y1 = points[len - 1][1];

      long x2 = 0;
      long y2 = 0;
      for (int i = 0; i < len; i++) {
        x2 = points[i][0];
        y2 = points[i][1];

        if (x1 == x2 && x1 == p) {
          if ((q >= y1 && q <= y2) || (q >= y2 && q <= y1)) {
            return 0;
          }
        }

        if (y1 == y2 && y1 == q) {
          if ((p >= x1 && p <= x2) || (p >= x2 && p <= x1)) {
            return 0;
          }
        }
        x1 = x2;
        y1 = y2;
      }
    }
    if (maxy - miny - 2 == 0)
      break;
  }
  return 1;
}

int compute(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen");
    return 1;
  }
  char buffer[LINE_BUFFER_SIZE];
  long points[500][2] = {0};
  int row = 0;
  while (fgets(buffer, sizeof(buffer), fp)) {
    buffer[strcspn(buffer, "\n")] = '\0';
    char *token = strtok(buffer, ",");
    char *endptr;
    points[row][0] = strtol(token, &endptr, 10);
    points[row][1] = strtol(endptr + 1, NULL, 10);

    row++;
  }

  long long max = 0;
  for (int i = 0; i < row; i++) {
    for (int j = i + 1; j < row; j++) {
      // if valid?
      long minx = points[i][0];
      long maxx = points[j][0];
      if (maxx < minx) {
        long temp = maxx;
        maxx = minx;
        minx = temp;
      }

      long miny = points[i][1];
      long maxy = points[j][1];
      if (maxy < miny) {
        long temp = maxy;
        maxy = miny;
        miny = temp;
      }

      long long area = (labs(points[i][0] - points[j][0]) + 1) *
                       (labs(points[i][1] - points[j][1]) + 1);
      if (area > max && is_valid(minx, maxx, miny, maxy, points, row)) {
        max = area;
        printf("valid %d * %d max=%lld \n", i, j, max);
      }
    }
  }
  printf("max=%lld \n", max);
  return 0;
}

int main() {
  compute("sample.txt");
  compute("input.txt");
  return 0;
}
