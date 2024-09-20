#pragma once
#include "Common.h"
#include "Race.h"
#include "Texture.h"

class Unit
{
public:
    virtual bool Initialize();
    virtual void Update(float deltaTime)=0;
    virtual void Render(sf::RenderWindow& renderer);

    virtual void CommandMovement(vec2 position);
    virtual vec2 GetPosition()const { return m_CurrentPosition; }
    virtual void SetPosition(vec2 position) { m_CurrentPosition = position; }
    virtual float GetRotation()const { return m_CurrentRotation; }
    virtual void SetRotation(float rotation) { m_CurrentRotation = rotation; }

protected:
    virtual void RotateToTarget(float deltaTime, float angle);
    virtual void MoveToTarget(float deltaTime, vec2 position)=0;

    vec2                m_StartPosition = vec2(800, 500);
    vec2                m_CurrentPosition;
    vec2                m_Direction;
    optional<vec2>      m_TargetPosition = nullopt;
    float               m_TargetRotation = 0.f;
    float               m_Speed = 400.0f;
    float               m_RotationSpeed = 220.f;
    float               m_CurrentRotation = 0.f;
    vector<string>      m_TexturesNames {};
    string              m_TextureNamePrefix = "";
    string              m_TexturePath = "";
    shared_ptr<Texture> m_CurrentTexture = make_shared<Texture>();
};