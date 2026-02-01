#pragma once

class Player;
//ゲーム中のカメラを制御
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	//スタート処理
	bool Start();
	//更新処理
	void Update();

	//メンバ変数
	Player* m_player;	//プレイヤー
	Vector3 m_toCameraPosition;	//注視点から視点に向かうベクトル
	Vector3 m_cameraPos;     // 現在のカメラ位置
	bool m_isFirst = true;   // 初回フラグ
};

