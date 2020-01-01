#pragma once

#include "Actor.h"

class RgbLevers : public Actor
{
public:
    RgbLevers(class Game* game);
    ~RgbLevers();
    
    void Initialize();
    void UpdateActor(float dtAsSeconds) override;
    
private:
    class Lever* m_levers[3];
    class RectComponent* m_background;
};
