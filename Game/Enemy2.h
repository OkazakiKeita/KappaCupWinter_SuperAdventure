#pragma once

class Game;
class Player;

class Enemy2 :public IGameObject
{
public:
	Enemy2();
	~Enemy2();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//プレイヤーを見つける処理
	void SearchPlayer();
	//移動処理
	void Move();
	const Vector3& GetPosition()const
	{
		return m_enemy2Position;
	}

	//メンバ変数
	ModelRender m_enemy2Render;	//描画
	Vector3 m_enemy2FirstPosition = { 0.0f,0.0f,-800.0f };	//初期位置
	Vector3 m_enemy2Position;	//現在位置
	Vector3 m_enemy2Forward;	//向き（前方ベクトル）を保持
	Player* m_player = nullptr;	//プレイヤーへのポインタ
	bool m_isSearchPlayer = false;	//プレイヤーを探しているかどうかのフラグ
	CharacterController m_enemy2Controller;
	SphereCollider m_sphereCollider;	//衝突判定
	RigidBody m_rigidBody;	//物理挙動に関する情報
	int m_moveState = 0;	//プレイヤーを探しているときの移動方向（0:右、1:左）
	float m_deltaTime = 1.0f / 60.0f;
	float m_gravity = 800.0f;
};

