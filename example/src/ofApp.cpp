#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	gui.setup("DROPDOWNS", "DropdownsSettings.xml");
	gui.setPosition(20,20);
	
    options.setName("STR tabs");
	strTabs =  make_unique<ofxGuiTabs>(options);
      
    intOptions.setName("INT Options");
    intTabs =  make_unique<ofxGuiIntTabs>(intOptions);
    
	
    
	ofSetWindowPosition(0, 0);
//	ofSetWindowShape(ofGetScreenWidth(), 500);
	
	
	
	
	for(int i = 0; i < 10; i++){
			strTabs->add("String   "+ofToString(i));
	}
    for(int i = 0; i < 15; i++){
            intTabs->add(i, "int  " + ofToString(i));
    }
	gui.add(strTabs.get());
    gui.add(intTabs.get());

    
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
	
    ofDrawBitmapStringHighlight(ofToString(intOptions.get()), 20, ofGetHeight() - 50);
    ofDrawBitmapStringHighlight(ofToString(options.get()), 20, ofGetHeight() - 70);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key >= '0' && key <= '9'){
        intOptions = key - '0';
	}else if(key == 's'){
		gui.saveToFile("DropdownsSettings.xml");
	}else if(key == 'l'){
		gui.loadFromFile("DropdownsSettings.xml");
	}
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
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
