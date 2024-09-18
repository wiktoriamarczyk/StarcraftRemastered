#pragma once
#include "Common.h"

class Texture
{
public:
    bool Load(const string& texturePath);
    virtual void Display(sf::RenderWindow& renderer, vec2 position, DisplayParameters param = {})const;
    void SetSize(vec2i Size);
    vec2i GetSize()const;
    string GetFilePath()const;

private:
    sf::Texture m_Texture;
    string      m_FilePath;
    vec2i       m_Size;
};