#include "Coin.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}
void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

}
void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}
void CCoin::SetState(int state)
{
	if (state == COIN_STATE_SPAWN) {
		vy = -COIN_JUMP_SPEED;
	}
	
	CGameObject::SetState(state);
}
