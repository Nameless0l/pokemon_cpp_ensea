#pragma once

#include "abstract_state.hpp"

class ExplorationState : public AbstractState
{
public:
    void run() override;
    explicit ExplorationState(GameEngine &engine) : AbstractState(engine) {}

    std::string name() const override;
};
