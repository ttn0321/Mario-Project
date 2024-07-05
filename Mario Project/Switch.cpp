#include "Switch.h"
#include "Brick.h"
#include "PlayScene.h"
#include "Game.h"
void CSwitch::Render() {
    int aniId = ID_ANI_SWITCH_BEFORE;
    if (state == SWITCH_STATE_AFTER) {
        aniId = ID_ANI_SWITCH_AFTER;
    }
    CAnimations* animations = CAnimations::GetInstance();
    animations->Get(aniId)->Render(x, y);
    // RenderBoundingBox();
}

void CSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SWITCH_BBOX_WIDTH / 2;
	t = y - SWITCH_BBOX_HEIGHT / 2;
	r = l + SWITCH_BBOX_WIDTH;
	b = t + SWITCH_BBOX_HEIGHT;
}
void CSwitch::SetState(int state)
{
    if (state == SWITCH_STATE_AFTER) {
        CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
        vector<LPGAMEOBJECT>& objects = currentScene->GetObjects();
        for (int i = 0; i < objects.size(); i++)
        {
            if (dynamic_cast<CBrick*>(objects[i]) != nullptr)
            {
                objects[i]->SetState(BRICK_STATE_COIN);
            }
        }
    }
	CGameObject::SetState(state);
}
