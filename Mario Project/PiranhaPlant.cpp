#include "PiranhaPlant.h"
#include "Mario.h"
#include "PlayScene.h"

#define PIRANHA_PLANT_DETECT_RADIUS 50.0f // Radius to detect Mario
#define PIRANHA_PLANT_SHOOT_NEAR_RADIUS 100.0f // Radius to detect Mario
#define PIRANHA_PLANT_SHOOT_RANGE 200.0f // Radius to detect Mario
#define PIRANHA_PLANT_SPEED 0.05f // Speed of emergence and hiding

#define PIRANHA_PLANT_EAT_TIMEOUT 1500
#define PIRANHA_PLANT_HIDE_TIMEOUT 2000 

CPiranhaPlant::CPiranhaPlant(float x, float y) : CGameObject(x, y)
{
    this->ax = 0;
    this->ay = 0;  // No gravity during the emergence
    this->initialY = y;
    this->SetState(PIRANHA_PLANT_STATE_HIDING); // Initial state
}
void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - PIRANHA_PLANT_BBOX_WIDTH / 2;
    top = y - PIRANHA_PLANT_BBOX_HEIGHT / 2;
    right = left + PIRANHA_PLANT_BBOX_WIDTH;
    bottom = top + PIRANHA_PLANT_BBOX_HEIGHT;
}

void CPiranhaPlant::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
    // Handle collisions here if needed
}
void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    LPGAMEOBJECT marioObj = currentScene->GetPlayer();
    CMario* mario = dynamic_cast<CMario*>(marioObj);  // Cast to CMario to access Mario-specific methods

    CGameObject::Update(dt, coObjects);

    float marioX, marioY;
    mario->GetPosition(marioX, marioY);

    float distance = abs(marioX - x);


    bool marioNear = (distance < PIRANHA_PLANT_DETECT_RADIUS) && (abs(marioY - y) < PIRANHA_PLANT_BBOX_HEIGHT + 7);
    bool marioInRange = (distance < PIRANHA_PLANT_SHOOT_RANGE);
    ULONGLONG now = GetTickCount64();

    if (state == PIRANHA_PLANT_STATE_HIDING && !marioNear && now - state_start > PIRANHA_PLANT_HIDE_TIMEOUT && marioInRange == true)
    {
        SetState(PIRANHA_PLANT_STATE_EMERGE);
    }
    else if (state == PIRANHA_PLANT_STATE_EMERGE)
    {
        if (now - state_start > PIRANHA_PLANT_EAT_TIMEOUT)
            SetState(PIRANHA_PLANT_STATE_HIDING);
    }


    // Handle the movement logic
    if (state == PIRANHA_PLANT_STATE_EMERGE && y <= initialY - PIRANHA_PLANT_BBOX_HEIGHT)
    {
        y = initialY - PIRANHA_PLANT_BBOX_HEIGHT; // Stop at the target position
        vy = 0; // Stop vertical movement
    }
    else if (state == PIRANHA_PLANT_STATE_HIDING && y >= initialY)
    {
        y = initialY; // Stop at the initial position
        vy = 0; // Stop vertical movement
    }

    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::Render()
{
    int aniId = ID_ANI_PIRANHA_PLANT;
    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CPiranhaPlant::SetState(int state)
{
    CGameObject::SetState(state);
    state_start = GetTickCount64();
    switch (state)
    {
    case PIRANHA_PLANT_STATE_HIDING:
        vy = PIRANHA_PLANT_SPEED; // Move downwards
        break;
    case PIRANHA_PLANT_STATE_EMERGE:
        vy = -PIRANHA_PLANT_SPEED;  // Move upwards
        break;
    }
}