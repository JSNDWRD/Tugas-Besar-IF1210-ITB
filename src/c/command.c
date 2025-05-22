#include "../header/command.h"

void CreateCommandList(CommandList *commandList, const char *COMMAND_READY[]){
    for(int i = 0; i < COMMAND_CAPACITY; i++){
        strcpy(commandList->command[i].name, COMMAND_READY[i]);
        commandList->command[i].key = i+1;
    }
}