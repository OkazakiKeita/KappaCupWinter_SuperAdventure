#pragma once
class Wall2 :public IGameObject
{
public:
	Wall2();
	~Wall2();
	//スタート処理
	bool Start();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

private:
	//メンバ変数
	ModelRender m_wall2Render;
	PhysicsStaticObject m_physicsStaticObject;
};

