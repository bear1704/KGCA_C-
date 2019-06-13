#pragma once
#include "PRectObject.h"

class PUIComponent : public PRectObject
{


public:
	PUIComponent();
	virtual ~PUIComponent();

private:
	std::vector<PUIComponent*> component_list_; //polymorphism
public:
	virtual PUIComponent* Clone() { return nullptr; }
	virtual void Draw() {};

public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	void Add(PUIComponent* component);
	void Set(multibyte_string data_path, multibyte_string object_name, pPoint position);
	std::vector<PUIComponent*>& get_component_list_();
};

