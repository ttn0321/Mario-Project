#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_FIRE_PLANT 12000
#define FIRE_PLANT_BBOX_WIDTH 16
#define FIRE_PLANT_BBOX_HEIGHT 32

#define FIRE_PLANT_STATE_HIDING 100
#define FIRE_PLANT_STATE_EMERGE 200

class CFirePlant : public CGameObject
{
protected:
	float ax;
	float ay;

	float initialY;  // Track the initial Y position
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	bool IsNearEdgeOfPlatform(vector<LPGAMEOBJECT>* coObjects);

public:
	CFirePlant(float x, float y);
	virtual void SetState(int state);
};