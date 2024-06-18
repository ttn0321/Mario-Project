#include "Koopa.h"
#include "Goomba.h"
#include "Question.h"
#include "Koopa.h"
#include "Collision.h"
#include "Game.h"
#include "Box.h"

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
    if (dynamic_cast<CGoomba*>(e->obj))
        OnCollisionWithGoomba(e);
    else if (dynamic_cast<CKoopa*>(e->obj))
        OnCollisionWithKoopa(e);
    else if (dynamic_cast<CQuestion*>(e->obj))
        OnCollisionWithQuestion(e);

    if (!e->obj->IsBlocking()) return;

    if (e->ny != 0)
    {
        vy = 0;
        if (e->ny < 0) isOnPlatform = true;
    }
    else if (e->nx != 0)
    {
        if (dynamic_cast<CBox*>(e->obj))
            return;
        vx = -vx;
    }
}


void CKoopa::OnCollisionWithQuestion(LPCOLLISIONEVENT e)
{
    CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    LPGAMEOBJECT marioObj = currentScene->GetPlayer();
    CMario* mario = dynamic_cast<CMario*>(marioObj);  // Cast to CMario to access Mario-specific methods
    CQuestion* question = dynamic_cast<CQuestion*>(e->obj);

    if (state == KOOPA_STATE_SHELL_SLIDE)
    {
        if (e->ny == 0)
        {
            if (question->GetState() != QUESTION_STATE_AFTER)
            {
                question->SetState(QUESTION_STATE_AFTER);
                if (question->GetContain() == 1)
                {
                    mario->addCoin();  // Increase Mario's coin count
                }
            }
        }
    }
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
    CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
    if (state == KOOPA_STATE_SHELL_SLIDE)
    {
        goomba->SetState(GOOMBA_STATE_DIE);
    }
}
void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
    CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
    if (state == KOOPA_STATE_SHELL_SLIDE)
    {
        if (koopa->GetState() == KOOPA_STATE_WALKING || koopa->GetState() == KOOPA_STATE_TRANSITION)
        {
            koopa->SetState(KOOPA_STATE_SHELL);
            vx = -vx;
        }
        if (koopa->GetState() == KOOPA_STATE_SHELL || koopa->GetState() == KOOPA_STATE_SHELL_SLIDE) {

            if (vx > 0)
            {
                koopa->SetState(KOOPA_STATE_SHELL_SLIDE);
                koopa->SetSpeed(KOOPA_SLIDING_SPEED, 0);
            }
            else if (vx < 0)
            {
                koopa->SetState(KOOPA_STATE_SHELL_SLIDE);
                koopa->SetSpeed(-KOOPA_SLIDING_SPEED, 0);
            }
            vx = -vx;
        }
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
        vx = 0;
        vy = 0;
        y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
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
    
}
