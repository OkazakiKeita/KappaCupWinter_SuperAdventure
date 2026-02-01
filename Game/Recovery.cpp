#include "stdafx.h"
#include "Recovery.h"
#include "Player.h"

Recovery::Recovery()
{
	//モデルの読み込み
	m_recoveryRender.Init("Assets/modelData/Recovery.tkm");
	//初期位置
	m_recoveryRender.SetPosition(m_recoveryFirstPosition);
	m_recoveryRender.SetScale(Vector3(0.8f, 0.8f, 0.8f));
	//プレイヤーオブジェクトを持ってくる
	m_player = FindGO<Player>("player");

	//スフィアコライダーを初期化
	m_sphereCollider.Create(35.0f);
	m_recoveryPosition = m_recoveryFirstPosition;
	m_recoveryController.Init(40.0f, 60.0f, m_recoveryPosition);
}

Recovery::~Recovery()
{

}

void Recovery::Update()
{
	if (m_player == nullptr)
	{
		return;
	}
	Move();
	SearchPlayer();
	m_recoveryRender.Update();
}

struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;
	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		//壁とぶつかってなかったら
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall)
		{
			return 0.0f;
		}

		//壁とぶつかったら
		//フラグをtrueに
		isHit = true;
		return 0.0f;
	}
};

//プレイヤー探索
void Recovery::SearchPlayer()
{
	if (m_player == nullptr)return;
	m_isSearchPlayer = false;

	m_recoveryForward = Vector3(0, 0, 1);

	//敵の前方ベクトルとプレイヤーの方向とのベクトルの角度を計算
	Vector3 playerPosition = m_player->GetPosition();
	Vector3 diff = playerPosition - m_recoveryPosition;

	diff.Normalize();
	float angle = acosf(diff.Dot(m_recoveryForward));

	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	//視点はエネミー座標
	start.setOrigin(btVector3(m_recoveryPosition.x, m_recoveryPosition.y + 70.0f, m_recoveryPosition.z));
	//終点はプレイヤーの座標
	end.setOrigin(btVector3(playerPosition.x, playerPosition.y + 70.0f, playerPosition.z));

	SweepResultWall callback;
	//衝突するかどうか調べる
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(), start, end, callback);
	//壁と衝突した
	if (callback.isHit == true)
	{
		//プレイヤーは見つかっていない
		return;
	}

	//壁と衝突してない
	//プレイヤー見つけたフラグをtrueに
	m_isSearchPlayer = true;
}

void Recovery::Move()
{
	Vector3 moveSpeed = Vector3::Zero;
	if (m_isSearchPlayer == false)
	{
		//moveStateが0の時
		if (m_moveState == 0)
		{
			//右に移動
			moveSpeed.x += 100.0f;
		}
		//moveStateが1の時
		else if (m_moveState == 1)
		{
			//左に移動
			moveSpeed.x -= 100.0f;
		}

		//x座標が初期座標x+200.0fを超えたら
		if (m_recoveryPosition.x >= m_recoveryFirstPosition.x + 200.0f)
		{
			//moveStateを1にする
			m_moveState = 1;
		}
		//x座標が初期座標x-200.0fを超えたら
		else if (m_recoveryPosition.x <= m_recoveryFirstPosition.x - 200.0f)
		{
			//moveStateを0にする
			m_moveState = 0;
		}
	}
	else
	{
		//プレイヤーの位置取得
		Vector3 playerPosition = m_player->GetPosition();
		//方向ベクトルの計算
		Vector3 dir = playerPosition - m_recoveryPosition;

		dir.y = 0.0f;	//高さ方向は無視

		//LengthSq()はベクトルの長さの二乗を返す（計算が軽い）
		//0.001fより大きいかどうかを判定することで、ほぼゼロベクトル（=同じ位置)ではないかチェック
		if (dir.LengthSq() > 0.001f)
		{
			//ベクトルの長さを1にして、方向だけを保持した単位ベクトルに変換する
			dir.Normalize();
			//追跡速度
			const float chaseSpeed = 150.0f;
			//敵の現在位置に、方向ベクトル×速度を加算して移動
			moveSpeed += dir * chaseSpeed;
		}

		//プレイヤーとの距離が離れすぎると追跡を終了
		float dist = (playerPosition - m_recoveryPosition).Length();
		if (dist > 500.0f)
		{
			m_lostTimer += m_deltaTime;
			if (m_lostTimer > 0.5f)
			{
				m_isSearchPlayer = false;
				m_lostTimer = 0.0f;
			}
		}
		else
		{
			m_lostTimer = 0.0f;
		}
	}
	if (m_recoveryController.IsOnGround())
	{

	}
	else
	{
		moveSpeed.y -= m_gravity;
	}
	m_recoveryPosition = m_recoveryController.Execute(moveSpeed, m_deltaTime);
	//絵描きに座標を教える
	m_recoveryRender.SetPosition(m_recoveryPosition);
}

void Recovery::SetPosition(const Vector3& pos)
{
	m_recoveryPosition = pos;
	m_recoveryFirstPosition = pos;
	m_recoveryRender.SetPosition(pos);
	m_recoveryController.SetPosition(pos);
}

void Recovery::Render(RenderContext& rc)
{
	m_recoveryRender.Draw(rc);
}
