#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Star.h"
#include "Game.h"
#include "GameCamera.h"

GameClear::GameClear()
{
	//ゲームクリア画面を読み込む
	m_spriteRender.Init("Assets/sprite/Gameclear.dds", 1920.0f, 1080.0f);
}

GameClear::~GameClear()
{

}

//更新処理
void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		DeleteGO(this);
		NewGO<Title>(0, "title");
		return;
	}
}

//描画処理
void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
