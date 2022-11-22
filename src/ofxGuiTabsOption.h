#pragma once

#include "ofxBaseGui.h"
#include "ofJson.h"
#ifdef USE_OFX_GUI_TOOLTIP
#include "ofxGuiTooltipBase.h"
#endif
#include "ofxGuiGroup.h"



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
	
    ofxGuiTabsOption(const std::string& tabName, ofxGuiGroup* guiGroup);
    ofxGuiTabsOption * setup(const std::string& tabName, ofxGuiGroup* guiGroup);
	

	virtual bool mouseMoved(ofMouseEventArgs & args) override;
	virtual bool mousePressed(ofMouseEventArgs & args) override;
	virtual bool mouseDragged(ofMouseEventArgs & args) override;
	virtual bool mouseReleased(ofMouseEventArgs & args) override;
	virtual bool mouseScrolled(ofMouseEventArgs & args) override{return false;}
	

    ofEvent<std::string> selection_E;

    bool isSelected();
    
    void setSelected(bool bSelected);
    
	void select();
	
	virtual void deselect();

	virtual ofAbstractParameter & getParameter() override;

    ofxGuiGroup * guiGroup = nullptr;
#ifdef USE_OFX_GUI_TOOLTIP
    virtual void setupTooltip(ofJson & json) override;
#endif

protected:
#ifdef USE_OFX_GUI_TOOLTIP
    virtual bool isOver() override{
        return bIsOver;
    }
#endif

    
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
