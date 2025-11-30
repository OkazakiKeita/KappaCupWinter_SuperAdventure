#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定
	m_toCameraPosition.Set(0.0f, 150.0f, 250.0f);
	//プレイヤーのインスタンスを探す
	m_player = FindGO<Player>("player");

	//カメラのニアクリップとファークリップを設定
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(15000.0f);
	return true;
}

void GameCamera::Update()
{
	//カメラ更新
	//注視点を計算
	Vector3 target = m_player->m_playerPosition;
	//プレイヤーの足元からちょっと上を注視点とする
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPosition;
	//パッドの入力を使ってカメラを回す。
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	qRot.Apply(m_toCameraPosition);
	//X軸周りの回転
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPosition);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * y);
	qRot.Apply(m_toCameraPosition);
	//カメラの回転の上限をチェックする
	//注視点からの視点までのベクトルを正規化する
	//正規化すると、ベクトルの大きさが１になる
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ
	Vector3 toPosDir = m_toCameraPosition;
	toPosDir.Normalize();
	if (toPosDir.y < -0.2f)
	{
		//カメラが下向きすぎ
		m_toCameraPosition = toCameraPosOld;
	}

	//視点を計算する
	Vector3 pos = target + m_toCameraPosition;
	//メインカメラに注視点と視点を設定する
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新
	g_camera3D->Update();
}