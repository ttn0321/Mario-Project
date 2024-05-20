#pragma once
#include "GameObject.h"
#include "Platform.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SLIDING_SPEED 0.15f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_DIE 16

#define KOOPA_DIE_TIMEOUT 500

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL 200
#define KOOPA_STATE_SHELL_SLIDE 300

#define ID_ANI_KOOPA_WALKING_LEFT 8000
#define ID_ANI_KOOPA_WALKING_RIGHT 8001
#define ID_ANI_KOOPA_SHELL 8002

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

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
	CKoopa(float x, float y);
	virtual void SetState(int state);
};