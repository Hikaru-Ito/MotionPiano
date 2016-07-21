#pragma once


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Key.h"

class Color {
public:
    float hue, sat, bri;
    ofVec2f pos;
};
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    // キーボード
    Key Keys[8];
    int key_num = 8;
    
    ofVideoGrabber vidGrabber;

    int camWidth;
    int camHeight;

    ofxCvColorImage colorImg;
    
    ofxCvColorImage colorImgHSV;

    ofxCvGrayscaleImage hueImg;
    ofxCvGrayscaleImage satImg;
    ofxCvGrayscaleImage briImg;

    ofxCvGrayscaleImage reds;

    Color one;
    unsigned char * colorTrackedPixelsRed;
    ofTexture trackedTextureRed;
    ofxCvContourFinder finderRed;
    
};
