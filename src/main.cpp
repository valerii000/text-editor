#include "../include/globals.h"
#include "../include/commands.h"

std::map <std::string, Buffer> buffers;
Register registers[26];
Register clipboard;
std::map <std::string, Buffer>::iterator curbuf;
u32 c = 0;
u32 leader = ' ';
Keybind normal;
Keybind insert;
Keybind visual;
Keybind replace;
Keybind command;
Parser parser;
std::string command_str;

int main()
{
	// ncurses init
	/// {{{
	initscr();
	//mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	keypad(stdscr, TRUE);
	noecho();
	cbreak();
	raw();
	intrflush(stdscr, TRUE);
	notimeout(stdscr, TRUE);
	meta(stdscr, TRUE);
	start_color();
	init_color(COLOR_ORANGE, 1000, 500, 0);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_ORANGE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_GREEN, COLOR_BLACK);
	/// }}}

	buffers["0"] = Buffer();

	curbuf = buffers.begin();

	normal[{leader, 'q'}] = []() { endwin(); exit(0); };
	normal[{leader, leader}] = []() { mode = 4; };
	normal[{'h'}] = []() { curbuf->second.moveLeft(); };
	normal[{'j'}] = []() { curbuf->second.moveDown(); };
	normal[{'k'}] = []() { curbuf->second.moveUp(); };
	normal[{'l'}] = []() { curbuf->second.moveRight(); };
	normal[{'x'}] = []() { curbuf->second.deletech(); };
	normal[{':'}] = []() { mode = 4; };
	normal[{'i'}] = []() { curbuf->second.insertBefore(); };
	normal[{'a'}] = []() { curbuf->second.insertAfter(); };
	normal[{'I'}] = []() { curbuf->second.insertBegin(); };
	normal[{'A'}] = []() { curbuf->second.insertEnd(); };
	normal[{'0'}] = []() { curbuf->second.moveBegin(); };
	normal[{'$'}] = []() { curbuf->second.moveEnd(); };
	normal[{'d', 'd'}] = []() { curbuf->second.delline(); };
	normal[{'g', 'g'}] = []() { curbuf->second.moveBeginFile(); };
	normal[{'G'}] = []() { curbuf->second.moveEndFile(); };
	normal[{'K'}] = bufUpCommand;
	normal[{'J'}] = bufDownCommand;
	normal[{'q'}] = []() { if (curbuf->first == ":message:") bdCurCommand(); };

	insert[{'q'}] = []() { endwin(); exit(0); };
	insert[{27}] = []() { mode = 0; if (curbuf->second.x != 0) curbuf->second.x--; };
	insert[{'\n'}] = []() { curbuf->second.newline(); };
	insert[{KEY_BACKSPACE}] = []() { curbuf->second.ins_deletech(); };
	insert[{'\t'}] = []() { curbuf->second.insertch('\t'); };
	insert[{' '}] = []() { curbuf->second.insertch(' '); };

	command[{'q'}] = []() { endwin(); exit(0); };
	command[{21}] = []() { command_str.clear(); };
	command[{' '}] = []() { command_str += ' '; };
	command[{KEY_BACKSPACE}] = []() { if (!command_str.empty()) command_str.pop_back(); };

	// 33 - 127 for insert
	/// {{{
	insert[{33}] =  [](){ curbuf -> second.insertch(33); };
	insert[{34}] =  [](){ curbuf -> second.insertch(34); };
	insert[{35}] =  [](){ curbuf -> second.insertch(35); };
	insert[{36}] =  [](){ curbuf -> second.insertch(36); };
	insert[{37}] =  [](){ curbuf -> second.insertch(37); };
	insert[{38}] =  [](){ curbuf -> second.insertch(38); };
	insert[{39}] =  [](){ curbuf -> second.insertch(39); };
	insert[{40}] =  [](){ curbuf -> second.insertch(40); };
	insert[{41}] =  [](){ curbuf -> second.insertch(41); };
	insert[{42}] =  [](){ curbuf -> second.insertch(42); };
	insert[{43}] =  [](){ curbuf -> second.insertch(43); };
	insert[{44}] =  [](){ curbuf -> second.insertch(44); };
	insert[{45}] =  [](){ curbuf -> second.insertch(45); };
	insert[{46}] =  [](){ curbuf -> second.insertch(46); };
	insert[{47}] =  [](){ curbuf -> second.insertch(47); };
	insert[{48}] =  [](){ curbuf -> second.insertch(48); };
	insert[{49}] =  [](){ curbuf -> second.insertch(49); };
	insert[{50}] =  [](){ curbuf -> second.insertch(50); };
	insert[{51}] =  [](){ curbuf -> second.insertch(51); };
	insert[{52}] =  [](){ curbuf -> second.insertch(52); };
	insert[{53}] =  [](){ curbuf -> second.insertch(53); };
	insert[{54}] =  [](){ curbuf -> second.insertch(54); };
	insert[{55}] =  [](){ curbuf -> second.insertch(55); };
	insert[{56}] =  [](){ curbuf -> second.insertch(56); };
	insert[{57}] =  [](){ curbuf -> second.insertch(57); };
	insert[{58}] =  [](){ curbuf -> second.insertch(58); };
	insert[{59}] =  [](){ curbuf -> second.insertch(59); };
	insert[{60}] =  [](){ curbuf -> second.insertch(60); };
	insert[{61}] =  [](){ curbuf -> second.insertch(61); };
	insert[{62}] =  [](){ curbuf -> second.insertch(62); };
	insert[{63}] =  [](){ curbuf -> second.insertch(63); };
	insert[{64}] =  [](){ curbuf -> second.insertch(64); };
	insert[{65}] =  [](){ curbuf -> second.insertch(65); };
	insert[{66}] =  [](){ curbuf -> second.insertch(66); };
	insert[{67}] =  [](){ curbuf -> second.insertch(67); };
	insert[{68}] =  [](){ curbuf -> second.insertch(68); };
	insert[{69}] =  [](){ curbuf -> second.insertch(69); };
	insert[{70}] =  [](){ curbuf -> second.insertch(70); };
	insert[{71}] =  [](){ curbuf -> second.insertch(71); };
	insert[{72}] =  [](){ curbuf -> second.insertch(72); };
	insert[{73}] =  [](){ curbuf -> second.insertch(73); };
	insert[{74}] =  [](){ curbuf -> second.insertch(74); };
	insert[{75}] =  [](){ curbuf -> second.insertch(75); };
	insert[{76}] =  [](){ curbuf -> second.insertch(76); };
	insert[{77}] =  [](){ curbuf -> second.insertch(77); };
	insert[{78}] =  [](){ curbuf -> second.insertch(78); };
	insert[{79}] =  [](){ curbuf -> second.insertch(79); };
	insert[{80}] =  [](){ curbuf -> second.insertch(80); };
	insert[{81}] =  [](){ curbuf -> second.insertch(81); };
	insert[{82}] =  [](){ curbuf -> second.insertch(82); };
	insert[{83}] =  [](){ curbuf -> second.insertch(83); };
	insert[{84}] =  [](){ curbuf -> second.insertch(84); };
	insert[{85}] =  [](){ curbuf -> second.insertch(85); };
	insert[{86}] =  [](){ curbuf -> second.insertch(86); };
	insert[{87}] =  [](){ curbuf -> second.insertch(87); };
	insert[{88}] =  [](){ curbuf -> second.insertch(88); };
	insert[{89}] =  [](){ curbuf -> second.insertch(89); };
	insert[{90}] =  [](){ curbuf -> second.insertch(90); };
	insert[{91}] =  [](){ curbuf -> second.insertch(91); };
	insert[{92}] =  [](){ curbuf -> second.insertch(92); };
	insert[{93}] =  [](){ curbuf -> second.insertch(93); };
	insert[{94}] =  [](){ curbuf -> second.insertch(94); };
	insert[{95}] =  [](){ curbuf -> second.insertch(95); };
	insert[{96}] =  [](){ curbuf -> second.insertch(96); };
	insert[{97}] =  [](){ curbuf -> second.insertch(97); };
	insert[{98}] =  [](){ curbuf -> second.insertch(98); };
	insert[{99}] =  [](){ curbuf -> second.insertch(99); };
	insert[{100}] = [](){ curbuf -> second.insertch(100); };
	insert[{101}] = [](){ curbuf -> second.insertch(101); };
	insert[{102}] = [](){ curbuf -> second.insertch(102); };
	insert[{103}] = [](){ curbuf -> second.insertch(103); };
	insert[{104}] = [](){ curbuf -> second.insertch(104); };
	insert[{105}] = [](){ curbuf -> second.insertch(105); };
	insert[{106}] = [](){ curbuf -> second.insertch(106); };
	insert[{107}] = [](){ curbuf -> second.insertch(107); };
	insert[{108}] = [](){ curbuf -> second.insertch(108); };
	insert[{109}] = [](){ curbuf -> second.insertch(109); };
	insert[{110}] = [](){ curbuf -> second.insertch(110); };
	insert[{111}] = [](){ curbuf -> second.insertch(111); };
	insert[{112}] = [](){ curbuf -> second.insertch(112); };
	insert[{113}] = [](){ curbuf -> second.insertch(113); };
	insert[{114}] = [](){ curbuf -> second.insertch(114); };
	insert[{115}] = [](){ curbuf -> second.insertch(115); };
	insert[{116}] = [](){ curbuf -> second.insertch(116); };
	insert[{117}] = [](){ curbuf -> second.insertch(117); };
	insert[{118}] = [](){ curbuf -> second.insertch(118); };
	insert[{119}] = [](){ curbuf -> second.insertch(119); };
	insert[{120}] = [](){ curbuf -> second.insertch(120); };
	insert[{121}] = [](){ curbuf -> second.insertch(121); };
	insert[{122}] = [](){ curbuf -> second.insertch(122); };
	insert[{123}] = [](){ curbuf -> second.insertch(123); };
	insert[{124}] = [](){ curbuf -> second.insertch(124); };
	insert[{125}] = [](){ curbuf -> second.insertch(125); };
	insert[{126}] = [](){ curbuf -> second.insertch(126); };
	insert[{127}] = [](){ curbuf -> second.insertch(127); };
	/// }}}

	// 33 - 127 for command
	/// {{{
	command[{33}] =  [](){ command_str.push_back(33); };
	command[{34}] =  [](){ command_str.push_back(34); };
	command[{35}] =  [](){ command_str.push_back(35); };
	command[{36}] =  [](){ command_str.push_back(36); };
	command[{37}] =  [](){ command_str.push_back(37); };
	command[{38}] =  [](){ command_str.push_back(38); };
	command[{39}] =  [](){ command_str.push_back(39); };
	command[{40}] =  [](){ command_str.push_back(40); };
	command[{41}] =  [](){ command_str.push_back(41); };
	command[{42}] =  [](){ command_str.push_back(42); };
	command[{43}] =  [](){ command_str.push_back(43); };
	command[{44}] =  [](){ command_str.push_back(44); };
	command[{45}] =  [](){ command_str.push_back(45); };
	command[{46}] =  [](){ command_str.push_back(46); };
	command[{47}] =  [](){ command_str.push_back(47); };
	command[{48}] =  [](){ command_str.push_back(48); };
	command[{49}] =  [](){ command_str.push_back(49); };
	command[{50}] =  [](){ command_str.push_back(50); };
	command[{51}] =  [](){ command_str.push_back(51); };
	command[{52}] =  [](){ command_str.push_back(52); };
	command[{53}] =  [](){ command_str.push_back(53); };
	command[{54}] =  [](){ command_str.push_back(54); };
	command[{55}] =  [](){ command_str.push_back(55); };
	command[{56}] =  [](){ command_str.push_back(56); };
	command[{57}] =  [](){ command_str.push_back(57); };
	command[{58}] =  [](){ command_str.push_back(58); };
	command[{59}] =  [](){ command_str.push_back(59); };
	command[{60}] =  [](){ command_str.push_back(60); };
	command[{61}] =  [](){ command_str.push_back(61); };
	command[{62}] =  [](){ command_str.push_back(62); };
	command[{63}] =  [](){ command_str.push_back(63); };
	command[{64}] =  [](){ command_str.push_back(64); };
	command[{65}] =  [](){ command_str.push_back(65); };
	command[{66}] =  [](){ command_str.push_back(66); };
	command[{67}] =  [](){ command_str.push_back(67); };
	command[{68}] =  [](){ command_str.push_back(68); };
	command[{69}] =  [](){ command_str.push_back(69); };
	command[{70}] =  [](){ command_str.push_back(70); };
	command[{71}] =  [](){ command_str.push_back(71); };
	command[{72}] =  [](){ command_str.push_back(72); };
	command[{73}] =  [](){ command_str.push_back(73); };
	command[{74}] =  [](){ command_str.push_back(74); };
	command[{75}] =  [](){ command_str.push_back(75); };
	command[{76}] =  [](){ command_str.push_back(76); };
	command[{77}] =  [](){ command_str.push_back(77); };
	command[{78}] =  [](){ command_str.push_back(78); };
	command[{79}] =  [](){ command_str.push_back(79); };
	command[{80}] =  [](){ command_str.push_back(80); };
	command[{81}] =  [](){ command_str.push_back(81); };
	command[{82}] =  [](){ command_str.push_back(82); };
	command[{83}] =  [](){ command_str.push_back(83); };
	command[{84}] =  [](){ command_str.push_back(84); };
	command[{85}] =  [](){ command_str.push_back(85); };
	command[{86}] =  [](){ command_str.push_back(86); };
	command[{87}] =  [](){ command_str.push_back(87); };
	command[{88}] =  [](){ command_str.push_back(88); };
	command[{89}] =  [](){ command_str.push_back(89); };
	command[{90}] =  [](){ command_str.push_back(90); };
	command[{91}] =  [](){ command_str.push_back(91); };
	command[{92}] =  [](){ command_str.push_back(92); };
	command[{93}] =  [](){ command_str.push_back(93); };
	command[{94}] =  [](){ command_str.push_back(94); };
	command[{95}] =  [](){ command_str.push_back(95); };
	command[{96}] =  [](){ command_str.push_back(96); };
	command[{97}] =  [](){ command_str.push_back(97); };
	command[{98}] =  [](){ command_str.push_back(98); };
	command[{99}] =  [](){ command_str.push_back(99); };
	command[{100}] = [](){ command_str.push_back(100); };
	command[{101}] = [](){ command_str.push_back(101); };
	command[{102}] = [](){ command_str.push_back(102); };
	command[{103}] = [](){ command_str.push_back(103); };
	command[{104}] = [](){ command_str.push_back(104); };
	command[{105}] = [](){ command_str.push_back(105); };
	command[{106}] = [](){ command_str.push_back(106); };
	command[{107}] = [](){ command_str.push_back(107); };
	command[{108}] = [](){ command_str.push_back(108); };
	command[{109}] = [](){ command_str.push_back(109); };
	command[{110}] = [](){ command_str.push_back(110); };
	command[{111}] = [](){ command_str.push_back(111); };
	command[{112}] = [](){ command_str.push_back(112); };
	command[{113}] = [](){ command_str.push_back(113); };
	command[{114}] = [](){ command_str.push_back(114); };
	command[{115}] = [](){ command_str.push_back(115); };
	command[{116}] = [](){ command_str.push_back(116); };
	command[{117}] = [](){ command_str.push_back(117); };
	command[{118}] = [](){ command_str.push_back(118); };
	command[{119}] = [](){ command_str.push_back(119); };
	command[{120}] = [](){ command_str.push_back(120); };
	command[{121}] = [](){ command_str.push_back(121); };
	command[{122}] = [](){ command_str.push_back(122); };
	command[{123}] = [](){ command_str.push_back(123); };
	command[{124}] = [](){ command_str.push_back(124); };
	command[{125}] = [](){ command_str.push_back(125); };
	command[{126}] = [](){ command_str.push_back(126); };
	command[{127}] = [](){ command_str.push_back(127); };
	/// }}}          
                     
	parser.insert("q", quitCommand);
	parser.insert("w", saveCommand);
	parser.insert("e", openCommand);
	parser.insert("cd", cdCommand);
	parser.insert("pwd", pwdCommand);
	parser.insert("ls", lsCommand);
	parser.insert("b", bCommand);
	parser.insert("buffers", buffersCommand);
	parser.insert("bd", bdCommand);
	parser.insert("bd%", bdCurCommand);
	parser.insert("u", bufUpCommand);
	parser.insert("d", bufDownCommand);
	parser.insert("shell", shellCommand);
	parser.insert("!", shellCommand);
                    
	loop            
	{               
		curbuf -> second.render();
		if (mode != 4) c = getch();
		switch (mode)
		{       
		case 0: 
			normal(c);
			break;
		case 1: 
			insert(c);
			break;
		case 2: 
			visual(c);
			break;
		case 3: 
			replace(c);
			break;
		case 4: 
			while (c != '\n')
			{   
				mvaddch(LINES - 1, 0, '>');
				addch(' ');

				if ((i32) command_str.size() < COLS - 3)
				{
					addstr(command_str.c_str());
					//for (u16 i = command_str.size(); i < COLS - 3; ++i) addch(' ');
					clrtoeol();
					move(LINES - 1, command_str.size() + 2);
				}
				else addstr(command_str.substr(command_str.size() - COLS + 3, COLS - 3).c_str());

				if (c == 27)
				{
					command_str.clear();
					break;
				}

				refresh();
				c = getch();
				command(c);
			}
			parser.parse(command_str);
			command_str.clear();
			mvaddch(LINES - 1, 0, ' ');
			//for (u16 i = 1; i < COLS; ++i) addch(' ');
			clrtoeol();
			mode = 0;
			break;
		default:
			break;
		}
	}

	endwin();
	return 1;
}

