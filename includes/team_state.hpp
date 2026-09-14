#pragma once

#include "abstract_state.hpp"

class TeamState : public AbstractState
{
public:
    void run() override;
    explicit TeamState(GameEngine &engine) : AbstractState(engine) {}

    std::string name() const override;
};
