#include "drawer.h"

#include <iostream>
#include "merrors.h"

Drawer::Drawer() : mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SpaceJunk")
{
	mediaFolder = "../SpaceJunk/assets/";
	bg.r = bg.g = bg.b = 0;
}

Drawer* Drawer::inst = nullptr;
Drawer* Drawer::getInst() {
	if (inst == nullptr) {
		inst = new Drawer();
	}
	return inst;
}

void Drawer::cleanup() {
	delete inst;
}

bool Drawer::loadMedia() {
	bool success = true;

	return success;
}

bool Drawer::loadTexture(const std::string& name) {
	bool success = true;
	if (mTextures.find(name) == mTextures.end()) {
		sf::Texture newTexture;
		if (!newTexture.loadFromFile(mediaFolder + name)) {
			// errors.add(...)
			mErr::oerr() << "Failed to load texture: " << name << std::endl;
			success = false; //= errors.isNotEmpty()
		}
		else {
			mTextures[name] = newTexture;
		}
	}
	return success;
}

bool Drawer::loadImage(const std::string& name) {
	bool success = true;
	if (mTextures.find(name) == mTextures.end()) {
		sf::Image newImage;
		if (!newImage.loadFromFile(mediaFolder + name)) {
			// errors.add(...)
			mErr::oerr() << "Failed to load image: " << name << std::endl;
			success = false; //= errors.isNotEmpty()
		}
		else {
			mImages[name] = newImage;
		}
	}
	return success;
}

bool Drawer::setColor(int r, int g, int b, int a) {
	mColor = sf::Color(r, g, b, a);
	return true;
}

bool Drawer::drawPoint(Geom::Vector v) {
	return drawPoint(v.x, v.y);
}

bool Drawer::drawPoint(float x, float y) {
	sf::RectangleShape point(sf::Vector2f(1, 1));
	point.setFillColor(mColor);
	point.setPosition(x, y);
	mWindow.draw(point);
	return true;
}

bool Drawer::drawLine(float x1, float y1, float x2, float y2) {
	sf::Vertex lines[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1)),
		sf::Vertex(sf::Vector2f(x2, y2))

	};
	mWindow.draw(lines, 2, sf::Lines);
	return true;
}

bool Drawer::drawLine(const Geom::Vector& a, const Geom::Vector& b) {
	return drawLine(a.x, a.y, b.x, b.y);
}

/*bool Drawer::drawLines(const std::vector<Geom::Vector>& v) {
	bool success = true;
	SDL_Point* a = new SDL_Point[v.size()];
	for (int i = 0; i < v.size(); ++i) {
		a[i].x = v[i].x;
		a[i].y = v[i].y;
	}
	success = SDL_RenderDrawLines(mRenderer, a, v.size());
	delete[] a;
	return success;
}*/

bool Drawer::drawRect(const Geom::Vector& a, const Geom::Vector& b) {
	sf::RectangleShape rect(sf::Vector2f(b.x - a.x, b.y - a.y));
	rect.setPosition(a.x, a.y);
	rect.setFillColor(mColor);
	mWindow.draw(rect);
	return true;
}

bool Drawer::drawRect(const Rect& rect) {
	return drawRect(rect.first, rect.second);
}

bool Drawer::drawEllipse(const Geom::Vector& a, const Geom::Vector& b) {
	using namespace Geom;
	Vector center = (a + b) * 0.5;
	return true;
}

/*bool Drawer::drawTexture(const std::string& name, double x, double y) {
	bool success = true;
	if (mTextures.find(name) == mTextures.end()) {
		//errors.add(...)
		mErr::oerr() << "Did not find texture: " << name << std::endl;
	}
	else {
		sf::Sprite sprite;
		sprite.setTexture(mTextures[name]);
		sprite.setPosition(x, y);
		mWindow.draw(sprite);
	}
	return success;
}*/

void Drawer::drawSprite(const sf::Sprite& sp) {
	mWindow.draw(sp);
}

const sf::Texture* Drawer::getTexture(const std::string& name) {
	if (mTextures.find(name) == mTextures.end()) {
		mErr::oerr() << "Did not find texture: " << name << std::endl;
		return nullptr;
	}
	return &(mTextures[name]);
}

sf::Image Drawer::getImage(const std::string& name) {
	if (mImages.find(name) == mImages.end()) {
		mErr::oerr() << "Did not find image: " << name << std::endl;
		return sf::Image();
	}
	return mImages[name];
}

void Drawer::render() {
	mWindow.display();
	mWindow.clear(bg);
}
