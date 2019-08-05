#pragma once
#include "PStd.h"
#include "PMonster.h"

class PComponentStorage : public PSingleton<PComponentStorage>
{

private:
	friend class PSingleton<PComponentStorage>;
	std::vector<PRectObject*> game_objects_;
public:
	~PComponentStorage();
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void InsertObject(std::vector<PRectObject*>& list_component);



};

