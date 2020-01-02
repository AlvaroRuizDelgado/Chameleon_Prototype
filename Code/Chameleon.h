#pragma once

#include "Actor.h"
#include "Color.h"

class Chameleon : public Actor
{
public:
	Chameleon(class Game* game);
    ~Chameleon();
    
	void Initialize();
	void UpdateActor(float dtAsSeconds) override;

    // Getters / setters
    void SetColor(Color newColor);
    Color GetColor() { return m_color; };
    
private:
    static constexpr int NUM_LAYERS{ 3 };
    static constexpr int CHANGE_PER_SEC[NUM_LAYERS]{ 255, 2, 1 };
//    static constexpr int LAYER2_CHANGE_PER_SEC{ 1.6f };
//    static constexpr int LAYER3_CHANGE_PER_SEC{ 0.8f };
    const int INITIAL_COLOR[3]{ 77, 133, 63 };

    Color m_color;
    
    class RectComponent* m_rectLayer[NUM_LAYERS];
};
