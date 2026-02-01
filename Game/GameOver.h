#pragma once
#include "sound/SoundSource.h"
class GameOver:public IGameObject
{
public:
	GameOver();
	~GameOver();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	SpriteRender m_GameOver;
	SoundSource* gameoverBGM;
};

