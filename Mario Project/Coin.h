#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_JUMP_SPEED	0.5f 
#define COIN_GRAVITY 0.002f

#define COIN_STATE_NORMAL 100
#define COIN_STATE_SPAWN 200

#define COIN_SPAWN_TIME 450

class CCoin : public CGameObject {
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	ULONGLONG state_start;
public:
	CCoin(float x, float y) : CGameObject(x, y) {
		this->ax = 0;
		this->ay = COIN_GRAVITY;
		SetState(COIN_STATE_NORMAL);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};