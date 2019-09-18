#include <iostream>
#include <vector>

class Observer
{
public:
	Observer();
	virtual ~Observer();

	virtual void Notify(const Entity& entity, Event event) = 0;
};

class Achievements : public Observer
{
public:
	virtual void Notify(const Entity& entity, Event event)
	{
		if (event == Event::EVENT_BRIDGE_FELL)
		{
			if(entity.isHero())
				unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
		}
	}

private:
	void unlock(Achievement achievement);

	//...
};

class Subject
{
private:
	std::vector<Observer*> observers_;

public:
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

protected:
	void Notify(const Entity& entity, Event event)
	{
		for (int i = 0; i < observers_.size(); i++)
		{
			observers_[i]->Notify(entity, event);
		}
	}

	//...
};



