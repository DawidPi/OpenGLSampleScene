//
// Created by dapl on 2017-05-12.
//

#ifndef PROJECT_STEPPERINTERPLOATION_HPP
#define PROJECT_STEPPERINTERPLOATION_HPP

#include <chrono>
#include <utility>

class Stepper {
public:
    Stepper(float currentZ_, float currentX_);

    void makeStep(float xDirection, float zDirection);
    std::pair<float, float> getCurrentPosition();

private:
    float currentZPosition=0.0f;
    float currentXPosition=0.0f;
};


#endif //PROJECT_STEPPERINTERPLOATION_HPP
