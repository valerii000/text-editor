#ifndef REGISTER_H
#define REGISTER_H

#include "buffer.h"

/// !!! does not work yet !!!

struct Register
{
	std::vector <std::string> content;
	void copy(Buffer& copyfrom, unsigned startL, unsigned endL)
	{
		content.clear();
		for (; startL <= endL; ++startL)
		{
			content.push_back(copyfrom.content[startL]); // Access content of buffer
		}
	}
	void paste(Buffer& pasteTo)
	{
		for (const let& line : content)
		{
			pasteTo.content.insert(pasteTo.content.begin() + pasteTo.y, line);
			pasteTo.y++;
		}
	}
};

#endif
