#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"

GameOver::GameOver()
{
	m_GameOver.Init("Assets/sprite/GameOver.dds", 1920.0f, 1080.0f);
}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//タイトルオブジェクトを作る
		NewGO<Title>(0, "title");
		//自身を削除
		DeleteGO(this);
		return;
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_GameOver.Draw(rc);
}