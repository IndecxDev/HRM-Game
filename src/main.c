#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/settings.h"
#include "../include/console_commands.h"
#include "../include/save_load.h"

void getUserInput(char *input) {
    printf(">> ");
    if (fgets(input, MAX_INPUT_LEN, stdin) != NULL) {
        // Remove the trailing newline character, if present
        input[strcspn(input, "\n")] = '\0';
    }
}

int main() {
    srand(time(nullptr)); // Random number initialization

    Level *levels = (Level*) malloc(sizeof(*levels) * MAX_LEVELS);
    loadData(levels);

    int currentLevel = 0;
    char input[MAX_INPUT_LEN];

    while (true) {
        getUserInput(input);
        bool running = handleCommand(input, levels, &currentLevel);
        if (!running) break;
    }
    free(levels);
    return EXIT_SUCCESS;
}