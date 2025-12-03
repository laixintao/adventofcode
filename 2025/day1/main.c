#include <stdio.h>
#include <stdlib.h>

#define LINE_BUFFER_SIZE 1024

int dial(int current, char direction, int number) {
    if (direction == 'L'){
        current -= number;
    }
    else {
        current += number;
    }
    while (current < 0)
        current += 100;
    while (current >= 100)
        current -=100;
    return current;
}
int dial_click(int current, char direction, int number, int* click_count) {
    int previous = current;
    int direction_int = 1;
    if (direction == 'L'){
        direction_int = -1;
    }

    while(number){
        number --;
        current += (direction_int);
        if (current == -1){
            current = 99;
        }
        if (current == 100){
            current = 0;
        }
        if (current == 0){
            (*click_count) ++;
        }
    }

    return current;
}

int compute(char * filename){
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    char buffer[LINE_BUFFER_SIZE];
    int counter = 0;
    int pointer = 50;
    int pointer2 = 50;
    int click_count = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        char direction = buffer[0];
        int number = atoi(&buffer[1]);
        pointer = dial(pointer, direction, number);
        if (pointer == 0){
            counter++;
        }
        pointer2 = dial_click(pointer2, direction, number, &click_count);
    }
    printf("%s answer: %d, part2 answer: %d\n", filename, counter, click_count);
    return counter;
}


int main() {
    compute("sample.txt");
    compute("input.txt");
    return 0;
}
