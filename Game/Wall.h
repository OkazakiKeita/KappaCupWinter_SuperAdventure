#pragma once
class Wall:public IGameObject
{
public:
	Wall();
	~Wall();
	//スタート処理
	bool Start();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

private:
	//メンバ変数
	ModelRender m_wallRender;
	PhysicsStaticObject m_physicsStaticObject;
};

