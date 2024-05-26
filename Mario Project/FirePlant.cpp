#include "FirePlant.h"
#include "Mario.h"
#include "Fireball.h"
#include "PlayScene.h"

#define FIRE_PLANT_DETECT_RADIUS 50.0f // Radius to detect Mario
#define FIRE_PLANT_SPEED 0.05f // Speed of emergence and hiding

CFirePlant::CFirePlant(float x, float y) : CGameObject(x, y)
{
    this->ax = 0;
    this->ay = 0;  
    this->initialY = y;
    this->SetState(FIRE_PLANT_STATE_HIDING); // Initial state
}

void CFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - FIRE_PLANT_BBOX_WIDTH / 2;
    top = y - FIRE_PLANT_BBOX_HEIGHT / 2;
    right = left + FIRE_PLANT_BBOX_WIDTH;
    bottom = top + FIRE_PLANT_BBOX_HEIGHT;
}

void CFirePlant::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CFirePlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
    // Handle collisions here if needed
}

void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    LPGAMEOBJECT marioObj = currentScene->GetPlayer();
    CMario* mario = dynamic_cast<CMario*>(marioObj);  // Cast to CMario to access Mario-specific methods

    CGameObject::Update(dt, coObjects);

    float marioX, marioY;
    mario->GetPosition(marioX, marioY);

    float distance = abs(marioX - x);

    if (state == FIRE_PLANT_STATE_HIDING && distance < FIRE_PLANT_DETECT_RADIUS)
    {
        SetState(FIRE_PLANT_STATE_EMERGE);
    }
    else if (state == FIRE_PLANT_STATE_EMERGE && distance >= FIRE_PLANT_DETECT_RADIUS)
    {
        SetState(FIRE_PLANT_STATE_HIDING);
    }

    // Handle the movement logic
    if (state == FIRE_PLANT_STATE_EMERGE && y <= initialY - FIRE_PLANT_BBOX_HEIGHT)
    {
        y = initialY - FIRE_PLANT_BBOX_HEIGHT; // Stop at the target position
        vy = 0; // Stop vertical movement
    }
    else if (state == FIRE_PLANT_STATE_HIDING && y >= initialY)
    {
        y = initialY; // Stop at the initial position
        vy = 0; // Stop vertical movement
    }

    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFirePlant::Render()
{
    int aniId = ID_ANI_FIRE_PLANT;

    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CFirePlant::SetState(int state)
{
    CGameObject::SetState(state);

    switch (state)
    {
    case FIRE_PLANT_STATE_HIDING:
        vy = FIRE_PLANT_SPEED; // Move downwards
        break;
    case FIRE_PLANT_STATE_EMERGE:
        vy = -FIRE_PLANT_SPEED;  // Move upwards
        break;
    }
}
