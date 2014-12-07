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

} // (juce namespace)

extern juce::JUCEApplicationBase* juce_CreateApplication(); // (from START_JUCE_APPLICATION)

//==============================================================================
void launchApp()
{
    using namespace juce;

    DBG (SystemStats::getJUCEVersion());

    JUCEApplicationBase::createInstance = &juce_CreateApplication;

    initialiseJuce_GUI();

    JUCEApplicationBase* app = JUCEApplicationBase::createInstance();
    if (! app->initialiseApp())
        exit (app->getApplicationReturnValue());

    jassert (MessageManager::getInstance()->isThisTheMessageThread());
}

#include <emscripten.h>

namespace juce
{

class EmscriptenComponentPeer : public ComponentPeer
{
    Rectangle< int > bounds;
    String id;
    long timerId;
    static int highestZIndex;

    public:
        //using ComponentPeer::ComponentPeer;
        EmscriptenComponentPeer(Component &component, int styleFlags)
        :ComponentPeer(component, styleFlags)
        {
            std::cout << "EmscriptenComponentPeer" << std::endl;

            id = Uuid().toDashedString();

            std::cout << "id is " << id << std::endl;

            EM_ASM_INT({
                var canvas = document.createElement('canvas');
                canvas.id  = Pointer_stringify($0);
                canvas.style.zIndex   = $6;
                console.log($6, canvas.style.zIndex);
                canvas.style.position = "absolute";
                canvas.style.border   = "1px solid";
                canvas.style.left = $1;
                canvas.style.top  = $2;
                canvas.width  = $3;
                canvas.height = $4;

                window.juce_mouseCallback = window.juce_mouse_callback || Module.cwrap('juce_mouseCallback', 'void', ['number', 'string', 'number', 'number']);

                canvas.onmousedown  = function(e) { window.juce_mouseCallback($5, 'down' , e.pageX, e.pageY); };
                canvas.onmouseenter = function(e) { window.juce_mouseCallback($5, 'enter', e.pageX, e.pageY); };
                canvas.onmouseleave = function(e) { window.juce_mouseCallback($5, 'leave', e.pageX, e.pageY); };
                canvas.onmousemove  = function(e) { window.juce_mouseCallback($5, 'move' , e.pageX, e.pageY); };
                //canvas.onmouseout   = function(e) window.juce_mouseCallbackck($5, 'out'  , pageX.x, pageY.y); };
                canvas.onmouseover  = function(e) { window.juce_mouseCallback($5, 'over' , e.pageX, e.pageY); };
                canvas.onmouseup    = function(e) { window.juce_mouseCallback($5, 'up'   , e.pageX, e.pageY); };
                canvas.onmousewheel = function(e) { window.juce_mouseCallback($5, 'wheel', e.wheelDeltaX, e.wheelDeltaY); };

                canvas.setAttribute('data-peer', $5);

                document.body.appendChild(canvas);
            }, id.toRawUTF8(), bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), this, ++highestZIndex);

            timerId = EM_ASM_ARGS({
                if(!window.repaintHandlerInstalled)
                {
                    window.repaintHandlerInstalled=true;
                    var repaintPeer = Module.cwrap('repaintPeer', 'void', ['number']);

                    return window.setInterval(function(){
                        repaintPeer($0);
                    }, 1000);
                }
            }, this);

            grabFocus();

            //if (isFocused())
            //    handleFocusGain();
        }

        ~EmscriptenComponentPeer()
        {
            EM_ASM_ARGS({
                window.clearInterval($1);

                var canvas = document.getElementById(Pointer_stringify($0));
                canvas.parentElement.removeChild(canvas);
            }, id.toRawUTF8(), timerId);
        }

        virtual void* getNativeHandle () const override
        {
            return (void*)this;
        }

        virtual void setVisible (bool shouldBeVisible) override
        {

        }

        virtual void setTitle (const String &title) override
        {
            std::cout << "setTitle: " << title << std::endl;
        }

        virtual void setBounds (const Rectangle< int > &newBounds, bool isNowFullScreen) override
        {
            EM_ASM_ARGS({
                var canvas = document.getElementById(Pointer_stringify($0));

                canvas.style.left = $1 + 'px';
                canvas.style.top  = $2 + 'px';
                if(canvas.width  != $3) canvas.width  = $3;
                if(canvas.height != $4) canvas.height = $4;
            }, id.toRawUTF8(), newBounds.getX(), newBounds.getY(), newBounds.getWidth(), newBounds.getHeight());

            //if(!newBounds.isEmpty() && (newBounds.getWidth() != bounds.getWidth() || newBounds.getHeight() != bounds.getHeight()))
            //    repaint(newBounds.withZeroOrigin());

            bounds = newBounds;
            fullscreen = isNowFullScreen;

            handleMovedOrResized();
        }

        virtual Rectangle<int> getBounds () const override
        {
            return bounds;
        }

        virtual Point<float>  localToGlobal (Point< float > relativePosition) override
        {
            return relativePosition + bounds.getPosition().toFloat();
        }

        virtual Point<float>  globalToLocal (Point< float > screenPosition) override
        {
            return screenPosition - bounds.getPosition().toFloat();
        }

        virtual void setMinimised (bool shouldBeMinimised) override
        {

        }

        virtual bool isMinimised () const override
        {
            return false;
        }

        bool fullscreen=false;
        virtual void setFullScreen (bool shouldBeFullScreen) override
        {
            EM_ASM_ARGS({
                var canvas = document.getElementById(Pointer_stringify($0));
                canvas.style.left='0px';
                canvas.style.top ='0px';

                canvas.width=window.innerWidth;
                canvas.height=window.innerHeight;
            }, id.toRawUTF8());

            bounds = bounds.withZeroOrigin();

            bounds.setWidth ( EM_ASM_ARGS({ return window.innerWidth; }, 0) );
            bounds.setHeight( EM_ASM_ARGS({ return window.innerHeight; }, 0) );

            this->setBounds(bounds, true);
        }

        virtual bool isFullScreen () const override
        {
            return fullscreen;
        }

        virtual void setIcon (const Image &newIcon) override
        {

        }

        virtual bool contains (Point< int > localPos, bool trueIfInAChildWindow) const override
        {
            Point<int> globalPos = localPos+bounds.getPosition();
            return bounds.contains(globalPos);
        }

        virtual BorderSize< int >   getFrameSize () const override
        {
            return BorderSize<int>();
        }

        virtual bool setAlwaysOnTop (bool alwaysOnTop) override
        {
            return false;
        }

        virtual void toFront (bool makeActive) override
        {
            std::clog << "toFront " << id << " " << makeActive <<  std::endl;

            highestZIndex = EM_ASM_INT({
                var canvas = document.getElementById(Pointer_stringify($0));
                canvas.style.zIndex = parseInt($1)+1;
                console.log(canvas.style.zIndex, $1);
                return parseInt(canvas.style.zIndex);
            }, id.toRawUTF8(), highestZIndex);

            handleBroughtToFront();

            if(makeActive)
            {
                grabFocus();
            }
        }

        virtual void toBehind (ComponentPeer *other) override
        {
            std::clog << "toBehind" << std::endl;

            if(EmscriptenComponentPeer* otherPeer = dynamic_cast<EmscriptenComponentPeer*>(other))
            {
                int newZIndex = EM_ASM_INT({
                    var canvas = document.getElementById(Pointer_stringify($0));
                    var other  = document.getElementById(Pointer_stringify($1));
                    canvas.zIndex = parseInt(other.zIndex)-1;
                    return parseInt(other.zIndex);
                }, id.toRawUTF8(), otherPeer->id.toRawUTF8());

                highestZIndex = std::max(highestZIndex, newZIndex);

                otherPeer->handleFocusGain();
            }

            if(focused)
                handleFocusLoss();

            focused=false;
        }

        bool focused=false;
        virtual bool isFocused() const override
        {
            return focused;
        }

        virtual void grabFocus() override
        {
            std::clog << "grabFocus " << id << std::endl;
            if(!focused)
                handleFocusGain();
            focused=true;
        }

        virtual void textInputRequired(Point< int > position, TextInputTarget &) override
        {
            std::cout << "textInputRequired" << std::endl;
        }


        bool currentlyRepainting = false;
        virtual void repaint (const Rectangle< int > &area) override
        {
            if(currentlyRepainting) return;
            currentlyRepainting = true;

            std::clog << "repaint: x=" << area.getX() << ", y=" << area.getY() << ", w=" << area.getWidth() << ", h=" << area.getHeight() << std::endl;

            Image temp(Image::ARGB, area.getWidth(), area.getHeight(), true);
            LowLevelGraphicsSoftwareRenderer g(temp);
            g.setOrigin (-area.getPosition());
            handlePaint (g);

            /*{
                Graphics g_(temp);
                g_.setColour(Colours::red);
                g_.fillEllipse(0,0,100,100);
                g_.setColour(Colours::green);
                g_.fillEllipse(100,0,100,100);
                g_.setColour(Colours::blue);
                g_.fillEllipse(0,100,100,100);
            }*/

            Image::BitmapData bitmapData(temp, Image::BitmapData::readOnly);

            EM_ASM_ARGS({
                var id = Pointer_stringify($0);
                var pointer = $1;
                var width   = $2;
                var height  = $3;
                var dest_x  = $4;
                var dest_y  = $5;

                var canvas = document.getElementById(id);
                var ctx = canvas.getContext("2d");

                var buffer = new Uint8ClampedArray(Module.HEAPU8.buffer, pointer, width*height*4);

                for (var idx = 0; idx < buffer.length; idx += 4)
                {
                    var r = buffer[idx+0];
                    var b = buffer[idx+2];

                    buffer[idx+0] = b;
                    buffer[idx+2] = r;
                }

                var imageData = ctx.createImageData(width, height);
                imageData.data.set(buffer);

                var tmp = document.createElement('canvas');
                tmp.width = width;
                tmp.height = height;
                var tmp_ctx = tmp.getContext("2d");
                tmp_ctx.putImageData(imageData, 0,0);

                ctx.drawImage(tmp, dest_x, dest_y);

                delete tmp;
                delete buffer;
            }, id.toRawUTF8(), bitmapData.getPixelPointer(0,0), temp.getWidth(), temp.getHeight(), area.getX(), area.getY());

            currentlyRepainting=false;
        }

        virtual void performAnyPendingRepaintsNow() override
        {
            std::cout << "performAnyPendingRepaintsNow" << std::endl;
        }

        virtual void setAlpha (float newAlpha) override
        {
            std::cout << "setAlpha" << std::endl;
        }

        virtual StringArray getAvailableRenderingEngines() override
        {
            return StringArray();
        }

        ModifierKeys currentModifiers;
};

int EmscriptenComponentPeer::highestZIndex = 10;

extern "C" void juce_mouseCallback(EmscriptenComponentPeer* ptr, const char* type, int x, int y)
{
    //std::clog << ptr << " " << type << " " << x << " " << y << std::endl;
    EmscriptenComponentPeer* peer = (EmscriptenComponentPeer*) (pointer_sized_uint) ptr;

    Point<float> pos = peer->globalToLocal(Point<float>(x, y));
    int64 time = 0;
    ModifierKeys modsToSend = peer->currentModifiers;

    if (type == std::string("down"))
    {
        peer->currentModifiers = peer->currentModifiers.withoutMouseButtons().withFlags (ModifierKeys::leftButtonModifier);
    }
    else if (type == std::string("up"))
    {
        peer->currentModifiers = modsToSend.withoutMouseButtons();
    }
    modsToSend = peer->currentModifiers;

    peer->handleMouseEvent (0, pos, modsToSend, time);

    //peer->handleMouseEvent(0, peer->globalToLocal(Point<float>(x, y)), ModifierKeys(), 0);
    //peer->handleModifierKeysChange();
}

extern "C" void repaintPeer(long ptr)
{
    EmscriptenComponentPeer* peer = (EmscriptenComponentPeer*) (pointer_sized_uint) ptr;
    peer->repaint(peer->getBounds());
}


//==============================================================================
ComponentPeer* Component::createNewPeer (int styleFlags, void*)
{
    return new EmscriptenComponentPeer(*this, styleFlags);
}

//==============================================================================
bool Desktop::canUseSemiTransparentWindows() noexcept
{
    return true;
}

double Desktop::getDefaultMasterScale()
{
    return 1.0;
}

Desktop::DisplayOrientation Desktop::getCurrentOrientation() const
{
    // TODO
    return upright;
}

bool MouseInputSource::SourceList::addSource()
{
    addSource (sources.size(), false);
    return true;
}

Point<float> MouseInputSource::getCurrentRawMousePosition()
{
    //return EmscriptenComponentPeer::lastMousePos;
    return Point<float>();
}

void MouseInputSource::setRawMousePosition (Point<float>)
{
    // not needed
}

//==============================================================================
bool KeyPress::isKeyCurrentlyDown (const int keyCode)
{
    // TODO
    return false;
}

void ModifierKeys::updateCurrentModifiers() noexcept
{
    //currentModifiers = EmscriptenComponentPeer::currentModifiers;
}

ModifierKeys ModifierKeys::getCurrentModifiersRealtime() noexcept
{
    //return EmscriptenComponentPeer::currentModifiers;
    return ModifierKeys();
}

//==============================================================================
// TODO
JUCE_API bool JUCE_CALLTYPE Process::isForegroundProcess() { return true; }
JUCE_API void JUCE_CALLTYPE Process::makeForegroundProcess() {}
JUCE_API void JUCE_CALLTYPE Process::hide() {}

//==============================================================================
void Desktop::setScreenSaverEnabled (const bool isEnabled)
{
    // TODO
}

bool Desktop::isScreenSaverEnabled()
{
    return true;
}

//==============================================================================
void Desktop::setKioskComponent (Component* kioskModeComponent, bool enableOrDisable, bool allowMenusAndBars)
{
    // TODO
}

//==============================================================================
bool juce_areThereAnyAlwaysOnTopWindows()
{
    return false;
}

//==============================================================================
void Desktop::Displays::findDisplays (float masterScale)
{
    Display d;
    d.userArea = d.totalArea = Rectangle<int> (800, 600) / masterScale;
    d.isMain = true;
    d.scale = masterScale;
    d.dpi = 70;//android.dpi;

    displays.add (d);
}





//==============================================================================
Image juce_createIconForFile (const File& file)
{
    return Image::null;
}

//==============================================================================
void* CustomMouseCursorInfo::create() const                                                     { return nullptr; }
void* MouseCursor::createStandardMouseCursor (const MouseCursor::StandardCursorType)            { return nullptr; }
void MouseCursor::deleteMouseCursor (void* const /*cursorHandle*/, const bool /*isStandard*/)   {}

//==============================================================================
void MouseCursor::showInWindow (ComponentPeer*) const   {}
void MouseCursor::showInAllWindows() const  {}

//==============================================================================
bool DragAndDropContainer::performExternalDragDropOfFiles (const StringArray& files, const bool canMove)
{
    return false;
}

bool DragAndDropContainer::performExternalDragDropOfText (const String& text)
{
    return false;
}

//==============================================================================
void LookAndFeel::playAlertSound()
{
}

//==============================================================================
void SystemClipboard::copyTextToClipboard (const String& text)
{
    //const LocalRef<jstring> t (javaString (text));
    //android.activity.callVoidMethod (JuceAppActivity.setClipboardContent, t.get());
}

String SystemClipboard::getTextFromClipboard()
{
    //const LocalRef<jstring> text ((jstring) android.activity.callObjectMethod (JuceAppActivity.getClipboardContent));
    //return juceString (text);
    return String();
}

// TODO: make async
void JUCE_CALLTYPE NativeMessageBox::showMessageBoxAsync (
    AlertWindow::AlertIconType iconType,
    const String &title,
    const String &message,
    Component *associatedComponent,
    ModalComponentManager::Callback *callback)
{
    EM_ASM_ARGS({
        alert( Pointer_stringify($0) );
    }, message.toRawUTF8());

    if(callback != nullptr) callback->modalStateFinished(1);
}

bool JUCE_CALLTYPE NativeMessageBox::showOkCancelBox(
    AlertWindow::AlertIconType iconType,
    const String &title,
    const String &message,
    Component *associatedComponent,
    ModalComponentManager::Callback *callback)
{
    int result = EM_ASM_ARGS({
        return window.confirm( Pointer_stringify($0) );
    }, message.toRawUTF8());
    if(callback != nullptr) callback->modalStateFinished(result?1:0);

    return result?1:0;
}

//==============================================================================
const int extendedKeyModifier       = 0x10000;

const int KeyPress::spaceKey        = ' ';
const int KeyPress::returnKey       = 66;
const int KeyPress::escapeKey       = 4;
const int KeyPress::backspaceKey    = 67;
const int KeyPress::leftKey         = extendedKeyModifier + 1;
const int KeyPress::rightKey        = extendedKeyModifier + 2;
const int KeyPress::upKey           = extendedKeyModifier + 3;
const int KeyPress::downKey         = extendedKeyModifier + 4;
const int KeyPress::pageUpKey       = extendedKeyModifier + 5;
const int KeyPress::pageDownKey     = extendedKeyModifier + 6;
const int KeyPress::endKey          = extendedKeyModifier + 7;
const int KeyPress::homeKey         = extendedKeyModifier + 8;
const int KeyPress::deleteKey       = extendedKeyModifier + 9;
const int KeyPress::insertKey       = -1;
const int KeyPress::tabKey          = 61;
const int KeyPress::F1Key           = extendedKeyModifier + 10;
const int KeyPress::F2Key           = extendedKeyModifier + 11;
const int KeyPress::F3Key           = extendedKeyModifier + 12;
const int KeyPress::F4Key           = extendedKeyModifier + 13;
const int KeyPress::F5Key           = extendedKeyModifier + 14;
const int KeyPress::F6Key           = extendedKeyModifier + 16;
const int KeyPress::F7Key           = extendedKeyModifier + 17;
const int KeyPress::F8Key           = extendedKeyModifier + 18;
const int KeyPress::F9Key           = extendedKeyModifier + 19;
const int KeyPress::F10Key          = extendedKeyModifier + 20;
const int KeyPress::F11Key          = extendedKeyModifier + 21;
const int KeyPress::F12Key          = extendedKeyModifier + 22;
const int KeyPress::F13Key          = extendedKeyModifier + 23;
const int KeyPress::F14Key          = extendedKeyModifier + 24;
const int KeyPress::F15Key          = extendedKeyModifier + 25;
const int KeyPress::F16Key          = extendedKeyModifier + 26;
const int KeyPress::numberPad0      = extendedKeyModifier + 27;
const int KeyPress::numberPad1      = extendedKeyModifier + 28;
const int KeyPress::numberPad2      = extendedKeyModifier + 29;
const int KeyPress::numberPad3      = extendedKeyModifier + 30;
const int KeyPress::numberPad4      = extendedKeyModifier + 31;
const int KeyPress::numberPad5      = extendedKeyModifier + 32;
const int KeyPress::numberPad6      = extendedKeyModifier + 33;
const int KeyPress::numberPad7      = extendedKeyModifier + 34;
const int KeyPress::numberPad8      = extendedKeyModifier + 35;
const int KeyPress::numberPad9      = extendedKeyModifier + 36;
const int KeyPress::numberPadAdd            = extendedKeyModifier + 37;
const int KeyPress::numberPadSubtract       = extendedKeyModifier + 38;
const int KeyPress::numberPadMultiply       = extendedKeyModifier + 39;
const int KeyPress::numberPadDivide         = extendedKeyModifier + 40;
const int KeyPress::numberPadSeparator      = extendedKeyModifier + 41;
const int KeyPress::numberPadDecimalPoint   = extendedKeyModifier + 42;
const int KeyPress::numberPadEquals         = extendedKeyModifier + 43;
const int KeyPress::numberPadDelete         = extendedKeyModifier + 44;
const int KeyPress::playKey         = extendedKeyModifier + 45;
const int KeyPress::stopKey         = extendedKeyModifier + 46;
const int KeyPress::fastForwardKey  = extendedKeyModifier + 47;
const int KeyPress::rewindKey       = extendedKeyModifier + 48;
