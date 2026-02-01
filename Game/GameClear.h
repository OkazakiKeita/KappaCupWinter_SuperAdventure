#pragma once
#include "sound/SoundSource.h"
class Game;

class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
	SoundSource* clearBGM;
};

