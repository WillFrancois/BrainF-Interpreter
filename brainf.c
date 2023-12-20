#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

    FILE* bf_file = fopen(argv[1], "r");

    if(bf_file == NULL){
        printf("No file with that name!");
        return -1;
    }

    //Initialize array
    char cells[30000] = {0};
    char *cell_num = cells;
    char bf_command;
    int loop_start;
    int skip = 0;

    //Read the characters
    while(!feof(bf_file)){
        bf_command = fgetc(bf_file);

        switch(bf_command){
            case '>':
                ++cell_num;
                break;
            case '<':
                --cell_num;
                break;
            case '+':
                ++*cell_num;
                break;
            case '-':
                --*cell_num;
                break;
            case '.':
                printf("%c", *cell_num);
                break;
            case ',':
                *cell_num = getchar();
                printf("\n");
                break;
            case '[':
                if(*cell_num == 0){
                    while(1){
                        bf_command = fgetc(bf_file);
                        if(bf_command == ']' && skip == 0){
                            puts("end.");
                            break;
                        }
                        else if(bf_command == '['){
                            puts("found inner loop");
                            skip += 1;
                        }
                        else if(bf_command == ']'){
                            puts("found outer loop");
                            skip -= 1;
                        }
                    }
                }
                break;
            case ']':
                if(*cell_num != 0){
                    while(1){
                        fseek(bf_file, -2, SEEK_CUR);
                        bf_command = fgetc(bf_file);
                        if(bf_command == '[' && skip == 0){
                            break;
                        }
                        else if(bf_command == ']'){
                            skip += 1;
                        }
                        else if(bf_command == '['){
                            skip -= 1;
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
    

    int err = fclose(bf_file);

    if(err != 0){
        printf("Could not close file!");
        return -2;
    }
    else{
        return 0;
    }
    
}