#pragma once
#include<SDL_ttf.h>
#include<string>

using namespace std;

class TextRenderer {
public:
	TextRenderer(SDL_Renderer* _renderer, string _ttfFileLocation, int _fontSize);
	virtual ~TextRenderer();

	void RenderString(string _text, int _x, int _y);

private:
	SDL_Surface* textSurface;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	TTF_Font* font;
};