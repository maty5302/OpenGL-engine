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
};

