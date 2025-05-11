#ifndef PARSER_H
#define PARSER_H

#include "defines.h"
#include "consts.h"

class Parser
{
public:
	Parser();

	void insert(const std::string& commandName, void (*action)());

	void parse(const std::string& input);

	/// kinda private
	std::vector <std::string> splitInput(const std::string& input);

	std::vector <std::string> args;
	std::unordered_map <std::string, void (*)()> commandMap;
};

#endif	
