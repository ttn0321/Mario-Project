#include "Fireball.h"

void CFireball::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALL)->Render(x, y);

	//RenderBoundingBox();
}

void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	CGameObject::Update(dt, coObjects);
}

void CFireball::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALL_BBOX_WIDTH / 2;
	t = y - FIREBALL_BBOX_HEIGHT / 2;
	r = l + FIREBALL_BBOX_WIDTH;
	b = t + FIREBALL_BBOX_HEIGHT;
}

void CFireball::SetState(int state)
{
	
	CGameObject::SetState(state);
}
