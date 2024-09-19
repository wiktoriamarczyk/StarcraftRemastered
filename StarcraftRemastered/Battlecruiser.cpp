#include "Battlecruiser.h"
#include "Engine.h"

class Engine;

static bool AreFloatsEqual(float a, float b)
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
    if (!AreFloatsEqual(m_TargetRotation, m_CurrentRotation))
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
    // render correct texture based on rotation
    float angleStep = 180.f / m_TexturesNames.size();
    int textureIndex = 0;
    float angle = m_CurrentRotation;
    printf("input angle: %f\n", angle);
    vec2 scale = { 1, 1 };
    if (angle > 180.f)
    {
        int fullRotations = angle / 180.f;
        printf("full rot: %d\n", fullRotations);
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
        vec2 position = GetPosition();
        texture->Display(renderer, position, { .DrawScale = scale });
        // render shadow
        texture->Display(renderer, position + vec2(0, 50), { .DrawScale = scale, .DrawColor = sf::Color(0, 0, 0, 100) });
    }

    printf("angle: %f\n", angle);
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
    vec2 finalPosition = {};
    if (shiftPerFrame.GetLength() >= m_Direction.GetLength())
    {
        finalPosition = m_TargetPosition.value();
    }
    else
    {
        finalPosition = m_CurrentPosition + shiftPerFrame;
    }
    SetPosition(finalPosition);
}

void Battlecruiser::RotateToTarget(float deltaTime)
{
    float rotationDiff = m_TargetRotation - m_CurrentRotation;
    while (rotationDiff > 180.0f) rotationDiff -= 360.0f;
    while (rotationDiff < -180.0f) rotationDiff += 360.0f;

    float rotationStep = m_RotationSpeed * deltaTime;
    float finalRotation = 0;
    if (fabs(rotationDiff) < rotationStep)
    {
        finalRotation = m_TargetRotation;
    }
    else
    {
        finalRotation = m_CurrentRotation + rotationStep * (rotationDiff > 0 ? 1 : -1);
    }
    SetRotation(finalRotation);
}