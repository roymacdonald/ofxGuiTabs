#include "ofxGuiTabsOption.h"
#include "ofGraphics.h"


using namespace std;

ofxGuiTabsOption::ofxGuiTabsOption(ofParameter<bool> _bVal, size_t index, float height){
	setup(_bVal, index, height);
}

ofxGuiTabsOption::~ofxGuiTabsOption(){
//	value.removeListener(this,&ofxGuiTabsOption::valueChanged);
}

ofxGuiTabsOption * ofxGuiTabsOption::setup(ofParameter<bool> _bVal, size_t index, float height){
#ifdef USE_OFX_GUI_TOOLTIP
        guiElement = this;
#endif
	b.x = 0;
	b.y = 0;
    tabIndex  = index;
	b.height = height + textPadding*2;
	bGuiActive = false;
	value.makeReferenceTo(_bVal);
    
    float tx = getTextBoundingBox(getName(), 0,0).width + (textPadding*4);
    if(tx  > defaultWidth){
//        cout << "ofxGuiTabsOption defaultWidth\n";
        b.width = defaultWidth ;
    }else{
        b.width =  tx;
    }
    


    
    listener = value.newListener(this,&ofxGuiTabsOption::valueChanged);
	registerMouseEvents();
	setNeedsRedraw();

	return this;

}

ofxGuiTabsOption * ofxGuiTabsOption::setup(const std::string& toggleName, size_t index, bool _bVal, float height){
	value.set(toggleName,_bVal);
	return setup(value,index, height);
}


bool ofxGuiTabsOption::mouseMoved(ofMouseEventArgs & args){
	if(isGuiDrawing() && b.inside(args)){
		bIsOver = true;
//		return true;
	}else{
		bIsOver = false;
	}
	return false;
}

bool ofxGuiTabsOption::mousePressed(ofMouseEventArgs & args){
	if(setValue(args.x, args.y, true)){
		bIsOver = true;
		return true;
	}else{
		bIsOver = false;
		return false;
	}
}

bool ofxGuiTabsOption::mouseDragged(ofMouseEventArgs & args){
	if(bGuiActive && b.inside(args)){
		bIsOver = true;
		return true;
	}else{
		bIsOver = false;
		return false;
	}
}

bool ofxGuiTabsOption::mouseReleased(ofMouseEventArgs & args){
	bool wasGuiActive = bGuiActive;
	bGuiActive = false;
	if(wasGuiActive && b.inside(args)){
		bIsOver = true;
		return true;
	}else{
		bIsOver = false;
		return false;
	}
}

void ofxGuiTabsOption::generateDraw(){
	bg.clear();
//	bg.rectangle(b);
    bg.rectRounded(b, textPadding);
    
    generateNameTextMesh(b);
    
}

void ofxGuiTabsOption::generateNameTextMesh(const ofRectangle& rect)
{
	std::string name;
	auto textX = rect.x + textPadding*2;
    name = getName();

	textMesh = getTextMesh(name, textX, getTextVCenteredInRect(rect));
}

void ofxGuiTabsOption::render(){
	if(value)
	{
		bg.setFillColor(thisFillColor);
	}
	else
	{
		if(bIsOver)
		{
			bg.setFillColor(thisBorderColor);
		}
		else
		{
			bg.setFillColor(thisBackgroundColor);
		}
	}
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


ofAbstractParameter & ofxGuiTabsOption::getParameter(){
	return value;
}

void ofxGuiTabsOption::valueChanged(bool & value){
    if(value){
        ofNotifyEvent(changed_E, tabIndex , this);
    }
    setNeedsRedraw();
}

void ofxGuiTabsOption::enableElement() {
	value.setWithoutEventNotifications(true);
	setNeedsRedraw();
}

void ofxGuiTabsOption::disableElement() {
    bGuiActive = false;
    value.setWithoutEventNotifications(false);
    setNeedsRedraw();
}

void ofxGuiTabsOption::select()
{
    value.setWithoutEventNotifications(true);
    setNeedsRedraw();
}

void ofxGuiTabsOption::deselect()
{
    value.setWithoutEventNotifications(false);
    setNeedsRedraw();
}


bool ofxGuiTabsOption::setValue(float mx, float my, bool bCheck){
    
    if( !isGuiDrawing() ){
        bGuiActive = false;
        return false;
    }
    if( bCheck ){
        if( b.inside(mx, my) ){
            bGuiActive = true;
        }else{
            bGuiActive = false;
        }
    }
    if( bGuiActive ){
      //  cout << "ofxGuiTabsOption::setValue  name: " << getName() << "\n";
        value =  !value;
        return true;
    }
    return false;
}
