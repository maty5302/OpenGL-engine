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

void Subject::addObserver(Observer* observer)
{
	this->observers.push_back(observer);
}

void Subject::notify()
{
	for (auto observer : this->observers)
	{
		observer->update();
	}
}
