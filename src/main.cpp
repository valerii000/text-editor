#include "../include/globals.h"
#include "../include/commands.h"

std::map <std::string, Buffer> buffers;
Register registers[26];
Register clipboard;
std::map <std::string, Buffer>::iterator curbuf;
u16 c = 0;
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

	// 0 - ctrl+space
	normal.insert({0, 'q'}, [](){ endwin(); exit(0); });
	normal.insert({'h'}, [](){ curbuf -> second.moveLeft(); });
	normal.insert({'j'}, [](){ curbuf -> second.moveDown(); });
	normal.insert({'k'}, [](){ curbuf -> second.moveUp(); });
	normal.insert({'l'}, [](){ curbuf -> second.moveRight(); });
	normal.insert({'x'}, [](){ curbuf -> second.deletech(); });
	normal.insert({':'}, [](){ mode = 4; });
	normal.insert({'i'}, [](){ curbuf -> second.insertBefore(); });
	normal.insert({'a'}, [](){ curbuf -> second.insertAfter(); curbuf -> second.x++; });
	normal.insert({'I'}, [](){ curbuf -> second.insertBegin(); });
	normal.insert({'A'}, [](){ curbuf -> second.insertEnd(); curbuf -> second.x++; });
	normal.insert({'0'}, [](){ curbuf -> second.moveBegin(); });
	normal.insert({'$'}, [](){ curbuf -> second.moveEnd(); });
	normal.insert({'d', 'd'}, [](){ curbuf -> second.delline(); });
	normal.insert({'g', 'g'}, [](){ curbuf -> second.moveBeginFile(); });
	normal.insert({'G'}, [](){ curbuf -> second.moveEndFile(); });
	normal.insert({'K'}, bufUpCommand);
	normal.insert({'J'}, bufDownCommand);
	normal.insert({'q'}, [](){ if (curbuf -> first == ":message:") bdCurCommand(); });

	insert.insert({27}, [](){ mode = 0; if (curbuf -> second.x != 0) curbuf -> second.x--; });
	insert.insert({'\n'}, [](){ curbuf -> second.newline(); });
	insert.insert({KEY_BACKSPACE}, [](){ curbuf -> second.ins_deletech(); });
	insert.insert({'\t'}, [](){ curbuf -> second.insertch('\t'); });
	insert.insert({' '},	[](){ curbuf -> second.insertch(' '); });

	// 33 - 127 for insert
	/// {{{
	insert.insert({33},  [](){ curbuf -> second.insertch(33); });
	insert.insert({34},  [](){ curbuf -> second.insertch(34); });
	insert.insert({35},  [](){ curbuf -> second.insertch(35); });
	insert.insert({36},  [](){ curbuf -> second.insertch(36); });
	insert.insert({37},  [](){ curbuf -> second.insertch(37); });
	insert.insert({38},  [](){ curbuf -> second.insertch(38); });
	insert.insert({39},  [](){ curbuf -> second.insertch(39); });
	insert.insert({40},  [](){ curbuf -> second.insertch(40); });
	insert.insert({41},  [](){ curbuf -> second.insertch(41); });
	insert.insert({42},  [](){ curbuf -> second.insertch(42); });
	insert.insert({43},  [](){ curbuf -> second.insertch(43); });
	insert.insert({44},  [](){ curbuf -> second.insertch(44); });
	insert.insert({45},  [](){ curbuf -> second.insertch(45); });
	insert.insert({46},  [](){ curbuf -> second.insertch(46); });
	insert.insert({47},  [](){ curbuf -> second.insertch(47); });
	insert.insert({48},  [](){ curbuf -> second.insertch(48); });
	insert.insert({49},  [](){ curbuf -> second.insertch(49); });
	insert.insert({50},  [](){ curbuf -> second.insertch(50); });
	insert.insert({51},  [](){ curbuf -> second.insertch(51); });
	insert.insert({52},  [](){ curbuf -> second.insertch(52); });
	insert.insert({53},  [](){ curbuf -> second.insertch(53); });
	insert.insert({54},  [](){ curbuf -> second.insertch(54); });
	insert.insert({55},  [](){ curbuf -> second.insertch(55); });
	insert.insert({56},  [](){ curbuf -> second.insertch(56); });
	insert.insert({57},  [](){ curbuf -> second.insertch(57); });
	insert.insert({58},  [](){ curbuf -> second.insertch(58); });
	insert.insert({59},  [](){ curbuf -> second.insertch(59); });
	insert.insert({60},  [](){ curbuf -> second.insertch(60); });
	insert.insert({61},  [](){ curbuf -> second.insertch(61); });
	insert.insert({62},  [](){ curbuf -> second.insertch(62); });
	insert.insert({63},  [](){ curbuf -> second.insertch(63); });
	insert.insert({64},  [](){ curbuf -> second.insertch(64); });
	insert.insert({65},  [](){ curbuf -> second.insertch(65); });
	insert.insert({66},  [](){ curbuf -> second.insertch(66); });
	insert.insert({67},  [](){ curbuf -> second.insertch(67); });
	insert.insert({68},  [](){ curbuf -> second.insertch(68); });
	insert.insert({69},  [](){ curbuf -> second.insertch(69); });
	insert.insert({70},  [](){ curbuf -> second.insertch(70); });
	insert.insert({71},  [](){ curbuf -> second.insertch(71); });
	insert.insert({72},  [](){ curbuf -> second.insertch(72); });
	insert.insert({73},  [](){ curbuf -> second.insertch(73); });
	insert.insert({74},  [](){ curbuf -> second.insertch(74); });
	insert.insert({75},  [](){ curbuf -> second.insertch(75); });
	insert.insert({76},  [](){ curbuf -> second.insertch(76); });
	insert.insert({77},  [](){ curbuf -> second.insertch(77); });
	insert.insert({78},  [](){ curbuf -> second.insertch(78); });
	insert.insert({79},  [](){ curbuf -> second.insertch(79); });
	insert.insert({80},  [](){ curbuf -> second.insertch(80); });
	insert.insert({81},  [](){ curbuf -> second.insertch(81); });
	insert.insert({82},  [](){ curbuf -> second.insertch(82); });
	insert.insert({83},  [](){ curbuf -> second.insertch(83); });
	insert.insert({84},  [](){ curbuf -> second.insertch(84); });
	insert.insert({85},  [](){ curbuf -> second.insertch(85); });
	insert.insert({86},  [](){ curbuf -> second.insertch(86); });
	insert.insert({87},  [](){ curbuf -> second.insertch(87); });
	insert.insert({88},  [](){ curbuf -> second.insertch(88); });
	insert.insert({89},  [](){ curbuf -> second.insertch(89); });
	insert.insert({90},  [](){ curbuf -> second.insertch(90); });
	insert.insert({91},  [](){ curbuf -> second.insertch(91); });
	insert.insert({92},  [](){ curbuf -> second.insertch(92); });
	insert.insert({93},  [](){ curbuf -> second.insertch(93); });
	insert.insert({94},  [](){ curbuf -> second.insertch(94); });
	insert.insert({95},  [](){ curbuf -> second.insertch(95); });
	insert.insert({96},  [](){ curbuf -> second.insertch(96); });
	insert.insert({97},  [](){ curbuf -> second.insertch(97); });
	insert.insert({98},  [](){ curbuf -> second.insertch(98); });
	insert.insert({99},  [](){ curbuf -> second.insertch(99); });
	insert.insert({100}, [](){ curbuf -> second.insertch(100); });
	insert.insert({101}, [](){ curbuf -> second.insertch(101); });
	insert.insert({102}, [](){ curbuf -> second.insertch(102); });
	insert.insert({103}, [](){ curbuf -> second.insertch(103); });
	insert.insert({104}, [](){ curbuf -> second.insertch(104); });
	insert.insert({105}, [](){ curbuf -> second.insertch(105); });
	insert.insert({106}, [](){ curbuf -> second.insertch(106); });
	insert.insert({107}, [](){ curbuf -> second.insertch(107); });
	insert.insert({108}, [](){ curbuf -> second.insertch(108); });
	insert.insert({109}, [](){ curbuf -> second.insertch(109); });
	insert.insert({110}, [](){ curbuf -> second.insertch(110); });
	insert.insert({111}, [](){ curbuf -> second.insertch(111); });
	insert.insert({112}, [](){ curbuf -> second.insertch(112); });
	insert.insert({113}, [](){ curbuf -> second.insertch(113); });
	insert.insert({114}, [](){ curbuf -> second.insertch(114); });
	insert.insert({115}, [](){ curbuf -> second.insertch(115); });
	insert.insert({116}, [](){ curbuf -> second.insertch(116); });
	insert.insert({117}, [](){ curbuf -> second.insertch(117); });
	insert.insert({118}, [](){ curbuf -> second.insertch(118); });
	insert.insert({119}, [](){ curbuf -> second.insertch(119); });
	insert.insert({120}, [](){ curbuf -> second.insertch(120); });
	insert.insert({121}, [](){ curbuf -> second.insertch(121); });
	insert.insert({122}, [](){ curbuf -> second.insertch(122); });
	insert.insert({123}, [](){ curbuf -> second.insertch(123); });
	insert.insert({124}, [](){ curbuf -> second.insertch(124); });
	insert.insert({125}, [](){ curbuf -> second.insertch(125); });
	insert.insert({126}, [](){ curbuf -> second.insertch(126); });
	insert.insert({127}, [](){ curbuf -> second.insertch(127); });
	/// }}}

	// 33 - 127 for command
	/// {{{
	command.insert({33},  [](){ command_str.push_back(33); });
	command.insert({34},  [](){ command_str.push_back(34); });
	command.insert({35},  [](){ command_str.push_back(35); });
	command.insert({36},  [](){ command_str.push_back(36); });
	command.insert({37},  [](){ command_str.push_back(37); });
	command.insert({38},  [](){ command_str.push_back(38); });
	command.insert({39},  [](){ command_str.push_back(39); });
	command.insert({40},  [](){ command_str.push_back(40); });
	command.insert({41},  [](){ command_str.push_back(41); });
	command.insert({42},  [](){ command_str.push_back(42); });
	command.insert({43},  [](){ command_str.push_back(43); });
	command.insert({44},  [](){ command_str.push_back(44); });
	command.insert({45},  [](){ command_str.push_back(45); });
	command.insert({46},  [](){ command_str.push_back(46); });
	command.insert({47},  [](){ command_str.push_back(47); });
	command.insert({48},  [](){ command_str.push_back(48); });
	command.insert({49},  [](){ command_str.push_back(49); });
	command.insert({50},  [](){ command_str.push_back(50); });
	command.insert({51},  [](){ command_str.push_back(51); });
	command.insert({52},  [](){ command_str.push_back(52); });
	command.insert({53},  [](){ command_str.push_back(53); });
	command.insert({54},  [](){ command_str.push_back(54); });
	command.insert({55},  [](){ command_str.push_back(55); });
	command.insert({56},  [](){ command_str.push_back(56); });
	command.insert({57},  [](){ command_str.push_back(57); });
	command.insert({58},  [](){ command_str.push_back(58); });
	command.insert({59},  [](){ command_str.push_back(59); });
	command.insert({60},  [](){ command_str.push_back(60); });
	command.insert({61},  [](){ command_str.push_back(61); });
	command.insert({62},  [](){ command_str.push_back(62); });
	command.insert({63},  [](){ command_str.push_back(63); });
	command.insert({64},  [](){ command_str.push_back(64); });
	command.insert({65},  [](){ command_str.push_back(65); });
	command.insert({66},  [](){ command_str.push_back(66); });
	command.insert({67},  [](){ command_str.push_back(67); });
	command.insert({68},  [](){ command_str.push_back(68); });
	command.insert({69},  [](){ command_str.push_back(69); });
	command.insert({70},  [](){ command_str.push_back(70); });
	command.insert({71},  [](){ command_str.push_back(71); });
	command.insert({72},  [](){ command_str.push_back(72); });
	command.insert({73},  [](){ command_str.push_back(73); });
	command.insert({74},  [](){ command_str.push_back(74); });
	command.insert({75},  [](){ command_str.push_back(75); });
	command.insert({76},  [](){ command_str.push_back(76); });
	command.insert({77},  [](){ command_str.push_back(77); });
	command.insert({78},  [](){ command_str.push_back(78); });
	command.insert({79},  [](){ command_str.push_back(79); });
	command.insert({80},  [](){ command_str.push_back(80); });
	command.insert({81},  [](){ command_str.push_back(81); });
	command.insert({82},  [](){ command_str.push_back(82); });
	command.insert({83},  [](){ command_str.push_back(83); });
	command.insert({84},  [](){ command_str.push_back(84); });
	command.insert({85},  [](){ command_str.push_back(85); });
	command.insert({86},  [](){ command_str.push_back(86); });
	command.insert({87},  [](){ command_str.push_back(87); });
	command.insert({88},  [](){ command_str.push_back(88); });
	command.insert({89},  [](){ command_str.push_back(89); });
	command.insert({90},  [](){ command_str.push_back(90); });
	command.insert({91},  [](){ command_str.push_back(91); });
	command.insert({92},  [](){ command_str.push_back(92); });
	command.insert({93},  [](){ command_str.push_back(93); });
	command.insert({94},  [](){ command_str.push_back(94); });
	command.insert({95},  [](){ command_str.push_back(95); });
	command.insert({96},  [](){ command_str.push_back(96); });
	command.insert({97},  [](){ command_str.push_back(97); });
	command.insert({98},  [](){ command_str.push_back(98); });
	command.insert({99},  [](){ command_str.push_back(99); });
	command.insert({100}, [](){ command_str.push_back(100); });
	command.insert({101}, [](){ command_str.push_back(101); });
	command.insert({102}, [](){ command_str.push_back(102); });
	command.insert({103}, [](){ command_str.push_back(103); });
	command.insert({104}, [](){ command_str.push_back(104); });
	command.insert({105}, [](){ command_str.push_back(105); });
	command.insert({106}, [](){ command_str.push_back(106); });
	command.insert({107}, [](){ command_str.push_back(107); });
	command.insert({108}, [](){ command_str.push_back(108); });
	command.insert({109}, [](){ command_str.push_back(109); });
	command.insert({110}, [](){ command_str.push_back(110); });
	command.insert({111}, [](){ command_str.push_back(111); });
	command.insert({112}, [](){ command_str.push_back(112); });
	command.insert({113}, [](){ command_str.push_back(113); });
	command.insert({114}, [](){ command_str.push_back(114); });
	command.insert({115}, [](){ command_str.push_back(115); });
	command.insert({116}, [](){ command_str.push_back(116); });
	command.insert({117}, [](){ command_str.push_back(117); });
	command.insert({118}, [](){ command_str.push_back(118); });
	command.insert({119}, [](){ command_str.push_back(119); });
	command.insert({120}, [](){ command_str.push_back(120); });
	command.insert({121}, [](){ command_str.push_back(121); });
	command.insert({122}, [](){ command_str.push_back(122); });
	command.insert({123}, [](){ command_str.push_back(123); });
	command.insert({124}, [](){ command_str.push_back(124); });
	command.insert({125}, [](){ command_str.push_back(125); });
	command.insert({126}, [](){ command_str.push_back(126); });
	command.insert({127}, [](){ command_str.push_back(127); });
	/// }}}

	command.insert({ 21 }, [](){ command_str.clear(); });
	command.insert({ ' ' }, [](){ command_str += ' '; });
	command.insert({ KEY_BACKSPACE }, [](){ if (!command_str.empty()) command_str.pop_back(); });

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
			c = getch();
			switch (mode)
			{
			case 0:
				normal.exec(c);
				break;
			case 1:
				insert.exec(c);
				break;
			case 2:
				visual.exec(c);
				break;
			case 3:
				replace.exec(c);
				break;
			case 4:
				while (c != '\n')
				{
						mvaddch(LINES - 1, 0, '>');
						addch(' ');

						if ((i32) command_str.size() < COLS - 3)
						{
							addstr(command_str.c_str());
							for (u16 i = command_str.size(); i < COLS - 3; ++i) addch(' ');
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
						command.exec(c);
				}
				parser.parse(command_str);
				command_str.clear();
				mvaddch(LINES - 1, 0, ' ');
				for (u16 i = 1; i < COLS; ++i) addch(' ');
				mode = 0;
				break;
			default:
				break;
			}
	}

	endwin();
	return 1;
}

