#include "Unit.h"
#include "Engine.h"

bool Unit::Initialize()
{
    m_CurrentPosition = m_StartPosition;
    m_TargetPosition = nullopt;
    m_CurrentRotation = 0.f;
    m_TargetRotation = 0.f;
    m_CurrentTexture = make_shared<Texture>();
    return true;
}

void Unit::Render(sf::RenderWindow& renderer)
{
    // debug
    sf::Vertex directionLine[] = {
        sf::Vertex(sf::Vector2f(m_CurrentPosition.x, m_CurrentPosition.y)),
        sf::Vertex(sf::Vector2f(m_CurrentPosition.x + m_Direction.x, m_CurrentPosition.y + m_Direction.y))
    };
    Engine::GetSingleton()->DrawLine(directionLine, 2);

    // render correct texture based on rotation
    if (m_TexturesNames.empty())
    {
        return;
    }
    float angleStep = 180.f / m_TexturesNames.size();
    int textureIndex = 0;
    float angle = m_CurrentRotation;
    vec2 scale = { 1, 1 };
    if (angle > 180.f)
    {
        angle -= 360.f;
    }
    if (angle < 0)
    {
        angle = abs(angle);
        scale = { -1, 1 };
    }
    textureIndex = int(angle / angleStep) % m_TexturesNames.size();
    string textureName = m_TexturePath + m_TexturesNames[textureIndex];
    shared_ptr<Texture> texture = Engine::GetSingleton()->GetTexture(textureName);
    if (texture)
    {
        m_CurrentTexture = texture;
        vec2 position = GetPosition();
        texture->Display(renderer, position, { .DrawScale = scale });
    }
}

void Unit::CommandMovement(vec2 position)
{
    if (m_TargetPosition.has_value() && m_TargetPosition.value() == position)
    {
        return;
    }
    m_TargetPosition = position;
}

void Unit::RotateToTarget(float deltaTime, float angle)
{
    float rotationDiff = angle - m_CurrentRotation;
    while (rotationDiff > 180.0f) rotationDiff -= 360.0f;
    while (rotationDiff < -180.0f) rotationDiff += 360.0f;

    float rotationStep = m_RotationSpeed * deltaTime;
    float finalRotation = 0;
    if (fabs(rotationDiff) < rotationStep)
    {
        finalRotation = angle;
    }
    else
    {
        finalRotation = m_CurrentRotation + rotationStep * (rotationDiff > 0 ? 1 : -1);
    }
    SetRotation(finalRotation);
}