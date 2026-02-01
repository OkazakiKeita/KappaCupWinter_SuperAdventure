#pragma once
class Game;
class Game2;
class Player;

class Recovery:public IGameObject
{
public:
	Recovery();
	~Recovery();
	void Update();
	void Render(RenderContext& rc);
	void SearchPlayer();
	void Move();
	void SetPosition(const Vector3& pos);
	const Vector3& GetPosition()const
	{
		return m_recoveryPosition;
	}

	ModelRender m_recoveryRender;
	Vector3 m_recoveryFirstPosition;
	Vector3 m_recoveryPosition;
	Vector3 m_recoveryForward;
	Player* m_player = nullptr;
	CharacterController m_recoveryController;
	SphereCollider m_sphereCollider;
	RigidBody m_rigidBody;

	bool m_isSearchPlayer = false;
	int m_moveState = 0;
	float m_deltaTime = 1.0f / 60.0f;
	float m_gravity = 300.0f;
	float m_lostTimer = 0.0f;
};

