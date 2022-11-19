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

ofxGuiTabs::ofxGuiTabs(){
#ifdef USE_OFX_GUI_TOOLTIP
        guiElement = this;
#endif
}
//--------------------------------------------------------------
ofxGuiTabs::ofxGuiTabs(ofParameter<string> param, float width , float height){
    setup(param,width,height);
}

ofxGuiTabs::ofxGuiTabs(ofParameter<string> param, const std::vector<string> & tabsNames, float width , float height){
    setup(param,width,height);
    add(tabsNames);
}

ofxGuiTabs::ofxGuiTabs(std::string name, float width, float height){
    setup(name, width, height);
}

ofxGuiTabs::~ofxGuiTabs(){
    
}

//--------------------------------------------------------------
ofxGuiTabs * ofxGuiTabs::setup(std::string name, float width , float height ){
#ifdef USE_OFX_GUI_TOOLTIP
        guiElement = this;
#endif
    if (bIsSetup){
        ofLogWarning("ofxGuiTabs::setup" ) << "Dropdown \"name\" is already setup. Nothing will be done";
        return this;
    }
    bGuiActive = false;
	
    selectedTab.setName(name);
	setlectedValueListener = selectedTab.newListener(this, &ofxGuiTabs::selectedTabChanged);
	
    
    bIsSetup = true;
    
	return this;
}

//--------------------------------------------------------------
ofxGuiTabs * ofxGuiTabs::setup(ofParameter<string> param, float width, float height){
    if (bIsSetup){
        ofLogWarning("ofxGuiTabs::setup" ) << "Dropdown \"name\" is already setup. Nothing will be done";
        return this;
    }
    selectedTab.makeReferenceTo(param);
	return setup(param.getName(), width, height);
}
//--------------------------------------------------------------
void ofxGuiTabs::selectedTabChanged(string & name){
    cout << "ofxGuiTabs::selectedTabChanged " << name << boolalpha << bIgnoreSelectedTabChange << endl;
    if(bIgnoreSelectedTabChange) return;

    setSelectedTab(name);
		
//	}
	
}

//--------------------------------------------------------------
void ofxGuiTabs::tabChanged(string & name){
    cout << "ofxGuiTabs::tabChanged " << name << boolalpha << bIgnoreSelectedTabChange << endl;
    
    bIgnoreSelectedTabChange = true;
    if(setSelectedTab(name)){
        
    }
    bIgnoreSelectedTabChange = false;
}

//--------------------------------------------------------------
bool ofxGuiTabs::setSelectedTab( const std::string& tabName){

    if(tabs.count(tabName)){
        cout << "ofxGuiTabs::setSelectedTab " << tabName << boolalpha << bIgnoreSelectedTabChange << endl;
//        bIgnoreSelectedTabChange = true;
//        selectedTab = tabName;
        selectedTab.setWithoutEventNotifications(tabName);
//        bIgnoreSelectedTabChange = false;
        
        disableSiblings(tabs[tabName].get());
        
        setNeedsRedraw();
        return true;
    }
    return false;
}
////--------------------------------------------------------------
//void ofxGuiTabs::optionChanged(const void * sender, size_t& b){
////    if(b){
////        cout << "ofxGuiTabs::optionChanged\n";
//        if(sender){
//
////                cout << "Found index " << b << endl;
//                setSelectedValueByIndex(b, true);
//    }else{
//        ofLogVerbose("ofxGuiTabs::optionChanged(...)")  << "sender = null";
//    }
//}

//--------------------------------------------------------------
ofxGuiGroup * ofxGuiTabs::add(const string& tabName) {

//    options.push_back(option);
//    values.push_back(value);
    
    if(guiGroups.count(tabName) == 0){
        guiGroups[tabName] = make_shared<ofxGuiGroup>(tabName);
        tabs[tabName] = make_shared<ofxGuiTabsOption>(tabName);
        tabNames.push_back(tabName);
        groups.push_back(guiGroups[tabName].get());
        tabsCollection.push_back(tabs[tabName].get());
        
        optionsListeners.push(tabs[tabName]->selection_E.newListener(this, &ofxGuiTabs::tabChanged));
    
        setNeedsRedraw();
        
//        return guiGroups[tabName].get();
	
    }else{
        
        ofLogWarning("ofxGuiTabs::add") << "There is already a group named " << tabName << endl;
    }
    if(tabs.size() == 1){
        setSelectedTab(tabNames[0]);
    }
    return guiGroups[tabName].get();
//    return nullptr;
}

//--------------------------------------------------------------
void ofxGuiTabs::add(const vector<string> & options){
	for(auto& option: options){
		add(option);
	}
}

//--------------------------------------------------------------
void ofxGuiTabs::clear(){
    guiGroups.clear();
    tabs.clear();
    optionsListeners.unsubscribeAll();

    tabNames.clear();
    groups.clear();
    tabsCollection.clear();
}


//--------------------------------------------------------------
void ofxGuiTabs::disableSiblings(ofxGuiTabsOption * child){
    
    for(auto& element : tabs){
        if(element.second){
            element.second->setSelected(child == element.second.get());
//            if(child != element.get()){
//                element->deselect();
//            }else{
//                element->select();
//            }
        }
    }
}


//--------------------------------------------------------------
void ofxGuiTabs::deselect(){
	for(auto&c: tabs)
	{
		if(c.second) c.second->deselect();
	}
	selectedTab = "";
}

//--------------------------------------------------------------
bool ofxGuiTabs::mouseReleased(ofMouseEventArgs & args){
    if(!isGuiDrawing()){
        bGuiActive = false;
        return false;
    }
    if(bGuiActive){
        bGuiActive = false;
        ofMouseEventArgs a = args;
        for(auto& c: tabs){
            
            if( c.second && c.second->mouseReleased(a)){
                return true;
            }
        }
        
        auto g = getCurrentTabGroup();
        if(g){
            
            if (g->mouseReleased(a)){
                return true;
            }
        }
        
        
        
        
//        if(
        return b.inside(args.x, args.y);
//           ){
//            return true;
//        }else{
//            return false;
//        }
    }
    return false;
}
//--------------------------------------------------------------
bool ofxGuiTabs::mousePressed(ofMouseEventArgs & args){
    if(!isGuiDrawing())return false;
    
    if(setValue(args.x, args.y, true)){
        return true;
    }
    auto attended = false;
    ofMouseEventArgs a = args;
    for(auto& c: tabs){
        if( c.second && c.second->mousePressed(a)){
            attended = true;
        }
    }
    
    auto g = getCurrentTabGroup();
    if(g){
        attended |= g->mousePressed(a);
    }
    
    
    return attended || b.inside(args);
}
//--------------------------------------------------------------
bool ofxGuiTabs::mouseMoved(ofMouseEventArgs & args){
    if(!isGuiDrawing())return false;
    ofMouseEventArgs a = args;
    for(auto& c: tabs){
        if( c.second && c.second->mouseMoved(a)){
            return true;
        }
    }
    
    auto g = getCurrentTabGroup();
    if(g){
        return g->mouseMoved(a);
    }
    
    
//    if(
    return b.inside(args);
//    ){
//        return true;
//    }else{
//        return false;
//    }
}
//--------------------------------------------------------------
bool ofxGuiTabs::mouseDragged(ofMouseEventArgs & args){
	
    if(!isGuiDrawing())return false;
    if(bGuiActive){
        if(setValue(args.x, args.y, false)){
            return true;
        }
        ofMouseEventArgs a = args;
        for(auto& c: tabs){
            if( c.second && c.second->mouseDragged(a)){
                return true;
            }
        }
        auto g = getCurrentTabGroup();
        if(g){
            return g->mouseDragged(a);
        }
        
    }
    return false;
	
	
}
//--------------------------------------------------------------
bool ofxGuiTabs::mouseScrolled(ofMouseEventArgs & args){
    if(!isGuiDrawing())return false;
    ofMouseEventArgs a = args;
//    for(std::size_t i = 0; i < collection.size(); i++){
    for(auto& c: tabs){
        if( c.second && c.second->mouseScrolled(a)){
            return true;
        }
    }

    auto g = getCurrentTabGroup();
    if(g){
        return g->mouseScrolled(a);
    }
    
    
    if(b.inside(args)){
        return true;
    }else{
        return false;
    }
}



//--------------------------------------------------------------
void ofxGuiTabs::generateDraw(){
	
	
    float x = b.getMinX() + textPadding;
    float y = b.getMinY() + textPadding;
    float h = 0;
    float b_mx = b.getMaxX() - textPadding;

    ofRectangle bb = b;
    bb.height = 0;
    
            
    for(auto& c: tabsCollection){
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
	
    auto g = getCurrentTabGroup();
    if(g){
        g ->setPosition(bb.getBottomLeft());
        bb.growToInclude(g->getShape());
    }
    
    
    if(bb != b){
        setShape(bb);
    }
}
//--------------------------------------------------------------
void ofxGuiTabs::render(){

    for(auto& c: tabs){
        if(c.second) c.second->draw();
    }
    
    auto g = getCurrentTabGroup();
    if(g){
        g->draw();
    }
    
}

//--------------------------------------------------------------
ofAbstractParameter & ofxGuiTabs::getParameter(){
	return selectedTab;
}


//--------------------------------------------------------------
bool ofxGuiTabs::setValue(float mx, float my, bool bCheck){
    
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
void ofxGuiTabs::registerMouseEvents(){
    if(bRegisteredForMouseEvents == true){
        return; // already registered.
    }
    bRegisteredForMouseEvents = true;

    int prio = int(defaultEventsPriority) - 100;

    mouseListeners.push(ofEvents().mouseDragged.newListener(this, &ofxGuiTabs::mouseDragged, prio));
    mouseListeners.push(ofEvents().mouseMoved.newListener(this, &ofxGuiTabs::mouseMoved, prio));
    mouseListeners.push(ofEvents().mousePressed.newListener(this, &ofxGuiTabs::mousePressed, prio));
    mouseListeners.push(ofEvents().mouseReleased.newListener(this, &ofxGuiTabs::mouseReleased, prio));
    mouseListeners.push(ofEvents().mouseScrolled.newListener(this, &ofxGuiTabs::mouseScrolled, prio));

}

//--------------------------------------------------------------
void ofxGuiTabs::unregisterMouseEvents(){
    if(bRegisteredForMouseEvents == false){
        return; // not registered.
    }

    mouseListeners.unsubscribeAll();

    bRegisteredForMouseEvents = false;
}


#ifdef USE_OFX_GUI_TOOLTIP
//--------------------------------------------------------------
void ofxGuiTabs::setupTooltip(ofJson &json){
    if(!json.contains(getName())){
        json[getName()] = ofJson::object({});
//        cout << "Created json object\n";
    }
    
    auto& j = json[getName()];
//    cout << j.dump(4);
    
    for(auto&c: tabs)
    {
        if(c.second) c.second->setupTooltip(j);
    }
    enableTooltip();
}

//--------------------------------------------------------------
void ofxGuiTabs::resetTooltips(){
    
    for(auto&c: tabs)
    {
        if(c.second) c.second->removeTooltip();
    }
}

//--------------------------------------------------------------
void ofxGuiTabs::addTooltip(const string& tabName, const string& toolTipText){
    auto o = getTabByName(tabName);
    if(o) o->setTooltipText(toolTipText);
}

//--------------------------------------------------------------
void ofxGuiTabs::enableTooltip(){
    if(!bTooltipsEnabled){
        bTooltipsEnabled = true;
        for(auto&c: tabs)
        {
            if(c.second) c.second->enableTooltip();
        }
    }
}

//--------------------------------------------------------------
void ofxGuiTabs::disableTooltip(){
    if(bTooltipsEnabled){
        bTooltipsEnabled = false;
        for(auto&c: tabs)
        {
            if(c.second) c.second->disableTooltip();
        }
    }
}

//--------------------------------------------------------------
void ofxGuiTabs::drawTooltip(){
    if(bTooltipsEnabled){
        for(auto&c: tabs)
        {
            if(c.second) c.second->drawTooltip();
        }
    }
}
#endif

ofxGuiGroup * ofxGuiTabs::getCurrentTabGroup(){
    return getTabGroup(selectedTab.get());
}

ofxGuiGroup * ofxGuiTabs::getTabGroup(const string & name){
    if(guiGroups.count(name)){
        return guiGroups[name].get();
    }
    return nullptr;
}
    
//--------------------------------------------------------------
ofxGuiTabsOption* ofxGuiTabs::getTabByName(const string& name){
    if(tabs.count(name) == 0) return nullptr;
    return tabs[name].get();
}

const vector<string> & ofxGuiTabs::getTabNames(){
    return tabNames;
}
const string& ofxGuiTabs::getSelectedTabName(){
    return selectedTab.get();
}
