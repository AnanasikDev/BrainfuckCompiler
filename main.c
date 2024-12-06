#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_SRC_SIZE 1000
#define BUFFER_SIZE 30000
#define SHOW_SOURCE 0

int ioshift = 0;

FILE* srcfile;
int buf[BUFFER_SIZE];
char* src;

void safeExit(){
    fclose(srcfile);
    free(src);
}

bool isSrcIndexValid(int index, const char* src){
    return index < MAX_SRC_SIZE && src != NULL && src[index] != '\0';
}

bool isSrcValid(const char* src){

    if (src == NULL || srcfile == NULL || !isSrcIndexValid(0, src)){
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

void readallto(const char* filename, char** buffer){
    srcfile = fopen(filename, "r");
    fseek(srcfile, 0, SEEK_END);
    long fsize = ftell(srcfile);
    rewind(srcfile);

    *buffer = (char*)malloc(fsize + 1);
    if (*buffer  == NULL){
        perror("Compilation failed: cannot open file");
        fclose(srcfile);
        return;
    }
    fread(*buffer, 1, fsize, srcfile);
    (*buffer)[fsize] = '\0';
}

void run(){
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
                            return;
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
                            return;
                        }
                    }
                    while (src[srcindex] != '[');
                }
                break;
        }

        srcindex++;
    }
    while (isSrcIndexValid(srcindex, src));
}

int main(){
    
    readallto("src.bf", &src);

    if (!isSrcValid(src))
    {
        safeExit();
        return 5;
    }
    
    if (SHOW_SOURCE){
        printf(src);
        printf("\n");
    }

    // define shift to ASCII printable characters starting from 0. 0 is Space.
    if (src[0] == '~'){
        ioshift = 32;
    }
    
    run();
    safeExit();

    // printf("\n");
    // pointer = 0;

    // do{
    //     printf("%d, ", buf[pointer]);
    //     pointer++;
    // }
    // while (pointer < BUFFER_SIZE);

    return 0;
}