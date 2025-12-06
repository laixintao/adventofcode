#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024
#define MAX 1024

int compute(char * filename){
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    char buffer[LINE_BUFFER_SIZE];
    long long range[MAX][2];
    int len = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (!strlen(buffer)){
            break;
        }
        long long start = 0;
        long long end = 0;
        int i=0;

        for (; buffer[i] !='-';i++) {
            start = start * 10 + buffer[i] - '0';
        }
        i++;
        for (; buffer[i] !='\0';i++) {
            end = end * 10 + buffer[i] - '0';
        }

        range[len][0] = start;
        range[len++][1] = end;
    }
    for (int i=0;i<len;i++){
        printf("%lld, %lld \n", range[i][0], range[i][1]);
    }

        int counter = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        long long num = strtol(buffer, NULL, 10);

        for (int i=0;i<len;i++){
            if (num >= range[i][0] && num <= range[i][1]) {
                counter++;
                break;
            }
        }
    }

    printf("counter: %d\n", counter);
    return 0;
}


int main() {
    compute("sample.txt");
    compute("input.txt");
    return 0;
}
