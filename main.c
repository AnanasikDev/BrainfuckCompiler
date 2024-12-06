#include <stdio.h>
#include <stdbool.h>
#define MAX_SRC_SIZE 1000
#define BUFFER_SIZE 30000
#define SHOW_SOURCE 1

int ioshift = 0;

FILE* srcfile;
int buf[BUFFER_SIZE];

bool isSrcIndexValid(int index, const char* src){
    return index < MAX_SRC_SIZE && src[index] != '\0';
}

bool isSrcValid(const char* src){

    if (srcfile == NULL || !isSrcIndexValid(0, src)){
        printf("Error opening file\n");
        return 0;
    }

    // check loops hierarchy
    int braces = 0;
    int index = 0;
    do{
        if (src[index] == '['){
            braces++;
        }
        if (src[index] == ']'){
            if (braces <= 0){
                printf("Compilation failed: cannot close ]: no [ preceding it found");
                return 0;
            }
            braces--;
        }
        index++;
    }
    while (isSrcIndexValid(index, src));

    if (braces != 0){
        printf("Compilation failed: loops have incorrect hierarchy\n");
        return 0;
    }

    printf("Compiled successfully\n");
    return 1;
}

int main(){
    srcfile = fopen("src.bf", "r");
    char src[MAX_SRC_SIZE];
    fgets(src, MAX_SRC_SIZE, srcfile);

    if (!isSrcValid(src))
        return 5;
    
    if (SHOW_SOURCE){
        printf(src);
        printf("\n");
    }

    // define shift to ASCII printable characters starting from 0. 0 is Space.
    if (src[0] == '~'){
        ioshift = 32;
    }
    
    int srcindex = 0;
    int pointer = 0;

    do{
        switch (src[srcindex]){
            case '<':
                pointer--;
                break;
            case '>':
                pointer++;
                break;
            case '-':
                buf[pointer]--;
                break;
            case '+':
                buf[pointer]++;
                break;
            case '.':
                printf("%c", (ioshift + buf[pointer]));
                break;
            case ',':
                scanf("%c", &buf[pointer]);
                buf[pointer] -= ioshift;
                break;
            case '[':
                if (buf[pointer] == 0){
                    // exit loop
                    do{
                        srcindex++;

                        // stop program if index is wrong
                        if (!isSrcIndexValid(srcindex, src)){
                            printf("SRC INDEX IS INVALID at [, %d", srcindex);
                            return -1;
                        }
                    }
                    while (src[srcindex] != ']');
                }
                break;
            case ']':
                if (buf[pointer] != 0){
                    // back to beginning of the loop

                    do{
                        srcindex--;

                        // stop program if index is wrong
                        if (!isSrcIndexValid(srcindex, src)){
                            printf("SRC INDEX IS INVALID at ], %d", srcindex);
                            return -1;
                        }
                    }
                    while (src[srcindex] != '[');
                }
                break;
        }

        srcindex++;
    }
    while (isSrcIndexValid(srcindex, src));

    // printf("\n");
    // pointer = 0;

    // do{
    //     printf("%d, ", buf[pointer]);
    //     pointer++;
    // }
    // while (pointer < BUFFER_SIZE);

    return 0;
}