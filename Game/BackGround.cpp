#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_stageRender.Init("Assets/modelData/stage3.tkm");
	m_stageRender.Update();
	m_physicsStaticObject.CreateFromModel(m_stageRender.GetModel(), m_stageRender.GetModel().GetWorldMatrix());
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

BackGround::~BackGround()
{

}

//描画処理
void BackGround::Render(RenderContext& rc)
{
	m_stageRender.Draw(rc);
}