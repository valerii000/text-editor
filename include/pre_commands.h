#ifndef PRE_COMMANDS_H
#define PRE_COMMANDS_H

#include "globals.h"
#include "parser.h"
#include "consts.h"

inline void message_big(const std::string& s)
{
	buffers[":message:"] = Buffer();

	curbuf = buffers.find(":message:");

	curbuf -> second.insert(s);
}

#endif
