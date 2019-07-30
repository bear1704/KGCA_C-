#include "PNetworkDataStorage.h"

PNetworkDataStorage::PNetworkDataStorage()
{
	b_need_report_ = false;
}

PNetworkDataStorage::~PNetworkDataStorage()
{
}

void PNetworkDataStorage::AddData(HitData data)
{
	hit_list_.push_back(data);
}

HitData PNetworkDataStorage::PopHitData()
{
	HitData ret = hit_list_.front();
	hit_list_.pop_front();
	return ret;
}

bool PNetworkDataStorage::IsQueueEmpty()
{
	return hit_list_.empty();
}

bool PNetworkDataStorage::GetHitListSize()
{
	return hit_list_.size();
}

void PNetworkDataStorage::set_b_need_report(bool ismove)
{
	b_need_report_ = ismove;
}

bool PNetworkDataStorage::is_b_need_report()
{
	return b_need_report_;
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
