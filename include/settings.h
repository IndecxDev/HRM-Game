#pragma once

#define MAX_INPUT_LEN 256
#define MAX_LINE_LEN 256
#define MAX_LEVELS 10
#define MAX_COMMAND_LOOP_LIMIT 5000
#define MAX_REF_PROGRAM_LEN 5000
#define MAX_OUTPUT_SIZE 500

typedef struct {
    bool fastProgram;
    bool shortProgram;
} Score;

typedef struct {
    int id;
    char name[64];
    char fluff[1024];
    char description[512];
    char inputOutput[256];
    char notes[512];

    bool unlocked;
    bool completed;
    Score score;
    int memorySize;
    int memory[10];
} Level;

typedef struct {
    int programLength;
    int totalCommandsRan;
} Result;

typedef enum {
    CMD_HELP,
    CMD_EXIT,
    CMD_LEVELS,
    CMD_PLAY,
    CMD_RUN,
    CMD_DOC,
    CMD_DEBUG,
    CMD_UNKNOWN,
    CMD_EMPTY
} CommandType;

typedef enum {
    CCMD_EMPTY,
    CCMD_COMMENT,
    CCMD_ERR,
    CCMD_INPUT,
    CCMD_OUTPUT,
    CCMD_JUMP,
    CCMD_COPY,
    CCMD_ADD,
    CCMD_SUB,
    CCMD_JUMPZ
} CodeCommandType;

typedef enum {
    RUNNING,
    STOPPED,
    DEBUGGING
} InterpreterState;

typedef enum {
    ERR_NONE,
    ERR_GENERAL,
    ERR_SYNTAX,
    ERR_PROGRAM_FAULT,
    ERR_NONEXISTANT_INPUT,
    ERR_FINISHED,
    ERR_WRONG_OUTPUT,
    ERR_EMPTY_HAND,
    ERR_OUTPUT_MISSING,
    ERR_INVALID_ARGUMENT,
    ERR_REFERENCE_END
} ErrorType;

typedef struct {
    char line[MAX_LINE_LEN];
    int lineNumber;
} ProgramLine;
