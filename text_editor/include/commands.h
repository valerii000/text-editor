#ifndef COMMANDS_H
#define COMMANDS_H

#include "globals.h"
#include "parser.h"
#include "consts.h"
#include "pre_commands.h"

std::string exec(const char* cmd);
void quitCommand();
void saveCommand();
void openCommand();
void cdCommand();
void pwdCommand();
void lsCommand();
void buffersCommand();
void bCommand();
void bdCommand();
void bdCurCommand();
void bufUpCommand();
void bufDownCommand();
void shellCommand();

#endif
