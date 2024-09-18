#pragma once
#include "Common.h"
#include "Unit.h"
#include "Texture.h"

using TexturesVec = vector<shared_ptr<Texture>>;

class Engine
{
public:
    static Engine* GetSingleton();
    bool Initialize();
    void Loop();
    shared_ptr<Texture> GetTexture(const string& texturePath);
    vec2i GetMousePos()const;
    const sf::Window& GetWindow()const { return m_Renderer; }
    void DrawLine(sf::Vertex* line, size_t size);

private:
    static Engine* pSingleton;
    sf::RenderWindow m_Renderer;
    vector<shared_ptr<Unit>> m_Units;
    TexturesVec m_Textures;
    float m_FramesPerSec = 60.0f;

    void OnKeyDown(sf::Keyboard::Key KeyCode);
    void OnMouseButtonDown(int Button);
    void Render();
};
