//
//  ofxGuiTabs.cpp
//  dropdown
//
//  Created by Roy Macdonald on 10/14/18.
//
//


#include "ofxGuiTabs.h"
#include "ofGraphics.h"
#include "ofxGui.h"

//--------------------------------------------------------------
template<class T>
ofxGuiTabs_<T>::ofxGuiTabs_(ofParameter<T> param, float width , float height){
    setup(param,width,height);
}
template<class T>
ofxGuiTabs_<T>::ofxGuiTabs_(ofParameter<T> param, const map<T,string>& dropDownOptions, float width , float height){
    setup(param,width,height);
    add(dropDownOptions);
}
template<class T>
ofxGuiTabs_<T>::ofxGuiTabs_(ofParameter<T> param, const std::vector<T> & dropDownOptions, float width , float height){
    setup(param,width,height);
    add(dropDownOptions);
}
template<class T>
ofxGuiTabs_<T>::ofxGuiTabs_(std::string name, float width, float height){
    setup(name, width, height);
}

template<class T>
ofxGuiTabs_<T>::~ofxGuiTabs_(){
    
}

//--------------------------------------------------------------
template<class T>
ofxGuiTabs_<T> * ofxGuiTabs_<T>::setup(std::string name, float width , float height ){
    if (bIsSetup){
        ofLogWarning("ofxGuiTabs_<T>::setup" ) << "Dropdown \"name\" is already setup. Nothing will be done";
        return this;
    }
    bGuiActive = false;
	
	selectedValue.setName(name);
	setlectedValueListener = selectedValue.newListener(this, &ofxGuiTabs_<T>::selectedValueChanged);
	
    
    bIsSetup = true;
    
	return this;
}

//--------------------------------------------------------------
template<class T>
ofxGuiTabs_<T> * ofxGuiTabs_<T>::setup(ofParameter<T> param, float width, float height){
    if (bIsSetup){
        ofLogWarning("ofxGuiTabs_<T>::setup" ) << "Dropdown \"name\" is already setup. Nothing will be done";
        return this;
    }
	selectedValue.makeReferenceTo(param);
	return setup(param.getName(), width, height);
}
//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::selectedValueChanged(T & newvalue){
	auto it = find(values.begin(), values.end(), newvalue);
	if(it != values.end()){// it was found. it should be found anyways but better to double check
		auto index = std::distance(values.begin(), it);
		setSelectedValueByIndex(index, true);
		
		
//		auto element = dynamic_cast <ofxGuiTabsOption *>(group.getControl(options[index]));
//		if(element){
//			element->enableElement();
//		}
		setNeedsRedraw();
	}
	
}
//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::setSelectedValueByIndex( const size_t& index, bool bNotify){
	if(index < values.size()){
		selectedValue = values[index];
		selectedOption = options[index];
		if(!bMultiselection){
//			auto control = group.getControl(options[index]);
//			if(control != nullptr){
				disableSiblings(ownedChildren[index].get());
//			}
		}
		if(bNotify) ofNotifyEvent(change_E, options[index], this);
	}
}
//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::setSelectedValueByName( const std::string& valueName, bool bNotify){

		auto it = find(options.begin(), options.end(), valueName);
		if(it != options.end()){// it was found. it should be found anyways but better to double check
			auto index = std::distance(options.begin(), it);
			setSelectedValueByIndex(index, bNotify);
		}
	
}
//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::optionChanged(const void * sender, bool& b){
	if(b){
        if(sender){
//        auto s = ( ofxGuiTabsOption*)(sender);
		

//			auto& g = group.getParameter().castGroup();
				
        
			int foundIndex = -1;           
			for(int i = 0; i <ownedChildren.size(); i++){
//            for(auto& c : ownedChildren){
                auto& c = ownedChildren[i];
                if(c.get() == sender){
//				if(ownedChildren[i]->getParameter().getInternalObject() == ((ofParameter<bool> *)(sender))->getInternalObject()){
                    
					foundIndex = i;
					break;
				}
			}
			if(foundIndex >= 0){
//                cout << "Found index " << foundIndex << endl;
				setSelectedValueByIndex(foundIndex, true);
			}
			
		
	}else{
		ofLogVerbose("ofxGuiTabs_::optionChanged(...)")  << "sender = null";
	}

    }

}
//--------------------------------------------------------------
template<class T>
ofxGuiTabs_<T> * ofxGuiTabs_<T>::add(const T& value) {
    return add(value, ofToString(value));
}

//--------------------------------------------------------------
template<>
ofxGuiTabs_<string> * ofxGuiTabs_<string>::add(const string& value) {
    return add(value, value);
}


//--------------------------------------------------------------
template<class T>
ofxGuiTabs_<T> * ofxGuiTabs_<T>::add(const T& value, const string& option) {
    options.push_back(option);
    values.push_back(value);
    	
	ownedChildren.emplace_back(make_unique<ofxGuiTabsOption>());
	auto o = ownedChildren.back().get();
	if(o){
		o->setup(option, value == selectedValue.get());
		optionsListeners.push(o->changed_E.newListener(this, &ofxGuiTabs_::optionChanged));
    
        setNeedsRedraw();
	}else
	{
		ofLogError("ofxGuiTabs_<T>::add") << "created children is nullptr";
	}
	

    return this;
}
//--------------------------------------------------------------
template<class T>
ofxGuiTabs_<T> * ofxGuiTabs_<T>::add(const vector<T> & options){
	for(auto& option: options){
		add(option);
	}
	return this;
}
//--------------------------------------------------------------
template<class T>
ofxGuiTabs_<T> * ofxGuiTabs_<T>::add(const map<T,string> & options){
    for(auto& option: options){
        add(option.first, option.second);
    }
    return this;
}
//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::clear(){
//	group.clear();
	ownedChildren.clear();
    optionsListeners.unsubscribeAll();

}
//--------------------------------------------------------------
template<class T>
string ofxGuiTabs_<T>::getOptionAt(size_t index){
	if(index < ownedChildren.size()){
        if(ownedChildren[index]){
            return ownedChildren[index]->getName();
        }
//		return group.getControl(index)->getName();
	}
	ofLogNotice("ofxGuiTabs_::getOptionAt", "index is out of bounds");
	return "";
}

//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::disableSiblings(ofxGuiTabsOption * child){
    
    for(auto& element : ownedChildren){
        if(element){
            if(child != element.get()){
                element->disableElement();
            }else{
                element->enableElement();
            }
        }
    }
}


//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::deselect(){
	for(auto&c: ownedChildren)
	{
		if(c) c->deselect();
	}
	selectedOption = "";
}

//--------------------------------------------------------------
template<class T>
bool ofxGuiTabs_<T>::mouseReleased(ofMouseEventArgs & args){
    if(!isGuiDrawing()){
        bGuiActive = false;
        return false;
    }
    if(bGuiActive){
        bGuiActive = false;
        for(auto& c: ownedChildren){
            ofMouseEventArgs a = args;
            if( c && c->mouseReleased(a)){
                return true;
            }
        }
        if(b.inside(ofPoint(args.x, args.y))){
            return true;
        }else{
            return false;
        }
    }
    return false;
}
//--------------------------------------------------------------
template<class T>
bool ofxGuiTabs_<T>::mousePressed(ofMouseEventArgs & args){
    if(!isGuiDrawing())return false;
    
    if(setValue(args.x, args.y, true)){
        return true;
    }
    auto attended = false;
    ofMouseEventArgs a = args;
    for(auto& c: ownedChildren){
        if( c && c->mousePressed(a)){
            attended = true;
        }
    }
    return attended || b.inside(args);
}
//--------------------------------------------------------------
template<class T>
bool ofxGuiTabs_<T>::mouseMoved(ofMouseEventArgs & args){
    if(!isGuiDrawing())return false;
    ofMouseEventArgs a = args;
    for(auto& c: ownedChildren){
        if( c && c->mouseMoved(a)){
            return true;
        }
    }
    if(b.inside(args)){
        return true;
    }else{
        return false;
    }
}
//--------------------------------------------------------------
template<class T>
bool ofxGuiTabs_<T>::mouseDragged(ofMouseEventArgs & args){
	
    if(!isGuiDrawing())return false;
    if(bGuiActive){
        if(setValue(args.x, args.y, false)){
            return true;
        }
        ofMouseEventArgs a = args;
        for(auto& c: ownedChildren){
            if( c && c->mouseDragged(a)){
                return true;
            }
        }
    }
    return false;
	
	
}
//--------------------------------------------------------------
template<class T>
bool ofxGuiTabs_<T>::mouseScrolled(ofMouseEventArgs & args){
    if(!isGuiDrawing())return false;
    ofMouseEventArgs a = args;
//    for(std::size_t i = 0; i < collection.size(); i++){
    for(auto& c: ownedChildren){
        if( c && c->mouseScrolled(a)){
            return true;
        }
    }
    if(b.inside(args)){
        return true;
    }else{
        return false;
    }
}



//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::generateDraw(){
	
	
//    cout << "generateDraw\n";
	
//	auto h = b.getHeight()/2;
//	auto x2 = b.getMaxX();
//
//	auto y = b.getY();
    
    float x = b.getMinX() + textPadding;
    float y = b.getMinY() + textPadding;
    float h = 0;
    float b_mx = b.getMaxX() - textPadding;

    ofRectangle bb = b;
    bb.height = 0;
    
    for(auto &c: ownedChildren){
        if(c){
            
            auto shape = c->getShape();
            shape.x = x;
            shape.y = y;
            
            if(shape.getMaxX() > b_mx ){
                x = bb.getMinX() + textPadding;
                y += shape.height + textPadding;
            }
            c->setPosition(x, y);
            x += shape.width + textPadding;
            bb.growToInclude(c->getShape());
        }
    }
    bb.height += textPadding;
	
    if(bb != b){
        setShape(bb);
    }
//    bg.clear();
//    bg.setFillColor(thisBackgroundColor);
//    bg.setFilled(true);
//    bg.rectangle(b);
    
	
//	optionTextMesh = getTextMesh(selectedOption, x2 - getTextBoundingBox(selectedOption, 0, 0).width - textPadding , getTextVCenteredInRect(optionsTextRect));
//	ofRectangle textRect = b;
//	textRect.width -= h*2.5;
//	textRect.x += h*1.5;
//	ofRemove(optionTextMesh.getVertices(), [&](const glm::vec3& p){
//		return !textRect.inside(p);
//	});	
	
}
//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::render(){
//    bg.draw();
    for(auto& c: ownedChildren){
        if(c) c->draw();
    }
//    group.draw();
//	arrow.draw();/
//	ofSetColor(thisTextColor, 200);
//
//	bindFontTexture();
//	optionTextMesh.draw();
//	unbindFontTexture();
	
}

//--------------------------------------------------------------
template<class T>
ofAbstractParameter & ofxGuiTabs_<T>::getParameter(){
	return selectedValue;
}


//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::enableMultipleSelection(){
	bMultiselection = true;
}
//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::disableMultipleSelection(){
	bMultiselection = false;
}
//--------------------------------------------------------------
template<class T>
bool ofxGuiTabs_<T>::isEnabledMultipleSelection(){
	return bMultiselection;
}
//--------------------------------------------------------------
template<class T>
bool ofxGuiTabs_<T>::setValue(float mx, float my, bool bCheck){
    
    if(!isGuiDrawing()){
        bGuiActive = false;
        return false;
    }


    if(bCheck){
        if(b.inside(mx, my)){
            bGuiActive = true;
        }
    }

    return false;
    
}

//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::registerMouseEvents(){
    if(bRegisteredForMouseEvents == true){
        return; // already registered.
    }
    bRegisteredForMouseEvents = true;

    int prio = int(defaultEventsPriority) - 100;

    mouseListeners.push(ofEvents().mouseDragged.newListener(this, &ofxGuiTabs_<T>::mouseDragged, prio));
    mouseListeners.push(ofEvents().mouseMoved.newListener(this, &ofxGuiTabs_<T>::mouseMoved, prio));
    mouseListeners.push(ofEvents().mousePressed.newListener(this, &ofxGuiTabs_<T>::mousePressed, prio));
    mouseListeners.push(ofEvents().mouseReleased.newListener(this, &ofxGuiTabs_<T>::mouseReleased, prio));
    mouseListeners.push(ofEvents().mouseScrolled.newListener(this, &ofxGuiTabs_<T>::mouseScrolled, prio));

}


//--------------------------------------------------------------
template<class T>
void ofxGuiTabs_<T>::unregisterMouseEvents(){
    if(bRegisteredForMouseEvents == false){
        return; // not registered.
    }

    mouseListeners.unsubscribeAll();

    bRegisteredForMouseEvents = false;
}

template<class T>
bool ofxGuiTabs_<T>::keyReleased(ofKeyEventArgs& args){
//    cout << "keys modifiers: " << args.modifiers << endl;
    if(args.hasModifier(OF_KEY_SUPER)){
        int k = args.key - '1';
        if(k >= 0 && k < 9 && k < values.size()){
            setSelectedValueByIndex(k, true);
            return true;
        }
    }
    return false;
}


template<class T>
void ofxGuiTabs_<T>::enableKeys(){
    if(!bListeningKeys){
        keysListener = ofEvents().keyReleased.newListener(this, &ofxGuiTabs_::keyReleased);
        bListeningKeys = true;
    }
}
template<class T>
void ofxGuiTabs_<T>::disableKeys(){
    if(bListeningKeys){
        keysListener.unsubscribe();
        bListeningKeys = false;
    }
}
template<class T>
bool ofxGuiTabs_<T>::isKeysEnabled(){
    return bListeningKeys;
}


template class ofxGuiTabs_<string>;
//template class ofxGuiTabs_<int>;

template class ofxGuiTabs_<int8_t>;
template class ofxGuiTabs_<uint8_t>;
template class ofxGuiTabs_<int16_t>;
template class ofxGuiTabs_<uint16_t>;
template class ofxGuiTabs_<int32_t>;
template class ofxGuiTabs_<uint32_t>;
template class ofxGuiTabs_<int64_t>;
template class ofxGuiTabs_<uint64_t>;

//for some reason osx errors if this isn't defined
#ifdef TARGET_OSX
template class ofxGuiTabs_<typename std::conditional<std::is_same<uint32_t, size_t>::value || std::is_same<uint64_t, size_t>::value, bool, size_t>::type>;
#endif


