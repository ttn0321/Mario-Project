#include "Koopa.h"
#include "Goomba.h"
#include "Question.h"
#include "Koopa.h"
#include "Collision.h"
#include "Game.h"
#include "Box.h"
#include "Brick.h"

CKoopa::CKoopa(float x, float y, int level) :CGameObject(x, y)
{
    this->level = level;
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
    else if (dynamic_cast<CBrick*>(e->obj))
        OnCollisionWithBrick(e);

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
void CKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
    CBrick* brick = dynamic_cast<CBrick*>(e->obj);
    if (state == KOOPA_STATE_SHELL_SLIDE)
    {
        if (e->ny == 0)
        {
            if (brick->GetType() == 2)
            {
                if (brick->GetState() == BRICK_STATE_BEFORE)
                {
                    brick->SetState(BRICK_STATE_AFTER);

                }
            }
            else if (brick->GetType() == 1)
                e->obj->Delete();
        }
    }
}
void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
    CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
    if (state == KOOPA_STATE_SHELL_SLIDE)
    {
        if (goomba->GetState() != GOOMBA_STATE_DIE)
        {
            if (goomba->GetLevel() == 1)
                goomba->SetState(GOOMBA_STATE_DIE);
            else
                goomba->SetLevel(1);
        }
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
        // Code for when Koopa is held by another object
        // Follow the holder's position
        float hx, hy;
        holder->GetPosition(hx, hy);
        x = hx;
        y = hy - KOOPA_BBOX_HEIGHT_DIE / 2 +4; // Adjust position as needed
    }
    else
    {
        vy += ay * dt;
        vx += ax * dt;

        ULONGLONG now = GetTickCount64();

        if ((state == KOOPA_STATE_SHELL || state == KOOPA_STATE_HELD) && now - state_start > KOOPA_SHELL_TIMEOUT)
        {
            SetState(KOOPA_STATE_TRANSITION);
        }
        else if (state == KOOPA_STATE_TRANSITION && now - state_start > KOOPA_TRANSITION_TIMEOUT)
        {
            SetState(KOOPA_STATE_WALKING);
            y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
        }

        if (state == KOOPA_STATE_WALKING)
        {
            if (IsNearEdgeOfPlatform(coObjects, dt))
            {
                vx = -vx; // Turn around
            }
        }
        if (level == 3)
        {
            if (state == KOOPA_STATE_WALKING && GetTickCount64() - jump_start > KOOPA_JUMP_TIME) {
                SetState(KOOPA_STATE_JUMPING);
            }
            if (state == KOOPA_STATE_JUMPING && vy > 0) {
                SetState(KOOPA_STATE_WALKING);
            }
        }
    }

    CGameObject::Update(dt, coObjects); // Ensure dt is passed to CGameObject's Update method
    CCollision::GetInstance()->Process(this, dt, coObjects);
}



void CKoopa::Render()
{
    int aniId = ID_ANI_KOOPA_WALKING_LEFT;
    switch (level) {
    case 1:
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
        break;
    case 2:
        if (state == KOOPA_STATE_WALKING && vx < 0)
            aniId = ID_ANI_GREEN_KOOPA_WALKING_LEFT;
        else if (state == KOOPA_STATE_WALKING && vx > 0)
            aniId = ID_ANI_GREEN_KOOPA_WALKING_RIGHT;
        if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_SHELL_SLIDE || state == KOOPA_STATE_HELD)
        {
            aniId = ID_ANI_GREEN_KOOPA_SHELL;
        }
        else if (state == KOOPA_STATE_TRANSITION)
        {
            aniId = ID_ANI_GREEN_KOOPA_TRANSITION;
        }
        break;
    case 3:
        if (state == KOOPA_STATE_WALKING && vx < 0)
            aniId = ID_ANI_KOOPA_WING_WALKING_LEFT;
        else if (state == KOOPA_STATE_WALKING && vx > 0)
            aniId = ID_ANI_KOOPA_WING_WALKING_RIGHT;
        else if (state == KOOPA_STATE_JUMPING && vx < 0)
            aniId = ID_ANI_KOOPA_WING_JUMPING_LEFT;
        else if (state == KOOPA_STATE_JUMPING && vx > 0)
            aniId = ID_ANI_KOOPA_WING_JUMPING_RIGHT;
        break;
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
        if (level == 3)
            jump_start = GetTickCount64();
        break;
    case KOOPA_STATE_TRANSITION:
        vx = 0;
        break;
    case KOOPA_STATE_HELD:
        vx = 0;
        vy = 0;
        isHeld = true;
        break;
    case KOOPA_STATE_JUMPING:
        vy = -KOOPA_JUMP_SPEED;
        break;
    }
}


bool CKoopa::IsNearEdgeOfPlatform(vector<LPGAMEOBJECT>* coObjects, DWORD dt)
{
    // Calculate future position 16 pixels ahead in the direction of movement
    float futureX = x + vx * dt + (vx > 0 ? 16 : -16);

    // Create a hypothetical future Koopa to check if it would fall off
    CKoopa futureKoopa = *this;  // Create a copy of the current Koopa
    futureKoopa.SetPosition(futureX, y);  // Move the future Koopa to the calculated position

    // Assume the future Koopa is falling due to gravity (adjust as per your game's logic)
    futureKoopa.vy += ay * dt;

    // Scan collisions for the future Koopa (which checks if it would fall)
    vector<LPCOLLISIONEVENT> coEvents;
    CCollision::GetInstance()->Scan(&futureKoopa, dt, coObjects, coEvents);

    // Check if the future Koopa is falling (no collisions below)
    bool nearEdge = true;
    for (auto& e : coEvents)
    {
        if (e->ny < 0)  // If there is a collision below the future Koopa, it's not near an edge
        {
            nearEdge = false;
            break;
        }
    }

    // Cleanup
    for (auto& e : coEvents)
        delete e;

    return nearEdge;
}


