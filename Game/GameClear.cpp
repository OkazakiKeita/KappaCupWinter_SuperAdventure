#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Star.h"
#include "Game.h"
#include "Game2.h"
#include "GameCamera.h"
#include "sound/SoundEngine.h"
#include "BGM.h"

GameClear::GameClear()
{
	//ゲームクリア画面を読み込む
	m_spriteRender.Init("Assets/sprite/gameclear.dds", 1920.0f, 1080.0f);

	//タイトルBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(BGM_Clear, "Assets/sound/clearBGM.wav");
	//タイトルのBGMを再生。
	clearBGM = NewGO<SoundSource>(BGM_Clear);
	clearBGM->Init(BGM_Clear);
	clearBGM->Play(true);
}

GameClear::~GameClear()
{
	if (clearBGM)
	{
		clearBGM->Stop();
		DeleteGO(clearBGM);
		clearBGM = nullptr;
	}
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
