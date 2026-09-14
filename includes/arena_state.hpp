#pragma once

#include "abstract_state.hpp"

class ArenaState : public AbstractState
{
public:
    void run() override;
    explicit ArenaState(GameEngine &engine) : AbstractState(engine) {}

    std::string name() const override;
};
