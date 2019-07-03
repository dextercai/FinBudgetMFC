#pragma once
#include "pch.h"
#include "FinBudgetSupport.h"
class FinBudgetDebt
{
private:
	double value, rate, range;
	int rid;
	time_t time;
	CString remark;
	Cycle cycle;
	DebtType type;
public:
	bool setValue(double _value);
	bool setRate(double _rate);
	bool setRange(double _range);
	bool setTime(time_t _t);
	bool setRemark(CString _str);
	bool setCycle(Cycle _cycle);
	bool setType(DebtType _type);
	double getValue();
	double getRate();
	double getRange();
	DebtType getType();
	time_t getTime();
	CString getRemark();
	Cycle getCycle();
};
