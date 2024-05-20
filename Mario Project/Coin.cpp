#include "Coin.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// If the coin is in the SPAWN state, apply gravity and update position
	if (state == COIN_STATE_SPAWN) {
		// Apply gravity
		vy += ay * dt;

		// Update position based on velocity and time delta
		x += vx * dt;
		y += vy * dt;

		// Check if the coin needs to disappear
		if (GetTickCount64() - state_start > COIN_SPAWN_TIME) {
			this->Delete();
			return;
		}
	}

	// Call parent class update to handle other potential updates
	CGameObject::Update(dt, coObjects);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::SetState(int state)
{
	switch (state)
	{
	case COIN_STATE_SPAWN:
		vy = -COIN_JUMP_SPEED; // Set initial upward velocity
		state_start = GetTickCount64(); // Record the start time of the spawn state
		break;
	case COIN_STATE_NORMAL:
		vy = 0; // Reset vertical velocity to 0 when in normal state
		break;
	}

	CGameObject::SetState(state);
}
