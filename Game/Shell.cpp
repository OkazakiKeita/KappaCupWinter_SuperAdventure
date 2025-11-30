#include "stdafx.h"
#include "Shell.h"
#include "Enemy2.h"
#include "Player.h"
#include "Game.h"

Shell::Shell()
{
	//モデルの読み込み
	m_shellRender.Init("Assets/modelData/koura.tkm");
	m_shellRender.SetScale({ 3.0f,3.0f,3.0f });
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
	//スフィアコライダーを初期化
	m_shellSpherCollider.Create(1.0f);
	m_shellPosition = m_shellPosition;
	//m_shellController.Init(30.0f, 1.0f, m_shellPosition);
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
	//移動処理
	Move();
	//ステート管理
	ManageState();
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

//ステート管理
void Shell::ManageState()
{
	if (!m_player || !m_game)return;
	float dist = (m_player->GetPosition() - m_shellPosition).Length();
	if (dist < 50.0f)
	{
		if (m_game && m_game->m_death == true && m_shellState == 0)
		{
			m_shellState = 1;
			//甲羅の位置をノコノコの位置に持ってくる
			//m_shellPosition = m_enemy2->GetPosition();
			m_shellDirection = m_player->GetForward();
			if (m_shellDirection.LengthSq() > 0.001f)
			{
				m_shellDirection.Normalize();
			}
			/*else
			{
				m_shellDirection = Vector3::AxisZ;
			}*/
		}
	}
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
	/*if (m_game->m_death == true)
	{
		m_shellRender.Draw(rc);
	}*/
	m_shellRender.Draw(rc);
}