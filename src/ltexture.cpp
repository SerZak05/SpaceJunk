#include "ltexture.h"

#include <SDL_image.h>
#include <iostream>
#include "merrors.h"

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* r) {
	free();
	bool success = true;

	SDL_Surface* loadedSurf = IMG_Load(path.c_str());
	if (loadedSurf == NULL) {
		mErr::oerr() << "Failed to load surface \"" << path << "\". Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else {
		SDL_SetColorKey(loadedSurf, SDL_TRUE, SDL_MapRGB(loadedSurf->format, 0, 0xFF, 0xFF));
		mTexture = SDL_CreateTextureFromSurface(r, loadedSurf);
		if (mTexture == NULL) {
			mErr::oerr() << "Failed to create texture from \"" << path << "\". Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else {
			mWidth = loadedSurf->w;
			mHeight = loadedSurf->h;
		}

		SDL_FreeSurface(loadedSurf);
	}

	return success;
}

void LTexture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(SDL_Renderer* r, int x, int y) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(r, mTexture, NULL, &renderQuad);
}
void LTexture::render(SDL_Renderer* r, const SDL_Rect* renderRect, const SDL_Rect* textureRect) {
	SDL_RenderCopy(r, mTexture, textureRect, renderRect);
}

int LTexture::getWidth() const {
	return mWidth;
}

int LTexture::getHeight() const {
	return mHeight;
}