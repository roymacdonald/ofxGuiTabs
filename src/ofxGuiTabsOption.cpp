#include "ofxGuiTabsOption.h"
#include "ofGraphics.h"


using namespace std;
//-----------------------------------------------------------------------
ofxGuiTabsOption::ofxGuiTabsOption(ofParameter<bool> _bVal, float height){
	setup(_bVal, height);
}
ofxGuiTabsOption::ofxGuiTabsOption(const std::string& tabName, bool _bVal, float height){
    setup(tabName, _bVal, height);
}

//-----------------------------------------------------------------------
ofxGuiTabsOption::~ofxGuiTabsOption(){}

//-----------------------------------------------------------------------
ofxGuiTabsOption * ofxGuiTabsOption::setup(ofParameter<bool> _bVal, float height){
#ifdef USE_OFX_GUI_TOOLTIP
        guiElement = this;
#endif
	b.x = 0;
	b.y = 0;
	b.height = height + textPadding*2;
	bGuiActive = false;
	value.makeReferenceTo(_bVal);
    
    float tx = getTextBoundingBox(getName(), 0,0).width + (textPadding*4);
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
ofxGuiTabsOption * ofxGuiTabsOption::setup(const std::string& toggleName, bool _bVal, float height){
	value.set(toggleName,_bVal);
	return setup(value, height);
}

//-----------------------------------------------------------------------
bool ofxGuiTabsOption::mouseMoved(ofMouseEventArgs & args){
    bIsOver = (isGuiDrawing() && b.inside(args));
    
//	if(isGuiDrawing() && b.inside(args)){
//		bIsOver = true;
//	}else{
//		bIsOver = false;
//	}
	return false;
}

//-----------------------------------------------------------------------
bool ofxGuiTabsOption::mousePressed(ofMouseEventArgs & args){
    bIsOver = setValue(args.x, args.y, true);
    return bIsOver;
//	if(setValue(args.x, args.y, true)){
//		bIsOver = true;
//		return true;
//	}else{
//		bIsOver = false;
//		return false;
//	}
}

//-----------------------------------------------------------------------
bool ofxGuiTabsOption::mouseDragged(ofMouseEventArgs & args){
    
    bIsOver = (bGuiActive && b.inside(args));
    return bIsOver;
    
//	if(bGuiActive && b.inside(args)){
//		bIsOver = true;
//		return true;
//	}else{
//		bIsOver = false;
//		return false;
//	}
}

//-----------------------------------------------------------------------
bool ofxGuiTabsOption::mouseReleased(ofMouseEventArgs & args){
	bool wasGuiActive = bGuiActive;
	bGuiActive = false;
    bIsOver = (wasGuiActive && b.inside(args));

    return bIsOver;
        
//	if(wasGuiActive && b.inside(args)){
//		bIsOver = true;
//		return true;
//	}else{
//		bIsOver = false;
//		return false;
//	}
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
//        ){
//             true;
//        }else{
//            bGuiActive = false;
//        }
    }
    if( bGuiActive ){
      //  cout << "ofxGuiTabsOption::setValue  name: " << getName() << "\n";
        value =  !value;
        return true;
    }
    return false;
}
