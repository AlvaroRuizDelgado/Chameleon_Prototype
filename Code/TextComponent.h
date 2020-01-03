#include "DrawComponent.h"

class TextComponent : public DrawComponent
{
public:
    TextComponent(class Actor* owner, int drawPriority = 100);
    ~TextComponent();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    void Initialize(float x, float y, std::wstring initString);
    
    // Getters / setters
    void SetText(std::wstring newString);
    
private:
    std::wstring m_string;
    sf::Text m_text;
};
