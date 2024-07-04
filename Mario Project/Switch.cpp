#include "Switch.h"
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
	
	CGameObject::SetState(state);
}
