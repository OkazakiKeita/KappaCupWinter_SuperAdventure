#include "stdafx.h"
#include "Wall2.h"

Wall2::Wall2()
{

}

Wall2::~Wall2()
{

}
bool Wall2::Start()
{
	m_wall2Render.Init("Assets/modelData/wall2.tkm");
	m_wall2Render.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_wall2Render.Update();
	m_physicsStaticObject.CreateFromModel(m_wall2Render.GetModel(), m_wall2Render.GetModel().GetWorldMatrix());
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);
	return true;
}

void Wall2::Update()
{

}

void Wall2::Render(RenderContext& rc)
{
	m_wall2Render.Draw(rc);
}