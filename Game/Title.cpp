#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	//‰æ‘œ“Ç‚Ýž‚Ý
	m_spriteRender.Init("Assets/sprite/Title.dds", 1920.0f, 1080.0f);
}

Title::~Title()
{

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