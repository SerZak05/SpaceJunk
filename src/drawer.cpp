#include "drawer.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "merrors.h"

bool Drawer::init()
{
	bool success = true;
	// list string , list task errors
	if (!mErr::maccept(!SDL_Init(SDL_INIT_EVERYTHING), "Failed to init SDL!", success)) {
		mErr::oerr() << SDL_GetError() << std::endl;
	}
	else {
		if (!mErr::maccept(IMG_Init(IMG_INIT_PNG), "Failed to init IMG!", success)) {
			mErr::oerr() << IMG_GetError() << std::endl;
		}
		if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_SHOWN, &mWindow, &mRenderer) == -1) {
			mErr::oerr() << "Failed to create window and render! Error: " << SDL_GetError() << std::endl;
			success = false;
		}
	}
	bg.a = 255;
	return success;
}

bool Drawer::loadMedia() {
	bool success = true;

	return success;
}

bool Drawer::loadTexture(const std::string& name) {
	bool success = true;
	if (mTextures.find(name) == mTextures.end()) {
		LTexture* newTexture = new LTexture();
		if (!newTexture->loadFromFile(mediaFolder + name, mRenderer)) {
			// errors.add(...)
			mErr::oerr() << "Failed to load image: " << name << std::endl;
			success = false; //= errors.isNotEmpty()
		}
		else {
			mTextures[name] = newTexture;
		}
	}
	return success;
}

bool Drawer::setColor(int r, int g, int b, int a) {
	return SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
}

bool Drawer::drawPoint(Geom::Vector v) {
	return drawPoint(v.x, v.y);
}

bool Drawer::drawPoint(int x, int y) {
	return SDL_RenderDrawPoint(mRenderer, x, y);
}

bool Drawer::drawLine(int x1, int y1, int x2, int y2) {
	return SDL_RenderDrawLine(mRenderer, x1, y1, x2, y2);
}

bool Drawer::drawLine(const Geom::Vector& a, const Geom::Vector& b) {
	return drawLine(a.x, a.y, b.x, b.y);
}

bool Drawer::drawLines(const std::vector<Geom::Vector>& v) {
	bool success = true;
	SDL_Point* a = new SDL_Point[v.size()];
	for (int i = 0; i < v.size(); ++i) {
		a[i].x = v[i].x;
		a[i].y = v[i].y;
	}
	success = SDL_RenderDrawLines(mRenderer, a, v.size());
	delete[] a;
	return success;
}

bool Drawer::drawRect(const Geom::Vector& a, const Geom::Vector& b) {
	SDL_Rect rect;
	rect.x = a.x;
	rect.y = a.y;
	rect.w = b.x - a.x;
	rect.h = b.y - a.y;
	return drawRect(&rect);
}

bool Drawer::drawRect(const SDL_Rect* rect) {
	return SDL_RenderDrawRect(mRenderer, rect);
}

bool Drawer::drawRect(const Rect& rect) {
	return drawRect(rect.first, rect.second);
}

bool Drawer::drawEllipse(const Geom::Vector& a, const Geom::Vector& b) {
	using namespace Geom;
	Vector center = (a + b) * 0.5;
	return true;
}

bool Drawer::drawTexture(const std::string& name, double x, double y) {
	bool success = true;
	if (mTextures.find(name) == mTextures.end()) {
		//errors.add(...)
		mErr::oerr() << "Did not find texture: " << name << std::endl;
	}
	else {
		mTextures[name]->render(mRenderer, int(x), int(y));
	}
	return success;
}

void Drawer::render() {
	SDL_RenderPresent(mRenderer);
	SDL_SetRenderDrawColor(mRenderer, bg.r, bg.g, bg.b, bg.a);
	SDL_RenderClear(mRenderer);
}

void Drawer::cleanup() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	IMG_Quit();
	SDL_Quit();
}
