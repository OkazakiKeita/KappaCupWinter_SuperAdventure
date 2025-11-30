#include "stdafx.h"
#include "Enemy2.h"
#include "Player.h"

Enemy2::Enemy2()
{
	//モデルの読み込み
	m_enemy2Render.Init("Assets/modelData/UnityChan.tkm");
	//初期位置
	m_enemy2Render.SetPosition(m_enemy2FirstPosition);
	//プレイヤーオブジェクトを持ってくる
	m_player = FindGO<Player>("player");

	//スフィアコライダーを初期化
	m_sphereCollider.Create(1.0f);
	m_enemy2Position = m_enemy2FirstPosition;
	m_enemy2Controller.Init(25.0f, 75.0f, m_enemy2Position);
}

Enemy2::~Enemy2()
{

}

//更新処理
void Enemy2::Update()
{
	if (m_player == nullptr)
	{
		return;
	}
	//移動処理
	//Move();
	//見つける処理
	SearchPlayer();
	//絵描き更新処理
	m_enemy2Render.Update();
}

//衝突したときに呼ばれる関数オブジェクト（壁用）
struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		//壁とぶつかっってなかったら
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
void Enemy2::SearchPlayer()
{
	m_isSearchPlayer = false;
	
	m_enemy2Forward = Vector3::AxisZ;

	//敵の前方ベクトルとプレイヤーの方向とのベクトルの角度を計算
	Vector3 playerPosition = m_player->GetPosition();
	Vector3 diff = playerPosition - m_enemy2FirstPosition;

	diff.Normalize();
	float angle = acosf(diff.Dot(m_enemy2Forward));
	//プレイヤーが視界内にいなかったら
	if (Math::PI * 0.35f <= fabsf(angle))
	{
		//プレイヤーは見つかっていない
		return;
	}

	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	//視点はエネミーの座標
	start.setOrigin(btVector3(m_enemy2Position.x, m_enemy2Position.y + 70.0f, m_enemy2Position.z));
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

void Enemy2::Move()
{
	Vector3 moveSpeed = Vector3::Zero;
	if (m_isSearchPlayer == false)
	{
		//moveStateが0の時
		if (m_moveState == 0)
		{
			//右に移動
			moveSpeed.x += 500.0f;
		}
		//moveStateが1の時
		else if (m_moveState == 1)
		{
			//左に移動
			moveSpeed.x -= 500.0f;
		}

		//x座標が初期座標x+100.0fを超えたら
		if (m_enemy2Position.x >= m_enemy2FirstPosition.x + 500.0f)
		{
			//moveStateを1にする
			m_moveState = 1;
		}
		//x座標が初期座標x-100.0fより下になったら
		else if (m_enemy2Position.x <= m_enemy2FirstPosition.x - 500.0f)
		{
			//moveStateを０にする
			m_moveState = 0;
		}
	}
	else
	{
		//プレイヤーの位置取得
		Vector3 playerPosition = m_player->GetPosition();
		//方向ベクトルの計算
		Vector3 dir = playerPosition - m_enemy2Position;

		dir.y = 0.0f;	//高さ方向は無視

		//LengthSq()はベクトルの長さの二乗を返す
		//0.001fより多きかどうかを判定することで、ほぼゼロベクトル（=同じ位置）ではないかをチェック
		if (dir.LengthSq() > 0.001f)
		{
			//ベクトルの長さを1にして、方向だけを保持した単位ベクトルに変換する
			dir.Normalize();
			//追跡速度
			const float chaseSpeed = 300.0f;
			//敵の現在位置に、方向ベクトル×速度を加算して移動
			moveSpeed += dir * chaseSpeed;
		}

		//プレイヤーとの距離が離れすぎると追跡を終了
		float dist = (playerPosition - m_enemy2Position).Length();
		if (dist > 2000.0f)
		{
			m_isSearchPlayer = false;
		}
	}
	if (m_enemy2Controller.IsOnGround())
	{

	}
	else
	{
		moveSpeed.y -= m_gravity;
	}
	m_enemy2Position = m_enemy2Controller.Execute(moveSpeed, m_deltaTime);
	//絵描きに座標を教える
	m_enemy2Render.SetPosition(m_enemy2Position);
}

void Enemy2::Render(RenderContext& rc)
{
	m_enemy2Render.Draw(rc);
}