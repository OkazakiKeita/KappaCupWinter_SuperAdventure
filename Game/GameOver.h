#pragma once
class GameOver:public IGameObject
{
public:
	GameOver();
	~GameOver();
	//XVˆ—
	void Update();
	//•`‰æˆ—
	void Render(RenderContext& rc);

	SpriteRender m_GameOver;
};

