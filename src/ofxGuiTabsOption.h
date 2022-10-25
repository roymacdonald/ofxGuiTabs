#pragma once

#include "ofxBaseGui.h"

class ofxGuiTabsOption : public ofxBaseGui{
  
public:
    ofxGuiTabsOption(){}
	virtual ~ofxGuiTabsOption();
	
	void enableElement();
    void disableElement();

    ofxGuiTabsOption(ofParameter<bool> _bVal, float height = defaultHeight);
    ofxGuiTabsOption * setup(ofParameter<bool> _bVal,  float height = defaultHeight);
    ofxGuiTabsOption * setup(const std::string& toggleName, bool _bVal, float height = defaultHeight);
	

	virtual bool mouseMoved(ofMouseEventArgs & args) override;
	virtual bool mousePressed(ofMouseEventArgs & args) override;
	virtual bool mouseDragged(ofMouseEventArgs & args) override;
	virtual bool mouseReleased(ofMouseEventArgs & args) override;
	virtual bool mouseScrolled(ofMouseEventArgs & args) override{return false;}
	

    ofEvent<bool> changed_E;
    
    template<typename... Args>
    std::unique_ptr<of::priv::AbstractEventToken> newListener(Args...args) {
        return value.newListener(args...);
    }
    
	template<class ListenerClass, typename ListenerMethod>
	void addListener(ListenerClass * listener, ListenerMethod method){
		value.addListener(listener,method);
	}

	template<class ListenerClass, typename ListenerMethod>
	void removeListener(ListenerClass * listener, ListenerMethod method){
		value.removeListener(listener,method);
	}

	void select();
	
	virtual void deselect();


	virtual ofAbstractParameter & getParameter() override;


protected:
	void generateNameTextMesh(const ofRectangle& rect);
	
	
//	enum State {
//		UNSELECTED=0,
//		OVER,
//		SELECTED
//	}_state;
//
//	void setState(State state);
//
	virtual void render() override;
//	ofRectangle checkboxRect;
	ofParameter<bool> value;
	bool bGuiActive;
	bool bIsOver = false;
	
    virtual bool setValue(float mx, float my, bool bCheck) override;
    virtual void generateDraw()override;
    void valueChanged(bool & value) ;
	ofPath bg;
	ofVboMesh textMesh;
    
    
private:
    ofEventListener listener;
};
