#include "Factory.h"

std::shared_ptr<GameObject> BallFactory::createGameObject()
{
    return std::make_shared<Ball>();
}

std::shared_ptr<GameObject> PlayerPaddleFactory::createGameObject()
{
    return std::make_shared<PlayerPaddle>();
}

std::shared_ptr<GameObject> AIPaddleFactory::createGameObject()
{
    return std::make_shared<AIPaddle>();
}