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

	Keybind& operator[](const std::initializer_list<u16>& keys);
	void operator()(u16 key);

	Keybind& operator=(FuncPtr func);
};

#endif

