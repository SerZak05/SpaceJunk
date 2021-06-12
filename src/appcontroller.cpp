#include "appcontroller.h"
#include "common.h"
#include "merrors.h"
#include "event.h"
#include "actionmanager.h"
#include "game.h"

AppController* AppController::inst = nullptr;

AppController::AppController() {}
AppController::~AppController() {
	ui.cleanup();
	Game::cleanup();
	Drawer::cleanup();
}

bool AppController::init() {
	mErr::oerr() << "I`m working." << std::endl;
	bool success = true;
	
	mErr::maccept(ui.init(), "Failed to init UI!", success);
	mErr::maccept(Game::getInst()->init(), "Failed to init Game!", success);
	//mErr::maccept(mDrawer.loadTexture("circle.png"), "Failed to load image!", success);

	ui.eventLoop.subscribe(this);
	return success;
}

AppController* AppController::getInst() {
	if (inst == nullptr) {
		inst = new AppController();
		if (!inst->init()) {
			mErr::oerr() << "Failed to initialize app controller!" << std::endl;
			inst = nullptr;
		}
	}
	return inst;
}

void AppController::run() {
	Running = true;
	while (Running) {
		ui.update();
		ActionManager::getInst()->loop();
		Game::getInst()->loop();
		Game::getInst()->draw(Drawer::getInst());
		//mGame.update();
		//mGame.draw(&mDrawer);
		//mDrawer.drawTexture(std::string("circle.png"), 10, 10);
		Drawer::getInst()->render();
		//mErr::oerr() << "====LOOP====" << std::endl;
	}
}

void AppController::stop() {
	Running = false;
}

void AppController::cleanup() {
	delete inst;
}

void AppController::processEvent(const Event*) {
	stop();
}

std::list<EventType> AppController::acceptTypes() const {
	return { EXIT_EVENT };
}
