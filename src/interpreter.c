#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/settings.h"
#include "../include/input_generator.h"
#include "../include/code_commands.h"
#include "../include/save_load.h"

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds){ // Cross-platform sleep function
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

void resetMemory(Level *levels) {
    levels[2].memory[0] = 1;
    levels[2].memory[1] = 3;
    levels[2].memory[2] = 4;
    levels[2].memory[3] = 5;
    levels[2].memory[4] = 9;

    levels[3].memory[0] = 0;
    levels[3].memory[1] = 0;

    levels[4].memory[0] = 0;
    levels[4].memory[1] = 0;
    levels[4].memory[2] = 0;
    levels[4].memory[3] = 0;

    levels[5].memory[0] = 0;
    levels[5].memory[1] = 0;

    levels[6].memory[0] = 0;
    levels[6].memory[1] = 0;

    levels[7].memory[0] = 0;
    levels[7].memory[1] = 0;

    levels[8].memory[0] = 1;
    levels[8].memory[1] = 0;
    levels[8].memory[2] = 0;
}

void scoreProgram(int levelId, Level *levels, int totalCommandsRan, int programLength, Result result) {
    printf("\n\033[1;32m---------------\nProgram Passed!\n---------------\033[0m\n\n");
    printf("\033[1;37mFast Program Challenge:\n");
    printf("\033[1;36mLimit: \033[1;37m%d\033[1;36m instructions\nAchieved: \033[1;37m%d\033[1;36m instructions\n", result.totalCommandsRan, totalCommandsRan);
    if (result.totalCommandsRan >= totalCommandsRan) {
        levels[levelId - 1].score.fastProgram = true;
        printf("\033[1;32mChallenge Passed!\033[0m\n");
    }
    else {
        printf("\033[1;31mChallenge Failed!\033[0m\n");
    }
    printf("\n\033[1;37mShort Program Challenge:\n");
    printf("\033[1;36mLimit: \033[1;37m%d\033[1;36m lines of code\nAchieved: \033[1;37m%d\033[1;36m lines of code\n", result.programLength, programLength);
    if (result.programLength >= programLength) {
        levels[levelId - 1].score.shortProgram = true;
        printf("\033[1;32mChallenge Passed!\033[0m\n");
    }
    else {
        printf("\033[1;31mChallenge Failed!\033[0m\n");
    }
    saveData(levels);
}

void unlockLevels(int levelId, Level *levels) {
    switch(levelId) {
        case 4:
            levels[4].unlocked = true;
            levels[6].unlocked = true;
        break;
        case 6: case 8:
            if (levels[5].completed && levels[7].completed) {
                levels[8].unlocked = true;
            }
        break;
        default:
            levels[levelId].unlocked = true;
        break;
    }
}

ErrorType interpret(ProgramLine* program, 
                    Level *levels, 
                    int levelId, 
                    bool debug, 
                    int programLength, 
                    bool reference,
                    Result *result,
                    int **input,
                    int **output,
                    int *inputCount,
                    int *outputCount) {
    if (!reference) printf("Interpreting NeoCOBOL program for %s\n", levels[levelId - 1].name);
    else printf("Interpreting reference NeoCOBOL program for %s\n", levels[levelId - 1].name);

    int pc = 0; // Program counter
    int hand = __INT_MAX__; // What the player currenly has in hand
    int inputIdx = 0; // Next input that will be grabbed with INPUT
    int outputIdx = 0; // Next output that will be compared to with OUTPUT
    int totalCommandsRan = 0; // How fast the program is

    int refProgramLength = 0;
    int refCommandCount = 0;

    if (reference) getInput(levelId, input, inputCount);
    if (!reference && *output == NULL) {
        printf("\033[1;31mReference program failed to give output.\033[0m\n");
        return ERR_GENERAL;
    }
    if (reference && *output == NULL) {
        printf("\033[1;31mNeed to allocate shit.\033[0m\n");
    }
    resetMemory(levels);

    if (debug) {
        printf("\033[1;36mInput line: [");
        for (int i = 0; i < *inputCount; i++) {
            printf("%d%s", (*input)[i], i < (*inputCount)-1 ? ", " : "]");
        }
        printf("\033[0m\n");
        printf("\033[1;36mExpected output line: [");
        for (int i = 0; i < *outputCount; i++) {
            printf("%d%s", (*output)[i], i < (*outputCount)-1 ? ", " : "]");
        }
        printf("\033[0m\n");
    }

    int emptyLines = 0;
    for (int i = 0; i < programLength; i++) {
        char buffer[MAX_LINE_LEN];
        char c = ' ';
        if (sscanf(program[i].line, "%s", buffer) <= 0) {emptyLines++;};
        sscanf(buffer, " %c", &c);
        if (c == '*') {emptyLines++;};
    }

    CodeCommandType cmd;
    char arg1[MAX_INPUT_LEN], arg2[MAX_INPUT_LEN];

    bool finished = false;
    int memIdx;
    while (pc < programLength && !finished) {
        cmd = parseCCommand(program[pc].line, arg1, arg2);
        if (cmd == CCMD_ERR) {
            printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid Command - %s\033[0m\n", pc+1, program[pc].line);
            return ERR_SYNTAX;
        }

        int previousPc;
        ErrorType err = ERR_NONE;
        switch (cmd) {
            case CCMD_EMPTY: case CCMD_COMMENT:
                totalCommandsRan--;
                break;
            case CCMD_INPUT:
                if (strcmp(arg1, "") != 0 || strcmp(arg2, "") != 0) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid argument\033[0m\n", pc+1);
                    return ERR_SYNTAX;
                }

                err = inputCCommand(*input, &inputIdx, *inputCount, &hand, reference);
                if (err == ERR_NONEXISTANT_INPUT) {
                    printf("\033[1;33mError on line \033[1;37m%d\033[1;33m: Tried to take non-existent value from input.\033[0m\n", pc+1);
                    return ERR_PROGRAM_FAULT;
                }
                
                if (err == ERR_REFERENCE_END) {
                    finished = true;
                    break;
                }

                if (debug) {printf("%3d: %-15s | Getting input: %d\n", pc+1, program[pc].line, hand);}
                break;
            case CCMD_OUTPUT:
                if (strcmp(arg1, "") != 0 || strcmp(arg2, "") != 0) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid argument\033[0m\n", pc+1);
                    return ERR_SYNTAX;
                }

                if (debug) {printf("%3d: %-15s | Pushing output: %d\n", pc+1, program[pc].line, hand);}
                err = outputCCommand(output, &outputIdx, outputCount, &hand, reference);
                if (err == ERR_WRONG_OUTPUT) {
                    printf("\033[1;33mError on line \033[1;37m%d\033[1;33m: Wrong output: \033[1;37m%d\033[1;33m, expected \033[1;37m%d\033[0m\n", pc+1, hand, (*output)[outputIdx]);
                    return ERR_PROGRAM_FAULT;
                } else if (err == ERR_EMPTY_HAND) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Tried to output empty value.\033[0m\n", pc+1);
                    return ERR_PROGRAM_FAULT;
                } else if (err == ERR_FINISHED) {
                    finished = true;
                }
                
                if (reference) {refProgramLength = programLength; refCommandCount = totalCommandsRan+1;}
                break;
            case CCMD_JUMP:
                if (strcmp(arg2, "") != 0) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid argument\033[0m\n", pc+1);
                    return ERR_SYNTAX;
                }
                
                previousPc = pc;
                err = jumpCCommand(arg1, &pc);
                if (debug) {printf("%3d: %-15s | Jumping to line %d\n", previousPc+1, program[previousPc].line, pc+2);}
                if (err == ERR_INVALID_ARGUMENT) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid jump instruction\033[0m\n", pc+1);
                    return ERR_SYNTAX;
                }
                break;
            case CCMD_JUMPZ:
                if (strcmp(arg2, "") != 0) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid argument\033[0m\n", pc+1);
                    return ERR_SYNTAX;
                }

                previousPc = pc;
                err = jumpzCCommand(arg1, &pc, &hand);
                if (debug) {
                    if (previousPc == pc) 
                        printf("%3d: %-15s | Not jumping, %d is not zero.\n", previousPc+1, program[previousPc].line, hand);
                    else 
                        printf("%3d: %-15s | Jumping to line %d, %d is zero.\n", previousPc+1, program[previousPc].line, pc+2, hand);
                }
                if (err == ERR_EMPTY_HAND) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid jump if zero because of empty register.\033[0m\n", pc+1);
                    return ERR_PROGRAM_FAULT;
                }
                if (err == ERR_INVALID_ARGUMENT) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid jump instruction\033[0m\n", pc+1);
                    return ERR_SYNTAX;
                }
                break;
            case CCMD_COPY:
                // COPY TO
                if (strcmp(arg1, "TO") == 0) {
                    memIdx = atoi(arg2);
                    if (memIdx <= 0 || memIdx > levels[levelId-1].memorySize) {
                        printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid memory address\033[0m\n", pc+1);
                        return ERR_SYNTAX;
                    }
                    if (debug) {printf("%3d: %-15s | Copying %d to address %d\n", pc+1, program[pc].line, hand, memIdx);}
                    err = copytoCCommand(memIdx, &hand, levels, levelId);
                    if (err == ERR_EMPTY_HAND){
                        printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Tried to copy an empty value.\033[0m\n", pc+1);
                        return ERR_PROGRAM_FAULT;
                    }
                    break;
                }
                // COPY FROM
                else if (strcmp(arg1, "FROM") == 0) {
                    memIdx = atoi(arg2);
                    if (memIdx <= 0 || memIdx > levels[levelId-1].memorySize) {
                        printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid memory address\033[0m\n", pc+1);
                        return ERR_SYNTAX;
                    }
                    if (debug) {printf("%3d: %-15s | Copying %d from address %d\n", pc+1, program[pc].line, levels[levelId-1].memory[memIdx-1], memIdx);}
                    err = copyfromCCommand(memIdx, &hand, levels, levelId);
                    if (err == ERR_NONEXISTANT_INPUT){
                        printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Tried to copy an empty value.\033[0m\n", pc+1);
                        return ERR_PROGRAM_FAULT;
                    }
                    break;
                }
                printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid Command - %s\033[0m\n", pc+1, program[pc].line);
                return ERR_SYNTAX;
            case CCMD_ADD:
                if (strcmp(arg2, "") != 0) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid argument\033[0m\n", pc+1);
                    return ERR_SYNTAX;
                }

                memIdx = atoi(arg1);
                if (memIdx <= 0 || memIdx > levels[levelId-1].memorySize) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid memory address\033[0m\n", pc+1);
                    return ERR_SYNTAX;
                }
                if (debug) {printf("%3d: %-15s | Adding %d from address %d to %d\n", pc+1, program[pc].line, levels[levelId-1].memory[memIdx-1], memIdx, hand);}
                err = addCCommand(memIdx, &hand, levels, levelId);
                if (err == ERR_NONEXISTANT_INPUT){
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Tried to add an empty value.\033[0m\n", pc+1);
                    return ERR_PROGRAM_FAULT;
                }
                if (err == ERR_EMPTY_HAND){
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Tried to add to an empty value.\033[0m\n", pc+1);
                    return ERR_PROGRAM_FAULT;
                }
                break;
            case CCMD_SUB:
                if (strcmp(arg2, "") != 0) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid argument\033[0m\n", pc+1);
                    return ERR_SYNTAX;
                }

                memIdx = atoi(arg1);
                if (memIdx <= 0 || memIdx > levels[levelId-1].memorySize) {
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Invalid memory address\033[0m\n", pc+1);
                    return ERR_SYNTAX;
                }
                if (debug) {printf("%3d: %-15s | Subtracting %d from address %d from %d\n", pc+1, program[pc].line, levels[levelId-1].memory[memIdx-1], memIdx, hand);}
                err = subCCommand(memIdx, &hand, levels, levelId);
                if (err == ERR_NONEXISTANT_INPUT){
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Tried to subtract an empty value.\033[0m\n", pc+1);
                    return ERR_PROGRAM_FAULT;
                }
                if (err == ERR_EMPTY_HAND){
                    printf("\033[1;31mError on line \033[1;37m%d\033[1;31m: Tried to subtract from an empty value.\033[0m\n", pc+1);
                    return ERR_PROGRAM_FAULT;
                }
                break;
            default:
                printf("\033[1;31mUnknown Error\033[0m\n");
                return ERR_GENERAL;
        }

        if (debug) {sleep_ms(10);}
        totalCommandsRan++;
        pc++;

        if (totalCommandsRan > MAX_COMMAND_LOOP_LIMIT) {
            printf("\033[1;31mError: Infinite loop.\033[0m\n");
            return ERR_GENERAL;
        }
    } 

    if (outputIdx != *outputCount) {
        printf("\033[1;33mError: Too few output values: \033[1;37m%d\033[1;33m, expected \033[1;37m%d\033[0m\n", outputIdx, *outputCount);
        return ERR_PROGRAM_FAULT;
    }

    programLength -= emptyLines;

    // REFERENCE PROGRAM STOPS HERE
    if (reference) {
        result->totalCommandsRan = refCommandCount;
        result->programLength = refProgramLength;
        return ERR_NONE;
    }

    levels[levelId-1].completed = true;
    
    unlockLevels(levelId, levels);
    scoreProgram(levelId, levels, totalCommandsRan, programLength, *result);

    return ERR_NONE;
}