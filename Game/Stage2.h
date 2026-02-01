#pragma once
class Stage2:public IGameObject
{
public:
	Stage2();
	~Stage2();

	void Render(RenderContext& rc);

	ModelRender m_stage2Render;
	PhysicsStaticObject m_physicsStaticObject;
};

