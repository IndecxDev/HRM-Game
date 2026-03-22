#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/settings.h"
#include "code_commands.h"

CodeCommandType parseCCommand(char* input, char* arg1, char* arg2) {
    char command[MAX_LINE_LEN];

    int parsed = sscanf(input, "%s %s %s", command, arg1, arg2);
    if (parsed <= 2) {strcpy(arg2, "");}
    if (parsed <= 1) {strcpy(arg1, "");}
    if (parsed <= 0) {return CCMD_EMPTY;}

    if      (strcmp(command, "INPUT") == 0) return CCMD_INPUT;  
    else if (strcmp(command, "OUTPUT") == 0) return CCMD_OUTPUT;
    else if (strcmp(command, "*") == 0) return CCMD_COMMENT;
    else if (strcmp(command, "JUMP") == 0) return CCMD_JUMP;
    else if (strcmp(command, "JUMPZ") == 0) return CCMD_JUMPZ;
    else if (strcmp(command, "COPY") == 0) return CCMD_COPY;
    else if (strcmp(command, "ADD") == 0) return CCMD_ADD;
    else if (strcmp(command, "SUB") == 0) return CCMD_SUB;
    else return CCMD_ERR;
}

/*---------------------------------------------*/

ErrorType inputCCommand(int* input, int* inputIdx, int inputCount, int* hand, bool reference) {
    if (*inputIdx >= inputCount) {
        if (reference) {
            return ERR_REFERENCE_END;
        }
        return ERR_NONEXISTANT_INPUT;
    }
    *hand = input[*inputIdx];
    (*inputIdx)++;
    return ERR_NONE;
}

ErrorType outputCCommand(int **output, int *outputIdx, int *outputCount, int *hand, bool reference)
{
    if (reference && *hand != __INT_MAX__) {
        (*output)[*outputIdx] = *hand;
        (*outputIdx)++;
        (*outputCount)++;
        *hand = __INT_MAX__;
        return ERR_NONE;
    }
    
    if (*hand == __INT_MAX__){
        return ERR_EMPTY_HAND;
    }
    if ((*output)[*outputIdx] != *hand) {
        return ERR_WRONG_OUTPUT;
    }
    if (*outputIdx >= (*outputCount) - 1){
        (*outputIdx)++;
        *hand = __INT_MAX__;
        return ERR_FINISHED;
    }
    (*outputIdx)++;
    *hand = __INT_MAX__;
    return ERR_NONE;
}

ErrorType jumpCCommand(char* arg1, int* pc){
    int line = atoi(arg1);
    if (line == 0){
        return ERR_INVALID_ARGUMENT;
    }
    *pc = line-2;
    return ERR_NONE;
}

ErrorType copytoCCommand(int memIdx, int* hand, Level *levels, int levelId){
    if (*hand == __INT_MAX__) {
        return ERR_EMPTY_HAND;
    }
    levels[levelId-1].memory[memIdx-1] = *hand;
    return ERR_NONE;
}

ErrorType copyfromCCommand(int memIdx, int* hand, Level *levels, int levelId){
    if (levels[levelId-1].memory[memIdx-1] == __INT_MAX__) {
        return ERR_NONEXISTANT_INPUT;
    }
    *hand = levels[levelId-1].memory[memIdx-1];
    return ERR_NONE;
}

ErrorType addCCommand(int memIdx, int* hand, Level *levels, int levelId){
    if (levels[levelId-1].memory[memIdx-1] == __INT_MAX__) {
        return ERR_NONEXISTANT_INPUT;
    }
    if (*hand == __INT_MAX__) {
        return ERR_EMPTY_HAND;
    }
    *hand = *hand + levels[levelId-1].memory[memIdx-1];
    return ERR_NONE;
}

ErrorType subCCommand(int memIdx, int* hand, Level *levels, int levelId){
    if (levels[levelId-1].memory[memIdx-1] == __INT_MAX__) {
        return ERR_NONEXISTANT_INPUT;
    }
    if (*hand == __INT_MAX__) {
        return ERR_EMPTY_HAND;
    }
    *hand = *hand - levels[levelId-1].memory[memIdx-1];
    return ERR_NONE;
}

ErrorType jumpzCCommand(char* arg1, int* pc, int* hand){
    int line = atoi(arg1);
    if (line == 0){
        return ERR_INVALID_ARGUMENT;
    }
    if (*hand == __INT_MAX__) {
        return ERR_EMPTY_HAND;
    }
    if (*hand == 0){
        *pc = line-2;
    } 
    return ERR_NONE;
}