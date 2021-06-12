#include "appcontroller.h"
#include "merrors.h"
#include "actionmanager.h"
#include "vector.h"

int main(int argc, char* args[]) {
	mErr::errors_init();
	
	AppController* app = AppController::getInst();
	if (app == 0) {
		return 0;
	}
	ActionManager::getInst();
	/*ActionManager::getInst()->readConfig({{ "up", KeyboardEvent {SDL_KEYDOWN, 0, 0,  }
		})*/
	// async
	//app->init();
	app->run();
	AppController::cleanup();
	mErr::errors_quit();
	return 0;
}