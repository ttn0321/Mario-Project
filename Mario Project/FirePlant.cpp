#include "FirePlant.h"
#include "Mario.h"
#include "Fireball.h"
#include "PlayScene.h"

#define FIRE_PLANT_DETECT_RADIUS 50.0f // Radius to detect Mario
#define FIRE_PLANT_SPEED 0.05f // Speed of emergence and hiding

#define FIRE_PLANT_SHOOT_TIMEOUT 1500
#define FIRE_PLANT_HIDE_TIMEOUT 2000 

CFirePlant::CFirePlant(float x, float y) : CGameObject(x, y)
{
    this->ax = 0;
    this->ay = 0;  // No gravity during the emergence
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

    bool marioNear = (distance < FIRE_PLANT_DETECT_RADIUS) && (abs(marioY - y) < FIRE_PLANT_BBOX_HEIGHT);
    ULONGLONG now = GetTickCount64();

    if (state == FIRE_PLANT_STATE_HIDING && !marioNear && now - state_start > FIRE_PLANT_HIDE_TIMEOUT)
    {
        SetState(FIRE_PLANT_STATE_EMERGE);
    }
    else if (state == FIRE_PLANT_STATE_SHOOT)
    {
        if(shot_fired == false)
            ShootFireball();
        if(now - state_start > FIRE_PLANT_SHOOT_TIMEOUT)
            SetState(FIRE_PLANT_STATE_HIDING);  
    }


    // Handle the movement logic
    if (state == FIRE_PLANT_STATE_EMERGE && y <= initialY - FIRE_PLANT_BBOX_HEIGHT)
    {
        y = initialY - FIRE_PLANT_BBOX_HEIGHT; // Stop at the target position
        vy = 0; // Stop vertical movement
        SetState(FIRE_PLANT_STATE_SHOOT);
    }
    else if (state == FIRE_PLANT_STATE_HIDING && y >= initialY)
    {
        y = initialY; // Stop at the initial position
        vy = 0; // Stop vertical movement
        SetDirection();
    }

    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFirePlant::Render()
{
    int aniId = ID_ANI_FIRE_PLANT_DOWN_LEFT;
    switch (direction) {
        case 1:
            aniId = ID_ANI_FIRE_PLANT_DOWN_LEFT;
            break;
        case 2:
            aniId = ID_ANI_FIRE_PLANT_UP_LEFT;
            break;
        case 3:
            aniId = ID_ANI_FIRE_PLANT_DOWN_RIGHT;
            break;
        case 4:
            aniId = ID_ANI_FIRE_PLANT_UP_RIGHT;
            break;
    }
    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CFirePlant::SetState(int state)
{
    CGameObject::SetState(state);
    state_start = GetTickCount64();
    switch (state)
    {
    case FIRE_PLANT_STATE_HIDING:
        vy = FIRE_PLANT_SPEED; // Move downwards
        break;
    case FIRE_PLANT_STATE_EMERGE:
        vy = -FIRE_PLANT_SPEED;  // Move upwards
        break;
    case FIRE_PLANT_STATE_SHOOT:
        vy = 0; // Stay still
        shot_fired = false;
        shoot_start = GetTickCount64(); // Start shooting timer
        break;
    }
}

void CFirePlant::ShootFireball()
{
    CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    vector<LPGAMEOBJECT>& objects = currentScene->GetObjects();

    CFireball* fireball = new CFireball(x, y-5);
    fireball->SetSpeed(-0.1f, 0); // Set appropriate speed for the fireball
    objects.push_back(fireball);
    shot_fired = true;
}

void CFirePlant::SetDirection()
{
    // 1 = Down left, 2 = Up left, 3 = Down right, 4 = Up right
    CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    LPGAMEOBJECT marioObj = currentScene->GetPlayer();
    CMario* mario = dynamic_cast<CMario*>(marioObj);  // Cast to CMario to access Mario-specific methods

    float marioX, marioY;
    mario->GetPosition(marioX, marioY);

    if (x - marioX > 0 && y - marioY < 0)
        direction = 1;
    else if (x - marioX > 0 && y - marioY > 0)
        direction = 2;
    else if (x - marioX < 0 && y - marioY < 0)
        direction = 3;
    else if (x - marioX < 0 && y - marioY > 0)
        direction = 4;
}

