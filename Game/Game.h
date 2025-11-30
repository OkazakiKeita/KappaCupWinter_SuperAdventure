#pragma once

class Player;
class BackGround;
class GameCamera;
class Enemy1;
class Enemy2;
class Boss;
class Wall;
class Star;
class Shell;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	std::vector<Enemy1*>m_enemy1List;
	BackGround* m_backGround;
	Player* m_player;
	GameCamera* m_gameCamera;
	Enemy1* m_enemy1;
	Enemy2* m_enemy2;
	Boss* m_boss;
	Wall* m_wall;
	Star* m_star;
	Shell* m_shell;
	SkyCube* m_skyCube;
	ModelRender m_modelRender;
	FontRender m_timeRender;
	FontRender m_lifeRender;
	FontRender m_scoreRender;
	Vector3 m_setTime = { 700.0f,500.0f,0.0f };
	Vector3 m_setLife = { -900.0f,450.0f,0.0f };
	Vector3 m_setScore = { 700.0f,450.0f,0.0f };
	SpriteRender m_spriteRender1;
	SpriteRender m_spriteRender2;
	SpriteRender m_spriteRender3;

	float m_time = 101.0f;
	float m_invincible = 0.0f;
	float m_blinkTimer = 0.0f;	//点滅用タイマー
	bool m_isVisble = true;		//表示フラグ
	bool m_death = false;		//死亡フラグ
	int m_life = 3;
	int m_score = 0;
};

