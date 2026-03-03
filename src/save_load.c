#include <stdio.h>
#include <string.h>

#include "../include/settings.h"

typedef enum {
    LOADING_NAME,
    LOADING_FLUFF,
    LOADING_DESCRIPTION,
    LOADING_INPUT_DESC,
    LOADING_OUTPUT_DESC
} LoadingStage;

void setLevelData(Level *levels) {

    // Level 1
    levels[0].id = 1;
    strcpy(levels[0].name, "Baby Steps");

    strcpy(levels[0].fluff, "Hello and welcome!\n");
    strcat(levels[0].fluff, "If you're seeing this, it means you already know how to navigate the console, which is great but that won't get you far.\n");
    strcat(levels[0].fluff, "To solve the tasks ahead of us, we'll need some better tools!\n");
    strcat(levels[0].fluff, "Unfortunately for you, we don't use COBOL like [INSERT BANK NAME HERE], we use our own proprietary language called NeoCOBOL which you will be learning and using during your lovely time here.\n");
    strcat(levels[0].fluff, "To get you started with how the basic commands work, imagine a conveyor belt where the input numbers come in, and a different conveyor belt where output numbers go.\n");
    strcat(levels[0].fluff, "You have an intermediary \"register\" where you can hold one number at a time. OUTPUTting a number will also remove that number from your register.\n");

    strcpy(levels[0].description, "So let's start with something simple. Use the \033[1;37mINPUT\033[0m and \033[1;37mOUTPUT\033[0m commands to take the numbers in the input and output them back.\n");
    strcat(levels[0].description, "INPUT will take a number from the input and replace anything you have in your register.\n");
    strcat(levels[0].description, "OUTPUT will take anything you have in your register and try to output it.\n");

    strcpy(levels[0].inputOutput, "\033[0;36mInput range: \033[1;36m<-10,10>\033[0m\n");
    strcat(levels[0].inputOutput, "\033[0;36mInput count:\033[1;36m 3\033[0m\n");
    strcat(levels[0].inputOutput, "\033[0;36mExample input: \033[1;36m[9, 3, -1]\033[0m\n");
    strcat(levels[0].inputOutput, "\033[0;36mExample output: \033[1;36m[9, 3, -1]\033[0m\n");

    strcpy(levels[0].notes, "If you have trouble with the syntax, feel free to use our documentation with the \033[1;33mDOCS\033[0m command.\n");
    strcat(levels[0].notes, "Please write all of your NeoCOBOL code in the file \"lvl1.ncob\" and then use the \033[1;33mRUN\033[0m command to run it when you're done.\n");

    levels[0].memorySize = 0;

    // Level 2
    levels[1].id = 2;
    strcpy(levels[1].name, "On Repeat");

    strcpy(levels[1].fluff,"Well done on your first job!\n");
    strcat(levels[1].fluff,"That wasn't that hard, was it? It was maybe a bit tiresome to write those lines three times. But what if we don't know how many times we need to write it?\n");
    strcat(levels[1].fluff,"But thankfully, NeoCOBOL has the right tool for that! Use the \033[1;37mJUMP\033[0m instruction to jump back to any other line.\n");
    
    strcpy(levels[1].description, "\033[1;37mTask:\033[0m Take the numbers on the input and output them back.\n");
    strcat(levels[1].description, "The difference is this time we don't know how many inputs there are. \n");
    strcat(levels[1].description, "Remember, the program will automatically stop once all expected outputs are accepted.\n");

    strcpy(levels[1].inputOutput, "\033[0;36mInput range: \033[1;36m<-10,10>\033[0m\n");
    strcat(levels[1].inputOutput, "\033[0;36mInput count: \033[1;36m<5,10>\033[0m\n");
    strcat(levels[1].inputOutput, "\033[0;36mExample input: \033[1;36m[8, 2, -5, -2, 0]\033[0m\n");
    strcat(levels[1].inputOutput, "\033[0;36mExample output: \033[1;36m[8, 2, -5, -2, 0]\033[0m\n");

    strcpy(levels[1].notes, "If you have trouble with the syntax, feel free to use our documentation with the \033[1;33mDOCS\033[0m command.\n");
    strcat(levels[1].notes, "Please write all of your NeoCOBOL code in the file \"lvl2.ncob\" and then use the \033[1;33mRUN\033[0m command to run it when you're done.\n");

    levels[1].memorySize = 0;

    // Level 3
    levels[2].id = 3;
    strcpy(levels[2].name, "Pi");

    strcpy(levels[2].fluff,"For your next task, we need to introduce a major feature of NeoCOBOL:\n");
    strcat(levels[2].fluff,"\033[1;37mMemory!\033[0m\n");
    strcat(levels[2].fluff,"Without it, we wouldn't really be able to do any complex tasks. Details of each task's memory will be below.\n");
    strcat(levels[2].fluff,"This time, there are some specific values already saved there.\n");
    strcat(levels[2].fluff,"For manipulating memory, NeoCOBOL has two instructions - \033[1;37mCOPY FROM\033[0m and \033[1;37mCOPY TO\033[0m.\n");
    strcat(levels[2].fluff,"Though only the COPY FROM instruction is needed here.\n");

    strcpy(levels[2].description, "\033[1;37mTask:\033[0m Output exactly the values in the example output.\n");

    strcpy(levels[2].inputOutput, "\033[0;36mInput range: \033[1;36m<-50,0>\033[0m\n");
    strcat(levels[2].inputOutput, "\033[0;36mInput count: \033[1;36m3\033[0m\n");
    strcat(levels[2].inputOutput, "\033[0;36mExample input: \033[1;36m[-24, -17, -50]\033[0m\n");
    strcat(levels[2].inputOutput, "\033[0;36mExample output: \033[1;36m [3, 1, 4, 1, 5, 9]\033[0m\n");
    strcat(levels[2].inputOutput, "\033[0;36mMemory: \033[1;36m[1, 3, 4, 5, 9]\033[0m\n");

    strcpy(levels[2].notes, "If you have trouble with the syntax, feel free to use our documentation with the \033[1;33mDOCS\033[0m command.\n");
    strcat(levels[2].notes, "Please write all of your NeoCOBOL code in the file \"lvl3.ncob\" and then use the \033[1;33mRUN\033[0m command to run it when you're done.\n");

    levels[2].memorySize = 5;

    // Level 4
    levels[3].id = 4;
    strcpy(levels[3].name, "Swap");

    strcpy(levels[3].fluff,"In this task, you will need to use the COPY TO instruction.\n");
    strcat(levels[3].fluff,"Here, the memory only has room for two numbers so use it wisely.\n");
    strcat(levels[3].fluff,"At this point, it might be useful to run a program using the \033[1;33mDEBUG\033[0m command to figure out where your mistakes might be.\n");

    strcpy(levels[3].description, "\033[1;37mTask:\033[0m Take each pair of numbers from the input and output them in the \033[0;37mreverse\033[0m order.\n");

    strcpy(levels[3].inputOutput, "\033[0;36mInput range: \033[1;36m<-10,10>\033[0m\n");
    strcat(levels[3].inputOutput, "\033[0;36mInput count: \033[1;36m10\033[0m\n");
    strcat(levels[3].inputOutput, "\033[0;36mExample input: \033[1;36m[3, 2, -1, 4]\033[0m\n");
    strcat(levels[3].inputOutput, "\033[0;36mExample output: \033[1;36m[2, 3, 4, -1]\033[0m\n");
    strcat(levels[3].inputOutput, "\033[0;36mMemory: \033[1;36m[0, 0]\033[0m\n");

    strcpy(levels[3].notes, "If you have trouble with the syntax, feel free to use our documentation with the \033[1;33mDOCS\033[0m command.\n");
    strcat(levels[3].notes, "Please write all of your NeoCOBOL code in the file \"lvl4.ncob\" and then use the \033[1;33mRUN\033[0m or \033[1;33mDEBUG\033[0m commands to run it when you're done.\n");

    levels[3].memorySize = 2;

    // Level 5
    levels[4].id = 5;
    strcpy(levels[4].name, "Multiplication");

    strcpy(levels[4].fluff,"We will start doing some math now.\n");
    strcat(levels[4].fluff,"But for that, we need yet another nice instruction - \033[1;33mADD\033[0m which adds a value in memory to your register.\n");
    strcat(levels[4].fluff,"Keep an eye out for the optional challenges too.\n");

    strcpy(levels[4].description, "\033[1;37mTask:\033[0m Take each number in the input and multiply it by 8.\n");

    strcpy(levels[4].inputOutput, "\033[0;36mInput range: \033[1;36m<-10,10>\033[0m\n");
    strcat(levels[4].inputOutput, "\033[0;36mInput count: \033[1;36m<5,10>\033[0m\n");
    strcat(levels[4].inputOutput, "\033[0;36mExample input: \033[1;36m[3, 2, -1, 4]\033[0m\n");
    strcat(levels[4].inputOutput, "\033[0;36mExample output: \033[1;36m[24, 16, -8, 32]\033[0m\n");
    strcat(levels[4].inputOutput, "\033[0;36mMemory: \033[1;36m[0, 0, 0, 0]\033[0m\n");

    strcpy(levels[4].notes, "If you have trouble with the syntax, feel free to use our documentation with the \033[1;33mDOCS\033[0m command.\n");
    strcat(levels[4].notes, "Please write all of your NeoCOBOL code in the file \"lvl5.ncob\" and then use the \033[1;33mRUN\033[0m or \033[1;33mDEBUG\033[0m commands to run it when you're done.\n");

    levels[4].memorySize = 4;

    // Level 6
    levels[5].id = 6;
    strcpy(levels[5].name, "Double Negative");

    strcpy(levels[5].fluff,"To continue our math play, adding obviously isn't enough.\n");
    strcat(levels[5].fluff,"The instruction \033[1;33mSUB\033[0m which subtracts a value in memory from your register will come in handy for this next task.\n");

    strcpy(levels[5].description, "\033[1;37mTask:\033[0m Take two numbers in the input and double their difference.\n");

    strcpy(levels[5].inputOutput, "\033[0;36mInput range: \033[1;36m<-20,20>\033[0m\n");
    strcat(levels[5].inputOutput, "\033[0;36mInput count: \033[1;36m<6,16>\033[0m\n");
    strcat(levels[5].inputOutput, "\033[0;36mExample input: \033[1;36m[3, 2, -1, 4, 3, 7]\033[0m\n");
    strcat(levels[5].inputOutput, "\033[0;36mExample output: \033[1;36m[2, -10, -8]\033[0m\n");
    strcat(levels[5].inputOutput, "\033[0;36mMemory: \033[1;36m[0, 0]\033[0m\n");

    strcpy(levels[5].notes, "If you have trouble with the syntax, feel free to use our documentation with the \033[1;33mDOCS\033[0m command.\n");
    strcat(levels[5].notes, "Please write all of your NeoCOBOL code in the file \"lvl6.ncob\" and then use the \033[1;33mRUN\033[0m or \033[1;33mDEBUG\033[0m commands to run it when you're done.\n");

    levels[5].memorySize = 2;

    // Level 7
    levels[6].id = 7;
    strcpy(levels[6].name, "Zero Filter");

    strcpy(levels[6].fluff,"Welcome to the second branch of the basic instruction set.\n");
    strcat(levels[6].fluff,"Thematically, we'll be introducing a branching function.\n");
    strcat(levels[6].fluff,"We already have a JUMP instruction, but that jumps every time. For this task, we will need the \033[1;33mJUMPZ\033[0m instruction.\n");
    strcat(levels[6].fluff,"JUMPZ jumps to the line specified only if there is a zero in the register.\n");

    strcpy(levels[6].description, "\033[1;37mTask:\033[0m Output only non-zero numbers from the input.\n");

    strcpy(levels[6].inputOutput, "\033[0;36mInput range: \033[1;36m<-20,20>\033[0m\n");
    strcat(levels[6].inputOutput, "\033[0;36mInput count: \033[1;36m<5,10>\033[0m\n");
    strcat(levels[6].inputOutput, "\033[0;36mExample input: \033[1;36m[5, 6, 0, 0, -1, 2, 0, -3]\033[0m\n");
    strcat(levels[6].inputOutput, "\033[0;36mExample output: \033[1;36m[5, 6, -1, 2, -3]\033[0m\n");
    strcat(levels[6].inputOutput, "\033[0;36mMemory: \033[1;36m[0, 0]\033[0m\n");

    strcpy(levels[6].notes, "If you have trouble with the syntax, feel free to use our documentation with the \033[1;33mDOCS\033[0m command.\n");
    strcat(levels[6].notes, "Please write all of your NeoCOBOL code in the file \"lvl7.ncob\" and then use the \033[1;33mRUN\033[0m or \033[1;33mDEBUG\033[0m commands to run it when you're done.\n");

    levels[6].memorySize = 2;

    // Level 8
    levels[7].id = 8;
    strcpy(levels[7].name, "Segmented Numbers");

    strcpy(levels[7].fluff,"This task might be a little more complicated to understand so pay attention.\n");
    strcat(levels[7].fluff,"It doesn't require any new instructions, just clever uses of JUMP and JUMPZ instructions and good code structure.\n");
    strcat(levels[7].fluff,"The numbers on the input come in two-number pairs, representing a number from 0-99.\n");
    strcat(levels[7].fluff,"\033[0;36mAll numbers are split into their digits and single digit numbers are written with a leading zero\033[0m, eg. 7 is written in the input as [0, 7] and 10 is written as [1, 0].\n");
    strcat(levels[7].fluff,"Your goal is to find the single digit numbers and strip them of their leading zero. Be careful of numbers like 10 or 20 though!\n");
    strcat(levels[7].fluff,"\033[0;33mNote: The number 0 is written like [0, 0] and needs to output only a single zero.\033[0m\n");

    strcpy(levels[7].description, "\033[1;37mTask:\033[0m Output everything except the leading zeros in single digit numbers.\n");

    strcpy(levels[7].inputOutput, "\033[0;36mInput range: \033[1;36m<-9,9>\033[0m\n");
    strcat(levels[7].inputOutput, "\033[0;36mInput count: \033[1;36m<10,20>\033[0m\n");
    strcat(levels[7].inputOutput, "\033[0;36mExample input: \033[1;36m[0, 7, 1, 0, 0, 2, 1, 6, 3, 9, 3, 0]\033[0m\n");
    strcat(levels[7].inputOutput, "\033[0;36mExample output: \033[1;36m[7, 1, 0, 2, 1, 6, 3, 9, 3, 0]\033[0m\n");
    strcat(levels[7].inputOutput, "\033[0;36mMemory: \033[1;36m[0, 0]\033[0m\n");

    strcpy(levels[7].notes, "If you have trouble with the syntax, feel free to use our documentation with the \033[1;33mDOCS\033[0m command.\n");
    strcat(levels[7].notes, "Please write all of your NeoCOBOL code in the file \"lvl8.ncob\" and then use the \033[1;33mRUN\033[0m or \033[1;33mDEBUG\033[0m commands to run it when you're done.\n");

    levels[7].memorySize = 2;

    // Level 9
    levels[8].id = 9;
    strcpy(levels[8].name, "For Loop");

    strcpy(levels[8].fluff,"Now let's pull both branches together with something more advanced.\n");
    strcat(levels[8].fluff,"This task will require the use of instructions from both branches.\n");

    strcpy(levels[8].description, "\033[1;37mTask:\033[0m Output all the numbers from 1 to N where N is each input given.\n");

    strcpy(levels[8].inputOutput, "\033[0;36mInput range: \033[1;36m<1,9>\033[0m\n");
    strcat(levels[8].inputOutput, "\033[0;36mInput count: \033[1;36m<3,5>\033[0m\n");
    strcat(levels[8].inputOutput, "\033[0;36mExample input: \033[1;36m[2, 4, 5]\033[0m\n");
    strcat(levels[8].inputOutput, "\033[0;36mExample output: \033[1;36m[1, 2, 1, 2, 3, 4, 1, 2, 3, 4, 5]\033[0m\n");
    strcat(levels[8].inputOutput, "\033[0;36mMemory: \033[1;36m[1, 0, 0]\033[0m\n");

    strcpy(levels[8].notes, "If you have trouble with the syntax, feel free to use our documentation with the \033[1;33mDOCS\033[0m command.\n");
    strcat(levels[8].notes, "Please write all of your NeoCOBOL code in the file \"lvl9.ncob\" and then use the \033[1;33mRUN\033[0m or \033[1;33mDEBUG\033[0m commands to run it when you're done.\n");

    levels[8].memorySize = 3;
}

void saveData(const Level *levels) {
    FILE *saveFile;
    saveFile = fopen("save.dat", "w");

    for (int i = 0; i < MAX_LEVELS; i++) {
        fprintf(saveFile, "%d: {%d, %d}, {%d, %d}\n", 
            levels[i].id, 
            levels[i].unlocked, 
            levels[i].completed,
            levels[i].score.fastProgram, 
            levels[i].score.shortProgram);
    }
    fclose(saveFile);
}

void loadData(Level *levels) {
    setLevelData(levels);
    
    FILE *saveFile;
    saveFile = fopen("save.dat", "r");

    if (saveFile == nullptr) {
        printf("No save file, writing default data...\n");

        levels[0].id = 1;
        levels[0].unlocked = true;
        levels[0].completed = false;
        levels[0].score.fastProgram = false;
        levels[0].score.shortProgram = false;
        
        for (int i = 1; i < MAX_LEVELS; i++) {
            levels[i].id = i+1;
            levels[i].unlocked = false;
            levels[i].completed = false;
            levels[i].score.fastProgram = false;
            levels[i].score.shortProgram = false;
        }

        saveData(levels);
        return;
    }
    
    char line[64];
    int loadingLevel = 0;
    while (fgets(line, 64, saveFile)) {
        int unlocked, completed, fastProgram, shortProgram;
        sscanf(line, "%d: {%d, %d}, {%d, %d}", 
            &(levels[loadingLevel].id), 
            &unlocked,
            &completed,
            &fastProgram,  
            &shortProgram);
        levels[loadingLevel].unlocked = (bool)unlocked;
        levels[loadingLevel].completed = (bool)completed;
        levels[loadingLevel].score.fastProgram = (bool)fastProgram;
        levels[loadingLevel].score.shortProgram = (bool)shortProgram;

        loadingLevel++;
    }

    fclose(saveFile);
}