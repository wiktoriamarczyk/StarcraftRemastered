#include "Battlecruiser.h"
#include "Engine.h"

class Engine;

static bool CompareFloats(float a, float b)
{
    return fabs(a - b) < 0.01f;
}

bool Battlecruiser::Initialize()
{
    m_CurrentPosition = m_StartPosition;
    m_TargetPosition = nullopt;
    return true;
}

void Battlecruiser::Update(float deltaTime)
{
    // debug
    sf::Vertex directionLine[] = {
        sf::Vertex(sf::Vector2f(m_CurrentPosition.x, m_CurrentPosition.y)),
        sf::Vertex(sf::Vector2f(m_CurrentPosition.x + m_Direction.x, m_CurrentPosition.y + m_Direction.y))
    };
    Engine::GetSingleton()->DrawLine(directionLine, 2);

    m_TargetRotation = (atan2(m_Direction.y, m_Direction.x) * 180.f / PI) + 90.f;
    if (!CompareFloats(m_TargetRotation, m_CurrentRotation))
    {
        RotateToTarget(deltaTime);
        return;
    }

    if (m_TargetPosition.has_value() &&
        vec2(m_TargetPosition.value() - m_CurrentPosition).GetLength() >= 0.01f)
    {
        MoveToTarget(deltaTime);
    }
    else
    {
        m_TargetPosition.reset();
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

void Battlecruiser::CommandMovement(vec2 position)
{
    if (m_TargetPosition.has_value() && m_TargetPosition.value() == position)
    {
        return;
    }
    m_TargetPosition = position;
}

void Battlecruiser::MoveToTarget(float deltaTime)
{
    m_Direction = m_TargetPosition.value() - m_CurrentPosition;
    vec2 normalizedDirection = m_Direction.GetNormalized();
    vec2 shiftPerFrame = normalizedDirection * m_Speed * deltaTime;

    if (shiftPerFrame.GetLength() >= m_Direction.GetLength())
    {
        SetPosition(m_TargetPosition.value());
    }
    else
    {
        SetPosition(m_CurrentPosition + shiftPerFrame);
    }
}

void Battlecruiser::RotateToTarget(float deltaTime)
{
    float rotationDiff = m_TargetRotation - m_CurrentRotation;
    while (rotationDiff > 180.0f) rotationDiff -= 360.0f;
    while (rotationDiff < -180.0f) rotationDiff += 360.0f;

    float rotationStep = m_RotationSpeed * deltaTime;
    if (fabs(rotationDiff) < rotationStep)
    {
        SetRotation(m_TargetRotation);
    }
    else
    {
        SetRotation(m_CurrentRotation + rotationStep * (rotationDiff > 0 ? 1 : -1));
    }
}