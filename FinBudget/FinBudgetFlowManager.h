#pragma once
#include <map>
#include "FinBudgetSupport.h"
#include "FinBudgetFlow.h"
class FinBudgetFlowManager
{
public:
	int C(double _value, time_t _time, CString _remark, FlowType _type);
	bool U(int _index, double _value, time_t _time, CString _remark, FlowType _type);
	FinBudgetFlow* R(int _index);
	bool D(int _index);
	int getSize();
	std::map<int, FinBudgetFlow*> FlowMap;
};

