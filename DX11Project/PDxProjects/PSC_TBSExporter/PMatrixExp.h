#pragma once
#include "PSCWriter.h"

class PMatrixExp : public PSCWriter
{

public:
	void PreProcess(INode* node) override; 
	bool Export() override;
	bool SwitchAllNodeToMesh();

public:
	static PMatrixExp& GetInstance()
	{
		static PMatrixExp theExp;
		return theExp;
	}

public:
	PMatrixExp();
	virtual ~PMatrixExp();

};

