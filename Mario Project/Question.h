#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define QUESTION_WIDTH 16
#define QUESTION_BBOX_WIDTH 16
#define QUESTION_BBOX_HEIGHT 16

#define QUESTION_STATE_BEFORE 100
#define QUESTION_STATE_AFTER 200

#define ID_ANI_QUESTION_BEFORE 7000
#define ID_ANI_QUESTION_AFTER 7001

class CQuestion: public CGameObject {
public:
	CQuestion(float x, float y);
	virtual void SetState(int state);
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};