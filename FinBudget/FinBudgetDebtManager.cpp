#include "pch.h"
#include "FinBudgetDebtManager.h"

int FinBudgetDebtManager::C(double _value, double _range, double _rate, time_t _time, CString _remark, Cycle _cycle, DebtType _type)
{
	FinBudgetDebt *pFBD = new FinBudgetDebt();
	pFBD->setValue(_value);
	pFBD->setTime(_time);
	pFBD->setRemark(_remark);
	pFBD->setRange(_range);
	pFBD->setRate(_rate);
	pFBD->setCycle(_cycle);
	pFBD->setType(_type);
	this->DebtMap.insert(std::map<int, FinBudgetDebt*>::value_type(this->getSize(), pFBD));
	return this->getSize()-1;
}

bool FinBudgetDebtManager::U(int _index, double _value, double _range, double _rate, time_t _time, CString _remark, Cycle _cycle, DebtType _type)
{
	std::map<int, FinBudgetDebt*>::iterator iter;
	iter = this->DebtMap.find(_index);
	if (iter != this->DebtMap.end()) {
		delete iter->second;
		iter->second = NULL;
		this->DebtMap.erase(iter);
		FinBudgetDebt* pFBD = new FinBudgetDebt();
		pFBD->setValue(_value);
		pFBD->setTime(_time);
		pFBD->setRemark(_remark);
		pFBD->setRange(_range);
		pFBD->setRate(_rate);
		pFBD->setCycle(_cycle);
		pFBD->setType(_type);
		this->DebtMap.insert(std::map<int, FinBudgetDebt*>::value_type(_index, pFBD));
		return true;
	}
	else {
		throw _index;
	}
}


FinBudgetDebt* FinBudgetDebtManager::R(int _index)
{
	std::map<int, FinBudgetDebt*>::iterator iter;
	iter = this->DebtMap.find(_index);
	if (iter != this->DebtMap.end()) {
		return iter->second;
	}
	else {
		throw _index;
	}
}

bool FinBudgetDebtManager::D(int _index)
{
	std::map<int, FinBudgetDebt*>::iterator iter;
	iter = this->DebtMap.find(_index);
	if (iter != this->DebtMap.end()) {
		delete iter->second;
		iter->second = NULL; //防止野指针这一步是否真的需要？
		this->DebtMap.erase(iter);
		return true;
	}
	else {
		throw _index;
	}
}

int FinBudgetDebtManager::getSize()
{
	return DebtMap.size();
}


