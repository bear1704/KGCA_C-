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

public:
	~PNetworkDataStorage();

	void AddData(HitData data);
	HitData PopHitData();
	bool IsQueueEmpty();
	bool GetHitListSize();


public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();


};

