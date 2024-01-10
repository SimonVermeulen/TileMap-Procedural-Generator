#include <iostream>
#include "Graphic.hpp"

Graphic::Graphic(int width, int height) {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not init SDL" << std::endl;
        exit(84);
    }
    if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )) {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }
    this->_window = SDL_CreateWindow(
        "MAP GENERATOR",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    if (this->_window == NULL) {
        std::cerr << "Could not create window" << std::endl;
        exit(84);
    }
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    if (this->_renderer == NULL) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(84);
    }
    SDL_SetRenderDrawColor(this->_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init( imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        exit(84);
    }
    if( TTF_Init() == -1 ) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(84);
    }
    this->_windowSurface = SDL_GetWindowSurface(this->_window);
    this->_width = width;
    this->_height = height;
}

Graphic::~Graphic() {
	TTF_CloseFont(this->_font);
	this->_font = NULL;
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyWindow(this->_window);
	this->_window = NULL;
	this->_renderer = NULL;
    for (const Texture *texture : this->_textures) {
        texture->~Texture();
    }
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Graphic::loop() {
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(this->_renderer, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(this->_renderer);
        for (Texture *texture : this->_textures) {
            texture->render(10, 10);
        }
        SDL_RenderPresent(this->_renderer);
    }
}

void Graphic::loadFont(std::string path) {
    this->_font = TTF_OpenFont(path.c_str(), 28);
    if (this->_font == NULL) {
		std::cerr << "Failed to load " << path.c_str() << "! SDL_ttf Error: " << TTF_GetError();
        exit(84);
    }
}

void Graphic::clearTexture() {
    for (Texture *texture : this->_textures) {
        texture->free();
    }
    this->_textures.clear();
}

void Graphic::pushTexture(Texture *texture) {
    this->_textures.push_back(texture);
}

SDL_Renderer *Graphic::getRenderer() {
    return this->_renderer;
}

TTF_Font *Graphic::getFont() {
    return this->_font;
}

std::vector<Texture *> &Graphic::getTextures() {
    return this->_textures;
}