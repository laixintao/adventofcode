#include <stdio.h>
#include <stdlib.h>

#define LINE_BUFFER_SIZE 1024

int compute(char * filename){
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    char buffer[LINE_BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), fp)) {
        // here!
    }
    return counter;
}


int main() {
    compute("sample.txt");
    compute("input.txt");
    return 0;
}
