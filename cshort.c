#include <stdio.h>
#include <stdlib.h>
#define MAX_SRC_SIZE 10000
#define BUFFER_SIZE 30000

FILE* srcfile;
int buf[BUFFER_SIZE];
char* src;

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
                printf("%c", buf[pointer]);
                break;
            case ',':
                scanf("%c", &buf[pointer]);
                break;
            case '[':
                if (buf[pointer] == 0){
                    int lbracecount = 0;
                    do{
                        srcindex++;
                        if      (src[srcindex] == ']') lbracecount--;
                        else if (src[srcindex] == '[') lbracecount++;
                    }
                    while (lbracecount != -1);
                }
                break;
            case ']':
                if (buf[pointer] != 0){
                    int rbracecount = 0;
                    do{
                        srcindex--;
                        if      (src[srcindex] == ']') rbracecount++;
                        else if (src[srcindex] == '[') rbracecount--;
                    }
                    while (rbracecount != -1);
                }
                break;
            case '"':
                do{
                    srcindex++;
                }
                while (src[srcindex] != '"');
                break;
        }
        srcindex++;
    }
    while (srcindex < MAX_SRC_SIZE && src[srcindex] != '\0');
}

int main(){
    srcfile = fopen("src.bf", "r");
    fseek(srcfile, 0, SEEK_END);
    long fsize = ftell(srcfile);
    rewind(srcfile);
    src = (char*)malloc(fsize + 1);
    fread(src, 1, fsize, srcfile);
    src[fsize] = '\0';
    
    run();
    fclose(srcfile);
    free(src);

    return 0;
}