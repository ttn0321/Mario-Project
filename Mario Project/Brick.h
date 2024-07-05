#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK_BEFORE 10000
#define ID_ANI_BRICK_AFTER 10001

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_BEFORE 100
#define BRICK_STATE_AFTER 200
#define BRICK_STATE_COIN 300

class CBrick : public CGameObject {
	int type;
public:
	CBrick(float x, float y, int type) : CGameObject(x, y) {
		this->type = type;
		SetState(BRICK_STATE_BEFORE);
	}
	virtual void SetState(int state);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetType() { return type; }
};