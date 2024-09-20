#include "Battlecruiser.h"
#include "Engine.h"

class Engine;

static bool AreFloatsEqual(float a, float b)
{
    return fabs(a - b) < 0.01f;
}

bool Battlecruiser::Initialize()
{
    Unit::Initialize();
    m_TexturesNames = { "000.png", "001.png",  "002.png", "003.png", "004.png",
        "005.png", "006.png", "007.png", "008.png", "009.png", "010.png", "011.png", "012.png", "013.png", "014.png", "015.png", "016.png" };
    m_TextureNamePrefix = "218_hd2_diffuse_";
    m_TexturePath = DATA_PATH.string() + "Terran/Units/Battlecruiser/" + m_TextureNamePrefix;
    return true;
}

void Battlecruiser::Update(float deltaTime)
{
    m_TargetRotation = (atan2(m_Direction.y, m_Direction.x) * 180.f / PI) + 90.f;
    if (!AreFloatsEqual(m_TargetRotation, m_CurrentRotation))
    {
        RotateToTarget(deltaTime, m_TargetRotation);
        return;
    }

    if (m_TargetPosition.has_value() &&
        vec2(m_TargetPosition.value() - m_CurrentPosition).GetLength() >= 0.01f)
    {
        MoveToTarget(deltaTime, m_TargetPosition.value());
    }
    else
    {
        m_TargetPosition.reset();
    }
}

void Battlecruiser::Render(sf::RenderWindow& renderer)
{
    AirUnit::Render(renderer);
}