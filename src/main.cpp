#include "World.hpp"
#include "Graphic.hpp"
#include "Texture.hpp"

bool isPointInVector(std::vector<Vector2I>& vec, Vector2I& point) {
    for (Vector2I& v : vec) {
        if (v.getX() == point.getX() && v.getY() == point.getY())
            return true;
    }
    return false;
}

int main(int ac, char **av) {
    std::cout << "qsdf" << std::endl;
    World world = World(20, 20, 6);
    Graphic view = Graphic(20 * 40, 20 * 40);
    Texture *texture = NULL;
    SDL_Color black = {.r = (Uint8)255, .g = (Uint8)255, .b = (Uint8)255};
    SDL_Color green = {.r = (Uint8)0, .g = (Uint8)255, .b = (Uint8)0};

    view.loadFont("./assets/fonts/OpenSans-Regular.ttf");




    world.generate();
    std::vector<Vector2I> lowestEntropies = world.getLowestEntropies();
    for (int y = 0; y < world.getSize().getY(); y++) {
        for (int x = 0; x < world.getSize().getX(); x++) {
            Vector2I coords = world.getTiles()[y][x]->getCoords();
            texture = new Texture(view.getRenderer());
            texture->setFont(view.getFont());
            if (isPointInVector(lowestEntropies, coords)) {
                texture->loadFromRenderedText(std::to_string(world.getTiles()[y][x]->_entropy), green);
            } else {
                texture->loadFromRenderedText(std::to_string(world.getTiles()[y][x]->_entropy), black);
            }
            texture->setCoords({x * 40, y * 40});
            view.pushTexture(texture);
        }
    }




    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(view.getRenderer(), 0x0, 0x0, 0x0, 0x00);
        SDL_RenderClear(view.getRenderer());
        world.generate();
        std::vector<Vector2I> lowestEntropies = world.getLowestEntropies();
        int i = 0;
        std::string type;
        for (int y = 0; y < world.getSize().getY(); y++) {
            for (int x = 0; x < world.getSize().getX(); x++, i++) {
                texture = view.getTextures()[i];
                type = world.getTiles()[y][x]->getType();
                if (type != "") {
                    texture->loadFromFile("./assets/img/" + type + ".PNG");
                } else {
                    Vector2I coords = world.getTiles()[y][x]->getCoords();
                    if (isPointInVector(lowestEntropies, coords)) {
                        texture->loadFromRenderedText(std::to_string(world.getTiles()[y][x]->_entropy), green);
                    } else {
                        texture->loadFromRenderedText(std::to_string(world.getTiles()[y][x]->_entropy), black);
                    }
                }
            }
        }
        for (Texture *texture : view.getTextures()) {
            texture->render(10, 10);
        }

        SDL_RenderPresent(view.getRenderer());
        SDL_Delay(100);
    }
    for (int y = 0; y < world.getSize().getY(); y++) {
        for (int x = 0; x < world.getSize().getX(); x++) {
            std::cout << world.getTiles()[y][x]->getType() << " ";
        }
        std::cout << std::endl;
    }
}
