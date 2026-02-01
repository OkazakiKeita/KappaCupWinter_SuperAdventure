#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "BGM.h"

Title::Title()
{
	//画像読み込み
	m_spriteRender.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);

	//タイトルBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(BGM_Title, "Assets/sound/titleBGM.wav");
	//タイトルのBGMを再生。
	titleBGM = NewGO<SoundSource>(BGM_Title);
	titleBGM->Init(BGM_Title);
	titleBGM->Play(true);
}

Title::~Title()
{
	if (titleBGM)
	{
		titleBGM->Stop();
		DeleteGO(titleBGM);
		titleBGM = nullptr;
	}
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
		return;
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}