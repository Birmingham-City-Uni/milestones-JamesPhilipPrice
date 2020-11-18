#include "TextRenderer.h"

TextRenderer::TextRenderer(SDL_Renderer* _renderer, string _ttfFileLocation, int _fontSize)
{
	if (TTF_Init() < 0) {
		printf("TTF could not be initialized, SDL error: ", SDL_GetError());
	}

	font = TTF_OpenFont(_ttfFileLocation.c_str(), _fontSize);
	if (font == NULL) {
		printf("Unable to load font %s due to SDL error: %s\n", _ttfFileLocation, SDL_GetError());
	}
	renderer = _renderer;
}

TextRenderer::~TextRenderer()
{
	SDL_FreeSurface(textSurface);
}

void TextRenderer::RenderString(string _text, int _x, int _y)
{
	SDL_Color textColor = { 255, 255, 255 };
	textSurface = TTF_RenderText_Solid(font, _text.c_str(), textColor);
	SDL_Rect src = { 0, 0, textSurface->w, textSurface->h };
	SDL_Rect dest = { _x, _y, textSurface->w, textSurface->h };

	texture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
	SDL_RenderCopy(renderer, texture, &src, &dest);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);
}
