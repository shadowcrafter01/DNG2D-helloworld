#pragma once

#include <DNG2D/Main.hpp>

class CustomDingus : public DNG::Dingus
{
private:
    DNG::Audio *_collisionSound = nullptr;

public:
    CustomDingus(DNG::Camera *camera, DNG::Texture *texture, DNG::Vector2<float> pos = {0, 0})
    {
        AssignCamera(camera);
        AssignTexture(texture);
        SetTransform(DNG::Transform2<float>(pos, texture->GetSize()));
        AssignCollisionShape(DNG::CollisionShape::CreateBox(GetTransform().size));
    }

    void AssignCollisionSound(DNG::Audio *audio)
    {
        _collisionSound = audio;
    }

    void Update() override
    {
    }
    void OnCollision(Dingus *other) override
    {
        if (_collisionSound)
        {
            float collisionSpeed = (this->GetVelocity() - other->GetVelocity()).Magnitude() * 0.1;
            DNG::Audio::Play(_collisionSound, DNG::Math::Clamp(collisionSpeed, 0.0f, 1.0f), DNG::Random::GetNext(0.75, 1.25));
        }
    }
};
