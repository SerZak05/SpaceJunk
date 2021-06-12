#pragma once
#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>
#include "vector.h"
#include "actionmanager.h"

//#include "../cairo-1.16.0/src/cairo.h"

typedef std::pair<Geom::Vector, Geom::Vector> Rect;

class Drawer {
public:
	static Drawer* getInst();

	const int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;

	bool loadMedia();

	bool setColor(int r, int g, int b, int a = 255);
	bool drawPoint(Geom::Vector);
	bool drawPoint(float x, float y);
	bool drawLine(float x1, float y1, float x2, float y2);
	bool drawLine(const Geom::Vector&, const Geom::Vector&);
	bool drawLines(const std::vector<Geom::Vector>&);
	bool drawRect(const Geom::Vector& leftUpperCorner, const Geom::Vector& rightLowerCorner);
	bool drawRect(const Rect&);
	bool drawEllipse(const Geom::Vector&, const Geom::Vector&);
	bool drawEllipse(const Rect&);

	bool loadTexture(const std::string& path);
	bool drawTexture(const std::string& name, double x, double y);
	//bool drawTexture(const std::string& name, SDL_Rect* textureRect, SDL_Rect* renderRect);

	void render();

	static void cleanup();
private:
	Drawer();
	static Drawer* inst;

	std::string mediaFolder = "assets/";

	sf::RenderWindow mWindow;
	std::map<std::string, sf::Texture> mTextures;

	sf::Color mColor, bg;

	friend void ActionManager::loop();
};