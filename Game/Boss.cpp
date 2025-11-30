#include "stdafx.h"
#include "Boss.h"
#include "Player.h"

Boss::Boss()
{
	//モデルの読み込み
	m_bossRender.Init("Assets/modelData/UnityChan.tkm");
	//初期位置
	m_bossRender.SetPosition(m_bossPosition);
	//スケール設定
	m_bossRender.SetScale(Vector3(2.0f, 2.0f, 2.0f));
	//プレイヤーオブジェクトを持ってくる
	m_player = FindGO<Player>("player");

	//スフィアコライダーを初期化
	m_sphereCollider.Create(1.0f);
	m_bossPosition = m_bossFirstPosition;
	m_bossController.Init(50.0f, 150.0f, m_bossPosition);
}

Boss::~Boss()
{

}

//更新処理
void Boss::Update()
{
	//移動処理
	Move();
	//プレイヤーを探す処理
	SearchPlayer();
	//絵描き更新処理
	m_bossRender.Update();
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
void Boss::SearchPlayer()
{
	m_isSearchPlayer = false;

	m_bossForward = Vector3::AxisZ;

	//敵の前方ベクトルとプレイヤーの方向とのベクトルの角度を計算
	Vector3 playerPosition = m_player->GetPosition();
	Vector3 diff = playerPosition - m_bossFirstPosition;

	diff.Normalize();
	float angle = acosf(diff.Dot(m_bossForward));
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
	start.setOrigin(btVector3(m_bossPosition.x, m_bossPosition.y + 70.0f, m_bossPosition.z));
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

void Boss::Move()
{
	Vector3 moveSpeed = Vector3::Zero;
	//ジャンプタイマー更新
	m_jumpTimer++;

	//ジャンプ開始判定
	if (m_jumpTimer >= jumpInterval && !m_isJumping)
	{
		//上昇速度の設定
		m_jumpVelocity = 20.0f;
		m_isJumping = true;
		m_jumpTimer = 0;
	}
	//ジャンプ中の処理
	if (m_isJumping)
	{
		m_bossPosition.y += m_jumpVelocity;
		m_jumpVelocity -= 1.0f;//重力のような減速

		//着地したらジャンプ終了
		if (m_bossPosition.y <= 0.0f)
		{
			m_bossPosition.y = 0.0f;
			m_isJumping = false;
			m_jumpVelocity = 0.0f;
		}
	}

	if (m_isSearchPlayer == false)
	{
		//moveStateが0の時
		if (m_moveState == 0)
		{
			//右に移動
			moveSpeed.x += 500.0f;
		}
		//moveStatが1の時
		else if (m_moveState == 1)
		{
			//左に移動
			moveSpeed.x -= 500.0f;
		}
		//x座標が初期座標x+500.0fを超えたら
		if (m_bossPosition.x >= m_bossFirstPosition.x + 500.0f)
		{
			//moveStateを1にする
			m_moveState = 1;
		}
		//x座標が初期座標x-500.0fより下になったら
		else if (m_bossPosition.x <= m_bossFirstPosition.x - 500.0f)
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
		Vector3 dir = playerPosition - m_bossPosition;

		dir.y = 0.0f;	//高さ方向は無視

		//プレイヤーとの距離を測定
		float currentDist = dir.Length();
		//目標距離
		const float targetDist = 500.0f;
		//誤差許容範囲
		const float tolerance = 10.0f;
		//移動速度調整
		const float adjustSpeed = 500.0f;
		
		//距離が遠すぎる
		if (currentDist > targetDist + tolerance)
		{
			//プレイヤーに近づく
			dir.Normalize();
			moveSpeed += dir * adjustSpeed;
		}
		//距離が近すぎる
		else if (currentDist < targetDist - tolerance)
		{
			//プレイヤーから離れる
			dir.Normalize();
			moveSpeed -= dir * adjustSpeed;
		}
	}
	m_bossPosition = m_bossController.Execute(moveSpeed, m_deltaTime);
	//絵描きに座標を教える
	m_bossRender.SetPosition(m_bossPosition);
}

void Boss::Render(RenderContext& rc)
{
	m_bossRender.Draw(rc);
}