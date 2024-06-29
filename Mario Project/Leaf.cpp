#include "Leaf.h"

void CLeaf::Render()
{
	int aniId = ID_ANI_LEAF_LEFT;
	if (vx < 0)
		aniId = ID_ANI_LEAF_LEFT;
	else if (vx > 0)
		aniId = ID_ANI_LEAF_RIGHT;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
	if (state == LEAF_STATE_SPAWN) {
		if (GetTickCount64() - state_start > LEAF_SPAWN_TIME) {
			SetState(LEAF_STATE_FALL_RIGHT);
		}
	}
	if (state == LEAF_STATE_FALL_LEFT) {
		if (GetTickCount64() - state_start > LEAF_CHANGE_TIME) {
			SetState(LEAF_STATE_FALL_RIGHT);
		}
	}
	if (state == LEAF_STATE_FALL_RIGHT) {
		if (GetTickCount64() - state_start > LEAF_CHANGE_TIME) {
			SetState(LEAF_STATE_FALL_LEFT);
		}
	}
	// Call parent class update to handle other potential updates

	CGameObject::Update(dt, coObjects); 
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}
void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
}
void CLeaf::SetState(int state)
{
	switch (state)
	{
	case LEAF_STATE_SPAWN:
		vx = 0.0f;
		vy = -LEAF_JUMP_SPEED; // Set initial upward velocity
		state_start = GetTickCount64(); // Record the start time of the spawn state
		break;
	case LEAF_STATE_FALL_RIGHT:
		vx = LEAF_SPEED;
		vy = LEAF_GRAVITY;
		ay = 0.00003f;
		state_start = GetTickCount64(); // Record the start time of the spawn state
		break;
	case LEAF_STATE_FALL_LEFT:
		vx = -LEAF_SPEED;
		vy = LEAF_GRAVITY;
		ay = 0.00003f;
		state_start = GetTickCount64(); // Record the start time of the spawn state
		break;
	case LEAF_STATE_NORMAL:
		break;
	}

	CGameObject::SetState(state);
}
