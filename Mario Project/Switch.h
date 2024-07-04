#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define SWITCH_BBOX_WIDTH			16
#define SWITCH_BBOX_HEIGHT			16

#define SWITCH_STATE_BEFORE 100
#define SWITCH_STATE_AFTER 200

#define ID_ANI_SWITCH_BEFORE 16000
#define ID_ANI_SWITCH_AFTER 16001


class CSwitch : public CGameObject {
public:
	CSwitch(float x, float y) : CGameObject(x, y) {
        SetState(SWITCH_STATE_BEFORE);
    }
    virtual void SetState(int state);
    void Render();
    void Update(DWORD dt);
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    int IsBlocking() { return 0; }
};