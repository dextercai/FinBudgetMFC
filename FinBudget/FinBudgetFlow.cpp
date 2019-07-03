#include "pch.h"
#include "FinBudgetFlow.h"

bool FinBudgetFlow::setValue(double _value)
{
	return this->value = _value;
}

bool FinBudgetFlow::setTime(time_t _t)
{
	return this->time = _t;
}

bool FinBudgetFlow::setRemark(CString _str)
{
	return this->remark = _str;
}

bool FinBudgetFlow::setType(FlowType _type)
{
	return this->type = _type;
}

bool FinBudgetFlow::setRId(int _rid)
{
	return this->rid = _rid;

}

double FinBudgetFlow::getValue()
{
	return this->value;
}

time_t FinBudgetFlow::getTime()
{
	return this->time;
}

CString FinBudgetFlow::getRemark()
{
	return this->remark;
}

FlowType FinBudgetFlow::getType()
{
	return this->type;
}

int FinBudgetFlow::getRId()
{
	return this->rid;
}
