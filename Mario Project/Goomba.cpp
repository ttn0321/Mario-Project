#include "Goomba.h"

CGoomba::CGoomba(float x, float y, int level):CGameObject(x, y)
{
	this->level = level;
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}
	if (state == GOOMBA_STATE_WALKING)
	{
		if (IsNearEdgeOfPlatform(coObjects, dt))
		{
			vx = -vx; // Turn around
		}
	}
	if (level == 2)
	{
		if (state==GOOMBA_STATE_WALKING && GetTickCount64() - state_start > GOOMBA_JUMP_TIME) {
			SetState(GOOMBA_STATE_JUMPING);
		}
		if (state == GOOMBA_STATE_JUMPING && vy > 0) {
			SetState(GOOMBA_STATE_WALKING);
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (level == 2) {
		aniId = ID_ANI_GOOMBA_WING_WALKING;
		if (state == GOOMBA_STATE_JUMPING)
		{
			aniId = ID_ANI_GOOMBA_WING_JUMPING;
		}
	}
	if (state == GOOMBA_STATE_DIE) 
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = GOOMBA_WALKING_SPEED;
			if(level==2)
				state_start = GetTickCount64();
			break;
		case GOOMBA_STATE_JUMPING:
			vy = -GOOMBA_JUMP_SPEED; 
			break;

	}
}

bool CGoomba::IsNearEdgeOfPlatform(vector<LPGAMEOBJECT>* coObjects, DWORD dt)
{
	// Calculate future position 16 pixels ahead in the direction of movement
	float futureX = x + vx * dt + (vx > 0 ? 16 : -16);

	// Create a hypothetical future Goomba to check if it would fall off
	CGoomba futureGoomba = *this;  // Create a copy of the current Goomba
	futureGoomba.SetPosition(futureX, y);  // Move the future Goomba to the calculated position

	// Assume the future Goomba is falling due to gravity (adjust as per your game's logic)
	futureGoomba.vy += ay * dt;

	// Scan collisions for the future Goomba (which checks if it would fall)
	vector<LPCOLLISIONEVENT> coEvents;
	CCollision::GetInstance()->Scan(&futureGoomba, dt, coObjects, coEvents);

	// Check if the future Goomba is falling (no collisions below)
	bool nearEdge = true;
	for (auto& e : coEvents)
	{
		if (e->ny < 0)  // If there is a collision below the future Goomba, it's not near an edge
		{
			nearEdge = false;
			break;
		}
	}

	// Cleanup
	for (auto& e : coEvents)
		delete e;

	return nearEdge;
}