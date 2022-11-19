//
//  ofxGuiTabs.hpp
//  tabs
//
//  Created by Roy Macdonald on 10/14/18.
//
//
//
#pragma once


#include "ofParameter.h"
#include "ofxGuiGroup.h"

#include "ofxGuiTabsOption.h"

#ifdef USE_OFX_GUI_TOOLTIP
#include "ofxGuiTooltipBase.h"
#endif
using namespace std;



class ofxGuiTabs : public ofxBaseGui
#ifdef USE_OFX_GUI_TOOLTIP
, public ofxGuiTooltipBase
#endif
{

public:
    virtual ~ofxGuiTabs();
    // ---------------------------------------------------
    // ----------------- Constructors
    // ---------------------------------------------------
    
    /// default constructor.
    /// \warning You will need to call the one of the setup class methods to be able to use this tabs
    ofxGuiTabs();
    
    /// \brief constructor that calls setup function with same parameters
    /// Dropdown will be empty. you should add values with the add(...) function
    /// @param name the name of the tabs.
    /// @param width = the width of the drawn element. Defaults to ofxGui's default
    /// @param height = the height of the drawn element. Defaults to twice of ofxGui's default. This is because one line is used to draw the tabs name and the second for the selected value it has, if any.
    ofxGuiTabs(std::string name, float width = defaultWidth, float height = defaultHeight*2);
    
    /// \brief constructor that calls setup function with same parameters
    /// Dropdown will be empty. You should add values with the add(...) function
    /// @param param The passed ofParameter will be "linked" to the tabs and will change as you select different elements from the tabs
    /// The name of this tabs is taken from the passed ofParameter's name
    /// @param width = the width of the drawn element. Defaults to ofxGui's default
    /// @param height = the height of the drawn element. Defaults to twice of ofxGui's default. This is because one line is used to draw the tabs name and the second for the selected value it has, if any.
    ofxGuiTabs(ofParameter<string> param, float width = defaultWidth, float height = defaultHeight*2);
    
    /// \brief Construct and add elements
    /// @param param The passed ofParameter will be "linked" to the tabs and will change as you select different elements from the tabs
    /// The name of this tabs is taken from the passed ofParameter's name
    /// \param groupNames vector with the names of the tabs that will get created.
    /// @param width = the width of the drawn element. Defaults to ofxGui's default
    /// @param height = the height of the drawn element. Defaults to twice of ofxGui's default. This is because one line is used to draw the tabs name and the second for the selected value it has, if any.
    /// This is useful when for instance you have an ofParameter<int> but you want to display different names for each value, rather than the value itself.
    /// You still can add more values with the add(...) function
    ofxGuiTabs(ofParameter<string> param, const vector<string>& tabNames, float width = defaultWidth, float height = defaultHeight*2);
    
    
    //---- Setup function.
    // Only call setup if the default constructor was used.
    /// \brief Setup this dropdonw
    /// Dropdown will be empty. You should add values with the add(...) function
    /// @param param The passed ofParameter will be "linked" to the tabs and will change as you select different elements from the tabs
    /// The name of this tabs is taken from the passed ofParameter's name
    /// @param width = the width of the drawn element. Defaults to ofxGui's default
    /// @param height = the height of the drawn element. Defaults to twice of ofxGui's default. This is because one line is used to draw the tabs name and the second for the selected value it has, if any.
    ofxGuiTabs * setup(ofParameter<string> param, float width = defaultWidth, float height = defaultHeight*2);
	
    /// \brief Setup this tabs
    /// \warning use only when you instanced this classs and used its default constructor.
    /// @param name the name of the tabs.
    /// @param width = the width of the drawn element. Defaults to ofxGui's default
    /// @param height = the height of the drawn element. Defaults to twice of ofxGui's default. This is because one line is used to draw the tabs name and the second for the selected value it has, if any.
    /// Dropdown will be empty. you should add values with the add(...) function
    ofxGuiTabs * setup(std::string name, float width = defaultWidth, float height = defaultHeight*2);
	
    		

    // ---------------------------------------------------
    // ----------------- Adding/creating tabs elements
    // ---------------------------------------------------
    
    /// \brief add a tabs option.
    /// This will create a new tab.
    /// @param tabName the name that this new tab will have
    /// \return pointer to the newly created tab
    ofxGuiGroup * newTab(const string& tabName);

    
    /// \brief add several tabs  at once.
    /// This will create new tabs.
    /// @param tabNames a vector of strings containing the names of all the tabs to create.
    void newTabs(const std::vector<string> & tabNames);
    
	    
		
    /// \brief clear all the elements from this tabs.
	void clear();
	
	
	
    /// \brief ofEvent called whenever  the selected tab changes. The data passed along with it is the name of the newly selected tab
	ofEvent<std::string> selection_E;
    
    
    // ---------------------------------------------------
    // ----------------- ofParameters
    // ---------------------------------------------------
    ///\brief this is just a needed function, as it overrides a virtual abstract base function.
    ///\return the selectedValue ofParam, but as it is an ofAbstractParam you will need to cast it properly in order to make it useful.
    virtual ofAbstractParameter & getParameter() override;
	
    
    // ---------------------------------------------------
    // ----------------- Show / Hide / Draw
    // ---------------------------------------------------
    
    ///\brief Force the redrawing of this gui widget. This automatically happens by itself but there are some edge case where you might want to trigger it.
    /// Don't call this function on every frame or very often as you will be using computational resources unnecesarily.
	void forceRedraw(){
		setNeedsRedraw();
	}
    
        // ---------------------------------------------------
    // ----------------- Selection
    // ---------------------------------------------------
    ///\brief Select a tab by its name
    ///\param the name of the tab to select
    ///\return boolean. true if there was a tab with the passed name and it got selected, false otherwise
	bool setSelectedTab( const std::string& tabName);
	
    ///\brief Deselect all tabs. No gui group will be shown
	void deselect() ;
    
    
    // ---------------------------------------------------
    // ----------------- Overriden mouse callbacks. Dont call these manually
    // ---------------------------------------------------
    
    virtual bool mouseReleased(ofMouseEventArgs & args) override;
    virtual bool mousePressed(ofMouseEventArgs & args) override;
    virtual bool mouseMoved(ofMouseEventArgs & args) override;
    virtual bool mouseDragged(ofMouseEventArgs & args) override;
    virtual bool mouseScrolled(ofMouseEventArgs & args) override;
    
    void registerMouseEvents() override;
    void unregisterMouseEvents() override;

    
    // ---------------------------------------------------
    // ----------------- getters
    // ---------------------------------------------------

    
    ///\brief returns the number of tabs
    ///\returns std::size_t with the amount of tabs.
    size_t getNumTabs(){return guiGroups.size(); }
    
    ///\brief Returns the option gui using the option's  name
    ///\param name the option name you want to get
    ///\returns an ofxGuiTabsOption pointer
    ofxGuiTabsOption* getTabByName(const string& name);
    
    ///\brief get all the names of the Tabs
    ///\return std::vector containing all the names
    const vector<string> & getTabNames();
    
    ///\brief Get the currently active gui group
    ///\return pointer to the active ofxGuiGroup
    ofxGuiGroup * getCurrentGuiGroup();
    
    
    ///\brief get a gui group by its name
    ///\param name the name of the guigroup to get
    ///\return pointer to an ofxGuiGroup. If there isn't a group with the passed name a nullptr will be returned.
    ofxGuiGroup * getGuiGroup(const string & name);
    
    ///\brief get the name of the currently selected tab
    ///\return std::string with the name of the currently selected tab
    const string& getSelectedTabName();
    
#ifdef USE_OFX_GUI_TOOLTIP

    // ---------------------------------------------------
    // ----------------- Tooltips
    // ---------------------------------------------------

    /// Use ofxGuiTooltips to manage the tooltips of this addon
    /// There is no extra code needed, Just add ofxGuiTooltips with project generator and these will become active
    
    
    ///\brief set tooltips for this tabs.
    ///If there is no tooltip data for any of the tooltip options, including nested tabss
    ///the json object will get populated with empty strings so it is easier to fill out.
    ///Make sure to save the json back to disk in order to save this auto generated json.
    ///\param json the json object containing the tooltip data
    virtual void setupTooltip(ofJson & json) override;
    
    ///\ reset all tooltips. This works recursively with any nested tabs
    virtual void resetTooltips() override;
    
    ///\brief Add a tooltip for the passed value
    ///\param tabName The name of the tab for which you want to add tthe tooltip
    ///\param toolTipText the text of the tooltip to add
    void addTooltip(const string& tabName, const string& toolTipText);
    
    
    ///\brief Enable tooltips. This works recursively with any nested tabs
    virtual void enableTooltip() override;

    ///\brief Disable tooltips. This works recursively with any nested tabs
    virtual void disableTooltip() override;
        
    ///\brief Draw the tooltips.
    ///This needs to be called independently and after the tabs and gui are drawn,
    ///otherwise the tooltips might get occluded by the gui.
    virtual void drawTooltip() override;
    
#endif


protected:
	
#ifdef USE_OFX_GUI_TOOLTIP
    virtual bool isOver() override{
        return false;
    }
#endif
    
	
	virtual bool setValue(float mx, float my, bool bCheck) override;
		
	void disableSiblings(ofxGuiTabsOption* child);
		
	virtual void generateDraw() override;
		
	virtual void render() override;
		
	void selectedTabChanged(string & name);
    
    void tabChanged(string & name);
	

	ofEventListeners optionsListeners;

    ofEventListeners mouseListeners;

    ofEventListener setlectedValueListener;
	
    ofPath bg;
        
    
private:
    
    map<string, shared_ptr<ofxGuiGroup>> guiGroups;
    map<string, shared_ptr<ofxGuiTabsOption>> tabs;
    vector<string> tabNames;
    vector<ofxGuiGroup*> groups;
    vector<ofxGuiTabsOption*> tabsCollection;
    
    bool bRegisteredForMouseEvents = false;
    bool bIsSetup = false;
    bool bGuiActive = false;
    
    
    bool bIgnoreSelectedTabChange = false;

    ///\brief selected value parameter. This is the one that actually changes when a tab gets selected.
    ofParameter<string> selectedTab;
    
    
    // this is used esentially to hold the parameter groups of the tabs so it can be saved and loaded by ofxGui
    ofParameterGroup groupsParam;

    
    
};




