#pragma once
#include "pch.h"
#include <cstring>
#include "FinBudgetSupport.h"
class FinBudgetFlow
{
private:
	double value;
	int rid;
	time_t time;
	CString remark;
	FlowType type;
public:
	bool setValue(double _value);
	bool setTime(time_t _t);
	bool setRemark(CString _str);
	bool setType(FlowType _type);
	bool setRId(int _rid);
	double getValue();
	time_t getTime();
	CString getRemark();
	FlowType getType();
	int getRId();
};

