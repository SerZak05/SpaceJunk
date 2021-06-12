#pragma once
#include <string>

#include "appcontroller.h"
#include "field.h"

class Game {
public:
	static Game* getInst();
	static void cleanup();
	bool init();
	void loop();
	void draw(Drawer* const) const;

	static Field* createField(std::string name);
	static void saveField(std::string name, Field* f);
private:
	Game();
	~Game();
	Field* currField;

	static Game* inst;
};