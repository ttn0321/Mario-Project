#pragma once

#include "GameObject.h"

class CVertical : public CGameObject
{
protected:
    int length;             // Unit: cell
    float cellWidth;
    float cellHeight;
    int spriteIdTopLeft, spriteIdTopRight, spriteIdBottomLeft, spriteIdBottomRight;

public:
    CVertical(float x, float y,
        float cell_width, float cell_height, int length,
        int sprite_id_top_left, int sprite_id_top_right, int sprite_id_bottom_left, int sprite_id_bottom_right) :CGameObject(x, y)
    {
        this->length = length;
        this->cellWidth = cell_width;
        this->cellHeight = cell_height;
        this->spriteIdTopLeft = sprite_id_top_left;
        this->spriteIdTopRight = sprite_id_top_right;
        this->spriteIdBottomLeft = sprite_id_bottom_left;
        this->spriteIdBottomRight = sprite_id_bottom_right;
    }

    void Render();
    void Update(DWORD dt) {}
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    void RenderBoundingBox();
    int IsBlocking() { return 0; }
};

typedef CVertical* LPVERTICAL;
