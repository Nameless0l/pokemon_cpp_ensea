#pragma once

#include "abstract_state.hpp"

class GameOverState : public AbstractState
{
public:
    void run() override;
    explicit GameOverState(GameEngine &engine) : AbstractState(engine) {}

    std::string name() const override;
};
