#include "Box.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"

void CBox::RenderBoundingBox()
{
    D3DXVECTOR3 p(x, y, 0);
    RECT rect;

    LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

    float l, t, r, b;

    GetBoundingBox(l, t, r, b);
    rect.left = 0;
    rect.top = 0;
    rect.right = (int)r - (int)l;
    rect.bottom = (int)b - (int)t;

    float cx, cy;
    CGame::GetInstance()->GetCamPos(cx, cy);

    float xx = x - this->cellWidth * width / 2 + rect.right / 2;

    CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CBox::Render()
{
    if (this->width <= 0 || this->height <= 0) return;

    float startX = x - (width * cellWidth) / 2;
    float startY = y - (height * cellHeight) / 2;

    CSprites* s = CSprites::GetInstance();

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            float xx = startX + col * cellWidth;
            float yy = startY + row * cellHeight;

            if (row == 0 && col == 0)
                s->Get(this->spriteIdTopLeft)->Draw(xx, yy);
            else if (row == 0 && col == width - 1)
                s->Get(this->spriteIdTopRight)->Draw(xx, yy);
            else if (row == 0)
                s->Get(this->spriteIdTopCenter)->Draw(xx, yy);
            else if (row == height - 1 && col == 0)
                s->Get(this->spriteIdBottomLeft)->Draw(xx, yy);
            else if (row == height - 1 && col == width - 1)
                s->Get(this->spriteIdBottomRight)->Draw(xx, yy);
            else if (row == height - 1)
                s->Get(this->spriteIdBottomCenter)->Draw(xx, yy);
            else if (col == 0)
                s->Get(this->spriteIdMiddleLeft)->Draw(xx, yy);
            else if (col == width - 1)
                s->Get(this->spriteIdMiddleRight)->Draw(xx, yy);
            else
                s->Get(this->spriteIdMiddleCenter)->Draw(xx, yy);
        }
    }

    //RenderBoundingBox();
}

void CBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    float halfCellWidth = this->cellWidth / 2;
    l = x - (this->width * this->cellWidth) / 2 - 8;
    t = y - (this->height * this->cellHeight) / 2 - 8;
    r = l + this->width * this->cellWidth;
    b = t + this->cellHeight-14; // Bounding box only at the top row
}

int CBox::IsDirectionColliable(float nx, float ny)
{
    if (nx == 0 && ny == -1) return 1;
    else return 0;
}