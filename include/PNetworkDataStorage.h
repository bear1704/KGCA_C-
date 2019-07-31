#pragma once
#include "PStd.h"

typedef struct HitData_ {
	int damage;
	WORD boss_id;
	WORD player_id;
}HitData;


class PNetworkDataStorage :
	public PSingleton<PNetworkDataStorage>
{
private:
	PNetworkDataStorage();
	friend class PSingleton<PNetworkDataStorage>;
	std::list<HitData> hit_list_;
	bool b_need_report_; //위치보고가 필요한지 여부(이동, 공격 등..)

public:
	~PNetworkDataStorage();

	void AddData(HitData data);
	HitData PopHitData();
	bool IsQueueEmpty();
	bool GetHitListSize();
	void set_b_need_report(bool need_report);
	bool is_b_need_report();

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();


};

