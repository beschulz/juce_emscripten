# PoC port of JUCE for the browser via emscripten

[Demo](http://beschulz.github.io/juce_emscripten/)

## What is working
- basic GUI
- basic mouse interaction
- Font-Rendering

## What is not working
- keyboard input (simple to fix)
- audio (I'd go for an OpenAL Audio device implementation in C++, because emscripten supports OpenAL)
- threading (This one's a real problem)

## Hacking

- (Download Emscripten)[http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html]
- install Emscripten ´´´# Fetch the latest registry of available tools.
./emsdk update

# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active"
./emsdk activate latest

# Set the current Emscripten path on Linux/Mac OS X
source ./emsdk_env.sh
´´´
- compile the sample ´´´cd examples/juce_emscripten/Builds/Linux/
CXX=em++ make CONFIG=Debug
cd build
python -m SimpleHTTPServer
´´´
- [watch it](http://127.0.0.1:8000)
