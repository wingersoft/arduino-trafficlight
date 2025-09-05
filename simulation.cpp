#include <iostream>
#include <chrono>
#include <thread>

// Traffic Light Simulation with State Machine for Two Lights
// 5 States: Light1 Green/Light2 Red, Light1 Yellow/Light2 Red, Light1 Red/Light2 Green, Light1 Red/Light2 Yellow, All Red
// Light 1: Pins 13,12,11 | Light 2: Pins 10,9,8

enum TrafficState
{
    LIGHT1_RED_LIGHT2_GREEN,
    LIGHT1_RED_LIGHT2_YELLOW,
    ALL_RED,
    LIGHT1_GREEN_LIGHT2_RED,
    LIGHT1_YELLOW_LIGHT2_RED
};

const int redDuration = 3000;    // 3 seconds for simulation
const int greenDuration = 3000;  // 3 seconds for simulation
const int yellowDuration = 500;  // 0.5 seconds for simulation
const int allRedDuration = 200;  // 0.2 seconds for simulation

void printLights(TrafficState state)
{
    std::cout << "Traffic Light State: ";
    switch (state)
    {
        case LIGHT1_RED_LIGHT2_GREEN:
            std::cout << "Light1: RED    Light2: GREEN" << std::endl;
            break;
        case LIGHT1_RED_LIGHT2_YELLOW:
            std::cout << "Light1: RED    Light2: YELLOW" << std::endl;
            break;
        case ALL_RED:
            std::cout << "Light1: RED    Light2: RED" << std::endl;
            break;
        case LIGHT1_GREEN_LIGHT2_RED:
            std::cout << "Light1: GREEN  Light2: RED" << std::endl;
            break;
        case LIGHT1_YELLOW_LIGHT2_RED:
            std::cout << "Light1: YELLOW Light2: RED" << std::endl;
            break;
    }
}

int main()
{
    TrafficState currentState = LIGHT1_RED_LIGHT2_GREEN;
    int cycleCount = 0;

    std::cout << "Arduino Traffic Light Simulation Started" << std::endl;
    std::cout << "=========================================" << std::endl;

    while (cycleCount < 3)  // Run 3 full cycles
    {
        printLights(currentState);

        switch (currentState)
        {
            case LIGHT1_RED_LIGHT2_GREEN:
                std::this_thread::sleep_for(std::chrono::milliseconds(greenDuration));
                currentState = LIGHT1_RED_LIGHT2_YELLOW;
                break;

            case LIGHT1_RED_LIGHT2_YELLOW:
                std::this_thread::sleep_for(std::chrono::milliseconds(yellowDuration));
                currentState = ALL_RED;
                break;

            case ALL_RED:
                std::this_thread::sleep_for(std::chrono::milliseconds(allRedDuration));
                currentState = LIGHT1_GREEN_LIGHT2_RED;
                break;

            case LIGHT1_GREEN_LIGHT2_RED:
                std::this_thread::sleep_for(std::chrono::milliseconds(greenDuration));
                currentState = LIGHT1_YELLOW_LIGHT2_RED;
                break;

            case LIGHT1_YELLOW_LIGHT2_RED:
                std::this_thread::sleep_for(std::chrono::milliseconds(yellowDuration));
                currentState = LIGHT1_RED_LIGHT2_GREEN;
                cycleCount++;
                std::cout << "Cycle " << cycleCount << " completed" << std::endl;
                break;
        }
    }

    std::cout << "Simulation completed!" << std::endl;
    return 0;
}