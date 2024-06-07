#include "Leaf.h"

void CLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_LEAF_LEFT)->Render(x, y);

	//RenderBoundingBox();
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// If the LEAF is in the SPAWN state, apply gravity and update position
	if (state == LEAF_STATE_SPAWN) {
		// Apply gravity
		vy += ay * dt;

		// Update position based on velocity and time delta
		x += vx * dt;
		y += vy * dt;

		// Check if the LEAF needs to disappear
		if (GetTickCount64() - state_start > LEAF_SPAWN_TIME) {
			this->Delete();
			return;
		}
	}

	// Call parent class update to handle other potential updates
	CGameObject::Update(dt, coObjects);
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::SetState(int state)
{
	switch (state)
	{
	case LEAF_STATE_SPAWN:
		vy = -LEAF_JUMP_SPEED; // Set initial upward velocity
		state_start = GetTickCount64(); // Record the start time of the spawn state
		break;
	case LEAF_STATE_NORMAL:
		vy = 0; // Reset vertical velocity to 0 when in normal state
		break;
	}

	CGameObject::SetState(state);
}
