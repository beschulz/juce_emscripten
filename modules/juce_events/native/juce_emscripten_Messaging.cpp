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

}

#include <emscripten.h>

namespace juce
{

void MessageManager::doPlatformSpecificInitialisation() {}
void MessageManager::doPlatformSpecificShutdown() {}

//==============================================================================
bool MessageManager::dispatchNextMessageOnSystemQueue (const bool returnIfNoPendingMessages)
{
    Logger::outputDebugString ("*** Modal loops are not possible in Android!! Exiting...");
    exit (1);

    return true;
}


extern "C" void deliverMessage(long value)
{
  using namespace juce;
  std::cout << "deliverMessage: " << value << std::endl;
  JUCE_TRY
  {
    MessageManager::MessageBase* const message = (MessageManager::MessageBase*) (pointer_sized_uint) value;
    std::cout << "deliverMessage-msg: " << message << "type: " << typeid(*message).name() << std::endl;
    message->messageCallback();
    message->decReferenceCount();
  }
  JUCE_CATCH_EXCEPTION
}

//==============================================================================
bool MessageManager::postMessageToSystemQueue (MessageManager::MessageBase* const message)
{
    std::cout << "MessageManager::postMessageToSystemQueue" << std::endl;

    EM_ASM({
      if( !window.messageHandlerInstalled ){
        window.messageHandlerInstalled = true;

        var deliverMessage = Module.cwrap('deliverMessage', 'void', ['number']);

        var receiveMessage = function(event)
        {
          console.log('receiveMessage', event, typeof(event.data));
          deliverMessage(event.data);
        };

        window.addEventListener('message', receiveMessage, false);
      }
    });

    message->incReferenceCount();

    EM_ASM_ARGS({
      console.log('window.postMessage', $0);
      window.postMessage($0, '*');
    }, message);

    //android.activity.callVoidMethod (JuceAppActivity.postMessage, (jlong) (pointer_sized_uint) message);
    return true;
}

/*JUCE_JNI_CALLBACK (JUCE_ANDROID_ACTIVITY_CLASSNAME, deliverMessage, void, (JNIEnv* env, jobject activity, jlong value))
{
    JUCE_TRY
    {
        MessageManager::MessageBase* const message = (MessageManager::MessageBase*) (pointer_sized_uint) value;
        message->messageCallback();
        message->decReferenceCount();
    }
    JUCE_CATCH_EXCEPTION
}*/

//==============================================================================
void MessageManager::broadcastMessage (const String&)
{
}

void MessageManager::runDispatchLoop()
{
  //emscripten_set_main_loop(oneIteration, 60, 1);
}

void MessageManager::stopDispatchLoop()
{
    struct QuitCallback  : public CallbackMessage
    {
        QuitCallback() {}

        void messageCallback() override
        {
            //android.activity.callVoidMethod (JuceAppActivity.finish);
        }
    };

    (new QuitCallback())->post();
    quitMessagePosted = true;
}
