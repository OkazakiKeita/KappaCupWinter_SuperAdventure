#pragma once

class Game;
class Player;
class Enemy1;
class Enemy2;

class Shell :public IGameObject
{
public:
	Shell();
	~Shell();
	void Update();
	void Render(RenderContext&rc);
	//移動処理
	void Move();
	//ステート管理
	void ManageState();
	void SetPosition(const Vector3& position);
	const Vector3& GetPosition()const
	{
		return m_shellPosition;
	}

	//メンバ変数
	ModelRender m_shellRender;	//描画
	Vector3 m_shellPosition;	//現在位置
	Vector3 m_shellDirection;
	//CharacterController m_shellController;
	SphereCollider m_shellSpherCollider;	//衝突判定
	RigidBody m_shellRigidBody;	//物理挙動に関する情報
	Player* m_player;
	Enemy1* m_enemy1;
	Enemy2* m_enemy2;
	Game* m_game;

	int m_die = 0;
	int m_shellState = 0;	//ステート管理
	float m_shellSpeed = 500.0f;	//甲羅のスピード
	//float m_hitDistance = 50.0f;
	float m_deltaTime = 1.0f / 60.0f;
	float m_gravity = 800.0f;
};

