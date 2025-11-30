#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_stageRender.Init("Assets/modelData/stage.tkm");
	m_stageRender.Update();
	m_physicsStaticObject.CreateFromModel(m_stageRender.GetModel(), m_stageRender.GetModel().GetWorldMatrix());
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

BackGround::~BackGround()
{

}

//•`‰æˆ—
void BackGround::Render(RenderContext& rc)
{
	m_stageRender.Draw(rc);
}