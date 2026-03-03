#pragma once

#include "settings.h"

void sleep_ms(int milliseconds);
void freeVars(int* input, int* output);
void scoreProgram(int levelId, Level *levels, int totalCommandsRan, int programLength);
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
                    int *outputCount);