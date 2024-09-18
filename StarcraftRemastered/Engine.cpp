#include "Engine.h"
#include "Battlecruiser.h"

Engine* Engine::pSingleton = nullptr;

Engine* Engine::GetSingleton()
{
    return pSingleton;
}

bool Engine::Initialize()
{
    pSingleton = this;

    srand(time(NULL));

    m_Renderer.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), APP_NAME);

    shared_ptr<Battlecruiser> battlecruiser = make_shared<Battlecruiser>();
    battlecruiser->Initialize();
    m_Units.push_back(battlecruiser);

    return true;
}

void Engine::Loop()
{
    while (m_Renderer.isOpen())
    {
        sf::Event event;
        while (m_Renderer.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_Renderer.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                OnKeyDown(event.key.code);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                OnMouseButtonDown(event.mouseButton.button);
            }
        }

        sf::Clock clock;
        auto timePassed = clock.getElapsedTime();
        sf::sleep(sf::milliseconds(1000 / 60) - timePassed);

        m_Renderer.clear();
        Render();
        for(auto & unit : m_Units)
        {
            unit->Update(1.0f / m_FramesPerSec);
            unit->Render(m_Renderer);
        }

        m_Renderer.display();
    }
}

shared_ptr<Texture> Engine::GetTexture(const string& texturePath)
{
    for (auto& texture : m_Textures)
    {
        if (texture->GetFilePath() == texturePath)
        {
            return texture;
        }
    }

    shared_ptr<Texture> texture = make_shared<Texture>();
    texture->Load(texturePath);
    if (texture)
    {
        m_Textures.push_back(texture);
    }
    return texture;
}

vec2i Engine::GetMousePos() const
{
    auto realWindowSize = GetWindow().getSize();
    vec2 SCREEN_RATIO = vec2(SCREEN_WIDTH / (float)realWindowSize.x, SCREEN_HEIGHT / (float)realWindowSize.y);
    return vec2i(int(sf::Mouse::getPosition(GetWindow()).x * SCREEN_RATIO.x), int(sf::Mouse::getPosition(GetWindow()).y * SCREEN_RATIO.y));
}

void Engine::DrawLine(sf::Vertex* line, size_t size)
{
    m_Renderer.draw(line, size, sf::Lines);
}

void Engine::OnKeyDown(sf::Keyboard::Key KeyCode)
{
}

// hacky way to test buttlecruiser
void Engine::OnMouseButtonDown(int Button)
{
    m_Units[0]->Move(GetMousePos());
}

void Engine::Render()
{
    string mapTextureName = "Reference2.png";
    string mapTexturePath = DATA_PATH.string() + mapTextureName;

    sf::Texture texture;
    texture.loadFromFile(mapTexturePath);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);

    m_Renderer.draw(sprite);
}
