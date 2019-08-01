#pragma once
#include "PStd.h"
#include "PSkill.h"

typedef struct HitData_ {
	int damage;
	WORD boss_id;
	WORD player_cid;
}HitData;

typedef struct MeteorRandNumber_
{
	int skillnum;
	std::vector<int> initpos;
	std::vector<int> downspeed;

}MeteorRandNumber;


class PNetworkDataStorage :
	public PSingleton<PNetworkDataStorage>
{
private:
	PNetworkDataStorage();
	friend class PSingleton<PNetworkDataStorage>;
	std::list<HitData> hit_list_;
	std::list<FLOAT_RECT> col_rect_list_;
	std::list<PSkill*> skill_list_;
	std::list<MeteorRandNumber> meteor_data_;
	bool b_need_report_; //위치보고가 필요한지 여부(이동, 공격 등..)

public:
	~PNetworkDataStorage();

	void AddData(HitData data);
	void AddData(FLOAT_RECT data);
	void AddData(PSkill* skill);
	void AddData(MeteorRandNumber data);
	HitData PopHitData();
	FLOAT_RECT PopRECTData();
	PSkill* PopSkillData();
	MeteorRandNumber PopMeteorData();
	bool IsQueueEmpty();
	bool isColListEmpty();
	bool GetHitListSize();
	bool GetRECTListSize();
	bool GetSkillListSize();
	void set_b_need_report(bool need_report);
	bool is_b_need_report();

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();


};

