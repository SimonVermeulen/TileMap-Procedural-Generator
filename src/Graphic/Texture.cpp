#include "Texture.hpp"

Texture::Texture(SDL_Renderer *renderer) {
    this->_renderer = renderer;
    this->_texture = NULL;
    this->_width = 0;
    this->_height = 0;
}

Texture::~Texture() {
    this->free();
}

bool Texture::loadFromFile(std::string path) {
    this->free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL ) {
		std::cerr << "Unable to load image" << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
	} else {
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(this->_renderer, loadedSurface);
		if (newTexture == NULL) {
			std::cerr << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
		} else {
			this->_width = loadedSurface->w;
			this->_height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
    this->_texture = newTexture;
	return this->_texture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor) {
	this->free();
    if (this->_font) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(this->_font, textureText.c_str(), textColor);
        if (textSurface == NULL) {
            std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError();
        } else {
            this->_texture = SDL_CreateTextureFromSurface(this->_renderer, textSurface);
            if (this->_texture == NULL) {
                std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError();
            } else {
                this->_width = textSurface->w;
                this->_height = textSurface->h;
            }
            SDL_FreeSurface(textSurface);
        }
    }
	return this->_texture != NULL;
}

void Texture::free() {
	if (this->_texture != NULL) {
		SDL_DestroyTexture(this->_texture);
		this->_texture = NULL;
		this->_width = 0;
		this->_height = 0;
	}
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(this->_texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(this->_texture, blending);
}

void Texture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(this->_texture, alpha);
}

void Texture::setFont(TTF_Font *font) {
    this->_font = font;
}

void Texture::setCoords(Vector2I coords) {
    this->_x = coords.getX();
    this->_y = coords.getY();
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = {this->_x, this->_y, this->_width, this->_height};

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(this->_renderer, this->_texture, clip, &renderQuad, angle, center, flip);
}
