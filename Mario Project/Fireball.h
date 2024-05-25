#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_FIREBALL 13000	


#define FIREBALL_BBOX_WIDTH 8
#define FIREBALL_BBOX_HEIGHT 9


class CFireball : public CGameObject {
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	ULONGLONG state_start;
public:
	CFireball(float x, float y) : CGameObject(x, y) {
		
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};