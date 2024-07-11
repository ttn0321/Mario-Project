#pragma once
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 14
#define MUSHROOM_BBOX_HEIGHT_DIE 7

#define MUSHROOM_DIE_TIMEOUT 500

#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_DIE 200
#define MUSHROOM_STATE_EMERGE 300

#define MUSHROOM_EMERGE_SPEED 0.02f
#define MUSHROOM_EMERGE_HEIGHT 16

#define ID_ANI_MUSHROOM_WALKING 6000
#define ID_ANI_MUSHROOM_DIE 6001
#define ID_ANI_GREEN_MUSHROOM_WALKING 6002

class CMushroom : public CGameObject
{
protected:
    float ax;
    float ay;
    float initialY;  // Track the initial Y position
    ULONGLONG die_start;
    int level;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);

    virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
    CMushroom(float x, float y, int level);
    virtual void SetState(int state);
    int GetLevel() { return level; }
};
