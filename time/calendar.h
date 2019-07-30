#ifndef _3761_CALENDAR_H__
#define _3761_CALENDAR_H__
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
	int year	(void)const{return calendar.tm_year;}
	int month	(void)const{return calendar.tm_mon;}
	int day		(void)const{return calendar.tm_mday;}
	int hour	(void)const{return calendar.tm_hour;}
	int minute	(void)const{return calendar.tm_min;}
	int second	(void)const{return calendar.tm_sec;}
	int weekday	(void)const{return calendar.tm_wday;}
	int monthday(void)const{return calendar.tm_mday;}
	int yearday	(void)const{return calendar.tm_yday;}
};

#endif//_3761_CALENDAR_H__
