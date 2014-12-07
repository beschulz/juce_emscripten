/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainContentComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainContentComponent::MainContentComponent ()
{
    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->addListener (this);

    addAndMakeVisible (textEditor = new TextEditor ("new text editor"));
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setText (String::empty);

    addAndMakeVisible (slider = new Slider ("new slider"));
    slider->setRange (0, 10, 0);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    slider->addListener (this);

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("group")));

    addAndMakeVisible (slider2 = new Slider ("new slider"));
    slider2->setRange (0, 10, 0);
    slider2->setSliderStyle (Slider::RotaryHorizontalDrag);
    slider2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    slider2->addListener (this);

    addAndMakeVisible (textButton2 = new TextButton ("new button"));
    textButton2->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainContentComponent::~MainContentComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textButton = nullptr;
    textEditor = nullptr;
    slider = nullptr;
    groupComponent = nullptr;
    slider2 = nullptr;
    textButton2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainContentComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    std::clog << "MainContentComponent::paint: " << std::endl;
    //[/UserPrePaint]

    g.fillAll (Colour (0xff242424));

    g.setColour (Colour (0xffa52a71));
    g.fillRoundedRectangle (369.0f, 21.0f, 100.0f, 100.0f, 10.000f);

    g.setColour (Colour (0xffa32aa5));
    g.fillEllipse (57.0f, 101.0f, 100.0f, 100.0f);

    g.setColour (Colour (0xffa53e2a));
    g.fillPath (internalPath1);

    g.setColour (Colour (0xffa52a90));
    g.fillRoundedRectangle (193.0f, 253.0f, 100.0f, 100.0f, 10.000f);

    g.setColour (Colour (0xff3b2871));
    g.fillRoundedRectangle (129.0f, 61.0f, 100.0f, 100.0f, 10.000f);

    g.setColour (Colour (0xff2a44a5));
    g.fillRect (201, 29, 100, 100);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainContentComponent::resized()
{
    textButton->setBounds (16, 16, 150, 24);
    textEditor->setBounds (32, 288, 248, 96);
    slider->setBounds (288, 360, 150, 24);
    groupComponent->setBounds (16, 48, 200, 150);
    slider2->setBounds (240, 136, 87, 96);
    textButton2->setBounds (176, 16, 150, 24);
    internalPath1.clear();
    internalPath1.startNewSubPath (87.0f, 229.0f);
    internalPath1.lineTo (117.0f, 279.0f);
    internalPath1.lineTo (57.0f, 279.0f);
    internalPath1.closeSubPath();

    //[UserResized] Add your own custom resize handling here..
    std::clog << "MainContentComponent::resized: " << getWidth() << "x" << getHeight() << std::endl;
    //[/UserResized]
}

void MainContentComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        NativeMessageBox::showOkCancelBox(AlertWindow::NoIcon, "Title", "Message", this, nullptr);
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == textButton2)
    {
        //[UserButtonCode_textButton2] -- add your button handler code here..
        AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, "title", "message");
        //[/UserButtonCode_textButton2]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainContentComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }
    else if (sliderThatWasMoved == slider2)
    {
        //[UserSliderCode_slider2] -- add your slider handling code here..
        //[/UserSliderCode_slider2]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainContentComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff242424">
    <ROUNDRECT pos="369 21 100 100" cornerSize="10" fill="solid: ffa52a71" hasStroke="0"/>
    <ELLIPSE pos="57 101 100 100" fill="solid: ffa32aa5" hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: ffa53e2a" hasStroke="0" nonZeroWinding="1">s 87 229 l 117 279 l 57 279 x</PATH>
    <ROUNDRECT pos="193 253 100 100" cornerSize="10" fill="solid: ffa52a90"
               hasStroke="0"/>
    <ROUNDRECT pos="129 61 100 100" cornerSize="10" fill="solid: ff3b2871" hasStroke="0"/>
    <RECT pos="201 29 100 100" fill="solid: ff2a44a5" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="new button" id="2b34d71edae8652e" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="16 16 150 24" buttonText="new button"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="new text editor" id="c8d7b4d4a0926398" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="32 288 248 96" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <SLIDER name="new slider" id="4c8abdab8f24db35" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="288 360 150 24" min="0" max="10"
          int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GROUPCOMPONENT name="new group" id="8de3d402da093558" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="16 48 200 150" title="group"/>
  <SLIDER name="new slider" id="23ed4f5615882f88" memberName="slider2"
          virtualName="" explicitFocusOrder="0" pos="240 136 87 96" min="0"
          max="10" int="0" style="RotaryHorizontalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="new button" id="7c4aa0276d098607" memberName="textButton2"
              virtualName="" explicitFocusOrder="0" pos="176 16 150 24" buttonText="new button"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
