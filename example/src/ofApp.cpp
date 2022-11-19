#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	gui.setup("TabsGui", "TabsSettings.json");
	

    tabs.setup("Tabs");
    
    //uncomment the following code to generate parameters and tabs via code
//    for(int i = 0; i < 15; i++){
//        auto group = tabs.newTab("int  " + ofToString(i));
//        size_t n = round(ofRandom(2, 5));
//        for(int p = 0; p < n; p++){
//            params.push_back(ofParameter<float>(ofToString(i)+ "-" + ofToString(p), ofRandom(1), 0,1));
//            if(group) group->add(params.back());
//        }
//    }
    
    
    auto tab1 = tabs.newTab("First tab");
    
    tab1->add(param_1_1);
    tab1->add(param_1_2);
    tab1->add(param_1_3);
    tab1->add(param_1_4);

    auto tab2 = tabs.newTab("Second tab");
    tab2->add(param_2_1);
    tab2->add(param_2_2);
    tab2->add(param_2_3);
    tab2->add(param_2_4);

    auto tab3 = tabs.newTab("Tab Tres");
    tab3->add(param_3_1);
    tab3->add(param_3_2);
    tab3->add(param_3_3);
    tab3->add(param_3_4);

    
    /// in case you might want to know when a tab has been selected you can listen to the selection_E event
    listener = tabs.selection_E.newListener([](string& s){
        cout << "Tab changed " << s << endl;
    });
    
    
    gui.add(&tabs);

    
    
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
