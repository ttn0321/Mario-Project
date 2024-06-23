#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LEAF_LEFT 15001
#define ID_ANI_LEAF_RIGHT 15002

#define	LEAF_WIDTH 10
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 14

#define LEAF_JUMP_SPEED	0.4f 
#define LEAF_SPEED	0.02f 
#define LEAF_GRAVITY 0.002f

#define LEAF_STATE_NORMAL 100
#define LEAF_STATE_SPAWN 200
#define LEAF_STATE_FALL_RIGHT 300
#define LEAF_STATE_FALL_LEFT 400

#define LEAF_SPAWN_TIME 200
#define LEAF_CHANGE_TIME 1250

class CLeaf : public CGameObject {
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float initial_x;
	ULONGLONG state_start;
public:
	CLeaf(float x, float y) : CGameObject(x, y) {
		this->initial_x = x;
		this->ax = 0;
		this->ay = LEAF_GRAVITY;
		SetState(LEAF_STATE_NORMAL);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};
