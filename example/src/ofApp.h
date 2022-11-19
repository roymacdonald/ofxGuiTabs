#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxGuiTabs.h"
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
	
	
	ofxPanel gui;

    ofxGuiTabs tabs;
    
    ofEventListener listener;

    //uncomment the following line to algorithmically fill the tabs and guis
    // FYI: it is a lot more cryptic!
    //vector<ofParameter<float>> params;
    

    /// just a bunch of parameter to fill up the gui tabs

    // for tab 1
    ofParameter<float> param_1_1 = {"param_1_1", 0, 0, 1};
    ofParameter<float> param_1_2 = {"param_1_2", 0.33, 0, 1};
    ofParameter<float> param_1_3 = {"param_1_3", 0.66, 0, 1};
    ofParameter<float> param_1_4 = {"param_1_4", 1, 0, 1};


	// for tab 2
    ofParameter<float> param_2_1 = {"param_2_1", 1, 0, 1};
	ofParameter<float> param_2_2 = {"param_2_2", 0, 0, 1};
	ofParameter<float> param_2_3 = {"param_2_3", 0.33, 0, 1};
	ofParameter<float> param_2_4 = {"param_2_4", 0.66, 0, 1};


	// for tab 3
    ofParameter<float> param_3_1 = {"param_3_1", 0.33, 0, 1};
	ofParameter<float> param_3_2 = {"param_3_2", 0.66, 0, 1};
	ofParameter<float> param_3_3 = {"param_3_3", 1, 0, 1};
	ofParameter<float> param_3_4 = {"param_3_4", 0, 0, 1};


    

    
	
};
