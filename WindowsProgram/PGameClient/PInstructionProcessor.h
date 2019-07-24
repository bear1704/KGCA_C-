#pragma once
#include "TServerStd.h"
#include "PProtocol.h"
#include "PInstructionManager.h"
#include "PUserManager.h"
#include "PPacketManager.h"
#include "PScene.h"
#include "PObjectDataManager.h"


class PInstructionProcessor : public PSingleton<PInstructionProcessor>
{
private:
	friend class PSingleton<PInstructionProcessor>;
	
	PScene* current_scene_;
	std::mutex process_mutex_;

	const std::wstring path = L"data/character/character_data.txt";
	const std::wstring map_path = L"data/map/map_data.txt";
	const std::wstring status_path = L"data/character/character_status_data.txt";
	const std::wstring animation_path = L"data/character/sprite/animation_list.txt";

private:
	PInstructionProcessor();
public:
	~PInstructionProcessor();
	
	//Client only
	void BindScene(PScene* current_scene); //Client Only
	std::thread process_thread_;
	void ProcessInstruction();


public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	void SpawnPlayer(pPoint& pos);


};

