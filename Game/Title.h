#pragma once
class Title:public IGameObject
{
public:
	Title();
	~Title();
	//•`‰æŠÖ”B
	void Render(RenderContext& rc);
	//XVˆ—
	void Update();

	SpriteRender m_spriteRender;
};

