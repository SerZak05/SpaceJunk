#include "game.h"
#include <chrono>

Game* Game::inst = nullptr;

Game* Game::getInst() {
	if (inst == nullptr) {
		inst = new Game();
	}
	return inst;
}

void Game::cleanup() {
	delete inst;
}

bool Game::init() {
	currField = new Field();
	return currField->init();
}

void Game::loop() {
	static auto lastLoop = std::chrono::steady_clock::now();
	auto currLoop = std::chrono::steady_clock::now();
	std::chrono::duration<float> delta = currLoop - lastLoop;
	currField->loop(delta.count());
	lastLoop = currLoop;
}

void Game::draw(Drawer* const d) const {
	currField->draw(d);
}

Game::~Game() {
	delete currField;
}

Game::Game() : currField(nullptr) {}
