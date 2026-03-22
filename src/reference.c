#include <string.h>

#include "../include/settings.h"

void getReferenceProgram(char** program, int levelId){
    switch (levelId)
    {
    case 1:
        strcpy(*program, 
        "INPUT\n"
        "OUTPUT\n"
        "INPUT\n"
        "OUTPUT\n"
        "INPUT\n"
        "OUTPUT\n");
        break;
    case 2:
        strcpy(*program, 
        "INPUT\n"
        "OUTPUT\n"
        "JUMP 1\n");
        break;
    case 3:
        strcpy(*program, 
        "COPY FROM 2\n"
        "OUTPUT\n"
        "COPY FROM 1\n"
        "OUTPUT\n"
        "COPY FROM 3\n"
        "OUTPUT\n"
        "COPY FROM 1\n"
        "OUTPUT\n"
        "COPY FROM 4\n"
        "OUTPUT\n"
        "COPY FROM 5\n"
        "OUTPUT\n");
        break;
    case 4:
        strcpy(*program,
        "INPUT\n"
        "COPY TO 1\n"
        "INPUT\n"
        "OUTPUT\n"
        "COPY FROM 1\n"
        "OUTPUT\n"
        "JUMP 1\n");
        break;
    case 5:
        strcpy(*program,
        "INPUT\n"
        "COPY TO 1\n"
        "ADD 1\n"
        "COPY TO 1\n"
        "ADD 1\n"
        "COPY TO 1\n"
        "ADD 1\n"
        "OUTPUT\n"
        "JUMP 1\n");
        break;
    case 6:
        strcpy(*program,
        "INPUT\n"
        "COPY TO 1\n"
        "INPUT\n"
        "COPY TO 2\n"
        "COPY FROM 1\n"
        "SUB 2\n"
        "COPY TO 2\n"
        "ADD 2\n"
        "OUTPUT\n"
        "JUMP 1\n"
        );
        break;
    case 7:
        strcpy(*program,
        "INPUT\n"
        "JUMPZ 1\n"
        "OUTPUT\n"
        "JUMP 1\n"
        );
        break;
    case 8:
        strcpy(*program,
        "INPUT\n"
        "JUMPZ 4\n"
        "OUTPUT\n"
        "INPUT\n"
        "OUTPUT\n"
        "JUMP 1\n");
        break;
    case 9:
        strcpy(*program,
        "INPUT\n"
        "COPY TO 3\n"
        "COPY FROM 1\n"
        "COPY TO 2\n"
        "OUTPUT\n"
        "COPY FROM 2\n"
        "SUB 3\n"
        "JUMPZ 1\n"
        "COPY FROM 2\n"
        "ADD 1\n"
        "COPY TO 2\n"
        "OUTPUT\n"
        "JUMP 6\n");
        break;
    default:
        strcpy(*program, "\n");
        break;
    }
}