#ifndef _LOGER_H_
#define _LOGER_H_
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "calendar.h"
using namespace std;


class Loger
{
private:
	string   name;
	string   path;
	ofstream file;
	Calendar last;
	const uint32_t maxsize;
public:
	enum{defsize=(1<<23), minsize=(1<<18)};
public:
	Loger(const string& p="log", uint32_t s=defsize):maxsize( (s < minsize) ? minsize : s )
	{
		if(p.empty())
		{
			path = "log/";
		}
		else
		{
			path = p + "/";
		}
		mkdir(path.data(), 0755);
		open();
	}
public:
	bool open(void)
	{
		for(int i = 0; i < (1<<30); i++)
		{
			stringstream ss;
			ss << last.toString("%F.") << i << ".log";
			if(name != ss.str())
			{
				name = ss.str();
				file.close();
				file.clear();
				file.open(path+name, fstream::app);
				if(file.tellp() < maxsize)
				{
					return true;
				}
				file.close();
			}
		}
		return false;
	}
	Loger& operator<<(const string& s)
	{
		if(file.tellp() >= maxsize)
		{
			open();
		}
		Calendar now;
		if(now.toString("%F") != last.toString("%F"))
		{
			open();
		}
		file << now.toString("[%F %T] ") << s << endl;
		return *this;
	}
};

#endif//_LOGER_H_
