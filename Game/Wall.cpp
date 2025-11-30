#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{

}

Wall::~Wall()
{

}
bool Wall::Start()
{
	m_wallRender.Init("Assets/modelData/wall.tkm");
	m_wallRender.SetPosition(Vector3(0.0f, 0.0f, -1000.0f));
	m_wallRender.Update();
	m_physicsStaticObject.CreateFromModel(m_wallRender.GetModel(), m_wallRender.GetModel().GetWorldMatrix());
	m_physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);
	return true;
}

void Wall::Update()
{

}

void Wall::Render(RenderContext& rc)
{
	m_wallRender.Draw(rc);
}