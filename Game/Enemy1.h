#pragma once

class Game;
class Player;

class Enemy1:public IGameObject
{
public:
	Enemy1();
	~Enemy1();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//プレイヤーを探す処理
	void SearchPlayer();
	//移動処理
	void Move();
	void SetPosition(const Vector3& pos);
	const Vector3& GetPosition()const
	{
		return m_enemy1Position;
	}
	
	//メンバ変数
	ModelRender m_enemy1Render;	//描画
	Vector3 m_enemy1FirstPosition={ 0.0f,250.0f,-150.0f };	//初期位置
	Vector3 m_enemy1Position;	//現在位置
	Vector3 m_enemy1Forward;	//向き（前方ベクトル）を保持
	Player* m_player = nullptr;	//プレイヤーへのポインタ
	bool m_isSearchPlayer = true;	//プレイヤーを探しているかどうかのフラグ
	CharacterController m_enemy1Controller;
	FontRender m_fontRender;
	SphereCollider m_sphereCollider;	//衝突判定
	RigidBody m_rigidBody;	//物理挙動に関する情報
	int m_moveState = 0;	//プレイヤーを探しているときの移動方向（0:右、1:左）
	//int PlayerState = 0;	//プレイヤーの状態
	float m_deltaTime = 1.0f / 60.0f;
	float m_gravity = 800.0f;
};

