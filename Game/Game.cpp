#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Boss.h"
#include "Wall.h"
#include "Star.h"
#include "Shell.h"
#include "GameOver.h"
#include "GameClear.h"

Game::Game()
{
	Vector3 spawnPos[] = {
		{0.0f,250.0f,-150.0f},
		{0.0f,0.0f,-400.0f},
		{0.0f,0.0f,-500.0f}
	};
	//ステージ
	m_backGround = NewGO<BackGround>(0, "stage");
	//キャラクター
	m_player = NewGO<Player>(0, "player");
	//ゲームカメラのオブジェクト
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//エネミー1
	//m_enemy1 = NewGO<Enemy1>(0, "enemy1");
	for (int i = 0;i < 3;i++)
	{
		Enemy1* enemy = NewGO<Enemy1>(0, "enemy1");
		enemy->SetPosition(spawnPos[i]);
		m_enemy1List.push_back(enemy);
	}
	//エネミー2
	m_enemy2 = NewGO<Enemy2>(0, "enemy2");
	//ボス
	m_boss = NewGO<Boss>(0, "boss");
	//壁
	m_wall = NewGO<Wall>(0, "wall");
	//空のオブジェクト
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	//スター
	m_star= NewGO<Star>(0, "star");
	m_star->m_starPosition = { 1000.0f,800.0f,-4150.0f };
	
	m_spriteRender1.Init("Assets/sprite/hart.dds",512.0f,512.0f);
	m_spriteRender1.SetScale(Vector3{ 0.2f,0.15f,0.2f });
	m_spriteRender1.SetPosition({ -850.0f,400.0f,0.0f });
	m_spriteRender2.Init("Assets/sprite/hart.dds", 512.0f, 512.0f);
	m_spriteRender2.SetScale(Vector3{ 0.2f,0.15f,0.2f });
	m_spriteRender2.SetPosition({ -750.0f,400.0f,0.0f });
	m_spriteRender3.Init("Assets/sprite/hart.dds", 512.0f, 512.0f);
	m_spriteRender3.SetScale(Vector3{ 0.2f,0.15f,0.2f });
	m_spriteRender3.SetPosition({ -650.0f,400.0f,0.0f });

	/*auto* pointLight = g_sceneLight->NewPointLight();
	pointLight->SetPosition(Vector3(0.0f, 50.0f, 300.0f));
	pointLight->SetColor(100.0f, 0.1f, 0.1f);
	pointLight->SetRange(200.0f);
	pointLight->SetAffectPowParam(3.0f);
	pointLight->Update();*/
}

Game::~Game()
{
	DeleteGO(m_backGround);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	for (auto* enemy : m_enemy1List)
	{
		DeleteGO(enemy);
	}
	m_enemy1List.clear();
	//DeleteGO(m_enemy1);
	DeleteGO(m_enemy2);
	DeleteGO(m_boss);
	DeleteGO(m_wall);
	DeleteGO(m_star);
	DeleteGO(m_skyCube);
	DeleteGO(m_shell);
}

void Game::Update()
{
	wchar_t text4[256];
	swprintf_s(text4, 256, L"スコア:%04d", m_score);
	m_scoreRender.SetText(text4);
	m_scoreRender.SetPosition(m_setScore);
	m_scoreRender.SetColor(g_vec4Black);
	m_scoreRender.SetScale((0.8f, 0.8f, 0.8f));

	m_time -= g_gameTime->GetFrameDeltaTime();
	int sec = (int)m_time;

	wchar_t text[256];
	swprintf_s(text, 256, L"残り:%03d秒", sec);
	m_timeRender.SetText(text);
	m_timeRender.SetPosition(m_setTime);
	m_timeRender.SetColor(g_vec4Black);

	if (m_player->m_playerPosition.y < -1000.0f)
	{
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
		return;
	}
	for (auto it=m_enemy1List.begin();it !=m_enemy1List.end();)
	{
		Enemy1* enemy = *it;
		enemy->Update();
		Vector3 diff= m_player->GetPosition() - enemy->GetPosition();
		float distXZ = sqrtf(diff.x * diff.x + diff.z * diff.z);
		float heightDiff = m_player->GetPosition().y - enemy->GetPosition().y;
		float stompMinHeight = 5.0f;
		float stompMaxHeight = 50.0f;
		if (m_invincible <= 0.0f)
		{
			if (distXZ < 80.0f && heightDiff < 20.0f && m_invincible <= 0.0f)
			{
				m_life -= 1;
				m_invincible = 1.0f;
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
		if (distXZ< 60.0f &&heightDiff>stompMinHeight&&heightDiff<stompMaxHeight&&m_player->m_playerMoveSpeed.y<0)
		{
			DeleteGO(enemy);
			it = m_enemy1List.erase(it);
			m_player->m_playerMoveSpeed.y = 2000.0f;
			m_score += 100;
			continue;
		}
		++it;
	}
	//if (m_invincible > 0.0f)
	//{
	//	m_invincible -= g_gameTime->GetFrameDeltaTime();
	//}
	//if (m_player != nullptr)
	//{
	//	if (m_player->m_jump == 0)
	//	{
	//	if (m_invincible <= 0.0f)
	//	{
	//		float dist1 = (m_player->GetPosition() - m_enemy1->GetPosition()).Length();
	//		float dist2 = (m_player->GetPosition() - m_enemy2->GetPosition()).Length();
	//			if (dist1 < 80.0f||dist2<80.0f)
	//			{
	//				m_life -= 1;
	//				m_invincible = 1.0f;
	//				if (m_life == 0)
	//				{
	//					DeleteGO(m_player);
	//					NewGO<GameOver>(0, "gameover");
	//					DeleteGO(this);
	//					m_player = nullptr;
	//					return;
	//				}
	//			}
	//		}
	//	}
	//	else
	//	{
	//		float dist1 = (m_player->GetPosition() - m_enemy1->GetPosition()).Length();
	//		float dist2 = (m_player->GetPosition() - m_enemy2->GetPosition()).Length();
	//		if (dist1 < 50.0f)
	//		{
	//			if (m_enemy1->m_enemy1Position.y + 25.0f <= m_player->m_playerPosition.y)
	//			{
	//				DeleteGO(m_enemy1);
	//				m_player->m_playerMoveSpeed.y = 2000.0f;
	//				m_score += 100;
	//				return;
	//			}
	//		}
	//		if (dist2 < 50.0f)
	//		{
	//			if (m_enemy2->m_enemy2Position.y + 25.0f <= m_player->m_playerPosition.y)
	//			{
	//				m_death = true;
	//				Vector3 enemy2Position = m_enemy2->GetPosition();
	//				enemy2Position.y += 25.0f;
	//				//甲羅
	//				m_shell = NewGO<Shell>(0, "shell");
	//				m_shell->SetPosition(enemy2Position);
	//				DeleteGO(m_enemy2);
	//				m_player->m_playerMoveSpeed.y = 2000.0f;
	//				m_score += 100;
	//				return;
	//			}
	//		}
	//	}
	//}
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
	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_timeRender.Draw(rc);
	m_scoreRender.Draw(rc);
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
}