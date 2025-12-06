#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 10240

int compute(char * filename){
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    char buffer[LINE_BUFFER_SIZE];
    char num[10][5000][10];
    int col=0;
    int row=0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        char *token = strtok(buffer, " ");
        col = 0;
        while (token != NULL) {
            strncpy(num[row][col], token, sizeof(num[row][col]) - 1);
            token = strtok(NULL, " ");
            col++;
        }
        row++;
    }

    printf("row=%d, col=%d\n", row, col);
    long long ans =0 ;

    for (int i =0;i<col;i++) {
        char symbol = num[row-1][i][0];
        long long x=0;
        if (symbol == '*') {
            x=1;
        }
        printf("symbol %c \n", symbol);
        for (int j=0;j<row-1;j++) {
            if (symbol == '*') {
                x *= strtol(num[j][i], NULL, 10);
            }
            if (symbol == '+') {
                x += strtol(num[j][i], NULL, 10);
            }
        }
        printf("col=%d, x=%lld \n", i, x);
        ans += x;
    }
    printf("ans=%lld \n", ans);

    return 0;
}


int main() {
    /* compute("sample.txt"); */
    compute("input.txt");
    return 0;
}
