#include "Pipe.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CPipe::RenderBoundingBox()
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

    float yy = y - this->cellHeight / 2 + rect.bottom / 2;

    CGame::GetInstance()->Draw(x - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPipe::Render()
{
    if (this->length <= 0) return;
    float yy = y;
    CSprites* s = CSprites::GetInstance();

    s->Get(this->spriteIdTopLeft)->Draw(x - this->cellWidth / 2, yy);
    s->Get(this->spriteIdTopRight)->Draw(x + this->cellWidth / 2, yy);
    yy += this->cellHeight;
    for (int i = 1; i < this->length - 1; i++)
    {
        s->Get(this->spriteIdBottomLeft)->Draw(x - this->cellWidth / 2, yy);
        s->Get(this->spriteIdBottomRight)->Draw(x + this->cellWidth / 2, yy);
        yy += this->cellHeight;
    }
    if (length > 1)
    {
        s->Get(this->spriteIdBottomLeft)->Draw(x - this->cellWidth / 2, yy);
        s->Get(this->spriteIdBottomRight)->Draw(x + this->cellWidth / 2, yy);
    }

    RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    float cellHeight_div_2 = this->cellHeight / 2;
    l = x - this->cellWidth / 2 -8;
    t = y - cellHeight_div_2;
    r = l + this->cellWidth +18;
    b = t + this->cellHeight * this->length;
}
