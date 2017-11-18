#include "RoboHand.h"

#define MOVE_WAIT 50

RoboHand::RoboHand(int thumb, int index, int middle, int ring, int pinky) {
    fingers[0].attach(thumb);
    fingers[1].attach(index);
    fingers[2].attach(middle);
    fingers[3].attach(ring);
    fingers[4].attach(pinky);
}

float RoboHand::_getCurrAngle(int index) {
    return (float)(fingers[index].read() - minAngles[index]) / (maxAngles[index] - minAngles[index]);
}

void RoboHand::reset() {
    for (int i = 0; i < 5; ++i) {
        fingers[i].write(minAngles[i]);
    }
}

void RoboHand::pull(int index) {
    if (index < 0 || index > 4)
        return;
    
    float currAngle = _getCurrAngle(index);

    for (float i = currAngle; i > 0.0; i -= 0.2){
        setFastAngle(index, i);
        delay(MOVE_WAIT);
    }
}

void RoboHand::stretch(int index) {
    if (index < 0 || index > 4)
        return;
    
    float currAngle = _getCurrAngle(index);

    for (float i = currAngle; i < 1.0; i += 0.2){
        setFastAngle(index, i);
        delay(MOVE_WAIT);
    }
}

void RoboHand::setAngle(int index, float angle) {
    if (index < 0 || index > 4)
        return;

    angle = angle > 1.0 ? 1.0 : angle;
    angle = angle < 0.0 ? 0.0 : angle;

    float currAngle = _getCurrAngle(index);

    if (currAngle < angle) {
        for (float i = currAngle; i < angle - 0.05; i += 0.05){
            setFastAngle(index, i);
            delay(MOVE_WAIT);
        }
        setFastAngle(index, angle);
    } else {
        for (float i = currAngle; i > angle + 0.05; i -= 0.05){
            setFastAngle(index, i);
            delay(MOVE_WAIT);
        }
        setFastAngle(index, angle);
    }

}

void RoboHand::setFastAngle(int index, float angle) {
    if (index < 0 || index > 4)
        return;

    angle = angle > 1.0 ? 1.0 : angle;
    angle = angle < 0.0 ? 0.0 : angle;

    fingers[index].write(angle * (maxAngles[index] - minAngles[index]) + minAngles[index]);
}

RoboHand::~RoboHand() {
    for (int i = 0; i < 5; ++i) {
        fingers[i].detach();
    }
}