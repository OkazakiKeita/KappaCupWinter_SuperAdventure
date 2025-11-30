#include "stdafx.h"
#include "Enemy1.h"
#include "Player.h"

Enemy1::Enemy1()
{
	//モデルの読み込み
	m_enemy1Render.Init("Assets/modelData/UnityChan.tkm");
	//初期位置
	m_enemy1Render.SetPosition(m_enemy1FirstPosition);
	//m_enemy1Render.SetScale(Vector3(2.0f, 2.0f, 2.0f));
	//プレイヤーオブジェクトを持ってくる
	m_player = FindGO<Player>("player");

	//スフィアコライダーを初期化
	m_sphereCollider.Create(1.0f);
	m_enemy1Position = m_enemy1FirstPosition;
	m_enemy1Controller.Init(25.0f, 75.0f, m_enemy1Position);
}

Enemy1::~Enemy1()
{

}

//更新処理
void Enemy1::Update()
{
	//移動処理
	Move();
	//プレイヤーを探す処理
	SearchPlayer();
	//絵描き更新処理
	m_enemy1Render.Update();
}

//衝突したときに呼ばれる関数オブジェクト（壁用）
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

//プレイヤー探索
void Enemy1::SearchPlayer()
{
	if (m_player == nullptr)return;
	m_isSearchPlayer = false;

	m_enemy1Forward = Vector3(0,0,-1);

	//敵の前方ベクトルとプレイヤーの方向とのベクトルの角度を計算
	Vector3 playerPosition = m_player->GetPosition();
	Vector3 diff = playerPosition - m_enemy1Position;

	diff.Normalize();
	float angle = acosf(diff.Dot(m_enemy1Forward));
	//プレイヤーが視界内にいなかったら
	if (Math::PI/3<= fabsf(angle))
	{
		//プレイヤーは見つかっていない
		return;
	}

	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	//始点はエネミーの座標
	start.setOrigin(btVector3(m_enemy1Position.x, m_enemy1Position.y + 70.0f, m_enemy1Position.z));
	//終点はプレイヤーの座標
	end.setOrigin(btVector3(playerPosition.x, playerPosition.y + 70.0f, playerPosition.z));

	SweepResultWall callback;
	//衝突するかどうか調べる
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(),start,end, callback);
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

void Enemy1::Move()
{
	Vector3 moveSpeed = Vector3::Zero;
	if (m_isSearchPlayer == true)
	{
		//moveStateが0の時
		if (m_moveState == 0)
		{
			//右に移動
			moveSpeed.x += 50.0f;
		}
		//moveStateが1の時
		else if (m_moveState == 1)
		{
			//左に移動
			moveSpeed.x -= 50.0f;
		}

		//x座標が初期座標x+500.0fを超えたら
		if (m_enemy1Position.x >= m_enemy1FirstPosition.x + 50.0f)
		{
			//moveStateを1にする
			m_moveState = 1;
		}
		//x座標が初期座標x-500.0fより下になったら
		else if (m_enemy1Position.x <= m_enemy1FirstPosition.x - 50.0f)
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
		Vector3 dir = playerPosition -m_enemy1Position;

		dir.y = 0.0f;	//高さ方向は無視

		//LengthSq()はベクトルの長さの二乗を返す（計算が軽い）
		//0.001fより大きいかどうかを判定することで、ほぼゼロベクトル（=同じ位置）ではないかをチェック
		if (dir.LengthSq() > 0.001f)
		{
			//ベクトルの長さを1にして、方向だけを保持した単位ベクトルに変換する
			dir.Normalize();
			//追跡速度
			const float chaseSpeed = 200.0f;
			//敵の現在位置に、方向ベクトル×速度を加算して移動
			moveSpeed += dir * chaseSpeed;
		}

		//プレイヤーとの距離が離れすぎると追跡を終了
		float dist = (playerPosition - m_enemy1Position).Length();
		if (dist > 2000.0f)
		{
			m_isSearchPlayer = false;
			return;
		}
	}
	if (m_enemy1Controller.IsOnGround())
	{
		
	}
	else
	{
		moveSpeed.y -= m_gravity;
	}
	m_enemy1Position = m_enemy1Controller.Execute(moveSpeed, m_deltaTime);
	//絵描きに座標を教える
	m_enemy1Render.SetPosition(m_enemy1Position);

	/*if (m_player != nullptr)
	{
		float dist = (m_player->GetPosition() - m_enemy1Position).Length();
		if (dist < 100.0f)
		{
			DeleteGO(m_player);
			m_player = nullptr;
		}
	}*/
}

void Enemy1::SetPosition(const Vector3& pos)
{
	m_enemy1Position = pos;
	m_enemy1FirstPosition = pos;
	m_enemy1Render.SetPosition(pos);
	m_enemy1Controller.SetPosition(pos);
}

void Enemy1::Render(RenderContext& rc)
{
	m_enemy1Render.Draw(rc);

	if (m_isSearchPlayer == false)
	{
		m_fontRender.SetText(L"Search");
	}
	else
	{
		m_fontRender.SetText(L"Find");
	}
	m_fontRender.Draw(rc);
}