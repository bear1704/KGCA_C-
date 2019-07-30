#pragma once
#include "PStd.h"

typedef struct HitData_ {
	int damage;
	WORD boss_id;
	WORD player_id;
	WORD player_cid;
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
	HitData PopData();
	bool IsQueueEmpty();


public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();


};

