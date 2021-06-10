/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** sfml
*/

#ifndef SFMLINTERFACE_HPP_
#define SFMLINTERFACE_HPP_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <GObject.hpp>
#include <TObject.hpp>

enum ressources_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    PLAYER,
    RESSOURCES_COUNT // DO NOT MOVE: SHOULD BE LAST
};

const std::vector<std::string> RES_SPRITES =
{
    "res/food.png",
    "res/linemate.png",
    "res/deraumere.png",
    "res/sibur.png",
    "res/mendiane.png",
    "res/phiras.png",
    "res/thystame.png",
    "res/player.png"
};

struct player_s {
     int ressources[RESSOURCES_COUNT];
};
struct case_s {
    struct player_s *players;
    int ressources[RESSOURCES_COUNT];
};

class Frame {
public:
    Frame(int x, int y) {
        std::string number("0");
        std::string fontpath("res/font.otf");

        _frame = new GObject("res/frame.png", sf::Vector2f(x * 256, y * 256), sf::IntRect(0, 0, 256, 256), 0);
        for (int i = 0; i != RESSOURCES_COUNT; i++) {
            _qty.push_back(new TObject(number, fontpath,
                                       sf::Vector2f(x * 256 + 256 / 4 * (i % 4) + 20, y * 256 + 256 / 2 * (i / 4) + 85), 30));
            _obj.push_back(new GObject(RES_SPRITES[i],
                                       sf::Vector2f(x * 256 + 256 / 4 * (i % 4) + 10, y * 256 + 256 / 2 * (i / 4) + 20), sf::IntRect(0, 0, 48, 48), 0));
        }
    }
    ~Frame();

    void draw(sf::RenderWindow *window) {
        window->draw(*_frame->getSprite());
        for (int i = 0; i != RESSOURCES_COUNT; i++) {
            if (_qty[i]->getText()->getString().toAnsiString() != "0") {
                window->draw(*_obj[i]->getSprite());
                window->draw(*_qty[i]->getText());
            }
        }
    }

    void setQuantity(size_t p_id, int quantity) {
        this->_qty[p_id]->getText()->setString(std::to_string(quantity));
    }

private:
    GObject *_frame;
    std::vector<TObject *> _qty;
    std::vector<GObject *> _obj;
};

class SFMLInterface {
public:
    SFMLInterface();
    ~SFMLInterface();
    
    // SETTERS / GETTERS
    void setBoard(struct case_s ***board) { _board = board; }
    struct case_s ***getBoard() { return _board; }
    sf::RenderWindow *getWindow() { return _window; }
    
    // WESH
    void update_events(void);
    void updateBoard();
    void initializeBoard(int height, int width);
    void draw();

protected:
private:
    int _height;
    int _width;
    sf::RenderWindow *_window;
    sf::View _camera;
    struct case_s ***_board;
    std::vector<std::vector<Frame *>> _frame;

    void key_events(sf::Event event);
};

#endif /* !SFMLINTERFACE_HPP_ */
