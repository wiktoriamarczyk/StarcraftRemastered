#pragma once
#include "Texture.h"

bool Texture::Load(const string& texturePath)
{
    m_FilePath = texturePath;

    if (!m_Texture.loadFromFile(DATA_PATH.string() + texturePath))
    {
        printf("Texture could not be loaded!\n");
        return false;
    }

    SetSize(m_Texture.getSize());
    return true;
}

void Texture::SetSize(vec2i Size)
{
    m_Size = Size;
}

vec2i Texture::GetSize()const
{
    return m_Size;
}

string Texture::GetFilePath()const
{
    return m_FilePath;
}

void Texture::Display(sf::RenderWindow& renderer, vec2 position, DisplayParameters param) const
{
    sf::Sprite sprite;
    sprite.setTexture(m_Texture);
    sprite.setPosition(position.x, position.y);
    sprite.setScale(param.DrawScale);
    sprite.setColor(param.DrawColor);
    sprite.setOrigin(param.Pivot * GetSize());
    sprite.setRotation(param.Rotation);
    renderer.draw(sprite);
}

