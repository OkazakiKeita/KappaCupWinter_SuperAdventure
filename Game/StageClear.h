#pragma once
#include "sound/SoundSource.h"
class Game;

class StageClear :public IGameObject
{
public:
	StageClear();
	~StageClear();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
	SoundSource* clearBGM;
};

