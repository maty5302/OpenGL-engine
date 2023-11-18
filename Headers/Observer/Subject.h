/**
* @file Subject.h
*
* @brief Class used for observer pattern
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <vector>
#include "Observer.h"
class Subject
{
private:
	std::vector<Observer*> observers;
public:
	Subject();
	~Subject();
	std::vector<Observer*> getObservers();
	void addObserver(Observer* observer);
	virtual void notify();
	virtual void notify(int id);
};

