#pragma once
#include <assert.h>
#include "PSprite.h"


const int kPlaneTextureUvMax = 4;

class PSpriteManager : public PSingleton<PSpriteManager>
{//name maxframe lifetime once_playtime path
public:
	~PSpriteManager();
private:
	PSpriteManager();
	friend class PSingleton<PSpriteManager>;
	//std::map<std::wstring, SpriteDataInfo*> sprite_data_list_;
	std::map<std::wstring, PSprite*> sprite_list_;
	std::map<std::wstring, PSprite*> damage_font_list_;
	std::list<PSprite> render_wait_list_; //이 곳에 넣으면 렌더타임에 렌더된다.
	int dmg_font_index_;
	bool need_load_character_sprite_data_;
	bool need_load_UI_sprite_data_;
	bool need_load_map_sprite_data_;

	const int kDamageFontLifetime;
	const float kDamageFontGap;

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

	PSprite* get_sprite_from_map_ex(std::wstring key);
	PSprite* get_sprite_from_dmgfont_list(std::wstring key);
	void LoadSpriteDataFromScript(multibyte_string filepath, ObjectLoadType type);
	bool Delete(int key);
	void AddRenderWaitList(PSprite sprite);
	void CreateDamageFontFromInteger(int damage, pPoint firstPos);
	DX::PTex_uv ImageCoordinateToTexCoordinate(float x, float y, float image_width, float image_height);

};

