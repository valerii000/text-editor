#include "../include/parser.h"

Parser::Parser() {}

void Parser::insert(const std::string& commandName, void (*action)())
{
	commandMap[commandName] = action;
}

void Parser::parse(const std::string& input)
{
	args = splitInput(input);

	if (args.empty()) return;

	std::string commandName = args[0];

	auto it = commandMap.find(commandName);
	if (it != commandMap.end())
	{
		// Execute the command action
		it -> second();
	}
	else
	{
		message("command does not exist");
	}
}

std::vector <std::string> Parser::splitInput(const std::string& input)
{
	std::vector<std::string> words;
	std::string word;
	for (char c : input)
	{
		if (c == ' ')
		{
			if (!word.empty())
			{
				words.push_back(word);
				word.clear();
			}
		}
		else
		{
			word += c;
		}
	}
	if (!word.empty())
	{
		words.push_back(word);
	}
	return words;
}

