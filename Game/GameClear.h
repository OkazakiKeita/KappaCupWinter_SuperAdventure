#pragma once
class Game;

class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	//XVˆ—
	void Update();
	//•`‰æˆ—
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
};

