#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_FIRE_PLANT_DOWN_LEFT 12000
#define ID_ANI_FIRE_PLANT_UP_LEFT 12001
#define ID_ANI_FIRE_PLANT_DOWN_RIGHT 12002
#define ID_ANI_FIRE_PLANT_UP_RIGHT 12003

#define FIRE_PLANT_BBOX_WIDTH 16
#define FIRE_PLANT_BBOX_HEIGHT 32

#define FIRE_PLANT_STATE_HIDING 100
#define FIRE_PLANT_STATE_EMERGE 200
#define FIRE_PLANT_STATE_SHOOT 300

#define FIRE_PLANT_SHOOT_DELAY 1000 // 1 second delay before shooting


class CFirePlant : public CGameObject
{
protected:
    float ax;
    float ay;

    float initialY;  // Track the initial Y position
    int direction;
    int fire_direction;

    ULONGLONG state_start;

    ULONGLONG shoot_start;
    ULONGLONG shoot_stop;// Timer for shooting
    bool shot_fired;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual int IsCollidable() { return 0; };
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);

    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    bool IsNearEdgeOfPlatform(vector<LPGAMEOBJECT>* coObjects);
    void ShootFireball();
    void SetDirection();

public:
    CFirePlant(float x, float y);
    virtual void SetState(int state);
};
