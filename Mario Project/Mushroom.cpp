#include "Mushroom.h"

CMushroom::CMushroom(float x, float y,int level) : CGameObject(x, y)
{
    this->level = level;
    this->ax = 0;
    this->ay = 0;  // No gravity during the emergence
    this->initialY = y;  // Track the starting position
    die_start = -1;
    SetState(MUSHROOM_STATE_EMERGE);  // Start with the emerging state
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    if (state == MUSHROOM_STATE_DIE)
    {
        left = x - MUSHROOM_BBOX_WIDTH / 2;
        top = y - MUSHROOM_BBOX_HEIGHT_DIE / 2;
        right = left + MUSHROOM_BBOX_WIDTH;
        bottom = top + MUSHROOM_BBOX_HEIGHT_DIE;
    }
    else
    {
        left = x - MUSHROOM_BBOX_WIDTH / 2;
        top = y - MUSHROOM_BBOX_HEIGHT / 2;
        right = left + MUSHROOM_BBOX_WIDTH;
        bottom = top + MUSHROOM_BBOX_HEIGHT;
    }
}

void CMushroom::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CMushroom*>(e->obj)) return;

    if (e->ny != 0)
    {
        vy = 0;
    }
    else if (e->nx != 0)
    {
        vx = -vx;
    }
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (state == MUSHROOM_STATE_EMERGE)
    {
        y -= MUSHROOM_EMERGE_SPEED * dt;
        if (y <= initialY - MUSHROOM_EMERGE_HEIGHT)
        {
            SetState(MUSHROOM_STATE_WALKING);
        }
    }
    else
    {
        vy += ay * dt;
        vx += ax * dt;
    }

    if ((state == MUSHROOM_STATE_DIE) && (GetTickCount64() - die_start > MUSHROOM_DIE_TIMEOUT))
    {
        isDeleted = true;
        return;
    }

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
    int aniId = ID_ANI_MUSHROOM_WALKING;
    if (level==2)
    {
        aniId = ID_ANI_GREEN_MUSHROOM_WALKING;
    }

    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CMushroom::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case MUSHROOM_STATE_DIE:
        die_start = GetTickCount64();
        y += (MUSHROOM_BBOX_HEIGHT - MUSHROOM_BBOX_HEIGHT_DIE) / 2;
        vx = 0;
        vy = 0;
        ay = 0;
        break;
    case MUSHROOM_STATE_WALKING:
        vx = MUSHROOM_WALKING_SPEED;
        ay = MUSHROOM_GRAVITY;  // Apply gravity
        break;
    case MUSHROOM_STATE_EMERGE:
        vy = 0;
        break;
    }
}
