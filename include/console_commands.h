#pragma once

#include "settings.h"

void helpCmd();
void levelsCmd(Level *levels);
void playCmd(int levelId, Level *levels, int *currentLevel);
void runCmd(int levelId, Level *levels, bool debug);

CommandType parseCommand(const char *input, char *arg1);
bool handleCommand(char *command, Level *levels, int *currentLevel);