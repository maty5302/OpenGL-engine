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

void Subject::removeObserver(Observer* observer)
{
	this->observers.erase(std::remove(this->observers.begin(), this->observers.end(), observer), this->observers.end());
}

void Subject::notify()
{
}

void Subject::notify(int id)
{
}
