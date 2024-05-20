#include "Koopa.h"

CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
    this->ax = 0;
    this->ay = KOOPA_GRAVITY;
    state_start = -1;
    SetState(KOOPA_STATE_WALKING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_SHELL_SLIDE || state == KOOPA_STATE_TRANSITION)
    {
        left = x - KOOPA_BBOX_WIDTH / 2;
        top = y - KOOPA_BBOX_HEIGHT_DIE / 2;
        right = left + KOOPA_BBOX_WIDTH;
        bottom = top + KOOPA_BBOX_HEIGHT_DIE;
    }
    else
    {
        left = x - KOOPA_BBOX_WIDTH / 2;
        top = y - KOOPA_BBOX_HEIGHT / 2;
        right = left + KOOPA_BBOX_WIDTH;
        bottom = top + KOOPA_BBOX_HEIGHT;
    }
}

void CKoopa::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CKoopa*>(e->obj)) return;

    if (e->ny != 0)
    {
        vy = 0;
    }
    else if (e->nx != 0)
    {
        vx = -vx;
    }
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (isHeld && holder)
    {
        float hx, hy;
        // Follow the holder's position
        holder->GetPosition(hx, hy);
        x = hx;
        y = hy - KOOPA_BBOX_HEIGHT_DIE / 2; // Adjust position as needed
    }
    else
    {
        vy += ay * dt;
        vx += ax * dt;

        ULONGLONG now = GetTickCount64();

        if ((state == KOOPA_STATE_SHELL || state == KOOPA_STATE_SHELL_SLIDE) && now - state_start > KOOPA_SHELL_TIMEOUT)
        {
            SetState(KOOPA_STATE_TRANSITION);
        }
        else if (state == KOOPA_STATE_TRANSITION && now - state_start > KOOPA_TRANSITION_TIMEOUT)
        {
            SetState(KOOPA_STATE_WALKING);
            y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
        }

        if (state == KOOPA_STATE_WALKING && IsNearEdgeOfPlatform(coObjects))
        {
            vx = -vx; // Turn around
        }
    }

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{
    int aniId = ID_ANI_KOOPA_WALKING_LEFT;
    if (state == KOOPA_STATE_WALKING && vx < 0)
        aniId = ID_ANI_KOOPA_WALKING_LEFT;
    else if (state == KOOPA_STATE_WALKING && vx > 0)
        aniId = ID_ANI_KOOPA_WALKING_RIGHT;
    if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_SHELL_SLIDE || state == KOOPA_STATE_HELD)
    {
        aniId = ID_ANI_KOOPA_SHELL;
    }
    else if (state == KOOPA_STATE_TRANSITION)
    {
        aniId = ID_ANI_KOOPA_TRANSITION;
    }
    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
    CGameObject::SetState(state);
    state_start = GetTickCount64();
    switch (state)
    {
    case KOOPA_STATE_SHELL:
        y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
        vx = 0;
        vy = 0;
        break;
    case KOOPA_STATE_SHELL_SLIDE:
        vx = -KOOPA_SLIDING_SPEED;
        break;
    case KOOPA_STATE_WALKING:
        vx = -KOOPA_WALKING_SPEED;
        break;
    case KOOPA_STATE_TRANSITION:
        vx = 0;
        break;
    case KOOPA_STATE_HELD:
        vx = 0;
        vy = 0;
        isHeld = true;
        break;
    }
}


bool CKoopa::IsNearEdgeOfPlatform(vector<LPGAMEOBJECT>* coObjects)
{
    float xProbe = x + (vx > 0 ? KOOPA_BBOX_WIDTH / 2 : -KOOPA_BBOX_WIDTH / 2);
    float yProbe = y + KOOPA_BBOX_HEIGHT / 2 + 1; // Slightly below the Koopa's feet

    for (auto obj : *coObjects)
    {
        float l, t, r, b;
        obj->GetBoundingBox(l, t, r, b);
        if (dynamic_cast<CPlatform*>(obj)) // Assuming you have a platform class
        {
            if (xProbe > l && xProbe < r && yProbe > t && yProbe < b)
            {
                return false; // Ground detected
            }
        }
    }
    return true; // No ground detected
}
