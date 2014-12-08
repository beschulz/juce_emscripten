/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2013 - Raw Material Software Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

#ifndef __JUCER_COMPONENTLAYOUTEDITOR_JUCEHEADER__
#define __JUCER_COMPONENTLAYOUTEDITOR_JUCEHEADER__

#include "jucer_ComponentOverlayComponent.h"
#include "../jucer_JucerDocument.h"
#include "jucer_SnapGridPainter.h"


//==============================================================================
/**
*/
class ComponentLayoutEditor  : public Component,
                               public ChangeListener,
                               public FileDragAndDropTarget,
                               public DragAndDropTarget,
                               public LassoSource<Component*>
{
public:
    //==============================================================================
    ComponentLayoutEditor (JucerDocument& document, ComponentLayout& layout);
    ~ComponentLayoutEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void visibilityChanged() override;
    void changeListenerCallback (ChangeBroadcaster*) override;

    void mouseDown (const MouseEvent&) override;
    void mouseDrag (const MouseEvent&) override;
    void mouseUp (const MouseEvent&) override;
    bool keyPressed (const KeyPress&) override;

    bool isInterestedInFileDrag (const StringArray& files) override;
    void filesDropped (const StringArray& filenames, int x, int y) override;

    bool isInterestedInDragSource (const SourceDetails& dragSourceDetails) override;
    void itemDropped (const SourceDetails& dragSourceDetails) override;


    ComponentLayout& getLayout() const noexcept                 { return layout; }

    void findLassoItemsInArea (Array <Component*>& results, const Rectangle<int>& area);

    SelectedItemSet<Component*>& getLassoSelection();

    //==============================================================================
    void refreshAllComponents();
    void updateOverlayPositions();

    ComponentOverlayComponent* getOverlayCompFor (Component*) const;

    Rectangle<int> getComponentArea() const;
    Image createComponentLayerSnapshot() const;

	void setLookAndFeelFromDynamicLibrary(String libraryName);
	void freeLookAndFeel();

private:
	class LookAndFeelProvider
	{
	public:
		LookAndFeelProvider()
		:lookAndFeelIsFromLibrary(false)
		,lookAndFeel(new LookAndFeel_V3())
		{

		}

		LookAndFeelProvider(const String& libraryName)
				:dynamicLibrary(libraryName)
				,lookAndFeelIsFromLibrary(false)
		{
			typedef LookAndFeel* (*LookAndFeelCreate)();

			if( LookAndFeelCreate f = (LookAndFeelCreate)dynamicLibrary.getFunction("juce_newLookAndFeel"))
			{
				lookAndFeel = f();
				lookAndFeelIsFromLibrary = true;
			}

			// open of dynamic library, getting function pointer or creation failed
			if(!lookAndFeel)
			{
				lookAndFeel = new LookAndFeel_V3();
			}
		}

		~LookAndFeelProvider()
		{
			/*
			* This takes care of the case, that the Introjucer was for example
			* compiled against msvcrt and the dll the LookAndFeel comes from was
			* compiled against msvcrtd. If there is just the slightest chance, that
			* a dynamic library is using a different allocator than the loading application,
			* it's best practice to leave the object destruction and deallocation up to
			* the dynamic library.
			* */
			if(lookAndFeelIsFromLibrary)
			{
				typedef void (*LookAndFeelDestroy)(LookAndFeel*);
				if(LookAndFeelDestroy f = (LookAndFeelDestroy)dynamicLibrary.getFunction("juce_deleteLookAndFeel"))
				{
					f(lookAndFeel.release());
				}
			}
		}

		LookAndFeel* getLookAndFeel()
		{
			return lookAndFeel;
		}
	private:
		DynamicLibrary dynamicLibrary;
		bool lookAndFeelIsFromLibrary;
		ScopedPointer<LookAndFeel> lookAndFeel;
	};

	ScopedPointer<LookAndFeelProvider> lookAndFeelProvider;

    JucerDocument& document;
    ComponentLayout& layout;
    Component* subCompHolder;

    LassoComponent<Component*> lassoComp;
    SnapGridPainter grid;
    bool firstResize;
};


#endif   // __JUCER_COMPONENTLAYOUTEDITOR_JUCEHEADER__
