#include "AirUnit.h"
#include "Engine.h"

void AirUnit::RenderShadow(sf::RenderWindow& renderer, string& textureName)
{
    shared_ptr<Texture> texture = Engine::GetSingleton()->GetTexture(textureName);
    if (texture)
    {
    }
}
