OBJS = main.cpp Game.cpp TextureManager.cpp SDLGameObject.cpp InputHandler.cpp GameStateMachine.cpp MainMenuState.cpp PlayState.cpp PauseState.cpp MenuButton.cpp Player.cpp Enemy.cpp GameObjectFactory.cpp StateParser.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp tinystr.cpp TiledMapParser.cpp Camera.cpp World.cpp Bullet.cpp AnimatedGraphic.cpp AnimationManager.cpp Helicopter.cpp EnemyManager.cpp LevelCompleteState.cpp LevelParser.cpp GameOverState.cpp AudioManager.cpp

# OBJS = test.cpp

CC = cl

INCLUDE_PATHS = -IC:/SDL2/include

# Library options for gcc
# LIBRARY_PATHS = -LC:/SDL2/lib

# Library options for cl
LIBRARY_PATHS = /link /LIBPATH:C:/SDL2/lib/x86

# Compiler flags for console window, cl
COMPILER_FLAGS = /SUBSYSTEM:CONSOLE

# Compiler flags for console window, gcc
# COMPILER_FLAGS = -w -Wl,-subsystem,windows

# Library options for gcc
# LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2_image -lSDL2 -lSDL2_mixer

# Library options for cl
LINKER_FLAGS = SDL2main.lib SDL2.lib SDL2_image.lib SDL2_mixer.lib

TARGET = build/HeliAttack.exe

all : $(OBJS)
	$(CC) -Zi $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -out:$(TARGET)
