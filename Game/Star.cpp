#include "stdafx.h"
#include "Star.h"
#include "Player.h"

Star::Star()
{
	//モデルの読み込み。
	m_starRender.Init("Assets/modelData/star.tkm");

	//プレイヤーのオブジェクトを探して持ってくる
	m_player = FindGO<Player>("player");
}

Star::~Star()
{
	
}

//更新処理
void Star::Update()
{
	//回転処理
	Rotation();

	//移動処理
	Move();

	//絵描き更新処理
	m_starRender.Update();

	//プレイヤーからスターに向かうベクトルを計算
	Vector3 diff = m_player->m_playerPosition - m_starPosition;
	//ベクトルの長さ50.0fより小さかったら
	if (diff.Length() <= 50.0f)
	{
		//自身を消す
		DeleteGO(this);
		m_starCount += 1;
		return;
	}
}

//移動処理
void Star::Move()
{
	//絵描きに座標を教える
	m_starRender.SetPosition(m_starPosition);
}

//回転処理
void Star::Rotation()
{
	//回転を加算する
	m_starRotation.AddRotationDegY(2.0f);

	//絵描きに回転を教える
	m_starRender.SetRotation(m_starRotation);
}

//描画処理
void Star::Render(RenderContext& rc)
{
	//描画する
	m_starRender.Draw(rc);
}