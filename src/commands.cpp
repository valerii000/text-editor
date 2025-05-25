#include "../include/commands.h"

std::string exec(const char* cmd)
{
    std::string result;
    char cmdE[16384];
    snprintf(cmdE, sizeof(cmdE), "%s 2>&1", cmd);
    FILE* pipe = popen(cmdE, "r");
    if (!pipe) return "";
    char buffer[128];
    while (fgets(buffer, 128, pipe) != NULL)
        result += buffer;
    pclose(pipe);
    return result;
}

void quitCommand()
{
	endwin();
	exit(0);
}

void saveCommand()
{
	if (parser.args.size() > 1)
	{
		//save to these files
		return;
	}

	if (curbuf -> second.path.empty())
	{
		return;
		message("can not save scratch file");
	}

	std::ofstream file(curbuf -> second.path);

	if (!file)
	{
		return;
		message("file doesn't exist");
	}

	for (const let& line : curbuf -> second.content)
	{
		file << line << std::endl;
	}

	file.close();
}

void openCommand()
{
	if (parser.args.size() == 1)
	{
		message("no file selected");
		return;
	}

	std::ifstream file(parser.args[1]);

	if (!file)
	{
		message("file not found");
		return;
	}

	char cwd[256];
	getcwd(cwd, 256);
	curbuf -> second.content.clear();
	curbuf -> second.content.push_back("");
	curbuf -> second.path = (std::string) cwd + '/' + parser.args[1];
	std::string line;
	while (std::getline(file, line))
	{
		std::string s;
		for (let& ch : line)
		{
			if (ch == '\t') s += "	  ";
			else s += ch;
		}
		s += '\n';
		curbuf -> second.insert(s);
	}
	file.close();

	if (curbuf -> second.content.empty() && !curbuf -> second.content.back().empty()) curbuf -> second.insert("\n");

	curbuf -> second.y = 0;
	curbuf -> second.x = 0;
	curbuf -> second.topy = 0;
	curbuf -> second.topx = 0;
}

void cdCommand()
{
	if (parser.args.size() == 1) pwdCommand();
	else chdir(parser.args[1].c_str());
}

void pwdCommand()
{
	char cwd[256];
	getcwd(cwd, 256);
	message(cwd);
}

void lsCommand()
{
    if (parser.args.size() == 1)
	{
        std::string output = exec("ls");
        message_big(output);
		return;
    }

	std::string cmd = "ls";
	for (u32 i = 1; i < (u32) parser.args.size(); ++i)
		 cmd += ' ' + parser.args[i];

	std::string output = exec(cmd.c_str());
	message_big(output);
}

void buffersCommand()
{
	std::string s;

	for (const let& [name, b] : buffers)
	{
		if (name.empty()) s += "[untitled]";
		else s += name;

		s += "	  ";
		
		if (b.path.empty()) s += "[scratch]";
		else s += b.path;

		if (&b == &curbuf->second)
			s += " <-";

		s += '\n';
	}

	s.pop_back();

	message_big(s);
}

void bCommand()
{
	if (parser.args.size() == 1)
	{
		buffersCommand();
		return;
	}

	auto it = buffers.find(parser.args[1]);

	if (it != buffers.end())
	{
		curbuf = it;
		return;
	}

	buffers[parser.args[1]] = Buffer();
	curbuf = buffers.find(parser.args[1]);
}

void bdCurCommand()
{
	if (curbuf != buffers.end())
	{
		let nextIt = std::next(curbuf);
		buffers.erase(curbuf);
		if (nextIt == buffers.end() && buffers.size() == 0)
		{
			buffers["0"] = Buffer();
			curbuf = buffers.find("0");
		}
		else
			curbuf = (nextIt == buffers.end()) ? --nextIt : nextIt;
	}
	else message("no buffer selected");
}

void bdCommand()
{
	if (parser.args.size() == 1)
	{
		message("no buffer selected");
		return;
	}

	auto it = buffers.find(parser.args[1]);
	if (it != buffers.end())
	{
		if (curbuf == it)
			bdCurCommand();

		else
		{
			buffers.erase(it);
			if (curbuf == buffers.end()) --curbuf;
		}
	}
	else message("buffer not found");
}

void bufUpCommand()
{
	if (curbuf != buffers.begin())
		curbuf = std::prev(curbuf);
}

void bufDownCommand()
{
	if (curbuf != buffers.end() && std::next(curbuf) != buffers.end())
		curbuf = std::next(curbuf);
}

void shellCommand()
{
	if (parser.args.size() == 1) return;
	std::string s;
	for (u32 i = 1; i < parser.args.size(); ++i)
		s += parser.args[i] + ' ';
	message_big(exec(s.c_str()));
}
