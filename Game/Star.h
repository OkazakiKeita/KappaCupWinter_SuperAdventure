#pragma once

class Game;
class Player;
class Star:public IGameObject
{
public:
	Star();
	~Star();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//回転処理。
	void Rotation();
	//移動処理
	void Move();

	//メンバ変数
	ModelRender m_starRender;
	Vector3 m_starPosition;
	Quaternion m_starRotation;
	Player* m_player;
	int m_starCount = 0;
};

