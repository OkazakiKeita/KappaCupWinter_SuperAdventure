#pragma once

class Game;
class Player;

class Boss :public IGameObject
{
public:
	Boss();
	~Boss();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//プレイヤーをさがす処理
	void SearchPlayer();
	//移動処理
	void Move();

	//メンバ変数
	ModelRender m_bossRender;	//描画
	Vector3 m_bossFirstPosition = { 0.0f,0.0f,-800.0f };	//初期位置
	Vector3 m_bossPosition;	//現在位置
	Vector3 m_bossForward;	//向き（前方ベクトル）を保持
	Player* m_player = nullptr;	//プレイヤーへのポインタ
	bool m_isSearchPlayer = false;	//プレイヤーを探しているかどうかのフラグ
	CharacterController m_bossController;
	SphereCollider m_sphereCollider;	//衝突判定
	RigidBody m_rigidBody;	//物理挙動に関する情報
	int m_moveState = 0;	//移動方向や状態の管理
	int m_jumpTimer = 0;	//ジャンプのタイミングを計るタイマー
	const int jumpInterval = 180;	//ジャンプの間隔
	bool m_isJumping = false;	//現在ジャンプ中かどうか
	float m_jumpVelocity = 0.0f;	//ジャンプの速度
	float m_deltaTime = 1.0f / 60.0f;
};

