#include "Fireball.h"

void CFireball::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALL)->Render(x, y);

	//RenderBoundingBox();
}
void CFireball::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};
void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
	vx += ax * dt;

	float cx, cy;
	CGame* game = CGame::GetInstance();
	game->GetCamPos(cx, cy);

	float l, t, r, b;
	l = cx - 32;
	t = cy - 32;
	r = cx+ 320 + 32;
	b = cy + 240 + 32;
	if (x<l || x>r || y<t || y>b) {
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
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
