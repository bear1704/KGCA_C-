#include "PImageControl.h"



PImageControl::PImageControl()
{
}


PImageControl::~PImageControl()
{
}

bool PImageControl::Release()
{
	PButtonControl::Release();
	return true;
}
