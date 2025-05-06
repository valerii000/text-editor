#include "../include/keybind.h"

TrieNode::~TrieNode()
{
	for (auto& child : children) delete child.second;
}

Keybind::Keybind() : root(new TrieNode()), current(root) {}

Keybind::~Keybind()
{
	delete root;
}

void Keybind::insert(const std::vector<u16>& Keybinding, FuncPtr func)
{
	TrieNode* node = root;
	for (u16 c : Keybinding)
	{
		auto it = node->children.find(c);
		if (it == node->children.end())
		{
			node->children[c] = new TrieNode();
			node = node->children[c];
		}
		else node = it->second;
	}
	node->func = func;
}

void Keybind::exec(u16 key)
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
