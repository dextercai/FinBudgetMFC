#include "pch.h"
#include "FinBudgetFlowManager.h"

int FinBudgetFlowManager::C(double _value, time_t _time, CString _remark, FlowType _type)
{
	FinBudgetFlow* pFBD = new FinBudgetFlow();
	pFBD->setValue(_value);
	pFBD->setTime(_time);
	pFBD->setRemark(_remark);
	pFBD->setType(_type);;
	this->FlowMap.insert(std::map<int, FinBudgetFlow*>::value_type(this->getSize(), pFBD));
	return this->getSize()-1;
}

bool FinBudgetFlowManager::U(int _index, double _value, time_t _time, CString _remark, FlowType _type){
	std::map<int, FinBudgetFlow*>::iterator iter;
	iter = this->FlowMap.find(_index);
	if (iter != this->FlowMap.end()) {
		delete iter->second;
		iter->second = NULL;
		this->FlowMap.erase(iter);
		FinBudgetFlow *pFBD = new FinBudgetFlow();
		pFBD->setValue(_value);
		pFBD->setTime(_time);
		pFBD->setRemark(_remark);
		pFBD->setType(_type);
		this->FlowMap.insert(std::map<int, FinBudgetFlow*>::value_type(_index, pFBD));
		return true;
	}
	else {
		throw _index;
	}
}

FinBudgetFlow* FinBudgetFlowManager::R(int _index)
{
	std::map<int, FinBudgetFlow*>::iterator iter;
	iter = this->FlowMap.find(_index);
	if (iter != this->FlowMap.end()) {
		return iter->second;
	}
	else {
		throw _index;
	}
}

bool FinBudgetFlowManager::D(int _index)
{
	std::map<int, FinBudgetFlow*>::iterator iter;
	iter = this->FlowMap.find(_index);
	if (iter != this->FlowMap.end()) {
		delete iter->second;
		iter->second = NULL; //防止野指针这一步是否真的需要？
		this->FlowMap.erase(iter);
		return true;
	}
	else {
		throw _index;
	}
}

int FinBudgetFlowManager::getSize()
{
	return FlowMap.size();
}

