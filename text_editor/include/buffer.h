#ifndef BUFFER_H
#define BUFFER_H

#include "defines.h"
#include "consts.h"
#include "keybind.h"

extern u8 mode;

class Buffer
{
public:
	std::vector <std::string> content;
	std::string path;
	i32 x, y, topy, topx;

	Buffer();
	Buffer(const std::vector <std::string>& cont);

    void render();
    void insertch(char c);
    void deletech();
    void movecursor(u32 dy, u32 dx);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

	void moveBegin();
	void moveEnd();

	void moveBeginFile();
	void moveEndFile();

	void ins_deletech();
	void insertBefore();
	void insertAfter();
	void insertBegin();
	void insertEnd();
	void newline();
	void delline();
	void insert(const std::string& s);

    void command();
};

bool operator<(const Buffer& lhs, const Buffer& rhs);

#endif
