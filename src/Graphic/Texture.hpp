#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Vector2I.hpp"

class Texture {
    private:
        SDL_Renderer *_renderer;
        SDL_Texture *_texture;
        TTF_Font *_font;
        int _width;
        int _height;
        int _x;
        int _y;
    public:
        Texture(SDL_Renderer *renderer);
        ~Texture();
        bool loadFromFile(std::string path);
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
		void free();
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void setBlendMode(SDL_BlendMode blending);
		void setAlpha(Uint8 alpha);
        void setFont(TTF_Font *font);
        void setCoords(Vector2I coords);
		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
};