#include "Brick.h"
#include "Switch.h"
#include "PlayScene.h"
#include "Game.h"
void CBrick::Render()
{
    int aniId = ID_ANI_BRICK_BEFORE;
    if (state == BRICK_STATE_AFTER) {
        aniId = ID_ANI_BRICK_AFTER;
    }
    CAnimations* animations = CAnimations::GetInstance();
    animations->Get(aniId)->Render(x, y);
    // RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}
void CBrick::SetState(int state)
{
    CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    LPGAMEOBJECT marioObj = currentScene->GetPlayer();
    if (state == BRICK_STATE_AFTER && type == 2)
    {
        CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
        vector<LPGAMEOBJECT>& objects = currentScene->GetObjects();

        CSwitch* sw = new CSwitch(x, y - 16);

        objects.push_back(sw);
    }
    CGameObject::SetState(state);
}
