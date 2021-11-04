OBJS = main.cpp Game.cpp TextureManager.cpp SDLGameObject.cpp InputHandler.cpp GameStateMachine.cpp MainMenuState.cpp PlayState.cpp PauseState.cpp MenuButton.cpp Player.cpp Enemy.cpp GameObjectFactory.cpp StateParser.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp tinystr.cpp TiledMapParser.cpp Camera.cpp World.cpp Bullet.cpp AnimatedGraphic.cpp AnimationManager.cpp Helicopter.cpp EnemyManager.cpp LevelCompleteState.cpp LevelParser.cpp GameOverState.cpp AudioManager.cpp

CC = cl

INCLUDE_PATHS = -IZ:\SDL2_VC\include

# Library options for gcc
# LIBRARY_PATHS = -LZ:\SDL_32\lib  

# Library options for cl
LIBRARY_PATHS = /link /LIBPATH:Z:\SDL2_VC\lib\x64


COMPILER_FLAGS = /SUBSYSTEM:CONSOLE

# Library options for gcc
# LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# Library options for cl
LINKER_FLAGS = SDL2main.lib SDL2.lib SDL2_image.lib SDL2_mixer.lib

# TARGET = -o SDLMain

all : $(OBJS)
	$(CC) -Zi $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) 
