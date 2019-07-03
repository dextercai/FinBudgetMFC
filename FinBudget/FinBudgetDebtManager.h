#pragma once
#include "pch.h"
#include <map>
#include "FinBudgetDebt.h"
class FinBudgetDebtManager
{
public:
	int C(double _value, double _range, double _rate, time_t _time, CString _remark, Cycle _cycle, DebtType _type);
	bool U(int _index, double _value, double _range, double _rate, time_t _time, CString _remark, Cycle _cycle, DebtType _type);
	FinBudgetDebt* R(int _index);
	bool D(int _index);
	int getSize();
	std::map<int, FinBudgetDebt*> DebtMap;
};

