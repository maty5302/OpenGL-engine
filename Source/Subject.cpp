#include "../Headers/Observer/Subject.h"

Subject::Subject()
{
	this->observers = std::vector<Observer*>();
}

Subject::~Subject()
{
	for (auto observer : this->observers)
	{
		delete observer;
	}
}

std::vector<Observer*> Subject::getObservers()
{
	return this->observers;
}

void Subject::addObserver(Observer* observer)
{
	this->observers.push_back(observer);
}

void Subject::notify()
{
}

void Subject::notify(int id)
{
}
