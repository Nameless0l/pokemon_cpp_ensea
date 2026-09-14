#pragma once

#include "abstract_state.hpp"

class EncounterState : public AbstractState
{
public:
    void run() override;
    explicit EncounterState(GameEngine &engine) : AbstractState(engine) {}

    std::string name() const override;
};
