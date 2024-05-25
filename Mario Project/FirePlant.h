#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_FIRE_PLANT 12000
#define FIRE_PLANT_BBOX_WIDTH 16
#define FIRE_PLANT_BBOX_HEIGHT 32

class CFirePlant : public CGameObject {
public:
	CFirePlant(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};