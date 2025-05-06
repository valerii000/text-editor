#ifndef KEYBIND_H
#define KEYBIND_H

#include "defines.h"

typedef void (*FuncPtr)();

struct TrieNode
{
	std::unordered_map <u16, TrieNode*> children;
	FuncPtr func;

	TrieNode() : func(nullptr) {}
	~TrieNode();
};

class Keybind
{
private:
	TrieNode* root;
	TrieNode* current;

public:
	Keybind();
	~Keybind();

	void insert(const std::vector<u16>& Keybinding, FuncPtr func);
	void exec(u16 key);
};

#endif
