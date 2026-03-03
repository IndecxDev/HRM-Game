#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/settings.h"
#include "../include/interpreter.h"
#include "../include/reference.h"

void helpCmd() { 
    printf("Available commands:\n");
    printf("HELP: Displays this help message.\n");
    printf("LEVELS: Displays available levels.\n");
    printf("PLAY: <Level ID>: Enters an unlocked level.\n");
    printf("RUN: Runs the program corresponding to the current level named 'lvl[x].ncob'.\n");
    printf("DEBUG: Runs the program in debug mode, showing each step in detail.\n");
    printf("DOCS: Displays documentation for the available NeoCOBOL instructions.\n");
    printf("EXIT: Exits the game.\n");
}

void docsCmd(Level *levels) {
    printf("You can write comments by putting * at the start of a line.\n\n");

    printf("\033[1;33mINPUT\033[0m\n");
    printf("  Arguments: None\n");
    printf("  Gets the top value in the input buffer and replaces the register's value with it.\n\n");

    printf("\033[1;33mOUTPUT\033[0m\n");
    printf("  Arguments: None\n");
    printf("  Puts the register's value onto the output buffer and sets a null value into the register.\n");
    printf("  Outputting a value also forces a check if the value is correct and will throw an error if it is not.\n\n");

    if (!levels[1].unlocked) {return;}
    printf("\033[1;33mJUMP <Line Number>\033[0m\n");
    printf("  Arguments: (1) Line number to jump to.\n");
    printf("  Makes the program jump to the line specified in the argument.\n");
    printf("  \033[1;31mLine numbers start from 1.\033[0;m\n\n");

    if (levels[6].unlocked) {
        printf("\033[1;33mJUMPZ <Line Number>\033[0m\n");
        printf("  Arguments: (1) Line number to jump to.\n");
        printf("  Makes the program jump to the line specified in the argument only if the number in the register is zero.\n");
        printf("  \033[1;31mLine numbers start from 1.\033[0;m\n\n");
    }

    if (!levels[2].unlocked) {return;}
    printf("\033[1;33mCOPY FROM <Memory Address>\033[0m\n");
    printf("  Arguments: (1) The address index to copy from.\n");
    printf("  Copies the value from the memory address specified in the argument to the register.\n");
    printf("  \033[1;31mIndexing starts from 1.\033[0;m\n\n");

    printf("\033[1;33mCOPY TO <Memory Address>\033[0m\n");
    printf("  Arguments: (1) The address index to copy to.\n");
    printf("  Copies the value from the register to the memory address specified in the argument.\n");
    printf("  \033[1;31mIndexing starts from 1.\033[0;m\n\n");

    if (levels[4].unlocked) {
        printf("\033[1;33mADD <Memory Address>\033[0m\n");
        printf("  Arguments: (1) The address index to add from.\n");
        printf("  Copies the value from the memory address specified in the argument and adds it to the register.\n");
        printf("  \033[1;31mIndexing starts from 1.\033[0;m\n\n");
    }
    if (levels[5].unlocked) {
        printf("\033[1;33mSUB <Memory Address>\033[0m\n");
        printf("  Arguments: (1) The address index to subtract from.\n");
        printf("  Copies the value from the memory address specified in the argument and subtracts it from the register.\n");
        printf("  \033[1;31mIndexing starts from 1.\033[0;m\n\n");
    }
}

void levelsCmd(Level *levels) {
    printf("%s%s%s\n", levels[0].unlocked ? "\033[1;37m1\033[0m" : "\033[1;90m1\033[0m", levels[0].score.fastProgram ? "\033[1;32m*\033[0m" : " ", levels[0].score.shortProgram ? "\033[1;33m*\033[0m" : " ");
    printf("|\n");
    printf("%s%s%s\n", levels[1].unlocked ? "\033[1;37m2\033[0m" : "\033[1;90m2\033[0m", levels[1].score.fastProgram ? "\033[1;32m*\033[0m" : " ", levels[1].score.shortProgram ? "\033[1;33m*\033[0m" : " ");
    printf("|\n");
    printf("%s%s%s\n", levels[2].unlocked ? "\033[1;37m3\033[0m" : "\033[1;90m3\033[0m", levels[2].score.fastProgram ? "\033[1;32m*\033[0m" : " ", levels[2].score.shortProgram ? "\033[1;33m*\033[0m" : " ");
    printf("|\n");
    printf("%s%s%s\n", levels[3].unlocked ? "\033[1;37m4\033[0m" : "\033[1;90m4\033[0m", levels[3].score.fastProgram ? "\033[1;32m*\033[0m" : " ", levels[3].score.shortProgram ? "\033[1;33m*\033[0m" : " ");
    printf("+----+\n");
    printf("|    |\n");
    printf("%s%s%s  ", levels[4].unlocked ? "\033[1;37m5\033[0m" : "\033[1;90m5\033[0m", levels[4].score.fastProgram ? "\033[1;32m*\033[0m" : " ", levels[4].score.shortProgram ? "\033[1;33m*\033[0m" : " ");
    printf("%s%s%s\n", levels[6].unlocked ? "\033[1;37m7\033[0m" : "\033[1;90m7\033[0m", levels[6].score.fastProgram ? "\033[1;32m*\033[0m" : " ", levels[6].score.shortProgram ? "\033[1;33m*\033[0m" : " ");
    printf("|    |\n");
    printf("%s%s%s  ", levels[5].unlocked ? "\033[1;37m6\033[0m" : "\033[1;90m6\033[0m", levels[5].score.fastProgram ? "\033[1;32m*\033[0m" : " ", levels[5].score.shortProgram ? "\033[1;33m*\033[0m" : " ");
    printf("%s%s%s\n", levels[7].unlocked ? "\033[1;37m8\033[0m" : "\033[1;90m8\033[0m", levels[7].score.fastProgram ? "\033[1;32m*\033[0m" : " ", levels[7].score.shortProgram ? "\033[1;33m*\033[0m" : " ");
    printf("|    |\n");
    printf("+----+\n");
    printf("|\n");
    printf("%s%s%s\n", levels[8].unlocked ? "\033[1;37m9\033[0m" : "\033[1;90m9\033[0m", levels[8].score.fastProgram ? "\033[1;32m*\033[0m" : " ", levels[8].score.shortProgram ? "\033[1;33m*\033[0m" : " ");
}

void playCmd(int levelId, Level *levels, int *currentLevel) {
    if (levelId > 0 && levelId <= MAX_LEVELS && levels[levelId - 1].unlocked) {
        *currentLevel = levelId;
        printf("\033[1;37mLevel %d: %s\033[0m\n\n%s\n%s\n%s\n%s\n", 
        levels[levelId - 1].id, 
        levels[levelId - 1].name, 
        levels[levelId - 1].fluff, 
        levels[levelId - 1].description,
        levels[levelId - 1].inputOutput,
        levels[levelId - 1].notes);
    } else {
        printf("Invalid level ID or level is locked.\n");
    }
}

void runCmd(int levelId, Level *levels, bool debug) {
    if (levelId == 0) {
        printf("Cannot run program when not in a level.\n");
        return;
    }

    char programName[32];
    sprintf(programName, "lvl%d.ncob", levelId);
    FILE *programFile = fopen(programName, "r");

    if (programFile == NULL) {
        perror("Error opening program.\n");
        return;
    }

    // Reference program load
    Result result = {-1, -1};
    char* referenceProgramString = (char*) malloc(MAX_REF_PROGRAM_LEN);
    getReferenceProgram(&referenceProgramString, levelId);

    if (strcmp(referenceProgramString, "\n") == 0) {
        printf("\033[1;31mReference program doesn't exist.\033[0m\n");
        free(referenceProgramString);
        return;
    }

    ProgramLine *reference = NULL;
    int refLineCount = 0;
    int refProgramCapacity = 10;

    // Allocate initial memory for the reference program
    reference = (ProgramLine *)malloc(refProgramCapacity * sizeof(ProgramLine));
    if (reference == NULL) {
        perror("Memory allocation failed for reference program.\n");
        free(referenceProgramString);
        fclose(programFile);
        return;
    }

    char *lineStart = referenceProgramString;
    char *lineEnd;

    while ((lineEnd = strchr(lineStart, '\n')) != NULL) {
        int lineLength = lineEnd - lineStart;

        if (refLineCount >= refProgramCapacity) {
            refProgramCapacity *= 2;
            ProgramLine *temp = (ProgramLine *)realloc(reference, refProgramCapacity * sizeof(ProgramLine));
            if (temp == NULL) {
                perror("Memory reallocation failed for reference program.\n");
                free(reference);
                free(referenceProgramString);
                fclose(programFile);
                return;
            }
            reference = temp;
        }

        strncpy(reference[refLineCount].line, lineStart, lineLength);
        reference[refLineCount].line[lineLength] = '\0'; // Null-terminate
        reference[refLineCount].lineNumber = refLineCount + 1;
        refLineCount++;

        lineStart = lineEnd + 1; // Move to the next line
    }
    // Handle the last line (if any)
    if (*lineStart != '\0') { // Check if there's anything left
        int lineLength = strlen(lineStart);
        if (refLineCount >= refProgramCapacity) {
            refProgramCapacity *= 2;
            ProgramLine *temp = (ProgramLine *)realloc(reference, refProgramCapacity * sizeof(ProgramLine));
            if (temp == NULL) {
                perror("Memory reallocation failed for reference program.\n");
                free(reference);
                free(referenceProgramString);
                fclose(programFile);
                return;
            }
            reference = temp;
        }
        strncpy(reference[refLineCount].line, lineStart, lineLength);
                reference[refLineCount].line[lineLength] = '\0'; // Null-terminate
        reference[refLineCount].lineNumber = refLineCount + 1;
        refLineCount++;
    }

    // Real program load ----------------------------------------------

    ProgramLine *program = NULL; // Initialize to NULL
    int lineCount = 0;
    int programCapacity = 10; // Initial capacity

    program = (ProgramLine *)malloc(programCapacity * sizeof(ProgramLine));
    if (program == NULL) {
        perror("Memory allocation failed\n");
        fclose(programFile);
        free(program);
        free(referenceProgramString);
        free(reference);
        return;
    }

    // Read the entire program into memory, dynamically resizing the array
    while (fgets(program[lineCount].line, MAX_LINE_LEN, programFile) != NULL) {
        program[lineCount].line[strcspn(program[lineCount].line, "\n")] = 0;
        program[lineCount].lineNumber = lineCount + 1;
        lineCount++;

        if (lineCount >= programCapacity) {
            programCapacity *= 2;
            ProgramLine *temp = (ProgramLine *)realloc(program, programCapacity * sizeof(ProgramLine));
            if (temp == NULL) {
                perror("Memory reallocation failed\n");
                free(program); // Free previously allocated memory
                free(referenceProgramString);
                free(reference);
                fclose(programFile);
                return;
            }
            program = temp;
        }
    }
    
    if (ferror(programFile)) {
        free(referenceProgramString);
        free(reference);
        free(program);
        perror("Error reading program.\n");
        return;
    }
    fclose(programFile);

    int *input = nullptr; 
    int *output = (int*) malloc(sizeof(int) * MAX_OUTPUT_SIZE); 
    int inputCount = 0, outputCount = 0;
    if (interpret(reference, levels, levelId, false, refLineCount, true, &result, &input, &output, &inputCount, &outputCount) != ERR_NONE) {
        printf("\033[1;31mReference program doesn't exist or failed.\033[0m\n");
        free(referenceProgramString);
        free(reference);
        free(program);
        free(input);
        free(output);
        return;
    }
    interpret(program, levels, levelId, debug, lineCount, false, &result, &input, &output, &inputCount, &outputCount);

    free(referenceProgramString);
    free(reference);
    free(program);
    free(input);
    free(output);
}

/*-----------------------------------------------------------*/

CommandType parseCommand(const char *input, char *arg1) {
    char command[MAX_INPUT_LEN];
    if (strcmp(input, "") == 0) return CMD_EMPTY;

    int err = sscanf(input, "%s %s", command, arg1);
    if (err == 1) {strcpy(arg1, "");}
    
    if      (strcasecmp(command, "HELP") == 0) return CMD_HELP;  
    else if (strcasecmp(command, "LEVELS") == 0) return CMD_LEVELS;
    else if (strcasecmp(command, "RUN") == 0) return CMD_RUN;
    else if (strcasecmp(command, "PLAY") == 0) return CMD_PLAY;
    else if (strcasecmp(command, "DOCS") == 0) return CMD_DOC;
    else if (strcasecmp(command, "DEBUG") == 0) return CMD_DEBUG;
    else if (strcasecmp(command, "EXIT") == 0) return CMD_EXIT;
    
    else return CMD_UNKNOWN;
}

bool handleCommand(char *command, Level *levels, int *currentLevel) {
    char arg1[MAX_INPUT_LEN];
    CommandType cmd = parseCommand(command, arg1);
    int levelId = atoi(arg1);

    switch (cmd) {
        case CMD_HELP:
            helpCmd();
            break;
        case CMD_LEVELS:
            levelsCmd(levels);
            break;
        case CMD_PLAY:
            playCmd(levelId, levels, currentLevel);
            break;
        case CMD_RUN: 
            runCmd(*currentLevel, levels, false);
            break;
        case CMD_DOC: 
            docsCmd(levels);
            break;
        case CMD_DEBUG: 
            runCmd(*currentLevel, levels, true);
            break;
        case CMD_EMPTY: 
            break;
        case CMD_EXIT:
            return false;
        case CMD_UNKNOWN:
            printf("Invalid command. Type HELP for available commands.\n");
            break;
    }
    return true;
}