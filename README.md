# common
个些通用的c++封装，C99,C++98,C++11尽量不使用太新的C++特性影响兼容

## calender.h
```C++
#ifndef _CALENDAR_H_
#define _CALENDAR_H_
#include <ctime>
#include <string>
using namespace std;

class Calendar
{
    struct tm calendar;
public:
    Calendar(void)
    {
        update();
    }
    void update(void)
    {
        time_t t = time(0);
        calendar = *localtime(&t);
    }
    string toString(const string& fmt = "%F %T")
    {
        char buf[128] = {0};
        strftime(buf, sizeof(buf), fmt.empty() ? "%F %T" : fmt.c_str(), &calendar);
        return buf;
    }
    bool fromString(const string& s, const string& fmt="%F %T")
    {
        if(s.empty() || fmt.empty())
        {
            return false;
        }    
        if(strptime(s.c_str(), fmt.c_str(), &calendar) == false)
        {
            return false;
        }
        return true;
    }
    int year    (void)const{return calendar.tm_year;}
    int month    (void)const{return calendar.tm_mon;}
    int day        (void)const{return calendar.tm_mday;}
    int hour    (void)const{return calendar.tm_hour;}
    int minute    (void)const{return calendar.tm_min;}
    int second    (void)const{return calendar.tm_sec;}
    int weekday    (void)const{return calendar.tm_wday;}
    int monthday(void)const{return calendar.tm_mday;}
    int yearday    (void)const{return calendar.tm_yday;}
};

#endif//_CALENDAR_H_
```

## loger.h
```C++
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
```
