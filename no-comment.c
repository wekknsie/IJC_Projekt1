// no-comment.c
// Řešení IJC-DU1, příklad b), 23.3.2024
// Autor: Jan Hájek, FIT
// Přeloženo: gcc 13.2.0
// algoritmus odstraňující poznámky ve zdrojových kódech za pomocí stavového automatu

#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "error.h"

void noComment(int argc, char *argv[]);

int main(int argc, char *argv[]){
    noComment(argc, argv);
    return 0;
}

void noComment(int argc, char *argv[]){
    if(argc == 1){ //STDIN
        struct stat st;
        char c;
        int state = 0;
        bool sFlag = 0, bsFlag = 0;

        if((fstat(0, &st) == 0) && !(S_ISREG(st.st_mode))){
            warning("Program didn't get pipelined file on stdin - program awaits EOF");
        }

        while((c = getchar()) != EOF){
            switch(state){
                case 0:{
                    if(c == '"'){
                        state = 5;
                    }else if(c == '\''){
                        state = 6;
                    }else if(c == '/' && sFlag == false){
                        state = 1;
                        break;
                    }
                    fprintf(stdout ,"%c", c);
                    break;
                }
                case 1:{
                    if(c == '/'){
                        state = 2;
                    }else if(c == '*'){
                        state = 3;
                    }else{
                        state = 0;
                        fprintf(stdout, "/");
                    }
                    break;
                }
                case 2:{
                    if(c == '\n'){
                        state = 0;
                    }
                    break;
                }
                case 3:{
                    if(c == '*'){
                        state = 4;
                    }
                    break;
                }
                case 4:{
                    if(c == '/'){
                        state = 0;
                        break;
                    }
                    state = 3;
                    break;
                }
                case 5:{
                    if(bsFlag){
                        fprintf(stdout ,"%c", c);
                        bsFlag = 0;
                        break;
                    }else if(c == '\\'){
                        bsFlag = 1;
                    }else if(c == '"'){
                        state = 0;
                    }
                    fprintf(stdout ,"%c", c);
                    break;
                }
                case 6:{
                    if(bsFlag){
                        fprintf(stdout ,"%c", c);
                        bsFlag = 0;
                        break;
                    }else if(c == '\\'){
                        bsFlag = 1;
                    }else if(c == '\''){
                        state = 0;
                    }
                    fprintf(stdout ,"%c", c);
                    break;
                }
            }
        }

        if(sFlag){
            error_exit("Incomplete string");
        }else if(state > 0){
            error_exit("Incomplete comment");
        }

    }else if(argc > 2){ //ERROR
        error_exit("Bad argument count - %d arguments", argc);
    }else{ //FILE
        FILE *file;
        char c;
        int state = 0;
        bool sFlag = 0, bsFlag = 0;

        if((file = fopen(argv[1], "r+")) == NULL){
            error_exit("Cant open file named %s", argv[1]);
        }

        while((c = getc(file)) != EOF){
            switch(state){
                case 0:{
                    if(c == '"'){
                        state = 5;
                    }else if(c == '\''){
                        state = 6;
                    }else if(c == '/' && sFlag == false){
                        state = 1;
                        break;
                    }
                    fprintf(stdout ,"%c", c);
                    break;
                }
                case 1:{
                    if(c == '/'){
                        state = 2;
                    }else if(c == '*'){
                        state = 3;
                    }else{
                        state = 0;
                        //fseek(file, -1, SEEK_CUR);
                        fprintf(stdout, "/%c", c);
                    }
                    break;
                }
                case 2:{
                    if(c == '\n'){
                        state = 0;
                    }
                    break;
                }
                case 3:{
                    if(c == '*'){
                        state = 4;
                    }
                    break;
                }
                case 4:{
                    if(c == '/'){
                        state = 0;
                        break;
                    }
                    state = 3;
                    break;
                }
                case 5:{
                    if(bsFlag){
                        fprintf(stdout ,"%c", c);
                        bsFlag = 0;
                        break;
                    }else if(c == '\\'){
                        bsFlag = 1;
                    }else if(c == '"'){
                        state = 0;
                    }
                    fprintf(stdout ,"%c", c);
                    break;
                }
                case 6:{
                    if(bsFlag){
                        fprintf(stdout ,"%c", c);
                        bsFlag = 0;
                        break;
                    }else if(c == '\\'){
                        bsFlag = 1;
                    }else if(c == '\''){
                        state = 0;
                    }
                    fprintf(stdout ,"%c", c);
                    break;
                }
            }
        }

        if(sFlag){
            error_exit("Incomplete string");
        }else if(state > 0){
            error_exit("Incomplete comment");
        }

        fclose(file);
    }
}
