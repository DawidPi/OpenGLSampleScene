//
// Created by dapl on 2017-05-12.
//

#include <cassert>
#include <cmath>
#include <ostream>
#include <iostream>
#include "Stepper.hpp"

using namespace std::chrono;

Stepper::Stepper(float currentZ_, float currentX_) :
    currentZPosition(currentZ_), currentXPosition(currentX_){}

void Stepper::makeStep(float xDirection, float zDirection) {
    currentXPosition += xDirection;
    currentZPosition += zDirection;
}

std::pair<float, float> Stepper::getCurrentPosition() {
    return {currentXPosition, currentZPosition};
}
