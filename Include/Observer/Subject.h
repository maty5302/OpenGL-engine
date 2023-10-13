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
	void addObserver(Observer* observer);
	void notify();
};

