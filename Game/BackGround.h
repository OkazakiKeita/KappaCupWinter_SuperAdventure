#pragma once
class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数
	ModelRender m_stageRender;	//描画
	PhysicsStaticObject m_physicsStaticObject;
};

