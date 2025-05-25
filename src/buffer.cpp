#include "../include/buffer.h"

u8 mode;

Buffer::Buffer()
{
	content = {""};
	path = "";
	x = 0;
	y = 0;
	topy = 0;
	topx = 0;
}

Buffer::Buffer(const std::vector <std::string>& cont)
{
	for (const let& line : cont) content.push_back(line);
	path = "";
	x = 0;
	y = 0;
	topy = 0;
	topx = 0;
}

void Buffer::render()
{
	if (topy > y) topy = y;
	else if (topy + LINES - 3 < y) topy = y - (LINES - 3);

	if (topx > x) topx = x;
	else if (topx + COLS - 3 < x) topx = x - (COLS - 3);

	for (u16 i = 0; i < LINES - 2; ++i)
	{
		u16 lineIndex = topy + i;
		if (lineIndex >= content.size())
		{
			mvaddch(i, 0, '~');
			//for (u16 j = 1; j < COLS; ++j) addch(' ');
			clrtoeol();
		}
		else
		{
			std::string line = content[lineIndex];
			u32 start = std::min((u32)topx, (u32)line.size());
			u32 end = std::min((u32) topx + COLS, (u32) line.size());

			if (start > 0)
			{
				attron(COLOR_PAIR(5));
				mvaddch(i, 0, '<');
				attroff(COLOR_PAIR(5));
			}
			else mvaddch(i, 0, ' ');

			if (start < line.length() && end > start && (u32) end - start <= (u32) line.length())
				mvaddstr(i, 1, line.substr(start, end - start).c_str());

			//for (u16 j = 1 + (end - start); j < COLS - 1; ++j) addch(' ');
			clrtoeol();

			if (line.size() > (u32) topx + COLS - 2)
			{
				attron(COLOR_PAIR(5));
				mvaddch(i, COLS - 1, '>');
				attroff(COLOR_PAIR(5));
			}
			else mvaddch(i, COLS - 1, ' ');

		}
	}

	std::string pos = std::to_string(y) + ":" + std::to_string(x);
	std::string info;
	if (path == "") info = "[scratch]";
	else info = path;
	mvaddstr(LINES - 2, 0, info.c_str());
	//for (u16 j = info.size(); j < COLS - pos.length(); ++j) addch(' ');
	clrtoeol();
	mvaddstr(LINES - 2, COLS - pos.length() - 1, pos.c_str());

	move(y - topy, x - topx + 1);
	refresh();
}

void Buffer::insertch(char c)
{
	if (x < (i32) content[y].size())
		content[y].insert(x, 1, c);
	else
		content[y].push_back(c);
	++x;
}

void Buffer::deletech()
{
	if (content[y].size() == 0) return;
	if (content[y].size() == 1)
	{
		content[y].clear();
		return;
	}
	content[y].erase(x, 1);
	if (x == (i32) content[y].size()) x--;
}

void Buffer::ins_deletech()
{
	if (content[y].size() == 0) return;
	if (x == 0)
	{
		if (y == 0) return;
		content[y - 1] += content[y];
		content.erase(content.begin() + y);
		y--;
		x = content[y].size() - 1;
		return;
	}
	content[y].erase(x - 1, 1);
	x--;
}

void Buffer::movecursor(u32 dy, u32 dx)
{
	y += dy;
	x += dx;
	if (y < 0) y = 0;
	if (x < 0) x = 0;
	if (y >= (i32) content.size()) y = content.size() - 1;
	if (x >= (i32) content[y].size()) x = content[y].size();
}

void Buffer::moveLeft()
{
	if (x != 0) --x;
}

void Buffer::moveDown()
{
	if (y != (i32) content.size() - 1)
	{
		++y;
		if (x > (i32) content[y].size() - 1)
		{

			if (content[y].size() == 0) x = 0;
			else x = content[y].size() - 1;
		}
	}
}

void Buffer::moveUp()
{
	if (y != 0)
	{
		y--;
		if (x > (i32) content[y].size() - 1)
		{
			if (content[y].size() == 0) x = 0;
			else x = content[y].size() - 1;
		}
	}
}

void Buffer::moveRight()
{
	if (x < (i32) content[y].size() - 1) x++;
}

void Buffer::moveBegin()
{
	x = 0;
}

void Buffer::moveEnd()
{
	if (content[y].size() != 0) x = content[y].size() - 1;
}

void Buffer::moveBeginFile()
{
	y = 0;
	if ((u32) x > (u32) content[y].size())
	{
		if (content[y].size() == 0) x = 0;
		else x = content[y].size() - 1;

	}
}

void Buffer::moveEndFile()
{
	y = content.size() - 1;
	if ((u32) x > (u32) content[y].size()) x = content[y].size() - 1;
}

void Buffer::insertBefore()
{
	mode = 1;
	if (x != 0) x--;
}

void Buffer::insertAfter()
{
	mode = 1;
	if (content[y].size() != 0) ++x;
	if ((x != (i32) content[y].size() - 1) || (content[y].size() != 0)) return;
	++x;
}

void Buffer::insertBegin()
{
	x = 0;
	mode = 1;
}

void Buffer::insertEnd()
{
	if (content[y].size() == 0) mode = 1;
	else 
	{
		x = content[y].size() - 1;
		mode = 1;
		++x;
	}
}

void Buffer::newline()
{
	if (x == (i32) content[y].size())
		content.insert(content.begin() + y + 1, "");

	else
	{
		std::string s = content[y].substr(x);
		content[y].erase(x);
		content.insert(content.begin() + y + 1, s);
	}
	y++;
	x = 0;
}

void Buffer::delline()
{
	if (y != 0 || content.size() != 1)
	{
		content.erase(content.begin() + y);
		if (y == (i32) content.size()) y--;
		x = std::min(x, (int)content[y].size());
	}
	else if (content[y].size() > 0)
	{
		content[y].clear();
		x = 0;
	}
}

void Buffer::command()
{
	mode = 4;
}

void Buffer::insert(const std::string& s)
{
	if (content.empty()) content.push_back("");
	for (const let& ch : s)
	{
		if (ch == '\n') content.push_back("");
		else if (ch == '\t') content.back() += "    ";
		else content.back() += ch;
	}
}

