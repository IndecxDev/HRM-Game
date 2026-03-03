#pragma once

#include "settings.h"

CodeCommandType parseCCommand(char* input, char* arg1, char* arg2);
ErrorType inputCCommand      (int* input, int* inputIdx, int inputCount, int* hand, bool reference);
ErrorType outputCCommand     (int** output, int* outputIdx, int* outputCount, int* hand, bool reference);
ErrorType jumpCCommand       (char* arg1, int* pc);
ErrorType copyfromCCommand   (int memIdx, int* hand, Level *levels, int levelId);
ErrorType copytoCCommand     (int memIdx, int* hand, Level *levels, int levelId);
ErrorType addCCommand        (int memIdx, int* hand, Level *levels, int levelId);
ErrorType subCCommand        (int memIdx, int* hand, Level *levels, int levelId);
ErrorType jumpzCCommand      (char* arg1, int* pc, int* hand);