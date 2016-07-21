#pragma once
#include "ofMain.h"

class Key {
    
public:
    void update();
    void draw();
    void setColor(ofColor col);
    void setPos(float x, float y);
    void setSize(float w, float h);
    void setRound(float r);
    void checkTouch(float x, float y, float w, float h);
    void setSound(int n);
    bool is_touch;
    float circleSize;
    ofSoundPlayer sound;
    
    Key();
    
private:
    ofVec2f pos;
    float width;
    float height;
    float round;
    ofColor color;
    ofVec2f vel;
};
