#pragma once
#include "sound/SoundSource.h"
#include "SE.h"
#include <array>

class Player;
class Stage2;
class GameCamera;
class Enemy1;
class Enemy2;
class Boss;
class Recovery;
class Wall2;
class Star;
class Shell;

class Game2 : public IGameObject
{
public:
	Game2();
	~Game2();
	//更新処理
	void Update();
	void DrawNumber(RenderContext& rc,
		int value,
		const Vector3& startPos,
		float digitSpace,
		int minDigits,
		int slotBase,
		int slotCount);
	void UpdateDigits();
	//描画処理
	void Render(RenderContext& rc);

	std::vector<Enemy1*>m_enemy1List;
	std::vector<Enemy2*>m_enemy2List;
	std::vector<Recovery*>m_recoveryList;
	std::vector<Shell*>m_shells;
	Stage2* m_stage2;
	Player* m_player;
	GameCamera* m_gameCamera;
	Enemy1* m_enemy1;
	Enemy2* m_enemy2;
	Boss* m_boss;
	Recovery* m_recovery;
	Wall2* m_wall2;
	Star* m_star;
	Shell* m_shell;
	SkyCube* m_skyCube;
	SoundSource* gameBGM;
	SoundSource* m_jumpSE = nullptr;
	ModelRender m_modelRender;
	SpriteRender m_spriteRender1;
	SpriteRender m_spriteRender2;
	SpriteRender m_spriteRender3;
	SpriteRender m_scoreSprite;
	SpriteRender m_timeSprite;
	std::array<SpriteRender, 10>m_digits;
	Vector3 m_digitScale = { 10.0f,8.0f,10.0f };
	Vector3 m_scoreStartPos = { 800.0f,400.0f,0.0f };
	Vector3 m_timeStartPos = { 825.0f,500.0f,0.0f };

	static constexpr int kMaxNumberDigits = 10;
	static constexpr int kTimeDigits = 3;
	static constexpr int kScoreDigits = 4;
	static constexpr int kTimeSlotBase = 0;
	static constexpr int kScoreSlotBase = 4;
	std::array<SpriteRender, kMaxNumberDigits>m_digitSlots;
	std::array<int, kMaxNumberDigits>m_digitSlotPrev;
	float m_scoreDigitSpace = 30.0f;
	float m_timeDigitSpace = 30.0f;
	float m_time = 201.0f;
	float m_invincible = 0.0f;
	float m_blinkTimer = 0.0f;	//点滅用タイマー
	bool m_isVisble = true;		//表示フラグ
	bool m_death = false;		//死亡フラグ
	int m_life = 3;
	int m_score = 0;
	int m_bossLife = 5;
};


