#include <stdio.h>
#include <stdlib.h>

void getInput(int levelId, int** input, int* count) {
    switch (levelId) {
        case 1:
            *count = 3;
            *input = (int*) malloc(sizeof(int) * *count);
            for (int i = 0; i < *count; i++){
                int number = rand() % 21 - 10;
                (*input)[i] = number;
            }
            break;
        case 2:
            *count = 5 + rand() % 6;
            *input = (int*) malloc(sizeof(int) * *count);
            for (int i = 0; i < *count; i++){
                int number = rand() % 21 - 10;
                (*input)[i] = number;
            }
            break;
        case 3:
            *count = 3;
            *input = (int*) malloc(sizeof(int) * *count);
            for (int i = 0; i < *count; i++){
                int number = rand() % 51 - 50;
                (*input)[i] = number;
            }
            break;
        case 4:
            *count = 10;
            *input = (int*) malloc(sizeof(int) * *count);
            for (int i = 0; i < *count; i++){
                int number = rand() % 21 - 10;
                (*input)[i] = number;
            }
            break;
        case 5:
            *count = 5 + rand() % 6;
            *input = (int*) malloc(sizeof(int) * *count);
            for (int i = 0; i < *count; i++){
                int number = rand() % 21 - 10;
                (*input)[i] = number;
            }
            break;
        case 6:
            *count = 6 + (rand() % 6) * 2;
            *input = (int*) malloc(sizeof(int) * *count);
            for (int i = 0; i < *count; i++){
                int number = rand() % 41 - 20;
                (*input)[i] = number;
            }
            break;
        case 7:
            *count = 5 + rand() % 6;
            *input = (int*) malloc(sizeof(int) * *count);
            (*input)[0] = 1 + rand() % 20;
            (*input)[1] = 0;
            for (int i = 2; i < *count; i++){
                if (rand() % 5 <= 1) {
                    (*input)[i] = 0;
                    continue;
                }
                int number = rand() % 41 - 20;
                (*input)[i] = number;
            }
            break;
        case 8:
            *count = 10 + (rand() % 6) * 2;
            *input = (int*) malloc(sizeof(int) * *count);
            (*input)[0] = 1 + rand() % 9;
            (*input)[1] = 0;
            (*input)[2] = 0;
            (*input)[3] = 1 + rand() % 9;
            for (int i = 4; i < *count; i++){
                if (rand() % 5 <= 1) {
                    (*input)[i] = 0;
                    continue;
                }
                int number = 1 + rand() % 9;
                (*input)[i] = number;
            }
            break;
        case 9:
            *count = 3 + rand() % 3;
            *input = (int*) malloc(sizeof(int) * *count);
            for (int i = 0; i < *count; i++){
                int number = 1 + rand() % 9;
                (*input)[i] = number;
            }
            break;
        default:
            break;
    }
}