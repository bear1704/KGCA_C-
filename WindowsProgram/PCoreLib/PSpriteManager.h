#pragma once
#include <assert.h>
#include "PSprite.h"



class PSpriteManager : public PSingleton<PSpriteManager>
{//name maxframe lifetime once_playtime path
public:
	~PSpriteManager();
private:
	friend class PSingleton<PSpriteManager>;
	std::map<std::wstring, SpriteDataInfo*> sprite_data_list_;
	std::map<std::wstring, PSprite*> sprite_list_;
	int index_;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

	SpriteDataInfo* get_sprite_data_list_from_map(std::wstring key);
	PSprite* get_sprite_from_map_ex(std::wstring key);
	void LoadDataFromScript(multibyte_string filepath);  //파일에서 스프라이트 정보(Rect 좌표 등...)를 전부 읽어서 맵에 저장한다. name maxframe lifetime once_playtime path
	void LoadSpriteDataFromScript(multibyte_string filepath);
	bool Delete(int key);
	


};

