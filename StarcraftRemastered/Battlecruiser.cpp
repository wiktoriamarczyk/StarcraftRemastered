#include "Battlecruiser.h"
#include "Engine.h"

class Engine;

bool Battlecruiser::Initialize()
{
    m_CurrentPosition = m_StartPosition;
    m_TargetPosition = nullopt;
    return true;
}

void Battlecruiser::Update(float deltaTime)
{
    if (m_TargetPosition.has_value() && m_TargetPosition.value() != m_CurrentPosition)
    {
        m_Direction = m_TargetPosition.value() - m_CurrentPosition;
        vec2 normalizedDirection = m_Direction.GetNormalized();
        vec2 shiftPerFrame = normalizedDirection * m_Speed * deltaTime;

        // debug - draw the direction
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(m_CurrentPosition.x, m_CurrentPosition.y)),
            sf::Vertex(sf::Vector2f(m_CurrentPosition.x + m_Direction.x, m_CurrentPosition.y + m_Direction.y))
        };
        Engine::GetSingleton()->DrawLine(line, 2);

        if (shiftPerFrame.GetLength() >= m_Direction.GetLength())
        {
            SetPosition(m_TargetPosition.value());
        }
        else
        {
            SetPosition(m_CurrentPosition + shiftPerFrame);
        }
    }
    else
    {
        m_TargetPosition.reset();
    }


    m_TargetRotation = (atan2(m_Direction.y, m_Direction.x) * 180.f / PI) + 90.f;
    if (m_TargetRotation != m_CurrentRotation)
    {
        float rotationDiff = m_TargetRotation - m_CurrentRotation;
        while (rotationDiff >= 180.0f) rotationDiff -= 360.0f;
        while (rotationDiff < -180.0f) rotationDiff += 360.0f;
        m_CurrentRotation += rotationDiff * m_RotationSpeed;
    }

}

void Battlecruiser::Render(sf::RenderWindow& renderer)
{
    shared_ptr<Texture> texture = Engine::GetSingleton()->GetTexture(m_TexturePath);
    if (texture)
    {
        DisplayParameters params;
        params.Rotation = m_CurrentRotation;
        vec2 position = GetPosition();
        texture->Display(renderer, position, params);
    }
}

void Battlecruiser::Move(vec2 position)
{
    if (m_TargetPosition.has_value() && m_TargetPosition.value() == position)
    {
        return;
    }
    m_TargetPosition = position;
}
