
#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum ButtonStates{BTN_idle=0,BTN_Active, BTN_hover};

class Button

{
private:
    short unsigned buttonState;
    bool pressed;
    bool hover;

    sf::RectangleShape shape;
    sf::Font * font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;


public:
    Button(double x, double y,
        sf::Font * font,std::string text,sf::Color idlecolor,
        sf::Color hoverColor,sf::Color activeColor);
    ~Button();

    //Funtions
    void render(sf::RenderTarget * target);
    void update(const sf::Vector2f mousePos);
    const bool isPress() const;
};

Button::Button(double x, double y, sf::Font * font,std::string text,sf::Color idlecolor,
        sf::Color hoverColor,sf::Color activeColor)
{
    this->buttonState = BTN_idle;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(100, 100));

    this->font= font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(12);
    this->text.setPosition(
        this->shape.getPosition().x / 2.f - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y / 2.f- this->text.getGlobalBounds().height / 2.f
    );


    this->idleColor= idlecolor;
    this->hoverColor= hoverColor;
    this->activeColor= activeColor;

    this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

const bool Button::isPress() const
{
    if(this->buttonState == BTN_Active) return true;
    return false;
}

void Button::render(sf::RenderTarget * target)
{
    target->draw(this->shape);
}

void Button::update(const sf::Vector2f mousePos)
{
    
    this->buttonState = BTN_idle;

    //hover 
    if(this->shape.getGlobalBounds().contains(mousePos)){
        this->buttonState = BTN_hover;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->buttonState = BTN_Active;
        }
    }

    switch (this->buttonState)
    {
    case  BTN_idle:
        this->shape.setFillColor(this->idleColor);
        break;
    case  BTN_hover:
        this->shape.setFillColor(this->hoverColor);
        break;
    case  BTN_Active:
        this->shape.setFillColor(this->activeColor);
        break;

    default:
        this->shape.setFillColor(sf::Color::Red);
        break;
    }


}


#endif 
