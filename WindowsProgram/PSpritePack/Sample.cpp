#include "Sample.h"
#include <time.h>


Sample::Sample()
{
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	
	PSpriteManager::GetInstance().LoadDataFromScript(L"sprite_coord.txt"); //��������Ʈ �� 3���� rect�����͸� ���� ��������Ʈ �ε�
	sprites[0].Set(*PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"rtBomb"));
	sprites[0].SetPosition(300, 300);
	//sprite1.Set(*(PSpriteManager::GetInstance().get_sprite_data_list_from_map(L"rtExplosion")));
	//sprite1.SetPosition(200, 300);
	
	return true;
}

bool Sample::Frame()
{
	sprites[0].Frame();
	//sprite2.Frame();
	/*if (g_InputActionMap.leftClick == KEYSTAT::KEY_PUSH)
	{
		sprite1.Play();
	}
*/
	

	return true;
}

bool Sample::Render()
{
	sprites[0].Render();
	//sprite2.Render();
	
	return true;
}