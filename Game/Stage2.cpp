#include "stdafx.h"
#include "Stage2.h"

Stage2::Stage2()
{
	m_stage2Render.Init("Assets/modelData/stage2.tkm");
	m_stage2Render.Update();
	m_physicsStaticObject.CreateFromModel(m_stage2Render.GetModel(), m_stage2Render.GetModel().GetWorldMatrix());
}

Stage2::~Stage2()
{

}

void Stage2::Render(RenderContext& rc)
{
	m_stage2Render.Draw(rc);
}