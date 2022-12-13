#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <vector>

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wnarrowing"
#endif

namespace shapes
{
    class PShape : public sf::Drawable
    {
    public:
        virtual int area() = 0;
        virtual std::string name() = 0;

    protected:
        PShape(){};
    };


    class CircleShape : public PShape
    {
    public:
        // координаты центра и радиус
        CircleShape(int x, int y, int r, sf::Color color = sf::Color::Red)
        {
            shape.setPosition(x, y);
            shape.setRadius(r);
            shape.setFillColor(color);
        };

        int area() override { return M_PI * shape.getRadius() * shape.getRadius(); }

        std::string name() { return "Circle"; };

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(shape, states);
        }

        sf::CircleShape shape;
    };


    class RectangleShape : public PShape
    {
    public:
        // длины сторон и координаты левой верхней точки
        RectangleShape(int a, int b, int x, int y, sf::Color color = sf::Color::Green)
        {
            shape.setSize({a, b});
            shape.setPosition({x, y});
            shape.setFillColor(color);
        };

        int area() override { return shape.getSize().x * shape.getSize().y; };

        std::string name() override { return "Rectangle"; };

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(shape, states);
        }
        
        sf::RectangleShape shape;
    };


    class SquareShape : public RectangleShape
    {
    public:
        // длина стороны и координаты верхней левой точки  
        SquareShape(int a, int x, int y, sf::Color color = sf::Color::Blue) : RectangleShape (a, a, x, y, color) {};

        std::string name() override { return "Square"; };
    };

    
    class TriangleShape : public PShape
    {
    public:
        // три пары координат точек
        TriangleShape(int x1, int y1, int x2, int y2, int x3, int y3, sf::Color color = sf::Color::Yellow)
        {
            shape.setPointCount(3);
            shape.setPoint(0, {x1, y1});
            shape.setPoint(1, {x2, y2});
            shape.setPoint(2, {x3, y3});
            shape.setFillColor (color);
        }

        int area() override 
        { 
            auto tmp = shape.getPoint(1) - shape.getPoint(0);
            float side1 = sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
            tmp = shape.getPoint(2) - shape.getPoint(1);
            float side2 = sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
            tmp = shape.getPoint(0) - shape.getPoint(2);
            float side3 = sqrt(tmp.x * tmp.x + tmp.y * tmp.y);

            float s = 0.5 * (side1 + side2 + side3);
            return sqrt (s * (s - side1) * (s - side2) * (s - side3));
        };

        std::string name() override { return "Triangle"; };

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw (shape, states);
        }

        sf::ConvexShape shape;
    };
}

int main()
{
    // различные фигуры
    shapes::CircleShape circle {100, 100, 20};
    shapes::RectangleShape rectangle {40, 30, 100, 200};
    shapes::SquareShape square {60, 200, 200};
    shapes::TriangleShape triangle {0, 0, 80, 0, 60, 50};


    // обращение к методам фигур через базовый класс
    std::vector<shapes::PShape*> shapesVector;
    shapesVector.push_back (&circle);
    shapesVector.push_back (&rectangle);
    shapesVector.push_back (&square);
    shapesVector.push_back (&triangle);

    // вывод имени и площади фигуры
    for (auto i : shapesVector)
    {
        std::cout << i->name() << ": " << i->area() << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(300, 300), "sfmlshapes");
    sf::Event event;
    bool redraw = true;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (redraw)
        {
            window.clear();
            // отрисовка фигур
            for (auto i : shapesVector)
            {
                window.draw (*i);
            }
            window.display();
            redraw = false;
        }
    }
}