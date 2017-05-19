//
// Created by dapl on 2017-05-12.
//

#include <cassert>
#include <cmath>
#include <ostream>
#include <iostream>
#include "StepperInterploator.hpp"

using namespace std::chrono;

StepperInterploator::StepperInterploator(std::chrono::milliseconds stepTime, float currentZ_, float currentX_) :
    currentZPosition(currentZ_), currentXPosition(currentX_), timeStep(stepTime)
{}

void StepperInterploator::makeStep(float xDirection, float zDirection) {
    auto currentTime = system_clock::now();

    if(currentTime < destinationTime){
        auto newPosition = getCurrentPosition();
        currentXPosition = newPosition.first;
        currentZPosition = newPosition.second;
        destinationPositionX = currentXPosition;
        destinationPositionZ = currentZPosition;
        destinationTime = currentTime;
        return;
    }

    startTime = currentTime;
    destinationTime = currentTime + timeStep;

    destinationPositionX += xDirection;
    destinationPositionZ += zDirection;

    stepPerMilliX = (double)xDirection / timeStep.count();
    stepPerMilliZ = (double)zDirection / timeStep.count();
}

std::pair<float, float> StepperInterploator::getCurrentPosition() {
    auto currentTime = system_clock::now();

    if(currentTime >= destinationTime){
        currentZPosition = destinationPositionZ;
        currentXPosition = destinationPositionX;
        return {destinationPositionX, destinationPositionZ};
    }
    else{
        auto stepX = duration_cast<milliseconds>(currentTime - startTime).count() * stepPerMilliX;
        auto stepZ = duration_cast<milliseconds>(currentTime - startTime).count() * stepPerMilliZ;

        return {currentXPosition + stepX, currentZPosition + stepZ};
    }
}
