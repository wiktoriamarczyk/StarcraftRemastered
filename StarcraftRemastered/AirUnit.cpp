#include "AirUnit.h"
#include "Engine.h"

void AirUnit::Render(sf::RenderWindow& renderer)
{
    Unit::Render(renderer);
    // render shadow
    vec2 scale = m_CurrentRotation < 0 ? vec2(-1, 1) : vec2(1, 1);
    m_CurrentTexture->Display(renderer, m_CurrentPosition + vec2(0, 50), { .DrawScale = scale, .DrawColor = sf::Color(0, 0, 0, 100) });
}

void AirUnit::MoveToTarget(float deltaTime, vec2 position)
{
    m_Direction = position - m_CurrentPosition;
    vec2 normalizedDirection = m_Direction.GetNormalized();
    vec2 shiftPerFrame = normalizedDirection * m_Speed * deltaTime;
    vec2 finalPosition = {};
    if (shiftPerFrame.GetLength() >= m_Direction.GetLength())
    {
        finalPosition = position;
    }
    else
    {
        finalPosition = m_CurrentPosition + shiftPerFrame;
    }
    SetPosition(finalPosition);
}
