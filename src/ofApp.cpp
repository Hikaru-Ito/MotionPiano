#include "ofApp.h"


/*
 
 OpenCVを用いた、Motionによるバーチャルピアノ演奏
 
 OpenCVを用いて、特定の色を追尾し、鍵盤を操作して音を出すことができます。
 
 起動したら、追尾する色を、画面上でクリックします。できるだけ特徴的な色（黄色、赤など）がいいです。
 設定した色が追尾されるので、それが鍵盤に触れると、音が出て演奏できます。
 
*/



//--------------------------------------------------------------
void ofApp::setup(){
    
    //カメラの大きさを指定
    camWidth = 1024;
    camHeight = 768;
    
    colorImg.allocate(camWidth, camHeight);
    colorImgHSV.allocate(camWidth, camHeight);
    hueImg.allocate(camWidth, camHeight);
    satImg.allocate(camWidth, camHeight);
    briImg.allocate(camWidth, camHeight);
    reds.allocate(camWidth, camHeight);
    
    colorTrackedPixelsRed =new unsigned char [camWidth*camHeight];
    trackedTextureRed.allocate(camWidth, camHeight, GL_LUMINANCE);
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(camWidth, camHeight);
    
    // キーボードを生成
    for(int i=0; i<8; i++) {
        Key* k = new Key();
        Keys[i] = *k;
        Keys[i].setPos(100 * i + 40 * i, 20);
        Keys[i].setSound(i);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vidGrabber.update();
    
    // カメラのピクセルを突っ込む
    colorImg.setFromPixels(vidGrabber.getPixels(), camWidth, camHeight);
    
    colorImgHSV = colorImg;
    colorImgHSV.convertRgbToHsv();
    
    //HSBにマッピング
    colorImgHSV.convertToGrayscalePlanarImages(hueImg, satImg, briImg);
    
    // 画像オブジェクトを書き換えたら変更を通知する
    hueImg.flagImageChanged();
    satImg.flagImageChanged();
    briImg.flagImageChanged();
    
    unsigned char * huePixels = hueImg.getPixels();
    unsigned char * satPixels = satImg.getPixels();
    unsigned char * briPixels = briImg.getPixels();
    
    //ピクセルの数
    int nPixels = camWidth*camHeight;
    
    // 色が閾値ないなら、255,それ以外は0を代入
    for (int i=0; i<nPixels; i++) {
        if ( (huePixels[i]>=one.hue-12 && huePixels[i] <= one.hue + 12) &&
            (satPixels[i]>=one.sat-24 && satPixels[i]<=one.sat+200)){
            colorTrackedPixelsRed[i] = 255;
        }else {
            colorTrackedPixelsRed[i]=0;
        }
        
    }
    
    //colorTrackedPixelsRedをもとに輪郭線情報を抽出
    reds.setFromPixels(colorTrackedPixelsRed, camWidth, camHeight);
    
    //輪郭線を見つける
    finderRed.findContours(reds, 10, nPixels/3, 1, false, true);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(100, 100, 100);
    ofSetColor(0xffffff);
    
    //映像を表示
    vidGrabber.draw(camWidth, 0, -camWidth, camHeight);
    
    // 輪郭線を表示
    finderRed.draw(camWidth, 0, -camWidth, camHeight);
    
    //追跡する色の位置を表示
    float blob_x = 99999;
    float blob_y = 99999;
    float blob_width = 0;
    float blob_height = 0;
    
    if (finderRed.blobs.size()>0) {
        blob_x = camWidth - finderRed.blobs[0].boundingRect.x; // centroid
        blob_y = finderRed.blobs[0].boundingRect.y;
        char tempStr1[255];
        sprintf(tempStr1, "x:%f\ny:%f", blob_x, blob_y);
        ofDrawBitmapString(tempStr1, 20, 250);
        
        blob_width = finderRed.blobs[0].boundingRect.width;
        blob_height = finderRed.blobs[0].boundingRect.height;
        
    }
    
    // 鍵盤を表示
    for(int i=0; i<key_num; i++){
        Keys[i].checkTouch(blob_x, blob_y, blob_width, blob_height);
        Keys[i].draw();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    unsigned char * huePixels = hueImg.getPixels();
    unsigned char * satPixels = satImg.getPixels();
    unsigned char * briPixels = briImg.getPixels();
    
    x=MIN(x,hueImg.width-1);
    y=MIN(y,hueImg.height-1);
    x=camWidth-x;
    
    if (button==0) {
        one.hue = huePixels[x+(y*hueImg.width)];
        one.sat = satPixels[x+(y*satImg.width)];
        one.bri = briPixels[x+(y*briImg.width)];
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
