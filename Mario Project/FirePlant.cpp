#include "FirePlant.h"
void CFirePlant::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIRE_PLANT)->Render(x, y);
	RenderBoundingBox();
}

void CFirePlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIRE_PLANT_BBOX_WIDTH / 2;
	t = y - FIRE_PLANT_BBOX_HEIGHT / 2;
	r = l + FIRE_PLANT_BBOX_WIDTH;
	b = t + FIRE_PLANT_BBOX_HEIGHT;
}