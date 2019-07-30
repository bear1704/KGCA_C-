#include "PNetworkDataStorage.h"

PNetworkDataStorage::PNetworkDataStorage()
{
}

PNetworkDataStorage::~PNetworkDataStorage()
{
}

void PNetworkDataStorage::AddData(HitData data)
{
	hit_list_.push_back(data);
}

HitData PNetworkDataStorage::PopData()
{
	HitData ret = hit_list_.front();
	hit_list_.pop_front();
	return ret;
}

bool PNetworkDataStorage::IsQueueEmpty()
{
	return hit_list_.empty();
}

bool PNetworkDataStorage::Init()
{
	return false;
}

bool PNetworkDataStorage::Frame()
{
	return false;
}

bool PNetworkDataStorage::Render()
{
	return false;
}

bool PNetworkDataStorage::Release()
{
	return false;
}
