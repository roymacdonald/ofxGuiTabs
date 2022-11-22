#include "ofxGuiTabsOption.h"
#include "ofGraphics.h"

#ifdef USE_OFX_GUI_TOOLTIP
#include "ofxGuiTooltip.h"
#endif

using namespace std;
//-----------------------------------------------------------------------
ofxGuiTabsOption::ofxGuiTabsOption(const std::string& tabName, ofxGuiGroup* guiGroup){
    setup(tabName, guiGroup);
}

//-----------------------------------------------------------------------
ofxGuiTabsOption::~ofxGuiTabsOption(){}


//-----------------------------------------------------------------------
ofxGuiTabsOption * ofxGuiTabsOption::setup(const std::string& tabName, ofxGuiGroup* guiGroup){
	value.set(tabName,false);
#ifdef USE_OFX_GUI_TOOLTIP
        guiElement = this;
#endif
    
    this->guiGroup = guiGroup;
    
    b.x = 0;
    b.y = 0;
    b.height = defaultHeight + textPadding*2;
    bGuiActive = false;
//    value.makeReferenceTo(_bVal);
    
    float tx = getTextBoundingBox(tabName, 0,0).width + (textPadding*4);
    if(tx  > defaultWidth){
        b.width = defaultWidth ;
    }else{
        b.width =  tx;
    }
    
    listener = value.newListener(this,&ofxGuiTabsOption::valueChanged);
    registerMouseEvents();
    setNeedsRedraw();

    return this;


}

//-----------------------------------------------------------------------
bool ofxGuiTabsOption::mouseMoved(ofMouseEventArgs & args){
    bIsOver = (isGuiDrawing() && b.inside(args));

	return false;
}

//-----------------------------------------------------------------------
bool ofxGuiTabsOption::mousePressed(ofMouseEventArgs & args){
    bIsOver = setValue(args.x, args.y, true);
    return bIsOver;
}

//-----------------------------------------------------------------------
bool ofxGuiTabsOption::mouseDragged(ofMouseEventArgs & args){
    
    bIsOver = (bGuiActive && b.inside(args));
    return bIsOver;
}

//-----------------------------------------------------------------------
bool ofxGuiTabsOption::mouseReleased(ofMouseEventArgs & args){
	bool wasGuiActive = bGuiActive;
	bGuiActive = false;
    bIsOver = (wasGuiActive && b.inside(args));

    return bIsOver;
}

//-----------------------------------------------------------------------
void ofxGuiTabsOption::generateDraw(){
	bg.clear();
//	bg.rectangle(b);
    bg.rectRounded(b, textPadding);
    
    generateNameTextMesh(b);
    
}

//-----------------------------------------------------------------------
void ofxGuiTabsOption::generateNameTextMesh(const ofRectangle& rect)
{
	std::string name;
	auto textX = rect.x + textPadding*2;
    name = getName();

	textMesh = getTextMesh(name, textX, getTextVCenteredInRect(rect));
}

//-----------------------------------------------------------------------
void ofxGuiTabsOption::render(){
    bg.setFillColor(value?
                    thisFillColor:
                    (bIsOver?
                        thisBorderColor:
                        thisBackgroundColor));
    bg.draw();

	ofColor c = ofGetStyle().color;
	ofBlendMode blendMode = ofGetStyle().blendingMode;
	if(blendMode!=OF_BLENDMODE_ALPHA){
		ofEnableAlphaBlending();
	}
	ofSetColor(thisTextColor);
    bindFontTexture();
    textMesh.draw();
    unbindFontTexture();
    
	ofSetColor(c);
	if(blendMode!=OF_BLENDMODE_ALPHA){
		ofEnableBlendMode(blendMode);
	}
}

//-----------------------------------------------------------------------
ofAbstractParameter & ofxGuiTabsOption::getParameter(){
	return value;
}

//-----------------------------------------------------------------------
void ofxGuiTabsOption::valueChanged(bool & value){
    if(value){
        auto n = getName();
        ofNotifyEvent(selection_E,  n, this);
    }
    setNeedsRedraw();
}

//-----------------------------------------------------------------------
void ofxGuiTabsOption::select()
{
    value = true;
}

//-----------------------------------------------------------------------
void ofxGuiTabsOption::deselect()
{
    bGuiActive = false;
    value  = false;
}

//-----------------------------------------------------------------------
bool ofxGuiTabsOption::isSelected(){
    return value.get();
}

//-----------------------------------------------------------------------
void ofxGuiTabsOption::setSelected(bool bSelected){
    value = bSelected;
}

//-----------------------------------------------------------------------
bool ofxGuiTabsOption::setValue(float mx, float my, bool bCheck){
    
    if( !isGuiDrawing() ){
        bGuiActive = false;
        return false;
    }
    if( bCheck ){
        bGuiActive = b.inside(mx, my) ;
    }
    if( bGuiActive ){
        value =  !value;
        return true;
    }
    return false;
}
#ifdef USE_OFX_GUI_TOOLTIP
//-----------------------------------------------------------------------
void ofxGuiTabsOption::setupTooltip(ofJson & json){
    if(!guiElement){
        ofLogWarning("ofxGuiTooltipBase::setupTooltip") << "guiElement is nullptr!";
        return;
    }
    removeTooltip();
    
    auto name = guiElement -> getName();

    
    if(!json.contains(name)){
        json[getName()] = ofJson::object({});
    }

    auto &j = json[name];
    
    if(j.contains("tooltip")){
        setTooltipText(j["tooltip"]);
    }else{
        j["tooltip"] = "Tab Tooltip . Change this text!";
    }
    
    
//    if(!j.contains("group")){
//        j["group"]= ofJson::object({});
//    }
//
//    auto& g = j["group"];
//
//    if(tooltips && this->guiGroup){
//        tooltips->registerGui(this->guiGroup, j);
//    }else{
//        ofLogError("ofxGuiTabsOption::setupTooltip") << "failed registering gui. ofxGuiTooltip ptr " << boolalpha << (bool)(tooltips) << "  guiGroup ptr" << (bool)(this->guiGroup);
//    }
    
    
    
}
#endif
