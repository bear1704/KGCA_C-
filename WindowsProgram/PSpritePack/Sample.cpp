#include "Sample.h"



Sample::Sample()
{
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	
	PSpriteManager::GetInstance().LoadRectData(L"sprite_coord.txt"); //��������Ʈ �� 3���� rect�����͸� ���� ��������Ʈ �ε�
	object_sprite.Load(L"../../bitmap/bitmap1.bmp"); //ù��° ��������Ʈ��(rt_explosion)  ��Ʈ�� �ε� 
	object_sprite.Set(100, 100, PSpriteManager::GetInstance().get_sprite_from_map(0)->sprite_rectlist_, 10, 1);
	//100,100��ǥ�� �Ŵ����� ������ �ִ� ��������Ʈ �� ù ��° ��������Ʈ�� ��Ʈ �����͸� �����ͼ� �����Ѵ�. 
	object_sprite.Render();
	

	return true;

}