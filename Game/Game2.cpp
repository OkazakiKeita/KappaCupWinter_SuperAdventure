#include "stdafx.h"
#include "Game2.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Boss.h"
#include "Recovery.h"
#include "Wall2.h"
#include "Star.h"
#include "Shell.h"
#include "GameOver.h"
#include "GameClear.h"
#include "Stage2.h"
#include "sound/SoundEngine.h"
#include "BGM.h"
#include "SE.h"
#include <string>

Game2::Game2()
{
	Vector3 enemy1SpawnPosition[] = {
		{-9.1f,0.1f,-3905.8},
		{-9.1f,0.1f,-4301.8},
		{2732.8f,3.9f,-5409.3f},
		{-2787.8f,0.1f,-9000.0f},
		{-2787.8f,0.1f,-10000.0f},
		{-2787.8f,0.1f,-11000.0f},
		{-2787.8f,0.1f,-11500.0f},
		{-2787.8f,0.1f,-12000.0f},
		{-2787.8f,0.1f,-14500.0f},
		{2746.9f,0.1f,-15000.0f},
		{2746.9f,0.1f,-14000.0f},
		{2746.9f,0.1f,-12000.0f},
		{2746.9f,0.1f,-10000.0f},
		{-2806.9f,3.9f,-20125.8f},
		{-2798.5f,0.1f,-28000.0f},
		{-2798.5f,0.1f,-28500.0f},
		{-2798.5f,0.1f,-29000.0f},
		{2741.4f,3.9f,-20120.2f},
		{2741.4f,0.1f,-22000.0f},
		{2741.4f,0.1f,-23000.0f},
		{2741.4f,0.1f,-30000.0f},
		{-27960.0f,3.9f,-34879.7f},
		{-2803.2f,0.1f,-37000.0f},
		{-2803.2f,0.1f,-37500.0f},
		{-2803.2f,0.1f,-39500.0f},
		{-2803.2f,0.1f,-45000.0f},
		{2777.8f,0.1f,-36010.0f},
		{2777.8f,0.1f,-37000.0f},
		{2777.8f,0.1f,-37500.0f},
		{2777.8f,0.1f,-44000.0f},
		{0.0f,3.9f,-51000.0f},
		{250.0f,3.9f,-51000.0f},
		{500.0f,3.9f,-51000.0f},
		{-250.0f,3.9f,-51000.0f},
		{-500.0f,3.9f,-51000.0f},
	};
	Vector3 enemy2SpawnPosition[] = {
		{-2787.8f,3.9f,-5396.7f},
		{-2798.5f,0.1f,-23012.3f},
		{-2798.5f,0.1f,-23500.0f},
		{2741.4f,0.1f,-28000.0f},
		{-2803.2f,0.1f,-38000.0f},
		{-2803.2f,0.1f,-40000.0f},
		{-2803.2f,0.1f,-40500.0f},
		{2752.6f,3.9f,-34871.2f},
		{2777.8f,0.1f,-39000.0f},
	};
	Vector3 recoverySpawnPosition[]
	{
		{-2787.8f,0.1f,-14000.0f},
		{-2803.2f,0.1f,-39000.0f }
	};
	//ステージ
	m_stage2 = NewGO<Stage2>(0, "stage2");
	//キャラクター
	m_player = NewGO<Player>(0, "player");
	//ゲームカメラのオブジェクト
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//エネミー1
	for (int i = 0;i < 35;i++)
	{
		Enemy1* enemy1 = NewGO<Enemy1>(0, "enemy1");
		enemy1->SetPosition(enemy1SpawnPosition[i]);
		m_enemy1List.push_back(enemy1);
	}
	//エネミー2
	for (int i = 0;i < 9;i++)
	{
		Enemy2* enemy2 = NewGO<Enemy2>(0, "enemy2");
		enemy2->SetPosition(enemy2SpawnPosition[i]);
		m_enemy2List.push_back(enemy2);
	}
	//ボス
	m_boss = NewGO<Boss>(0, "boss");
	//回復エネミー
	for (int i = 0;i < 2;i++)
	{
		Recovery* recovery = NewGO < Recovery>(0, "recovery");
		recovery->SetPosition(recoverySpawnPosition[i]);
		m_recoveryList.push_back(recovery);
	}
	//壁
	m_wall2 = NewGO<Wall2>(0, "wall2");
	//空のオブジェクト
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	//スター
	m_star = NewGO<Star>(0, "star");
	m_star->m_starPosition = { 0.0f,200.0f,-54792.7f };

	m_spriteRender1.Init("Assets/sprite/hart.dds", 512.0f, 512.0f);
	m_spriteRender1.SetScale(Vector3{ 0.2f,0.15f,0.2f });
	m_spriteRender1.SetPosition({ -900.0f,450.0f,0.0f });
	m_spriteRender2.Init("Assets/sprite/hart.dds", 512.0f, 512.0f);
	m_spriteRender2.SetScale(Vector3{ 0.2f,0.15f,0.2f });
	m_spriteRender2.SetPosition({ -800.0f,450.0f,0.0f });
	m_spriteRender3.Init("Assets/sprite/hart.dds", 512.0f, 512.0f);
	m_spriteRender3.SetScale(Vector3{ 0.2f,0.15f,0.2f });
	m_spriteRender3.SetPosition({ -700.0f,450.0f,0.0f });
	m_scoreSprite.Init("Assets/sprite/Score.dds", 64.0f, 64.0f);
	m_scoreSprite.SetScale(Vector3{ 10.0f,8.0f,10.0f });
	m_scoreSprite.SetPosition({ 700.0f,400.0f,0.0f });
	m_timeSprite.Init("Assets/sprite/TimeLimit.dds", 64.0f, 64.0f);
	m_timeSprite.SetScale(Vector3{ 10.0f,8.0f,10.0f });
	m_timeSprite.SetPosition({ 700.0f,500.0f,0.0f });
	for (int i = 0;i < 10;i++)
	{
		char path[128];
		sprintf_s(path, "Assets/sprite/font%d.dds", i);
		m_digits[i].Init(path, 64.0f, 64.0f);
		m_digits[i].SetScale(m_digitScale);
	}
	for (int i = 0;i < kMaxNumberDigits;i++)
	{
		m_digitSlots[i].Init("Assets/sprite/font0.dds", 64.0f, 64.0f);
		m_digitSlots[i].SetScale(m_digitScale);
	}

	g_soundEngine->ResistWaveFileBank(BGM_Stage2, "Assets/sound/stage2BGM.wav");
	gameBGM = NewGO<SoundSource>(BGM_Stage2);
	gameBGM->Init(BGM_Stage2);
	gameBGM->Play(true);

	g_soundEngine->ResistWaveFileBank(SE_Jump, "Assets/sound/jump.wav");

	m_digitSlotPrev.fill(-1);
}

Game2::~Game2()
{
	DeleteGO(m_stage2);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	for (auto* enemy1 : m_enemy1List)
	{
		DeleteGO(enemy1);
	}
	m_enemy1List.clear();
	for (auto* enemy2 : m_enemy2List)
	{
		DeleteGO(enemy2);
	}
	m_enemy2List.clear();
	DeleteGO(m_boss);
	for (auto* recovery : m_recoveryList)
	{
		DeleteGO(recovery);
	}
	m_recoveryList.clear();
	DeleteGO(m_wall2);
	DeleteGO(m_star);
	DeleteGO(m_skyCube);
	for (auto* sh : m_shells)
	{
		DeleteGO(sh);
	}
	m_shells.clear();
	if (gameBGM)
	{
		gameBGM->Stop();
		DeleteGO(gameBGM);
		gameBGM = nullptr;
	}
	if (m_jumpSE)
	{
		DeleteGO(m_jumpSE);
		m_jumpSE = nullptr;
	}
}

void Game2::Update()
{
	if (m_player == nullptr)
	{
		return;
	}
	m_time -= g_gameTime->GetFrameDeltaTime();

	if (m_player != nullptr)
	{
		if (m_player->m_playerPosition.y < -1000.0f)
		{
			NewGO<GameOver>(0, "gameover");
			DeleteGO(this);
			return;
		}
	}
	if (m_invincible > 0.0f)
	{
		m_invincible -= g_gameTime->GetFrameDeltaTime();
		if (m_invincible < 0.0f)m_invincible = 0.0f;
	}
	for (auto it = m_enemy1List.begin();it != m_enemy1List.end();)
	{
		Enemy1* enemy = *it;
		enemy->Update();
		Vector3 diff = m_player->GetPosition() - enemy->GetPosition();
		float distXZ = sqrtf(diff.x * diff.x + diff.z * diff.z);
		float heightDiff = m_player->GetPosition().y - enemy->GetPosition().y;
		float stompMinHeight = 5.0f;
		float stompMaxHeight = 50.0f;
		if (m_invincible <= 0.0f)
		{
			if (distXZ < 65.0f && fabsf(heightDiff) < 20.0f)
			{
				m_life -= 1;
				m_invincible = 1.5f;
				if (m_life == 0)
				{
					DeleteGO(m_player);
					NewGO<GameOver>(0, "gameover");
					DeleteGO(this);
					m_player = nullptr;
					return;
				}
			}
		}
		if (distXZ< 60.0f && heightDiff>stompMinHeight && heightDiff < stompMaxHeight && m_player->m_playerMoveSpeed.y < 0)
		{
			DeleteGO(enemy);
			it = m_enemy1List.erase(it);
			m_player->m_playerMoveSpeed.y = 2000.0f;
			m_score += 100;
			SoundSource* se = NewGO<SoundSource>(SE_Jump);
			se->Init(SE_Jump);
			se->Play(false);
			continue;
		}
		++it;
	}
	for (auto it = m_enemy2List.begin(); it != m_enemy2List.end(); )
	{
		Enemy2* enemy = *it;

		Vector3 diff = m_player->GetPosition() - enemy->GetPosition();
		float distXZ = sqrtf(diff.x * diff.x + diff.z * diff.z);
		float heightDiff = m_player->GetPosition().y - enemy->GetPosition().y;

		float stompMinHeight = 25.0f;
		float stompMaxHeight = 80.0f;

		// ダメージ
		if (m_invincible <= 0.0f &&
			distXZ < 80.0f &&
			heightDiff < stompMinHeight)
		{
			m_life--;
			m_invincible = 1.5f;

			if (m_life == 0)
			{
				DeleteGO(m_player);
				NewGO<GameOver>(0, "gameover");
				DeleteGO(this);
				m_player = nullptr;
				return;
			}
		}

		// 踏みつけ
		if (distXZ < 60.0f &&
			heightDiff > stompMinHeight &&
			heightDiff < stompMaxHeight &&
			m_player->m_playerMoveSpeed.y < 0)
		{
			Vector3 pos = enemy->GetPosition();
			pos.y += 45.0f;

			Shell* sh = NewGO<Shell>(0, "shell");
			sh->SetPosition(pos);
			sh->Kick(m_player->GetForward());
			m_shells.push_back(sh);

			DeleteGO(enemy);
			it = m_enemy2List.erase(it);
			m_player->m_playerMoveSpeed.y = 2000.0f;
			m_score += 100;
			SoundSource* se = NewGO<SoundSource>(SE_Jump);
			se->Init(SE_Jump);
			se->Play(false);
			continue;
		}

		++it;
	}
	for (auto it = m_recoveryList.begin();it != m_recoveryList.end();)
	{
		Recovery* recovery = *it;
		recovery->Update();
		Vector3 diff = m_player->GetPosition() - recovery->GetPosition();
		float distXZ = sqrtf(diff.x * diff.x + diff.z * diff.z);
		float hightDiff = m_player->GetPosition().y - recovery->GetPosition().y;
		float stompMinHeight = 5.0f;
		float stompMaxHeight = 50.0f;
		if (m_invincible <= 0.0f)
		{
			if (distXZ < 65.0f && fabsf(hightDiff) < 20.0f)
			{
				m_life -= 1;
				m_invincible = 1.5f;
				if (m_life == 0)
				{
					DeleteGO(m_player);
					NewGO<GameOver>(0, "gameover");
					DeleteGO(this);
					m_player = nullptr;
					return;
				}
			}

			if (distXZ<60.0f && hightDiff>stompMinHeight && hightDiff < stompMaxHeight && m_player->m_playerMoveSpeed.y < 0)
			{
				DeleteGO(recovery);
				it = m_recoveryList.erase(it);
				m_player->m_playerMoveSpeed.y = 2000.0f;
				if (m_life == 3)
				{
					m_score += 300;
				}
				else
				{
					m_life += 1;
				}
				SoundSource* se = NewGO<SoundSource>(SE_Jump);
				se->Init(SE_Jump);
				se->Play(false);
				continue;
			}
		}
		++it;
	}
	if (!m_shells.empty())
	{
		std::vector<Enemy1*>enemiesToDelete;
		for (auto* sh : m_shells)
		{
			if (sh == nullptr)continue;
			const Vector3 shellPos = sh->GetPosition();
			for (auto* enemy : m_enemy1List)
			{
				if (enemy == nullptr)continue;
				float dist = (enemy->GetPosition() - shellPos).Length();
				if (dist < 80.0f)
				{
					enemiesToDelete.push_back(enemy);
				}
			}
		}
		if (!enemiesToDelete.empty())
		{
			for (Enemy1* e : enemiesToDelete)
			{
				auto itE = std::find(m_enemy1List.begin(), m_enemy1List.end(), e);
				if (itE != m_enemy1List.end())
				{
					m_enemy1List.erase(itE);
					DeleteGO(e);
					m_score += 100;
				}
			}
		}
		if (m_invincible <= 0.0f)
		{
			for (auto* sh : m_shells)
			{
				if (sh == nullptr)continue;
				if (sh->m_shellState == 1 && sh->m_safeTime <= 0.0f)
				{
					float dist = (m_player->GetPosition() - sh->GetPosition()).Length();
					if (dist < 60.0f)
					{
						m_life -= 1;
						m_invincible = 1.5f;
						if (m_life == 0)
						{
							DeleteGO(m_player);
							NewGO<GameOver>(0, "gameover");
							DeleteGO(this);
							m_player = nullptr;
							return;
						}
						break;
					}
				}
			}
		}
	}

	if (m_player != nullptr&&m_boss!=nullptr)
	{
		Vector3 pdiff = m_player->GetPosition() - m_boss->GetPosition();
		float dist3XZ = sqrt(pdiff.x * pdiff.x + pdiff.z * pdiff.z);
		float diffY = m_player->m_playerPosition.y - m_boss->m_bossPosition.y;

		const float bossHitXZ = 80.0f;
		const float bossHitY = 120.0f;
		if (m_player->m_jump == 0)
		{
			if (m_invincible <= 0.0f)
			{
				if (dist3XZ<bossHitXZ&&abs(diffY)<=bossHitY)
				{
						m_life -= 1;
						m_invincible = 1.5f;
						if (m_life == 0)
						{
							DeleteGO(m_player);
							NewGO<GameOver>(0, "gameover");
							DeleteGO(this);
							m_player = nullptr;
							return;
						}
				}
			}
		}
		else if (m_boss != nullptr)
		{
			const float stompMinHeight = 25.0f;
			const float stompMaxHeight = 200.0f;
			if (dist3XZ<bossHitXZ&&diffY>=stompMinHeight&&diffY<=stompMaxHeight&&m_player->m_playerMoveSpeed.y<0)
			{
				m_bossLife -= 1;
				if (m_bossLife == 0)
				{
					m_death = true;
					DeleteGO(m_boss);
					m_player->m_playerMoveSpeed.y = 2000.0f;
					m_score += 100;
					m_boss = nullptr;
					SoundSource* se = NewGO<SoundSource>(SE_Jump);
					se->Init(SE_Jump);
					se->Play(false);
					return;
				}
				m_player->m_playerMoveSpeed.x += 500.0f;
				m_player->m_playerMoveSpeed.y = 2000.0f;
			}
		}
	}
	if (m_life == 1)
	{
		m_blinkTimer += g_gameTime->GetFrameDeltaTime();
		if (m_blinkTimer > 0.3f)
		{
			m_isVisble = !m_isVisble;
			m_blinkTimer = 0.0f;
		}
	}
	else
	{
		m_isVisble = true;	//ライフが１以外なら常に表示
	}
	if (m_star->m_starCount == 1)
	{
		NewGO<GameClear>(0, "gameclear");
		DeleteGO(this);
		return;
	}
	if (m_time < 0)
	{
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
		return;
	}
	m_spriteRender1.Update();
	m_spriteRender2.Update();
	m_spriteRender3.Update();
	m_scoreSprite.Update();
	m_timeSprite.Update();
	m_modelRender.Update();
	UpdateDigits();
}

void Game2::UpdateDigits()
{
	for (auto& s : m_digitSlots)
	{
		s.Update();
	}
}

void Game2::DrawNumber(RenderContext& rc,
	int value,
	const Vector3& startPos,
	float digitSpace,
	int minDigits,
	int slotBase,
	int slotCount)
{
	if (value < 0)value = 0;
	char fmt[16];
	sprintf_s(fmt, "%%0%dd", minDigits);

	char buf[32];
	sprintf_s(buf, fmt, value);

	Vector3 pos = startPos;
	int slot = 0;
	for (char c : std::string(buf))
	{
		if (c < '0' || c>'9')continue;
		if (slot >= slotCount)break;
		const int idx = c - '0';
		const int sidx = slotBase + slot;

		if (m_digitSlotPrev[sidx] != idx)
		{
			char path[128];
			sprintf_s(path, "Assets/sprite/font%d.dds", idx);
			m_digitSlots[sidx].Init(path, 64.0f, 64.0f);
			m_digitSlotPrev[sidx] = idx;
		}

		m_digitSlots[sidx].SetScale(m_digitScale);
		m_digitSlots[sidx].SetPosition(pos);
		m_digitSlots[sidx].Draw(rc);

		pos.x += digitSpace;
		++slot;;
	}
}

void Game2::Render(RenderContext& rc)
{
	if (m_life == 3)
	{
		m_spriteRender1.Draw(rc);
		m_spriteRender2.Draw(rc);
		m_spriteRender3.Draw(rc);
	}
	else if (m_life == 2)
	{
		m_spriteRender1.Draw(rc);
		m_spriteRender2.Draw(rc);
	}
	else if (m_life == 1)
	{
		if (m_isVisble)
		{
			m_spriteRender1.Draw(rc);
		}
	}

	m_scoreSprite.Draw(rc);
	m_timeSprite.Draw(rc);

	DrawNumber(rc,
		m_score,
		m_scoreStartPos,
		m_scoreDigitSpace,
		4,
		kScoreSlotBase,
		kScoreDigits);

	int sec = static_cast<int>(m_time);
	if (sec < 0)sec = 0;
	DrawNumber(rc,
		sec,
		m_timeStartPos,
		m_timeDigitSpace,
		3,
		kTimeSlotBase,
		kTimeDigits);
}