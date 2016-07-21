#include "Key.h"

Key::Key(){
    pos.x = 0;
    pos.y = 0;
    width = 100;
    height = 300;
    round = 4;
    ofColor(44, 62, 80, 80);
    is_touch = false;
    sound.loadSound("0.mp3");
    circleSize = 80;
}

void Key::update() {
}

void Key::setColor(ofColor col) {
    color = col;
}

void Key::setSound(int n){
    std::string str = std::to_string(n);
    sound.loadSound(str+".mp3");
}

void Key::setPos(float x, float y) {
    pos.x = x;
    pos.y = y;
}

void Key::setSize(float w, float h) {
    width = w;
    height = h;
}

void Key::setRound(float r) {
    round = r;
}

// 触れたかチェックする
void Key::checkTouch(float x, float y, float w, float h) {
    
    float diffX = x - pos.x;
    float diffY = y - pos.y;
    if(diffX < 100 && diffX > 0 && diffY < 200 && diffY > 0) {
        color = ofColor(243, 156, 18, 200);
        if(is_touch == false) {
            sound.play();
            is_touch = true;
        }
        circleSize += 10;
    } else {
        color = ofColor(44, 62, 80, 80);
        is_touch = false;
        circleSize = 80;
    }
    
}

void Key::draw() {
    ofSetColor(color);
    ofDrawRectRounded(pos.x, pos.y, width, height, round);
    
    if(is_touch) {
        ofSetColor(ofColor(243, 156, 18, 60)); //rgba(52, 152, 219,1.0)
        ofCircle(pos.x + 50, pos.y + 400, circleSize);
        ofCircle(pos.x - 80, pos.y - 80, circleSize * 0.8);
        ofCircle(pos.x + 100, pos.y + 100, circleSize * 0.6);
    }
}