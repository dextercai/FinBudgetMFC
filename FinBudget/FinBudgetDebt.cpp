#include "pch.h"
#include "FinBudgetDebt.h"
bool FinBudgetDebt::setValue(double _value)
{
	return this->value = _value;
}

bool FinBudgetDebt::setRange(double _range)
{
	return this->range = _range;
}

bool FinBudgetDebt::setRate(double _rate)
{
	return this->rate = _rate;
}

bool FinBudgetDebt::setTime(time_t _t)
{
	return this->time = _t;
}

bool FinBudgetDebt::setRemark(CString _str)
{
	return this->remark = _str;
}

bool FinBudgetDebt::setCycle(Cycle _cycle)
{
	return this->cycle = _cycle;
}

bool FinBudgetDebt::setType(DebtType _type)
{
	return this->type=_type;
}


double FinBudgetDebt::getValue()
{
	return this->value;
}

double FinBudgetDebt::getRate()
{
	return this->rate;
}

double FinBudgetDebt::getRange()
{
	return this->range;
}

DebtType FinBudgetDebt::getType()
{
	return this->type;
}




time_t FinBudgetDebt::getTime()
{
	return this->time;
}

CString FinBudgetDebt::getRemark()
{
	return this->remark;
}

Cycle FinBudgetDebt::getCycle()
{
	return this->cycle;
}
