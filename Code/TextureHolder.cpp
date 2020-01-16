#include "TextureHolder.h"

#include <iostream>
#include <stdio.h>
#include <assert.h>

TextureHolder* TextureHolder::s_Instance = nullptr;

TextureHolder::TextureHolder()
{
    assert(s_Instance == nullptr);
    s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
    // Get a reference to m_textures using s_Instance
    auto& m = s_Instance->m_textures;
    
    // Create an iterator to hold a key-value pair and search for filename.
    auto keyValuePair = m.find(filename);   // auto == map<string, sf::Texture)::iterator
    
    if (keyValuePair != m.end())
    {
        return keyValuePair->second;    // The value Texture is the second parameter
    }
    else
    {
        // Filename not found, add the texture
        auto& texture = m[filename];
        std::cout << "Loading file " << filename << std::endl;
        if (!texture.loadFromFile(filename))
        {
            std::cout << " - Couldn't load " << filename << std::endl;
        }
        texture.loadFromFile(filename);
        return texture;
    }
}
