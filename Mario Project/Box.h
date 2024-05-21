#pragma once

#include "GameObject.h"

class CBox : public CGameObject
{
protected:
    int width, height;   // Width and height in cells
    float cellWidth, cellHeight;
    int spriteIdTopLeft, spriteIdTopCenter, spriteIdTopRight;
    int spriteIdMiddleLeft, spriteIdMiddleCenter, spriteIdMiddleRight;
    int spriteIdBottomLeft, spriteIdBottomCenter, spriteIdBottomRight;

public:
    CBox(float x, float y, float cell_width, float cell_height, int width, int height,
        int sprite_id_top_left, int sprite_id_top_center, int sprite_id_top_right,
        int sprite_id_middle_left, int sprite_id_middle_center, int sprite_id_middle_right,
        int sprite_id_bottom_left, int sprite_id_bottom_center, int sprite_id_bottom_right)
        : CGameObject(x, y)
    {
        this->width = width;
        this->height = height;
        this->cellWidth = cell_width;
        this->cellHeight = cell_height;
        this->spriteIdTopLeft = sprite_id_top_left;
        this->spriteIdTopCenter = sprite_id_top_center;
        this->spriteIdTopRight = sprite_id_top_right;
        this->spriteIdMiddleLeft = sprite_id_middle_left;
        this->spriteIdMiddleCenter = sprite_id_middle_center;
        this->spriteIdMiddleRight = sprite_id_middle_right;
        this->spriteIdBottomLeft = sprite_id_bottom_left;
        this->spriteIdBottomCenter = sprite_id_bottom_center;
        this->spriteIdBottomRight = sprite_id_bottom_right;
    }

    void Render();
    void Update(DWORD dt) {}
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    void RenderBoundingBox();
};

typedef CBox* LPBOX;
