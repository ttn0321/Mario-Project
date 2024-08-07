#pragma once
#include "GameObject.h"
#include "Platform.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SLIDING_SPEED 0.15f
#define KOOPA_JUMP_SPEED	0.3f

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_DIE 16

#define KOOPA_SHELL_TIMEOUT 5000 // 5 seconds in shell state
#define KOOPA_TRANSITION_TIMEOUT 2000 // 2 seconds in transition state
#define KOOPA_JUMP_TIME 2000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL 200
#define KOOPA_STATE_SHELL_SLIDE 300
#define KOOPA_STATE_TRANSITION 400
#define KOOPA_STATE_HELD 500
#define KOOPA_STATE_JUMPING 600

#define ID_ANI_KOOPA_WALKING_LEFT 8000
#define ID_ANI_KOOPA_WALKING_RIGHT 8001
#define ID_ANI_KOOPA_SHELL 8002
#define ID_ANI_KOOPA_TRANSITION 8003

#define ID_ANI_GREEN_KOOPA_WALKING_LEFT 8010
#define ID_ANI_GREEN_KOOPA_WALKING_RIGHT 8011
#define ID_ANI_GREEN_KOOPA_SHELL 8012
#define ID_ANI_GREEN_KOOPA_TRANSITION 8013

#define ID_ANI_KOOPA_WING_WALKING_LEFT 8020
#define ID_ANI_KOOPA_WING_JUMPING_LEFT 8021
#define ID_ANI_KOOPA_WING_WALKING_RIGHT 8022
#define ID_ANI_KOOPA_WING_JUMPING_RIGHT 8023


class CKoopa : public CGameObject
{
protected:
    float ax;
    float ay;

    int level;

    ULONGLONG state_start,jump_start;

    bool isHeld;
    CGameObject* holder;
    BOOLEAN isOnPlatform;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);

    virtual void OnCollisionWith(LPCOLLISIONEVENT e);

    void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
    void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
    void OnCollisionWithQuestion(LPCOLLISIONEVENT e);
    void OnCollisionWithBrick(LPCOLLISIONEVENT e);

    bool IsNearEdgeOfPlatform(vector<LPGAMEOBJECT>* coObjects, DWORD dt);

public:
    CKoopa(float x, float y,int level);
    virtual void SetState(int state);
    void SetHeld(bool isHeld, CGameObject* holder) { this->isHeld = isHeld; this->holder = holder; }
    int GetLevel() { return level; }
    void SetLevel(int level) { this->level = level; }
};
