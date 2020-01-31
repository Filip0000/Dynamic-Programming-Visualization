#include "factorial.h"
#include "figures.h"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Factorial
{
const int n = 7;
sf::Texture arrow_image[n];
sf::Sprite arrow[n];
sf::Texture circle_image[n];
sf::Sprite circle[n];
sf::Texture number_image[n];
sf::Sprite number[n];
sf::Texture num_image[n][7];
sf::Sprite num[n][7];

void solve(sf::Sprite& background, sf::RenderWindow& window)
{
    for(int i=0; i<n; i++)
    {
        long long pom = 1;
        int nn[7];
        for(int i=0;i<7;i++)
            nn[i] = 0;
        for(long long j=2; j<=n-i-1; j++)
            pom*=j;

        int last = 6;
        while(pom>0)
        {
            nn[last] = pom%10;
            pom/=10;
            last--;
        }

        for(int j=0; j<7; j++)
        {
            num_image[i][j].loadFromFile(Figures::number[nn[j]]);
            num_image[i][j].setSmooth(true);

            num[i][j].setTexture(num_image[i][j], true);
            num[i][j].setScale(sf::Vector2f(.04f, .04f));
            num[i][j].setPosition(Figures::size/2 + 20 + 34*j, Figures::size/n*i);
        }
    }

    for(int i=0; i<n; i++)
    {
        circle_image[i].loadFromFile(Figures::circle);
        circle_image[i].setSmooth(true);

        circle[i].setTexture(circle_image[i], true);
        circle[i].setScale(sf::Vector2f(.04f, .04f));
        circle[i].setPosition(Figures::size/2-circle_image[i].getSize().x*circle[i].getScale().x/2, Figures::size/n*i);
    }

    for(int i=0; i<n; i++)
    {
        arrow_image[i].loadFromFile(Figures::arrow);
        arrow_image[i].setSmooth(true);

        arrow[i].setTexture(arrow_image[i], true);
        arrow[i].setOrigin(400.f,400.f);
        arrow[i].setScale(sf::Vector2f(((double)Figures::size/n-32.f)/800.f, .04f));
//        std::cout<<arrow[i].getScale().x<<"\n";
        arrow[i].setPosition(Figures::size/2, (double)Figures::size/n*i+(arrow[i].getScale().x*400.f)+32.f);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
        arrow[i].setRotation(90);
    }

    for(int i=0; i<n; i++)
    {
        number_image[i].loadFromFile(Figures::number[n-i-1]);
        number_image[i].setSmooth(true);

        number[i].setTexture(number_image[i], true);
        number[i].setScale(sf::Vector2f(.03f, .03f));
        number[i].setPosition(Figures::size/2-number_image[i].getSize().x*number[i].getScale().x/2, Figures::size/n*i+((circle[i].getScale().x-number[i].getScale().x)*(Figures::size/2)));
    }

    int bb = 1;
    bool t = false;
    bool click = false;
    int ll = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonPressed && ll<n)
                click = true;
        }

        window.draw(background);

        if(click && bb<n-1)
            bb++;
        if(t && click && ll<n-1)
            ll++;

        for(int i=0; i<bb; i++)
            window.draw(circle[i]);

        for(int i=0; i<std::min(bb, n-2); i++)
            window.draw(arrow[i]);

        for(int i=0; i<bb; i++)
            window.draw(number[i]);

        if(bb == n-1)
            t = true;

        if(t)
        {
            for(int i=bb-1;i>=bb-ll;i--)
            {
                for(int j=0;j<7;j++)
                    window.draw(num[i][j]);
            }
        }

        window.display();

        click = false;
    }
}
}
