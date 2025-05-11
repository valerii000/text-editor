#include "../include/keybind.h"

TrieNode::~TrieNode()
{
	for (let& child : children) delete child.second;
}

Keybind::Keybind() : root(new TrieNode()), current(root) {}

Keybind::~Keybind()
{
	delete root;
}

Keybind& Keybind::operator[](const std::initializer_list <u16>& keys)
{
	TrieNode* node = root;
	for (const let& c : keys)
	{
		let it = node->children.find(c);
		if (it == node->children.end())
		{
			node->children[c] = new TrieNode();
			node = node->children[c];
		}
		else node = it->second;
	}
	current = node;
	return *this;
}

/*
void Keybind::operator() (u16 key)
{
	let it = current->children.find(key);
	if (it != current->children.end())
	{
		current = it->second;
		if (current->func != nullptr)
		{
			current->func();
			current = root;
		}
	}
	else current = root;
}
*/

void Keybind::operator()(u16 key)
{
	let it = current->children.find(key);
	if (it != current->children.end())
	{
		current = it->second;
		if (current->func != nullptr)
		{
			current->func();
			current = root;
		}
	}
	else
	{
		current = root;
		let it = current->children.find(key);
		if (it != current->children.end())
		{
			current = it->second;
			if (current->func != nullptr)
			{
				current->func();
				current = root;
			}
		}
	}
}

Keybind& Keybind::operator=(FuncPtr func)
{
	current->func = func;
	current = root;
	return *this;
}

