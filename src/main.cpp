#include "engine.hpp"

int main(int argc, char **argv) {
    srand (time(NULL));
    
    // Initialize the random manager
    libpmg::RndManager::seed_ = rand();
    
    // Engine initialization
    Engine eng;
    eng.InitializeStartScreen();
    
    // Game loop
    while ( !TCODConsole::isWindowClosed() ) {
        eng.RenderStartScreen();
        eng.UpdateStartScreen();

        while (eng.IsPlaying()) {
            eng.Render();
            eng.Update();
        }

    }

    return 0;
}
