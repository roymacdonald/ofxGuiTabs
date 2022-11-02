//
//  ofxGuiTabs.hpp
//  dropdown
//
//  Created by Roy Macdonald on 10/14/18.
//
//
//
#pragma once


#include "ofParameter.h"
#include "ofxGuiGroup.h"

#include "ofxGuiTabsOption.h"


using namespace std;



template<class T>
class ofxGuiTabs_ : public ofxBaseGui{

public:
    virtual ~ofxGuiTabs_();
    // ---------------------------------------------------
    // ----------------- Constructors
    // ---------------------------------------------------
    
    /// default constructor.
    /// \warning You will need to call the one of the setup class methods to be able to use this dropdown
    ofxGuiTabs_(){};
    
    /// \brief constructor that calls setup function with same parameters
    /// Dropdown will be empty. you should add values with the add(...) function
    /// @param name the name of the dropdown.
    /// @param width = the width of the drawn element. Defaults to ofxGui's default
    /// @param height = the height of the drawn element. Defaults to twice of ofxGui's default. This is because one line is used to draw the dropdown name and the second for the selected value it has, if any.
    ofxGuiTabs_(std::string name, float width = defaultWidth, float height = defaultHeight*2);
    
    /// \brief constructor that calls setup function with same parameters
    /// Dropdown will be empty. You should add values with the add(...) function
    /// @param param The passed ofParameter will be "linked" to the dropdown and will change as you select different elements from the dropdown
    /// The name of this dropdown is taken from the passed ofParameter's name
    /// @param width = the width of the drawn element. Defaults to ofxGui's default
    /// @param height = the height of the drawn element. Defaults to twice of ofxGui's default. This is because one line is used to draw the dropdown name and the second for the selected value it has, if any.
    ofxGuiTabs_(ofParameter<T> param, float width = defaultWidth, float height = defaultHeight*2);
    
    /// \brief Construct and add elements
    /// @param param The passed ofParameter will be "linked" to the dropdown and will change as you select different elements from the dropdown
    /// The name of this dropdown is taken from the passed ofParameter's name
    /// \param dropDownOptions  std::map which maps  whatever type the passed ofParameter has to a string representation of it. Dropdown will be populated with it.
    /// @param width = the width of the drawn element. Defaults to ofxGui's default
    /// @param height = the height of the drawn element. Defaults to twice of ofxGui's default. This is because one line is used to draw the dropdown name and the second for the selected value it has, if any.
    /// This is useful when for instance you have an ofParameter<int> but you want to display different names for each value, rather than the value itself.
    /// You still can add more values with the add(...) function
    ofxGuiTabs_(ofParameter<T> param, const map<T,string>& dropDownOptions, float width = defaultWidth, float height = defaultHeight*2);
    
    
    /// Construct and add elements
    /// \brief Construct and add elements
    /// \param dropDownOptions  std:vector with values of the same type as the ofParameter passed. Dropdown will be populated with this values.
    /// @param param The passed ofParameter will be "linked" to the dropdown and will change as you select different elements from the dropdown
    /// The name of this dropdown is taken from the passed ofParameter's name
    /// @param width = the width of the drawn element. Defaults to ofxGui's default
    /// @param height = the height of the drawn element. Defaults to twice of ofxGui's default. This is because one line is used to draw the dropdown name and the second for the selected value it has, if any.
    /// This is useful when for instance you have an ofParameter<int> but you want to display different names for each value, rather than the value itself.
    /// You still can add more values with the add(...) function
    ofxGuiTabs_(ofParameter<T> param, const std::vector<T> & dropDownOptions, float width = defaultWidth, float height = defaultHeight*2);
	
    
    //---- Setup function.
    // Only call setup if the default constructor was used.
    /// \brief Setup this dropdonw
    /// Dropdown will be empty. You should add values with the add(...) function
    /// @param param The passed ofParameter will be "linked" to the dropdown and will change as you select different elements from the dropdown
    /// The name of this dropdown is taken from the passed ofParameter's name
    /// @param width = the width of the drawn element. Defaults to ofxGui's default
    /// @param height = the height of the drawn element. Defaults to twice of ofxGui's default. This is because one line is used to draw the dropdown name and the second for the selected value it has, if any.
    ofxGuiTabs_ * setup(ofParameter<T> param, float width = defaultWidth, float height = defaultHeight*2);
	
    /// \brief Setup this dropdonw
    /// \warning use only when you instanced this classs and used its default constructor.
    /// @param name the name of the dropdown.
    /// @param width = the width of the drawn element. Defaults to ofxGui's default
    /// @param height = the height of the drawn element. Defaults to twice of ofxGui's default. This is because one line is used to draw the dropdown name and the second for the selected value it has, if any.
    /// Dropdown will be empty. you should add values with the add(...) function
    ofxGuiTabs_ * setup(std::string name, float width = defaultWidth, float height = defaultHeight*2);
	
    
    // ---------------------------------------------------
    // ----------------- Multiple Selection Option
    // ---------------------------------------------------
    
    /// \brief Enable Multiple Items selection. This is mutually exclusive with collapse on selection
	void enableMultipleSelection();
    
    /// \brief Disable Multiple Items selection. This is mutually exclusive with collapse on selection
    void disableMultipleSelection();
    
    /// \brief get if multiple selection is enabled.
    /// \return true if multiple selection is enabled, false otherwise
	bool isEnabledMultipleSelection();
    
    /// \brief get the ofParameter that indicates if multiple selection is enabled or not.
    /// Use this to add this option to a GUI.
//	ofParameter<bool> & getMultiSelectionParameter();
		

    // ---------------------------------------------------
    // ----------------- Adding/creating dropdown elements
    // ---------------------------------------------------
    
    /// \brief add a dropdown option.
    /// This will create a new dropdown element which is owend by the dropdown.
    /// @param value the value that the this new option will have
    /// @param option The string  that will be shown when selecting this value
    /// \return pointer to the newly created dropdown element
    ofxGuiTabs_ * add(const T& value, const string& option);

    /// \brief add a dropdown option.
    /// This will create a new dropdown element which is owend by the dropdown.
    /// @param value the value that the this new option will have.
    /// The string shown in the dropdown will be the automatic string representation of this value
    /// \return pointer to the newly created dropdown element
    ofxGuiTabs_ * add(const T& value);
    
    /// \brief add several dropdown option at once.
    /// This will create new dropdown elements which will be owend by the dropdown.
    /// @param options a vector with several options.
    /// The string shown in the dropdown will be the automatic string representation of this value
    /// \return pointer to the newly created dropdown element
    ofxGuiTabs_ * add(const std::vector<T> & options);
    
    /// \brief add several dropdown option at once.
    /// This will create new dropdown elements which will be owend by the dropdown.
    /// @param options a map containing the values and their string representations to be added.
    /// This is the same as calling  add(const T& value, const string& option) for each of the map's values.
    /// \return pointer to the newly created dropdown element
    ofxGuiTabs_ * add(const std::map<T, std::string> & options);
    
	    
		
    /// \brief clear all the elements from this dropdown.
    /// \warning the correct destruction of dropdown elements will happen ONLY for the ones  owned by this dropdown will be carried out.
	void clear();
	
	
	
	
	
    // ---------------------------------------------------
    // ----------------- Events and listeners
    // ---------------------------------------------------
    
    /// \brief Helper function to add a listenerr that gets called whenever the dropdown selection changes
    /// \param listener pointer to the object that is listening
    /// \param method pointer to the listener's method to be called
	template<class ListenerClass, typename ListenerMethod>
	void addListener(ListenerClass * listener, ListenerMethod method){
		selectedValue.addListener(listener,method);
	}
	
    /// \brief Helper function to remove a previously added listener.
    ///  The parameters passed to this function must be exactly the same as the ones passed to addListener in order to successfuly remove the listener
    /// \param listener pointer to the object that is listening
    /// \param method pointer to the listener's method to be called
	template<class ListenerClass, typename ListenerMethod>
	void removeListener(ListenerClass * listener, ListenerMethod method){
		selectedValue.removeListener(listener,method);
	}

    
    /// \brief ofEvent called whenever the dropdown selection changes. The data passed along with it is the displayed name of the option that changed
	ofEvent<std::string> change_E;
    
    
    // ---------------------------------------------------
    // ----------------- ofParameters
    // ---------------------------------------------------
    ///\brief this is just a needed function, as it overrides a virtual abstract base function.
    ///\return the selectedValue ofParam, but as it is an ofAbstractParam you will need to cast it properly in order to make it useful.
    ///As such, it is way much easier to simply acces selectedValue directly.
    virtual ofAbstractParameter & getParameter() override;

    ///\brief get the parameter group for the dropdown paramaters. Use this if you want to add to a gui these parameters.
    ///\return ofParameterGroup with the dropdown params.
//    ofParameterGroup& getDropdownParameters();
	
	
    
    ///\brief selected value parameter. This is the one that actually changes when a selection in the dropdown is made.
	ofParameter<T> selectedValue;
	
	
    
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
	void setSelectedValueByName( const std::string& valueName, bool bNotify);
	void setSelectedValueByIndex( const size_t& index, bool bNotify);

	void deselect() ;

    std::string getOptionAt(size_t index);
    
    // ---------------------------------------------------
    // ----------------- Children
    // ---------------------------------------------------
	

    std::vector<unique_ptr<ofxGuiTabsOption>>& getOwnedChildren(){return ownedChildren;}
    
    
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

    
    void enableKeys();
    void disableKeys();
    bool isKeysEnabled();
    
    
    
protected:
	
    
    
    ofEventListeners paramsListeners;
    

//    void multiSelectionChanged(bool&);
    

	ofParameter<bool> bMultiselection = { "Multi Selection", false};
    
//    ofParameterGroup dropdownParams;
	
	virtual bool setValue(float mx, float my, bool bCheck) override;
	
//	void disableElement(ofxGuiTabsOption* e, bool bCheckAgainstThis = false);
	
	int myMouseEventsPriority;
	
	void disableSiblings(ofxGuiTabsOption* child);
		
	virtual void generateDraw() override;
		
	virtual void render() override;

	vector<string> options;
    vector<T> values;
	
	
	void optionChanged( const void * sender,bool&);
//	bool bGroupEnabled = false;
	
//	void buttonClicked(bool &);
		
	void selectedValueChanged(T & newvalue);
	
    
//	ofxGuiGroup group;
	ofEventListeners optionsListeners;
//	ofEventListeners childDropdownListeners;
    ofEventListeners mouseListeners;
	
//	ofEventListener buttonListener;
    ofEventListener setlectedValueListener;
    
	ofVboMesh optionTextMesh;
	
	std::string selectedOption;
		
	
    ofPath bg;
    
    bool keyReleased(ofKeyEventArgs&);
    
private:

    ofEventListener keysListener;
    bool bListeningKeys = false;
    

	std::vector<unique_ptr<ofxGuiTabsOption>> ownedChildren;
    
    bool bRegisteredForMouseEvents = false;
    bool bIsSetup = false;
    bool bGuiActive = false;
};






typedef ofxGuiTabs_<string> ofxGuiTabs;
typedef ofxGuiTabs_<int> ofxGuiIntTabs;
