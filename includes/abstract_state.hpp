#pragma once

#include <string>

class GameEngine;

class AbstractState
{
protected:
    GameEngine &engine;

    static void waitForEnter();
    static int askChoice(int min, int max);

public:
    explicit AbstractState(GameEngine &engine) : engine(engine) {}
    virtual ~AbstractState() = default;

    virtual void run() = 0;
    virtual std::string name() const = 0;
};
