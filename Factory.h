#pragma once
#include "GameObject.h"

#include <memory>

class Factory
{
public:
    virtual ~Factory() {}
    virtual std::shared_ptr<GameObject> createGameObject() = 0;
};

class BallFactory : public Factory
{
public:
    virtual std::shared_ptr<GameObject> createGameObject() override;
};

class PaddleFactory : public Factory
{
};

class PlayerPaddleFactory : public PaddleFactory
{
public:
    virtual std::shared_ptr<GameObject> createGameObject() override;
};

class AIPaddleFactory : public PaddleFactory
{
public:
    virtual std::shared_ptr<GameObject> createGameObject() override;
};