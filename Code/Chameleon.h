#pragma once

#include "Actor.h"
#include "Color.h"

class Chameleon : public Actor
{
public:
	Chameleon(class Game* game, class Color& color);
    ~Chameleon();
    
	void Initialize();
	void UpdateActor(float dtAsSeconds) override;

    // Getters / setters
    void SetColor(Color newColor);
    Color GetColor() { return m_color; };
    
private:
    static constexpr int NUM_LAYERS{ 3 };
    static constexpr int NUM_EYES{ 2 };
    const float CHANGE_PER_SEC[NUM_LAYERS]{ 3.f, 0.5f, 0.8f };
    const int INITIAL_COLOR[3]{ 77, 133, 63 };

    Color& m_color;
    
    class SpriteComponent* m_spriteEyesWhite;
    class SpriteComponent* m_spriteLayer[NUM_LAYERS];
    class EyeComponent* m_eyeComponent[NUM_EYES];
};
