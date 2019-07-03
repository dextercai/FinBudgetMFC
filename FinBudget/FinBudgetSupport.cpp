#include "pch.h"
#include "FinBudgetSupport.h"
#include <map>

time_t StringToDateTime(char* str)
{
	tm tm_;
	int year, month, day, hour, min, sec;
	afxDump << str << "\n\n\n\n";
	sscanf_s(str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &min, &sec);

	tm_.tm_year = year - 1900;
	tm_.tm_mon = month - 1;
	tm_.tm_mday = day;
	tm_.tm_hour = hour;
	tm_.tm_min = min;
	tm_.tm_sec = sec;

	tm_.tm_isdst = -1;
	time_t t_ = mktime(&tm_);
	return t_;
}

CString DateTimeToString(time_t _time)
{
	tm *_tm = new tm();
	gmtime_s(_tm ,&_time);
	CString t_str;
	t_str.Format(_T("%d-%d-%d %d:%d:%d"), _tm->tm_year+1900, 1+_tm->tm_mon, _tm->tm_mday, _tm->tm_hour , _tm->tm_min, _tm->tm_sec);
	delete _tm;
	return t_str;
}

CString _toCString(double _value)
{
	CString t_str;
	t_str.Format(_T("%lf"), _value);
	return t_str;
}

CString _toCString(int _value)
{
	CString t_str;
	t_str.Format(_T("%d"), _value);
	return t_str;
}

double _toDouble(CString _str) {
	return _ttof(_str);
}


char* CStringToCharArray(CString str)
{
	int str_len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);//¼ÆËã×Ö½ÚÊý
	char* CharArray = new char[str_len + 1];
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), CharArray, str_len, NULL, NULL);
	CharArray[str_len] = '\0';
	return CharArray;
}

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}