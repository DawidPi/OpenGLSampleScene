//
// Created by dapl on 2017-05-12.
//

#ifndef PROJECT_STEPPERINTERPLOATION_HPP
#define PROJECT_STEPPERINTERPLOATION_HPP

#include <chrono>
#include <utility>

class StepperInterploator {
public:
    StepperInterploator(std::chrono::milliseconds stepTime, float currentZ_=0.0f, float currentX_=0.0f);

    void makeStep(float xDirection, float zDirection);
    std::pair<float, float> getCurrentPosition();

private:
    float currentZPosition=0.0f;
    float currentXPosition=0.0f;

    std::chrono::milliseconds timeStep;

    float destinationPositionX=0.0f;
    float destinationPositionZ=0.0f;

    double stepPerMilliX =0.0;
    double stepPerMilliZ =0.0;

    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point destinationTime;

};


#endif //PROJECT_STEPPERINTERPLOATION_HPP
