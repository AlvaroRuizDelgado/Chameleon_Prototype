#include "TextureHolder.h"

#include <stdio.h>
#include <assert.h>

TextureHolder* TextureHolder::s_Instance_ = nullptr;

TextureHolder::TextureHolder()
{
    assert(s_Instance_ == nullptr);
    s_Instance_ = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
    // Get a reference to textures_ using s_Instance_
    auto& m = s_Instance_->textures_;
    
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
        texture.loadFromFile("Resources/" + filename);
        return texture;
    }
}
