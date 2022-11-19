#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	gui.setup("TabsGui", "TabsSettings.json");
	

    tabs.setup("Tabs");
    
    for(int i = 0; i < 15; i++){
        auto group = tabs.newTab("int  " + ofToString(i));
        size_t n = round(ofRandom(2, 5));
        for(int p = 0; p < n; p++){
            params.push_back(ofParameter<float>(ofToString(i)+ "-" + ofToString(p), ofRandom(1), 0,1));
            if(group) group->add(params.back());
        }
    }
    
    listener = tabs.selection_E.newListener([](string& s){
        cout << "Tab changed " << s << endl;
    });
    
    gui.add(&tabs);

    tabs.setSelectedTab(tabs.getTabNames()[0]);
    
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
	    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if(key >= '1' && key - '1' < tabs.getTabNames().size()){
        tabs.setSelectedTab(tabs.getTabNames()[key - '1']);
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
