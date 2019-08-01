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

void PNetworkDataStorage::AddData(FLOAT_RECT data)
{
	col_rect_list_.push_back(data);
}

void PNetworkDataStorage::AddData(PSkill* skill)
{
	skill_list_.push_back(skill);
}

void PNetworkDataStorage::AddData(MeteorRandNumber data)
{
	meteor_data_.push_back(data);
}

HitData PNetworkDataStorage::PopHitData()
{
	HitData ret = hit_list_.front();
	hit_list_.pop_front();
	return ret;
}

FLOAT_RECT PNetworkDataStorage::PopRECTData()
{
	FLOAT_RECT ret = col_rect_list_.front();
	col_rect_list_.pop_front();
	return ret;
}

PSkill* PNetworkDataStorage::PopSkillData()
{
	PSkill* ret = skill_list_.front();
	col_rect_list_.pop_front();
	return ret;
}

MeteorRandNumber PNetworkDataStorage::PopMeteorData()
{
	MeteorRandNumber ret = meteor_data_.front();
	meteor_data_.pop_front();
	return ret;
}

bool PNetworkDataStorage::IsQueueEmpty()
{
	return hit_list_.empty();
}

bool PNetworkDataStorage::isColListEmpty()
{
	return col_rect_list_.empty();
}

bool PNetworkDataStorage::GetHitListSize()
{
	return hit_list_.size();
}

bool PNetworkDataStorage::GetRECTListSize()
{
	return col_rect_list_.size();
}

bool PNetworkDataStorage::GetSkillListSize()
{
	return skill_list_.size();
}

void PNetworkDataStorage::set_b_need_report(bool need_report)
{
	b_need_report_ = need_report;
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
