#pragma once
#include "GameObject.h"
#include "Platform.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_JUMP_SPEED	0.3f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500
#define GOOMBA_JUMP_TIME 2000

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_JUMPING 300

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_WING_WALKING 5002
#define ID_ANI_GOOMBA_WING_JUMPING 5003

#define GOOMBA_LEVEL_NORMAL 1
#define GOOMBA_LEVEL_WING 2


class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 

	int level;

	ULONGLONG die_start, state_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	bool IsNearEdgeOfPlatform(vector<LPGAMEOBJECT>* coObjects, DWORD dt);

public: 	
	CGoomba(float x, float y,int level);
	virtual void SetState(int state);
	int GetLevel() { return level; }
	void SetLevel(int level) { this->level = level; }
};