# PoC port of JUCE for the browser via emscripten

[Demo](http://beschulz.github.io/juce_emscripten/)

## What is working
- basic GUI
- basic mouse interaction
- Font-Rendering (via freetype)

## What is not working
- keyboard input (simple to fix)
- audio (I'd go for an OpenALAudioDevice implementation in C++, because emscripten apparently supports OpenAL (via the AudioAPI) )
- threading (This one's a real problem)

## Hacking

- [Download Emscripten](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
- install Emscripten
```shell
# Fetch the latest registry of available tools.
./emsdk update

# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active"
./emsdk activate latest

# Set the current Emscripten path on Linux/Mac OS X
source ./emsdk_env.sh
```

- compile the sample
```shell
cd examples/juce_emscripten/Builds/Linux/
CXX=em++ make CONFIG=Debug
cd build
python -m SimpleHTTPServer
```
- [have a play](http://127.0.0.1:8000)

## Thoughts

I just slapped this together to see, if it's possible. So don't expect your fancy JUCE Applications to Just Work (tm). There's still a lot of work to be done.

One of the hardest problems is threading. There are WebWorkers, but they use an entirely different model (no shared memory with main thread).

Networking is another interesting problem. Maybe one could adapt the Juce networking API to use WebSockets.

The URL-class also needs adoption to work inside the browser.

Audio should be possible via the WebAudioAPI or emscriptens OpenAL wrapper.

OpenGL should be doable.

Currently I am using LowLevelGraphicsSoftwareRenderer to do the rendering. But the API of LowLevelGraphicsContext looks suspiciously like the canvas API. There might be some performance to be gained by implementing LowLevelGraphicsCanvasRenderer.

It would be nice to have support for @font-face fonts.

It would be great to have a working implementation of WebBrowserComponent - just for the Inception-like effect :) 

Overall I was surprised, how nicely everything worked out. I see a lot of practical applications for JUCE supporting emscripten as a platform:
  - rich audio applications in the browser
  - node.js license-key validation (if you're using juce_cryptography)
  - bringing your existing applications to the web

