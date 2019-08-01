#pragma once
class PSkill
{
	
public:
	PSkill();
	~PSkill();

public:
	virtual void Init()= 0;
	virtual void Frame() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void Start();

};

