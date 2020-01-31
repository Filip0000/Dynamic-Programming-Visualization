#include "fibonacci.h"
#include "figures.h"
#include <iostream>
#include <math.h>
#include <cstring>
#include <SFML/Graphics.hpp>

#define PI 3.14159265

namespace Fibonacci
{
const int n = 7;
sf::Texture arrow_image[(1<<n)][2];
sf::Sprite arrow[(1<<n)][2];
sf::Texture circle_image[(1<<n)];
sf::Sprite circle[(1<<n)];
sf::Texture number_image[(1<<n)];
sf::Sprite number[(1<<n)];
sf::Texture num_image[(1<<n)][7];
sf::Sprite num[(1<<n)][7];
int last = -1;
double difference = (double)Figures::size/n;
bool click = false;
int odd = 165;
int even = 3*Figures::size/4;
int dp[n+1];
int xx[n+1], yy[n+1];

int rek(int _at, double left, double right, double depth, sf::RenderWindow& window, sf::Sprite& background)
{
    bool click = false;
    last++;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonPressed)
                click = true;
        }
        if(click)
        {
            circle_image[last].loadFromFile(Figures::circle);
            circle_image[last].setSmooth(true);
            circle[last].setTexture(circle_image[last], true);
            circle[last].setScale(sf::Vector2f(.04f, .04f));
            circle[last].setOrigin(400.f, 400.f);
            circle[last].setPosition((left+right)/2.0, difference*depth+16);

            number_image[last].loadFromFile(Figures::number[_at]);
            number_image[last].setSmooth(true);
            number[last].setTexture(number_image[last], true);
            number[last].setScale(sf::Vector2f(.03f, .03f));
            number[last].setOrigin(400.f, 400.f);
            number[last].setPosition((left+right)/2.0, difference*depth+16);

            window.draw(circle[last]);
            window.draw(number[last]);
            window.display();

            if(_at == 0)
            {
                num_image[last][0].loadFromFile(Figures::number[_at]);
                num_image[last][0].setSmooth(true);
                num[last][0].setTexture(number_image[last], true);
                num[last][0].setScale(sf::Vector2f(.02f, .02f));
                num[last][0].setOrigin(400.f, 400.f);
                num[last][0].setPosition((left+right)/2.0, difference*depth+34);

                window.draw(circle[last]);
                window.draw(number[last]);
                window.draw(num[last][0]);
                window.display();
                window.draw(circle[last]);
                window.draw(number[last]);
                window.draw(num[last][0]);
                window.display();

                return 0;
            }
            else if(_at == 1)
            {
                num_image[last][0].loadFromFile(Figures::number[_at]);
                num_image[last][0].setSmooth(true);
                num[last][0].setTexture(number_image[last], true);
                num[last][0].setScale(sf::Vector2f(.02f, .02f));
                num[last][0].setOrigin(400.f, 400.f);
                num[last][0].setPosition((left+right)/2.0, difference*depth+34);

                window.draw(circle[last]);
                window.draw(number[last]);
                window.draw(num[last][0]);
                window.display();
                window.draw(circle[last]);
                window.draw(number[last]);
                window.draw(num[last][0]);
                window.display();
                return 1;
            }
            else
            {
                double mid = (left+right) / 2.0;
                double x = mid;
                double y = difference*depth+16;

                double levox = (left+mid)/2;
                double levoy = (difference*(depth+1)+16);

                double desnox = (right+mid)/2;
                double desnoy = (difference*(depth+1)+16);

                double diffx0 = x-levox;
                double diffy0 = y-levoy;
                double diffx1 = x-desnox;
                double diffy1 = y-desnoy;

                arrow_image[last][0].loadFromFile(Figures::arrow);
                arrow_image[last][0].setSmooth(true);

                arrow[last][0].setTexture(arrow_image[last][0], true);
                arrow[last][0].setOrigin(0.f,400.f);
                arrow[last][0].setScale(sf::Vector2f((sqrt(diffx0*diffx0 + diffy0*diffy0)-16.f)/800.f, .04f));
                arrow[last][0].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                arrow[last][0].setRotation(180 - acos(diffx0/sqrt(diffx0*diffx0 + diffy0*diffy0)) * 180.0 / PI);
                window.draw(arrow[last][0]);
                window.draw(circle[last]);
                window.draw(number[last]);
                window.display();
                window.draw(arrow[last][0]);
                window.draw(circle[last]);
                window.draw(number[last]);
                window.display();
                int val1 = rek(_at-1, left, mid, depth+1, window, background);

                arrow_image[last][1].loadFromFile(Figures::arrow);
                arrow_image[last][1].setSmooth(true);

                arrow[last][1].setTexture(arrow_image[last][1], true);
                arrow[last][1].setOrigin(0.f,400.f);
                arrow[last][1].setScale(sf::Vector2f((sqrt(diffx1*diffx1 + diffy1*diffy1)-16.f)/800.f, .04f));
                arrow[last][1].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                arrow[last][1].setRotation(acos(diffx0/sqrt(diffx1*diffx1 + diffy1*diffy1)) * 180.0 / PI);

                window.draw(arrow[last][1]);
                window.draw(circle[last]);
                window.draw(number[last]);
                window.display();
                window.draw(arrow[last][1]);
                window.draw(circle[last]);
                window.draw(number[last]);
                window.display();

                int val2 = rek(_at-2, mid, right, depth+1, window, background);

                int nn[4];
                for(int i=0; i<4; i++)
                    nn[i] = 0;

                int last = 3;
                int pp = val1+val2;
                while(pp>0)
                {
                    nn[last] = pp%10;
                    pp/=10;
                    last--;
                }

                for(int j=0; j<4; j++)
                {
                    num_image[last][j].loadFromFile(Figures::number[nn[j]]);
                    num_image[last][j].setSmooth(true);

                    num[last][j].setTexture(num_image[last][j], true);
                    num[last][j].setScale(sf::Vector2f(.02f, .02f));
                    num[last][j].setPosition((left+right)/2.0-36+20*j, difference*depth+34);
                }

                for(int i=0; i<4; i++)
                {
                    window.draw(num[last][i]);
                    window.display();
                    window.draw(num[last][i]);
                    window.display();
                }
                return val1 + val2;
            }
            click = false;
        }
    }
}

int dynamic(int _at, int depth, sf::RenderWindow& window)
{
    bool click;
    while (window.isOpen())
    {
        click = false;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonPressed)
                click = true;
        }

        if(click)
        {
            int val1, val2;
            if(dp[_at] != -1)
                return dp[_at];

            xx[_at] = _at&1 ? odd : even;
            yy[_at] = depth * difference + 16;

            circle_image[_at].loadFromFile(Figures::circle);
            circle_image[_at].setSmooth(true);
            circle[_at].setTexture(circle_image[_at], true);
            circle[_at].setScale(sf::Vector2f(.04f, .04f));
            circle[_at].setOrigin(400.f, 400.f);
            circle[_at].setPosition(_at&1 ? odd : even, difference*depth+16);

            number_image[_at].loadFromFile(Figures::number[_at]);
            number_image[_at].setSmooth(true);
            number[_at].setTexture(number_image[_at], true);
            number[_at].setScale(sf::Vector2f(.03f, .03f));
            number[_at].setOrigin(400.f, 400.f);
            number[_at].setPosition(_at&1 ? odd : even, difference*depth+16);

            window.draw(circle[_at]);
            window.draw(number[_at]);
            window.display();
            window.draw(circle[_at]);
            window.draw(number[_at]);
            window.display();

            if(_at == 1)
            {
                num_image[_at][0].loadFromFile(Figures::number[_at]);
                num_image[_at][0].setSmooth(true);
                num[_at][0].setTexture(num_image[_at][0], true);
                num[_at][0].setScale(sf::Vector2f(.02f, .02f));
                num[_at][0].setOrigin(400.f, 400.f);
                num[_at][0].setPosition(odd, difference*depth+44);

//                std::cout<<_at<<"\n";
                window.draw(num[_at][0]);
                window.display();
                window.draw(num[_at][0]);
                window.display();
                dp[1] = 1;
                return 1;
            }

            if(_at&1)
            {
                double newx = even;
                double newy = difference * (depth+1) + 16;
                double x = odd;
                double y = difference * depth + 16;
                double diffx0 = x-newx;
                double diffy0 = y-newy;

                arrow_image[_at][0].loadFromFile(Figures::arrow);
                arrow_image[_at][0].setSmooth(true);

                arrow[_at][0].setTexture(arrow_image[_at][0], true);
                arrow[_at][0].setOrigin(0.f,400.f);
                arrow[_at][0].setScale(sf::Vector2f((sqrt(diffx0*diffx0 + diffy0*diffy0)-16.f)/800.f, .04f));
                arrow[_at][0].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                arrow[_at][0].setRotation(180-acos(diffx0/sqrt(diffx0*diffx0 + diffy0*diffy0)) * 180.0 / PI);
                window.draw(arrow[_at][0]);
                window.display();
                window.draw(arrow[_at][0]);
                window.display();

                val1 = dynamic(_at-1, depth+1, window);
                dp[_at] = val1;
            }
            else
            {
                double newx = odd;
                double newy = difference * depth + 16;
                double x = even;
                double y = difference * depth + 16;
                double diffx0 = x-newx;
                double diffy0 = y-newy;

                arrow_image[_at][0].loadFromFile(Figures::arrow);
                arrow_image[_at][0].setSmooth(true);

                arrow[_at][0].setTexture(arrow_image[_at][0], true);
                arrow[_at][0].setOrigin(0.f,400.f);
                arrow[_at][0].setScale(sf::Vector2f((sqrt(diffx0*diffx0 + diffy0*diffy0)-16.f)/800.f, .04f));
                arrow[_at][0].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                arrow[_at][0].setRotation(180-acos(diffx0/sqrt(diffx0*diffx0 + diffy0*diffy0)) * 180.0 / PI);
                window.draw(arrow[_at][0]);
                window.display();
                window.draw(arrow[_at][0]);
                window.display();
                val1 = dynamic(_at-1, depth, window);
                dp[_at] = val1;

            }

            while (window.isOpen())
            {
                sf::Event event1;
                click = false;
                while (window.pollEvent(event1))
                {
                    if (event1.type == sf::Event::Closed)
                        window.close();
                    else if(event1.type == sf::Event::MouseButtonPressed)
                        click = true;
                }

                if(click)
                {
                    if(dp[_at-2] != -1)
                    {
                        double newx = xx[_at-2];
                        double newy = yy[_at-2];
                        double x = _at&1 ? odd : even;
                        double y = difference * depth + 16;
                        double diffx0 = x-newx;
                        double diffy0 = y-newy;

                        arrow_image[_at][1].loadFromFile(Figures::arrow);
                        arrow_image[_at][1].setSmooth(true);

                        arrow[_at][1].setTexture(arrow_image[_at][0], true);
                        arrow[_at][1].setOrigin(0.f,400.f);
                        arrow[_at][1].setScale(sf::Vector2f((sqrt(diffx0*diffx0 + diffy0*diffy0)-16.f)/800.f, .04f));
                        arrow[_at][1].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                        arrow[_at][1].setRotation(acos(diffx0/sqrt(diffx0*diffx0 + diffy0*diffy0)) * 180.0 / PI);
                        window.draw(arrow[_at][1]);
                        window.display();
                        window.draw(arrow[_at][1]);
                        window.display();
                        val2 = dp[_at-2];
                    }
                    else
                    {
                        xx[_at-2] = _at&1 ? odd : even;
                        yy[_at-2] = (depth+1) * difference + 16;

                        circle_image[_at-2].loadFromFile(Figures::circle);
                        circle_image[_at-2].setSmooth(true);
                        circle[_at-2].setTexture(circle_image[_at-2], true);
                        circle[_at-2].setScale(sf::Vector2f(.04f, .04f));
                        circle[_at-2].setOrigin(400.f, 400.f);
                        circle[_at-2].setPosition(_at-2&1 ? odd : even, difference*(depth+1)+16);

                        number_image[_at-2].loadFromFile(Figures::number[_at-2]);
                        number_image[_at-2].setSmooth(true);
                        number[_at-2].setTexture(number_image[_at-2], true);
                        number[_at-2].setScale(sf::Vector2f(.03f, .03f));
                        number[_at-2].setOrigin(400.f, 400.f);
                        number[_at-2].setPosition(_at-2&1 ? odd : even, difference*(depth+1)+16);

                        double newx = xx[_at-2];
                        double newy = yy[_at-2];
                        double x = _at&1 ? odd : even;
                        double y = difference * depth + 16;
                        double diffx0 = x-newx;
                        double diffy0 = y-newy;

                        arrow_image[_at][1].loadFromFile(Figures::arrow);
                        arrow_image[_at][1].setSmooth(true);

                        arrow[_at][1].setTexture(arrow_image[_at][0], true);
                        arrow[_at][1].setOrigin(0.f,400.f);
                        arrow[_at][1].setScale(sf::Vector2f((sqrt(diffx0*diffx0 + diffy0*diffy0)-16.f)/800.f, .04f));
                        arrow[_at][1].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                        arrow[_at][1].setRotation(acos(diffx0/sqrt(diffx0*diffx0 + diffy0*diffy0)) * 180.0 / PI);

                        val2 = dp[_at-2] = 0;

                        num_image[_at-2][0].loadFromFile(Figures::number[_at-2]);
                        num_image[_at-2][0].setSmooth(true);
                        num[_at-2][0].setTexture(num_image[_at-2][0], true);
                        num[_at-2][0].setScale(sf::Vector2f(.02f, .02f));
                        num[_at-2][0].setOrigin(400.f, 400.f);
                        num[_at-2][0].setPosition(even, difference*(depth+1)+44);

                        window.draw(circle[_at-2]);
                        window.draw(number[_at-2]);
                        window.draw(arrow[_at][1]);
                        window.display();
                        window.draw(circle[_at-2]);
                        window.draw(number[_at-2]);
                        window.draw(arrow[_at][1]);
                        window.display();

                        window.draw(num[_at-2][0]);
                        window.display();
                        window.draw(num[_at-2][0]);
                        window.display();
                        dp[_at-2] = 0;
                    }

                    int nn[4];
                    for(int i=0; i<4; i++)
                        nn[i] = 0;

                    int last = 3;
                    int pp = val1+val2;
                    while(pp>0)
                    {
                        nn[last] = pp%10;
                        pp/=10;
                        last--;
                    }

                    for(int j=0; j<4; j++)
                    {
                        num_image[last][j].loadFromFile(Figures::number[nn[j]]);
                        num_image[last][j].setSmooth(true);

                        num[last][j].setTexture(num_image[last][j], true);
                        num[last][j].setScale(sf::Vector2f(.02f, .02f));
                        num[last][j].setPosition((_at&1 ? odd : even)-36+20*j, difference*depth+34);
                        num[last][j].setPosition((_at&1 ? odd : even)-36+20*j, difference*depth+34);

                        window.draw(num[last][j]);
                        window.display();
                        window.draw(num[last][j]);
                        window.display();

                    }
                    dp[_at] = val1 + val2;
                    return val1+val2;
                }
            }
        }
        click = false;
    }
}

void solve(sf::Sprite& background, sf::RenderWindow& window1)
{
    memset(dp, -1, sizeof(dp));
    int type = 1; // 0 = recursion, 1 = dynamic
    if(type == 0)
        rek(n, 0.0, Figures::size, 0, window1, background);
    else if(type == 1)
        dynamic(n, 0, window1);

    while(1 == 1)
        window1.display();
}
}
