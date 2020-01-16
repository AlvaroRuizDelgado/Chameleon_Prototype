#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{
public:
    TextureHolder();
    static sf::Texture& GetTexture(std::string const& filename);
    
private:
    std::map<std::string, sf::Texture> m_textures;

    // A static pointer of the same type as the class itself.
    static TextureHolder* s_Instance;
};
