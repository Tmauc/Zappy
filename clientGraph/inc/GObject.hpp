 /*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Game object
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef GOBJECT_HPP_
    #define GOBJECT_HPP_

#include "Macros.hpp"

class GObject {
    public:
        GObject(std::string path, sf::Vector2f pos, sf::IntRect rect, float sp);
        GObject(GObject &object);
        ~GObject();

        sf::IntRect getRect() { return _rect; }
        void setRect(sf::IntRect rect);
        sf::Vector2f getPos() { return _pos; }
        void setPos(sf::Vector2f pos);
        sf::Vector2f getActualPos() { return _actualpos; }
        void setActualPos(sf::Vector2f actualpos) { _actualpos = actualpos; }
        float getSpeed() { return _sp; }
        void setSpeed(float speed) { _sp = speed; }
        float getAngle() { return _angle; }
        void setAngle(float angle);
        float getWRatio() { return _wratio; }
        void setWRatio(float wratio) { _wratio = wratio; }
        sf::Sprite *getSprite() { return _sprite; }
        void setSprite(sf::Sprite &sprite) { _sprite = &sprite; }
        sf::Texture *getTexture() { return _texture; }
        void setTexture(sf::Texture texture);
        bool checkCollide(GObject &other);
        void scaleWithWindow();
        void move(sf::Vector2f direction);
        void dump();

    protected:
    private:
        sf::Sprite *_sprite;
        sf::Texture *_texture;
        float _sp;
        float _angle;
        sf::Vector2f _pos;
        sf::Vector2f _actualpos;
        sf::IntRect _rect;
        float _wratio = 1;
};

#endif /* !GOBJECT_HPP_ */
