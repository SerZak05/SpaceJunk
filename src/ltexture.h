#pragma once
#include <SDL.h>
#include <string>

class LTexture {
public:
	LTexture();

	~LTexture();

	bool loadFromFile(std::string path, SDL_Renderer* r);

	void free();

	void render(SDL_Renderer*, int x, int y);
	void render(SDL_Renderer*, const SDL_Rect* textureRect, const SDL_Rect* renderRect);

	int getWidth() const;
	int getHeight() const;
private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};