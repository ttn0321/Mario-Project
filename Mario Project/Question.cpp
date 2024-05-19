#include "Question.h"
CQuestion::CQuestion(float x, float y) {
	SetState(QUESTION_STATE_BEFORE);
}
void CQuestion::Render()
{
	int aniId = ID_ANI_QUESTION_BEFORE;
	if (state == QUESTION_STATE_AFTER)
	{
		aniId = ID_ANI_QUESTION_AFTER;
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTION_BBOX_WIDTH / 2;
	t = y - QUESTION_BBOX_HEIGHT / 2;
	r = l + QUESTION_BBOX_WIDTH;
	b = t + QUESTION_BBOX_HEIGHT;
}
void CQuestion::SetState(int state)
{
	CGameObject::SetState(state);
}
