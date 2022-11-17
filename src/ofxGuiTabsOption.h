#pragma once

#include "ofxBaseGui.h"
#include "ofJson.h"
#ifdef USE_OFX_GUI_TOOLTIP
#include "ofxGuiTooltipBase.h"
#endif

class ofxGuiTabsOption : public ofxBaseGui
#ifdef USE_OFX_GUI_TOOLTIP
, public ofxGuiTooltipBase
#endif
{
  
public:
    ofxGuiTabsOption(){
#ifdef USE_OFX_GUI_TOOLTIP
        guiElement = this;
#endif
    }
	virtual ~ofxGuiTabsOption();
	
	void enableElement();
    void disableElement();

    ofxGuiTabsOption(ofParameter<bool> _bVal, size_t index, float height = defaultHeight);
    ofxGuiTabsOption * setup(ofParameter<bool> _bVal,  size_t index, float height = defaultHeight);
    ofxGuiTabsOption * setup(const std::string& toggleName, size_t index, bool _bVal, float height = defaultHeight);
	

	virtual bool mouseMoved(ofMouseEventArgs & args) override;
	virtual bool mousePressed(ofMouseEventArgs & args) override;
	virtual bool mouseDragged(ofMouseEventArgs & args) override;
	virtual bool mouseReleased(ofMouseEventArgs & args) override;
	virtual bool mouseScrolled(ofMouseEventArgs & args) override{return false;}
	

    ofEvent<size_t> changed_E;
    
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
#ifdef USE_OFX_GUI_TOOLTIP
    virtual bool isOver() override{
        return bIsOver;
    }
#endif
    size_t tabIndex;
    
	void generateNameTextMesh(const ofRectangle& rect);
    
	virtual void render() override;

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
