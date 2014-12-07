# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif



  CPPFLAGS := $(DEPFLAGS) -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../modules -I ../../compat -I /usr/X11R6/include/
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O0 -DJUCE_USE_FREETYPE=1 -DJUCE_USE_FREETYPE_AMALGAMATED=1 -DFT_DEBUG_LEVEL_TRACE=1 -D_NL_IDENTIFICATION_LANGUAGE=0 -D_NL_IDENTIFICATION_TERRITORY=0
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += -s TOTAL_MEMORY=536870912 --preload-file usr/X11R6/lib/X11/fonts/Lato-Regular.ttf --preload-file usr/X11R6/lib/X11/fonts/Lato-Bold.ttf -s EXPORTED_FUNCTIONS="['_main', '_deliverMessage', '_repaintPeer', '_doThreadIteration', '_juce_mouseCallback']" -s NO_EXIT_RUNTIME=1 $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../modules -I ../../compat -I /usr/X11R6/include/
  TARGET := index.html
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../modules -I ../../compat -I /usr/X11R6/include/
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O3 -DJUCE_USE_FREETYPE=1 -DJUCE_USE_FREETYPE_AMALGAMATED=1 -DFT_DEBUG_LEVEL_TRACE=1 -D_NL_IDENTIFICATION_LANGUAGE=0 -D_NL_IDENTIFICATION_TERRITORY=0
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += -O3 -s TOTAL_MEMORY=536870912 --preload-file usr/X11R6/lib/X11/fonts/Lato-Regular.ttf --preload-file usr/X11R6/lib/X11/fonts/Lato-Bold.ttf -s EXPORTED_FUNCTIONS="['_main', '_deliverMessage', '_repaintPeer', '_doThreadIteration', '_juce_mouseCallback']" -s NO_EXIT_RUNTIME=1 $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../modules -I ../../compat -I /usr/X11R6/include/
  TARGET := index.html
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/MainContentComponent_52535d99.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/juce_core_1ee54a40.o \
  $(OBJDIR)/juce_cryptography_3b1f489a.o \
  $(OBJDIR)/juce_data_structures_84790dfc.o \
  $(OBJDIR)/juce_events_584896b4.o \
  $(OBJDIR)/juce_graphics_f9afc18.o \
  $(OBJDIR)/juce_gui_basics_90929794.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking juce_emscripten
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning juce_emscripten
	@$(CLEANCMD)

strip:
	@echo Stripping juce_emscripten
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/MainContentComponent_52535d99.o: ../../Source/UI/MainContentComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainContentComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_1ee54a40.o: ../../../../modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_3b1f489a.o: ../../../../modules/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_84790dfc.o: ../../../../modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_584896b4.o: ../../../../modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_f9afc18.o: ../../../../modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_90929794.o: ../../../../modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
