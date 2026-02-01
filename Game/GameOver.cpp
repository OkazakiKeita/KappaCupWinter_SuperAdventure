#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "sound/SoundEngine.h"
#include "BGM.h"

GameOver::GameOver()
{
	m_GameOver.Init("Assets/sprite/GameOver.dds", 1920.0f, 1080.0f);

	//タイトルBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(BGM_GameOver, "Assets/sound/gameover.wav");
	//タイトルのBGMを再生。
	gameoverBGM = NewGO<SoundSource>(BGM_GameOver);
	gameoverBGM->Init(BGM_GameOver);
	gameoverBGM->Play(true);
}

GameOver::~GameOver()
{
	if (gameoverBGM)
	{
		gameoverBGM->Stop();
		DeleteGO(gameoverBGM);
		gameoverBGM = nullptr;
	}
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