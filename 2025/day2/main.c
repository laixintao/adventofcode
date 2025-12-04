#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 1024 * 100
#define MAX 32

long long sum_invalid_id(long long start_long, long long end, int count_odd){
    int start[MAX];
    int start_len = 0;
    long long t = start_long;
    while (t > 0) {
    start[start_len++] = t % 10;
    t /= 10;
    }

    for (int i = 0; i < start_len / 2; i++) {
        int tmp = start[i];
        start[i] = start[start_len - 1 - i];
        start[start_len - 1 - i] = tmp;
    }

    long long sum = 0;
    long long added[99999] = {0LL};
    int added_len = 0;
    for( int repeat_len = 1; repeat_len < start_len; repeat_len ++) {
        printf("repeat_len=%d\n",  repeat_len);
        if (start_len % repeat_len != 0) continue;

        long long repeat0 = 1;

        long long base = 0;
        for (int i=0; i< repeat_len; i++) {
            repeat0 = repeat0 * 10;
            base = base * 10 + start[i];
        }
        printf("base=%lld, repeat_len=%d, repeat0=%lld, start_len=%d\n", base, repeat_len, repeat0, start_len);

        while(1){
            long long num = 0;
            for (int i=0; i< (start_len/repeat_len); i++) {
                num = repeat0 * num + base;
            }
            if (num > end) {
                break;
            }
            if (num >= start_long) {

                int has = 0;
                for (int x=0; x<added_len; x++){
                    if (added[x] == num) {
                        has = 1;
                        break;
                    }
                }
                if (!has) {
                    printf("=> %lld\n", num);
                    sum += num;
                    added[added_len++] = num;
                }
            }
            base ++;
        }
    }

    return sum;
}

int compute(char * filename, int count_odd){
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    char buffer[LINE_BUFFER_SIZE];
    fgets(buffer, sizeof(buffer), fp);
    const char delim = ',';
    char* token = strtok(buffer, &delim);
    long long sum = 0;
    while (token!=NULL) {
        printf("token: %s\n", token);
        if (token == NULL) {
            break;
        }
        long long end=0;
        long long start = 0;
        int start_len = 0;
        int end_len = 0;
        for (int i=0; token[i] != '\0';i++){
            if (token[i] != '-'){
                start = start * 10 + token[i] - '0';
                start_len ++;
            } else {
                break;
            }
        }

        for (int i=start_len+1; i<strlen(token);i++){
            if (token[i] > 9+'0' || token[i] <0+'0') break;
            end = end * 10 + (token[i] - '0');
            end_len += 1;
        }

        while (start_len<=end_len){
            long long _end = 9;
            long long _start = 1;

            for (int i =0; i<start_len-1; i++){
                _end = _end * 10 + 9;
                _start *= 10;
            }

            long long compute_end = end;
            if (compute_end > _end) {
                compute_end = _end;
            }

            long long compute_start = start;
            if (compute_start < _start) {
                compute_start = _start;
            }

            printf("now compute %lld, %lld\n", compute_start, compute_end);
            long long result = sum_invalid_id(compute_start, compute_end, count_odd);
            sum += result;
            start_len += 1;
        }
        token = strtok(NULL, &delim);
    }
    printf("sum=%lld \n", sum);

    return 0;
}


int main() {
    /* compute("sample.txt", 0); */
    /* compute("input.txt", 0); */
    compute("sample.txt", 1);
    compute("input.txt", 1);
    return 0;
}

