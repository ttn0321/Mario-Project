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

class CCoin : public CGameObject {
public:
	CCoin(float x, float y) : CGameObject(x, y) {
		SetState(COIN_STATE_NORMAL);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};