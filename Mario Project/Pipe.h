#pragma once

#include "GameObject.h"
#define ID_SPRITE_PIPE_TOP_LEFT 140000
#define ID_SPRITE_PIPE_TOP_RIGHT (ID_SPRITE_PIPE_TOP_LEFT +100)
#define ID_SPRITE_PIPE_BOTTOM_LEFT (ID_SPRITE_PIPE_TOP_LEFT +200)
#define ID_SPRITE_PIPE_BOTTOM_RIGHT (ID_SPRITE_PIPE_TOP_LEFT +300)
#define PIPE_STATE_NORMAL   100
#define PIPE_STATE_PORTAL   200

class CPipe : public CGameObject
{
protected:
    int length;             // Unit: cell
    float cellWidth;
    float cellHeight;
    int spriteIdTopLeft, spriteIdTopRight, spriteIdBottomLeft, spriteIdBottomRight;
    int contain;
public:
    CPipe(float x, float y,int length, int contain) :CGameObject(x, y)
    {
        this->length = length;
        this->cellWidth = 16;
        this->cellHeight = 16;
        this->contain = contain;
        this->spriteIdTopLeft = ID_SPRITE_PIPE_TOP_LEFT;
        this->spriteIdTopRight = ID_SPRITE_PIPE_TOP_RIGHT;
        this->spriteIdBottomLeft = ID_SPRITE_PIPE_BOTTOM_LEFT;
        this->spriteIdBottomRight = ID_SPRITE_PIPE_BOTTOM_RIGHT;
        AddMob();

    }
    virtual void SetState(int state);
    virtual int IsBlocking();
    void Render();
    void Update(DWORD dt) {}
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    void RenderBoundingBox();
    void AddMob();
    int GetContain() { return contain; }
};

typedef CPipe* LPPIPE;
