#include "RoboHand.h"

RoboHand::RoboHand(int thumb, int index, int middle, int ring, int pinky) {
    fingers[0].attach(thumb);
    fingers[1].attach(index);
    fingers[2].attach(middle);
    fingers[3].attach(ring);
    fingers[4].attach(pinky);
}

void RoboHand::reset() {
    for (int i = 0; i < 5; ++i) {
        fingers[i].write(minAngles[i]);
    }
}

void RoboHand::pull(int index) {
    if (index < 0 || index > 4)
        return;
    
    fingers[index].write(minAngles[index]);
}

void RoboHand::stretch(int index) {
    if (index < 0 || index > 4)
        return;
    
    fingers[index].write(maxAngles[index]);
}

void RoboHand::setAngle(int index, float angle) {
    if (index < 0 || index > 4)
        return;

    if (angle > 1.0 || angle < 0.0)
        return;

    fingers[index].write(angle * (maxAngles[index] - minAngles[index]) + minAngles[index]);
}

RoboHand::~RoboHand() {
    for (int i = 0; i < 5; ++i) {
        fingers[i].detach();
    }
}