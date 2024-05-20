#include "Question.h"
#include "Mushroom.h"
#include "PlayScene.h"
#include "Game.h"

CQuestion::CQuestion(float x, float y, int contain) : CGameObject(x, y) {
    this->contain = contain;
    SetState(QUESTION_STATE_BEFORE);
}

void CQuestion::Render() {
    int aniId = ID_ANI_QUESTION_BEFORE;
    if (state == QUESTION_STATE_AFTER) {
        aniId = ID_ANI_QUESTION_AFTER;
    }

    CAnimations* animations = CAnimations::GetInstance();
    animations->Get(aniId)->Render(x, y);
    //RenderBoundingBox();
}

void CQuestion::GetBoundingBox(float& l, float& t, float& r, float& b) {
    l = x - QUESTION_BBOX_WIDTH / 2;
    t = y - QUESTION_BBOX_HEIGHT / 2;
    r = l + QUESTION_BBOX_WIDTH;
    b = t + QUESTION_BBOX_HEIGHT;
}

void CQuestion::SetState(int state) {
    if (state == QUESTION_STATE_AFTER && contain == 6) {
        // Get the current scene
        CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
        vector<LPGAMEOBJECT>& objects = currentScene->GetObjects();

        // Create a mushroom object
        CMushroom* mushroom = new CMushroom(x, y - 16);  // Adjust the y position as needed
        mushroom->SetState(MUSHROOM_STATE_WALKING);

        // Add the mushroom to the scene objects
        objects.push_back(mushroom);
    }

    CGameObject::SetState(state);
}
