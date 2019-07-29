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

public:
	~PNetworkDataStorage();

	std::list<HitData> hit_list_;





};

