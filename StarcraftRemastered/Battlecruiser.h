#pragma once
#include "AirUnit.h"

class Battlecruiser : public AirUnit
{
public:
    bool Initialize()override;
    void Update(float deltaTime)override;
    void Render(sf::RenderWindow& renderer)override;
    void CommandMovement(vec2 position)override;

private:
    int  m_ElevationIdleRange = 20;

    vector<string> m_TexturesNames = { "000.png", "001.png",  "002.png", "003.png", "004.png",
        "005.png", "006.png", "007.png", "008.png", "009.png", "010.png", "011.png", "012.png", "013.png", "014.png", "015.png", "016.png" };
    string m_TextureNamePrefix = "218_hd2_diffuse_";
    string m_TexturePath = DATA_PATH.string() + "Terran/Units/Battlecruiser/" + m_TextureNamePrefix;

    void MoveToTarget(float deltaTime);
    void RotateToTarget(float deltaTime);
};