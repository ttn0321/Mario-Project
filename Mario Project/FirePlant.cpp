#include "FirePlant.h"
CFirePlant::CFirePlant(float x, float y) :CGameObject(x, y)
{
	
}

void CFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIRE_PLANT_BBOX_WIDTH / 2;
	top = y - FIRE_PLANT_BBOX_HEIGHT / 2;
	right = left + FIRE_PLANT_BBOX_WIDTH;
	bottom = top + FIRE_PLANT_BBOX_HEIGHT;
	
}

void CFirePlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFirePlant::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFirePlant::Render()
{
	int aniId = ID_ANI_FIRE_PLANT;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFirePlant::SetState(int state)
{
	CGameObject::SetState(state);
	
}