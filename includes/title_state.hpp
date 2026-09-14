#pragma once

#include "abstract_state.hpp"

class TitleState : public AbstractState
{
public:
    void run() override;
    explicit TitleState(GameEngine &engine) : AbstractState(engine) {}

    std::string name() const override;
};
