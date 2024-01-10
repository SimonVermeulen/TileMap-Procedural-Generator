#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Texture.hpp"

class Graphic {
    private:
        int _width;
        int _height;
        SDL_Window *_window = NULL;
        SDL_Renderer *_renderer = NULL;
        SDL_Surface *_windowSurface = NULL;
        TTF_Font *_font;
        std::vector<Texture *> _textures;
    public:
        Graphic(int width, int height);
        ~Graphic();
        void loop();
        void loadFont(std::string path);
        void pushTexture(Texture *texture);
        void clearTexture();
        SDL_Renderer *getRenderer();
        TTF_Font *getFont();
        std::vector<Texture *> &getTextures();
};