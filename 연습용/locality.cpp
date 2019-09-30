#include <iostream>
#include <vector>


#ifdef WorstCase

class GameEntity
{
private:
	AIComponent* ai_;
	PhysicsComponent* physics_;
	RenderComponent* render_;

public:
	AIComponent* ai() { return ai_; }
	PhysicsComponent* physics() { return physics_; }
	RenderComponent* render() { return render_; }

};

class AIComponent
{
public:
	void Update();
};

class PhysicsComponent
{
public:
	void Update();
};

class RenderComponent
{
public:
	void Render();
};

int main()
{

	std::vector<GameEntity*> entities;

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->ai()->Update();
		entities[i]->physics()->Update();
		entities[i]->render()->Render();
	}


}

#endif

class GameEntity
{
private:
	AIComponent* ai_;
	PhysicsComponent* physics_;
	RenderComponent* render_;

public:
	AIComponent* ai() { return ai_; }
	PhysicsComponent* physics() { return physics_; }
	RenderComponent* render() { return render_; }

};


class AIComponent
{
public:
	void Update();
};

class PhysicsComponent
{
public:
	void Update();
};

class RenderComponent
{
public:
	void Render();
};

int main()
{
	const int kArraySize = 10;
	AIComponent* aicomponents = new AIComponent[10];
	PhysicsComponent* physicscomponents = new PhysicsComponent[10];
	RenderComponent* rendercomponents = new RenderComponent[10];

	for (int i = 0; i < kArraySize; i++)
	{
		aicomponents[i].Update();
		physicscomponents[i].Update();
		rendercomponents[i].Render();
	}

}