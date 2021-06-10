/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** smfl
*/

#include "SFMLInterface.hpp"

SFMLInterface::SFMLInterface() : _camera(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f))
{
    this->_window =
        new sf::RenderWindow(sf::VideoMode(1920, 1080), "Castagne.exe", sf::Style::Close);
    this->_window->setView(this->_camera);
};

SFMLInterface::~SFMLInterface() {};

void SFMLInterface::key_events(sf::Event event)
{
    switch (event.key.code) {
    case sf::Keyboard::Up: // camera up
        this->_camera.move(0, -100.f);
        this->_window->setView(this->_camera);
        break;
    case sf::Keyboard::Down: // camera down
        this->_camera.move(0, 100.f);
        this->_window->setView(this->_camera);
        break;
    case sf::Keyboard::Left: // camera left
        this->_camera.move(-100.f, 0);
        this->_window->setView(this->_camera);
        break;
    case sf::Keyboard::Right: // camera right
        this->_camera.move(100.f, 0);
        this->_window->setView(this->_camera);
        break;
    case sf::Keyboard::A: // camera zoom +
        this->_camera.zoom(0.75f);
        this->_window->setView(this->_camera);
        break;
    case sf::Keyboard::Z: // camera zoom -
        this->_camera.zoom(1.25f);
        this->_window->setView(this->_camera);
        break;
    default:
        break;
    }
};

void SFMLInterface::update_events(void)
{
    sf::Event event;

    while (this->_window->pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->_window->close();
            break;
        case sf::Event::KeyPressed:
            this->key_events(event);
            break;
        default:
            break;
        }
    }
};

void SFMLInterface::updateBoard()
{
    for (size_t y = 0; y < _height; y++) {
        for (size_t x = 0; x < _width; x++) {
            this->_frame[y][x]->setQuantity(FOOD, (*_board)[y][x].ressources[FOOD]);
            this->_frame[y][x]->setQuantity(LINEMATE, (*_board)[y][x].ressources[LINEMATE]);
            this->_frame[y][x]->setQuantity(DERAUMERE, (*_board)[y][x].ressources[DERAUMERE]);
            this->_frame[y][x]->setQuantity(SIBUR, (*_board)[y][x].ressources[SIBUR]);
            this->_frame[y][x]->setQuantity(MENDIANE, (*_board)[y][x].ressources[MENDIANE]);
            this->_frame[y][x]->setQuantity(PHIRAS, (*_board)[y][x].ressources[PHIRAS]);
            this->_frame[y][x]->setQuantity(THYSTAME, (*_board)[y][x].ressources[THYSTAME]);
            this->_frame[y][x]->setQuantity(PLAYER, (*_board)[y][x].ressources[PLAYER]);
        }
    }
}

void SFMLInterface::initializeBoard(int height, int width)
{
    int x;
    int y;
    _height = height;
    _width = width;

    for (y = 0; y != height; y++) {
        _frame.push_back(std::vector<Frame *>());
        x = 0;
        for (x = 0; x != width; x++) {
            _frame[y].push_back(new Frame(x, y));
        }
    }
}

void SFMLInterface::draw()
{
    int y = 0;
    int x = 0;
    
    for (y = 0; y != _height; y++) {
        x = 0;
        for (x = 0; x != _width; x++) {
            _frame[y][x]->draw(_window);
        }
    }
}
