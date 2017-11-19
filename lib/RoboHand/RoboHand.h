#ifndef RoboHand_h
#define RoboHand_h

#include <inttypes.h>
#include <Servo.h>

class RoboHand {
public:
    // one pin for each finger
    RoboHand(int, int, int, int, int);
    
    // all fingers are pulled in (the hand forms a knuckle)
    void reset();

    // set a given finger to an angle expressed in float
    // 0 - pulled in
    // 1 - stretched
    // (0-1) - in between
    void setFastAngle(int, float);
    void setAngle(int, float);
    void stretch(int);
    void pull(int);

    // detach all fingers
    ~RoboHand();
private:
    Servo fingers[5];
    int minAngles[5] = {0, 15, 5, 0, 0};
    int maxAngles[5] = {80, 90, 100, 90, 00};

    float _getCurrAngle(int);
};

#endif