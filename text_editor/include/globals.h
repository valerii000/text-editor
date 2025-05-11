#ifndef GLOBALS_H
#define GLOBALS_H

#include "buffer.h"
#include "register.h"
#include "keybind.h"
#include "parser.h"

extern std::map <std::string, Buffer> buffers;
extern Register registers[26];
extern Register clipboard;
extern std::map <std::string, Buffer>::iterator curbuf;
extern u16 c;
extern Keybind normal;
extern Keybind insert;
extern Keybind visual;
extern Keybind replace;
extern Keybind command;
extern Parser parser;
extern std::string command_string;
extern u8 mode;
/*
	0 - normal
	1 - insert
	2 - visual
	3 - replace
	4 - command
*/


#endif  // GLOBALS_H
