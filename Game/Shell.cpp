#include "stdafx.h"
#include "Shell.h"
#include "Enemy2.h"
#include "Player.h"
#include "Game.h"
#include "Game2.h"

Shell::Shell()
{
	//モデルの読み込み
	m_shellRender.Init("Assets/modelData/turtle.tkm");
	m_shellRender.SetScale({ 2.0f,2.0f,2.0f });
	m_shellRot.SetRotationX(Math::DegToRad(180.0f));
	m_shellRender.SetRotation(m_shellRot);
	//プレイヤーのオブジェクトを持ってくる
	m_player = FindGO<Player>("player");
	//ノコノコのオブジェクトを持ってくる
	m_enemy2 = FindGO<Enemy2>("enemy2");
	if (m_enemy2)
	{
		m_shellPosition = m_enemy2->GetPosition();
	}
	else
	{
		m_shellPosition = Vector3::Zero;
	}
	m_game = FindGO<Game>("game");
	m_game2 = FindGO<Game2>("game2");
	//スフィアコライダーを初期化
	m_shellSpherCollider.Create(1.0f);
	m_shellPosition = m_shellPosition;
	//m_shellController.Init(20.0f, 1.0f, m_shellPosition);
}

Shell::~Shell()
{
	
}

void Shell::Update()
{
	if (m_die == 1)
	{
		DeleteGO(this);
		return;
	}
	if (m_safeTime > 0.0f)
	{
		m_safeTime -= m_deltaTime;
		if (m_safeTime < 0.0f)m_safeTime = 0.0f;
	}
	//移動処理
	Move();
	//絵描き更新処理
	m_shellRender.Update();
	m_shellRender.SetPosition(m_shellPosition);
}

struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		//壁とぶつかってなかったら
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall) {
			return 0.0f;
		}

		//壁とぶつかったら
		//フラグをtrueに
		isHit = true;
		return 0.0f;
	}
};

void Shell::Kick(const Vector3& dir)
{
	if (m_shellState != 0)return;
	m_shellState = 1;
	m_shellDirection = dir;
	if (m_shellDirection.LengthSq() > 0.001f)
	{
		m_shellDirection.Normalize();
	}
	m_safeTime = 0.3f;
}

//移動処理
void Shell::Move()
{
	Vector3 moveSpeed = Vector3::Zero;
	switch (m_shellState)
	{
	case 0:
		break;
	case 1:
		moveSpeed+= m_shellDirection * m_shellSpeed;
		break;
	}
	if (moveSpeed.LengthSq() < 0.001f)
	{
		//m_shellPosition = m_shellController.Execute(moveSpeed, m_deltaTime);
		return;
	}
	Vector3 totalMove = m_shellDirection * m_shellSpeed * m_deltaTime;
	int steps = int(totalMove.Length() / 10.0f) + 1;
	Vector3 stepMove = totalMove / (float)steps;
	for (int i = 0;i < steps;i++)
	{
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		start.setOrigin(btVector3(m_shellPosition.x, m_shellPosition.y, m_shellPosition.z));
		end.setOrigin(btVector3(m_shellPosition.x + stepMove.x, m_shellPosition.y + stepMove.y, m_shellPosition.z + stepMove.z));

		SweepResultWall callback;
		PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_shellSpherCollider.GetBody(), start, end, callback);
		if (callback.isHit == true)
		{
			m_die = 1;
			return;
		}
		m_shellPosition += stepMove;
	}
	m_die = 0;
	Vector3 visualMove = Vector3(m_shellDirection.x,0.0f,m_shellDirection.z) * m_shellSpeed * m_deltaTime;

	//m_shellPosition = m_shellController.Execute(moveSpeed, m_deltaTime);
	//m_shellPosition.y += 20.0f;
	m_shellRender.SetPosition(m_shellPosition+visualMove);
}

void Shell::SetPosition(const Vector3& position)
{
	m_shellPosition = position;
}

//描画処理
void Shell::Render(RenderContext& rc)
{
	m_shellRender.Draw(rc);
}