#include "fibonacci.h"
#include "figures.h"
#include <iostream>
#include <math.h>
#include <cstring>
#include <SFML/Graphics.hpp>

#define PI 3.1415

namespace Knapsack
{
const int n = 3;
int w[] = {3, 4, 4};
int v[] = {10, 4, 5};
int weight = 10;

sf::Texture arrow_image[(1<<n)][2];
sf::Sprite arrow[(1<<n)][2];
sf::Texture circle_image[(1<<n)];
sf::Sprite circle[(1<<n)];
sf::Texture com_image[(1<<n)];
sf::Sprite com[(1<<n)];
sf::Texture number_image[(1<<n)][4];
sf::Sprite number[(1<<n)][4];
sf::Texture num_image[(1<<n)][7];
sf::Sprite num[(1<<n)][7];
int last = -1;
double difference = (double)Figures::size/n;
bool click = false;
int odd = 165;
int even = 3*Figures::size/4;
int xx[100][100], yy[100][100];
double sz = 24;
int dp[100][100];

int rek(int _at, int remaining, double left, double right, double depth, sf::RenderWindow& window, sf::Sprite& background)
{
    bool click = false;
    last++;
    int val1, val2;

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
            circle[last].setScale(sf::Vector2f(.06f, .06f));
            circle[last].setOrigin(400.f, 400.f);
            circle[last].setPosition((left+right)/2.0, difference*depth+sz);

            if(_at<10)
            {
                number_image[last][0].loadFromFile(Figures::number[0]);
                number_image[last][0].setSmooth(true);
                number[last][0].setTexture(number_image[last][0], true);
                number[last][0].setScale(sf::Vector2f(.02f, .02f));
                number[last][0].setOrigin(400.f, 400.f);
                number[last][0].setPosition((left+right)/2.0-17, difference*depth+sz);
                number_image[last][1].loadFromFile(Figures::number[_at]);
                number_image[last][1].setSmooth(true);
                number[last][1].setTexture(number_image[last][1], true);
                number[last][1].setScale(sf::Vector2f(.02f, .02f));
                number[last][1].setOrigin(400.f, 400.f);
                number[last][1].setPosition((left+right)/2.0-7, difference*depth+sz);
            }
            else
            {
                number_image[last][0].loadFromFile(Figures::number[_at/10]);
                number_image[last][0].setSmooth(true);
                number[last][0].setTexture(number_image[last][0], true);
                number[last][0].setScale(sf::Vector2f(.02f, .02f));
                number[last][0].setOrigin(400.f, 400.f);
                number[last][0].setPosition((left+right)/2.0-17, difference*depth+sz);
                number_image[last][1].loadFromFile(Figures::number[_at%10]);
                number_image[last][1].setSmooth(true);
                number[last][1].setTexture(number_image[last][1], true);
                number[last][1].setScale(sf::Vector2f(.02f, .02f));
                number[last][1].setOrigin(400.f, 400.f);
                number[last][1].setPosition((left+right)/2.0-7, difference*depth+sz);
            }

            if(remaining<10)
            {
                number_image[last][2].loadFromFile(Figures::number[0]);
                number_image[last][2].setSmooth(true);
                number[last][2].setTexture(number_image[last][2], true);
                number[last][2].setScale(sf::Vector2f(.02f, .02f));
                number[last][2].setOrigin(400.f, 400.f);
                number[last][2].setPosition((left+right)/2.0+7, difference*depth+sz);
                number_image[last][3].loadFromFile(Figures::number[remaining]);
                number_image[last][3].setSmooth(true);
                number[last][3].setTexture(number_image[last][3], true);
                number[last][3].setScale(sf::Vector2f(.02f, .02f));
                number[last][3].setOrigin(400.f, 400.f);
                number[last][3].setPosition((left+right)/2.0+17, difference*depth+sz);
            }
            else
            {
                number_image[last][2].loadFromFile(Figures::number[remaining/10]);
                number_image[last][2].setSmooth(true);
                number[last][2].setTexture(number_image[last][2], true);
                number[last][2].setScale(sf::Vector2f(.02f, .02f));
                number[last][2].setOrigin(400.f, 400.f);
                number[last][2].setPosition((left+right)/2.0+7, difference*depth+sz);
                number_image[last][3].loadFromFile(Figures::number[remaining%10]);
                number_image[last][3].setSmooth(true);
                number[last][3].setTexture(number_image[last][3], true);
                number[last][3].setScale(sf::Vector2f(.02f, .02f));
                number[last][3].setOrigin(400.f, 400.f);
                number[last][3].setPosition((left+right)/2.0+17, difference*depth+sz);
            }

            window.draw(circle[last]);
            window.draw(number[last][0]);
            window.draw(number[last][1])  ;
            window.draw(number[last][2]);
            window.draw(number[last][3]);
            window.display();
            window.draw(circle[last]);
            window.draw(number[last][0]);
            window.draw(number[last][1])  ;
            window.draw(number[last][2]);
            window.draw(number[last][3]);
            window.display();

            if(_at == 0)
            {
                if(remaining>=w[0])
                {
                    val1 = v[0];
                    int nn[4];
                    for(int i=0; i<4; i++)
                        nn[i] = 0;

                    int last1 = 3;
                    int pp = val1;
                    while(pp>0)
                    {
                        nn[last1] = pp%10;
                        pp/=10;
                        last1--;
                    }

                    for(int j=0; j<4; j++)
                    {
                        num_image[last][j].loadFromFile(Figures::number[nn[j]]);
                        num_image[last][j].setSmooth(true);

                        num[last][j].setTexture(num_image[last][j], true);
                        num[last][j].setScale(sf::Vector2f(.02f, .02f));
                        num[last][j].setPosition((left+right)/2.0-20+10*j, difference*depth+46);
                    }

                    for(int i=0; i<4; i++)
                    {
                        window.draw(num[last][i]);
                        window.display();
                        window.draw(num[last][i]);
                        window.display();
                    }
                    return v[0];
                }
                else
                {
                    val1 = 0;
                    int nn[4];
                    for(int i=0; i<4; i++)
                        nn[i] = 0;

                    int last1 = 3;
                    int pp = val1;
                    while(pp>0)
                    {
                        nn[last1] = pp%10;
                        pp/=10;
                        last1--;
                    }

                    for(int j=0; j<4; j++)
                    {
                        num_image[last][j].loadFromFile(Figures::number[nn[j]]);
                        num_image[last][j].setSmooth(true);

                        num[last][j].setTexture(num_image[last][j], true);
                        num[last][j].setScale(sf::Vector2f(.02f, .02f));
                        num[last][j].setPosition((left+right)/2.0-20+10*j, difference*depth+46);
                    }

                    for(int i=0; i<4; i++)
                    {
                        window.draw(num[last][i]);
                        window.display();
                        window.draw(num[last][i]);
                        window.display();
                    }
                    return 0;
                }
            }
            else
            {
                double mid = (left+right) / 2.0;
                double x = mid;
                double y = difference*depth+sz;

                double levox = (left+mid)/2.0;
                double levoy = (difference*(depth+1)+sz);

                double desnox = (right+mid)/2.0;
                double desnoy = (difference*(depth+1)+sz);

                double diffx0 = x-levox;
                double diffy0 = y-levoy;
                double diffx1 = x-desnox;
                double diffy1 = y-desnoy;

                arrow_image[last][0].loadFromFile(Figures::arrow);
                arrow_image[last][0].setSmooth(true);

                arrow[last][0].setTexture(arrow_image[last][0], true);
                arrow[last][0].setOrigin(0.f,400.f);
                arrow[last][0].setScale(sf::Vector2f((sqrt(diffx0*diffx0 + diffy0*diffy0)-sz)/800.f, .04f));
                arrow[last][0].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                arrow[last][0].setRotation(180 - acos(diffx0/sqrt(diffx0*diffx0 + diffy0*diffy0)) * 180.0 / PI);

                window.draw(arrow[last][0]);
                window.draw(circle[last]);
                window.draw(number[last][0]);
                window.draw(number[last][1])  ;
                window.draw(number[last][2]);
                window.draw(number[last][3]);
                window.display();
                window.draw(arrow[last][0]);
                window.draw(circle[last]);
                window.draw(number[last][0]);
                window.draw(number[last][1]);
                window.draw(number[last][2]);
                window.draw(number[last][3]);
                window.display();

                val1 = rek(_at-1, remaining, left, mid, depth+1, window, background);
                val2 = 0;

                if(remaining - w[_at]>=0)
                {
                    arrow_image[last][1].loadFromFile(Figures::arrow);
                    arrow_image[last][1].setSmooth(true);

                    arrow[last][1].setTexture(arrow_image[last][1], true);
                    arrow[last][1].setOrigin(0.f,400.f);
                    arrow[last][1].setScale(sf::Vector2f((sqrt(diffx1*diffx1 + diffy1*diffy1)-sz)/800.f, .04f));
                    arrow[last][1].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                    arrow[last][1].setRotation(acos(diffx0/sqrt(diffx1*diffx1 + diffy1*diffy1)) * 180.0 / PI);

                    window.draw(arrow[last][1]);
                    window.display();
                    window.draw(arrow[last][1]);
                    window.display();

                    val2 = rek(_at-1, remaining-w[_at], mid, right, depth+1, window, background) + v[_at];
                }

                int nn[4];
                for(int i=0; i<4; i++)
                    nn[i] = 0;

                int last1 = 3;
                int pp = std::max(val1, val2);
                while(pp>0)
                {
                    nn[last1] = pp%10;
                    pp/=10;
                    last1--;
                }

                for(int j=0; j<4; j++)
                {
                    num_image[last][j].loadFromFile(Figures::number[nn[j]]);
                    num_image[last][j].setSmooth(true);

                    num[last][j].setTexture(num_image[last][j], true);
                    num[last][j].setScale(sf::Vector2f(.02f, .02f));
                    num[last][j].setPosition((left+right)/2.0-20+10*j, difference*depth+46);
                }

                for(int i=0; i<4; i++)
                {
                    window.draw(num[last][i]);
                    window.display();
                    window.draw(num[last][i]);
                    window.display();
                }

                return std::max(val1, val2);
            }
            click = false;
        }
    }
}

int dynamic(int _at, int remaining, double left, double right, double depth, sf::RenderWindow& window, sf::Sprite& background)
{
    int val1, val2;
    bool click = false;
    last++;

//    std::cout<<last<<"\n";
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
            circle[last].setScale(sf::Vector2f(.06f, .06f));
            circle[last].setOrigin(400.f, 400.f);
            circle[last].setPosition((left+right)/2.0, difference*depth+sz);

            if(_at<10)
            {
                number_image[last][0].loadFromFile(Figures::number[0]);
                number_image[last][0].setSmooth(true);
                number[last][0].setTexture(number_image[last][0], true);
                number[last][0].setScale(sf::Vector2f(.02f, .02f));
                number[last][0].setOrigin(400.f, 400.f);
                number[last][0].setPosition((left+right)/2.0-17, difference*depth+sz);
                number_image[last][1].loadFromFile(Figures::number[_at]);
                number_image[last][1].setSmooth(true);
                number[last][1].setTexture(number_image[last][1], true);
                number[last][1].setScale(sf::Vector2f(.02f, .02f));
                number[last][1].setOrigin(400.f, 400.f);
                number[last][1].setPosition((left+right)/2.0-7, difference*depth+sz);
            }
            else
            {
                number_image[last][0].loadFromFile(Figures::number[_at/10]);
                number_image[last][0].setSmooth(true);
                number[last][0].setTexture(number_image[last][0], true);
                number[last][0].setScale(sf::Vector2f(.02f, .02f));
                number[last][0].setOrigin(400.f, 400.f);
                number[last][0].setPosition((left+right)/2.0-17, difference*depth+sz);
                number_image[last][1].loadFromFile(Figures::number[_at%10]);
                number_image[last][1].setSmooth(true);
                number[last][1].setTexture(number_image[last][1], true);
                number[last][1].setScale(sf::Vector2f(.02f, .02f));
                number[last][1].setOrigin(400.f, 400.f);
                number[last][1].setPosition((left+right)/2.0-7, difference*depth+sz);
            }

            if(remaining<10)
            {
                number_image[last][2].loadFromFile(Figures::number[0]);
                number_image[last][2].setSmooth(true);
                number[last][2].setTexture(number_image[last][2], true);
                number[last][2].setScale(sf::Vector2f(.02f, .02f));
                number[last][2].setOrigin(400.f, 400.f);
                number[last][2].setPosition((left+right)/2.0+7, difference*depth+sz);
                number_image[last][3].loadFromFile(Figures::number[remaining]);
                number_image[last][3].setSmooth(true);
                number[last][3].setTexture(number_image[last][3], true);
                number[last][3].setScale(sf::Vector2f(.02f, .02f));
                number[last][3].setOrigin(400.f, 400.f);
                number[last][3].setPosition((left+right)/2.0+17, difference*depth+sz);
            }
            else
            {
                number_image[last][2].loadFromFile(Figures::number[remaining/10]);
                number_image[last][2].setSmooth(true);
                number[last][2].setTexture(number_image[last][2], true);
                number[last][2].setScale(sf::Vector2f(.02f, .02f));
                number[last][2].setOrigin(400.f, 400.f);
                number[last][2].setPosition((left+right)/2.0+7, difference*depth+sz);
                number_image[last][3].loadFromFile(Figures::number[remaining%10]);
                number_image[last][3].setSmooth(true);
                number[last][3].setTexture(number_image[last][3], true);
                number[last][3].setScale(sf::Vector2f(.02f, .02f));
                number[last][3].setOrigin(400.f, 400.f);
                number[last][3].setPosition((left+right)/2.0+17, difference*depth+sz);
            }

            window.draw(circle[last]);
            window.draw(number[last][0]);
            window.draw(number[last][1])  ;
            window.draw(number[last][2]);
            window.draw(number[last][3]);
            window.display();
            window.draw(circle[last]);
            window.draw(number[last][0]);
            window.draw(number[last][1])  ;
            window.draw(number[last][2]);
            window.draw(number[last][3]);
            window.display();

            val1 = 0;

            if(_at == 0)
            {
                if(remaining>=w[0])
                {
                    val1 = v[0];
                    int nn[4];
                    for(int i=0; i<4; i++)
                        nn[i] = 0;

                    int last1 = 3;
                    int pp = val1;
                    while(pp>0)
                    {
                        nn[last1] = pp%10;
                        pp/=10;
                        last1--;
                    }

                    for(int j=0; j<4; j++)
                    {
                        num_image[last][j].loadFromFile(Figures::number[nn[j]]);
                        num_image[last][j].setSmooth(true);

                        num[last][j].setTexture(num_image[last][j], true);
                        num[last][j].setScale(sf::Vector2f(.02f, .02f));
                        num[last][j].setPosition((left+right)/2.0-20+10*j, difference*depth+46);
                    }

                    for(int i=0; i<4; i++)
                    {
                        window.draw(num[last][i]);
                        window.display();
                        window.draw(num[last][i]);
                        window.display();
                        window.draw(num[last][i]);
                        window.display();
                        window.draw(num[last][i]);
                        window.display();
                    }

                    dp[_at][remaining] = v[0];
                    return v[0];
                }
                else
                {
                    val1 = 0;
                    int nn[4];
                    for(int i=0; i<4; i++)
                        nn[i] = 0;

                    int last1 = 3;
                    int pp = val1;
                    while(pp>0)
                    {
                        nn[last1] = pp%10;
                        pp/=10;
                        last1--;
                    }

                    for(int j=0; j<4; j++)
                    {
                        num_image[last][j].loadFromFile(Figures::number[nn[j]]);
                        num_image[last][j].setSmooth(true);

                        num[last][j].setTexture(num_image[last][j], true);
                        num[last][j].setScale(sf::Vector2f(.02f, .02f));
                        num[last][j].setPosition((left+right)/2.0-20+10*j, difference*depth+46);
                    }

                    for(int i=0; i<4; i++)
                    {
                        window.draw(num[last][i]);
                        window.display();
                        window.draw(num[last][i]);
                        window.display();
                    }
                    dp[_at][remaining] = 0;
                    return 0;
                }
            }
            else
            {
                if(dp[_at-1][remaining] != -1)
                {
                    double mid = (left+right) / 2.0;
                    double x = mid;
                    double y = difference*depth+sz;

                    double newx = xx[_at-1][remaining];
                    double newy = yy[_at-1][remaining];

                    double diffx0 = x-newx;
                    double diffy0 = y-newy;

                    arrow_image[last][0].loadFromFile(Figures::arrow);
                    arrow_image[last][0].setSmooth(true);

                    arrow[last][0].setTexture(arrow_image[last][0], true);
                    arrow[last][0].setOrigin(0.f,400.f);
                    arrow[last][0].setScale(sf::Vector2f((sqrt(diffx0*diffx0 + diffy0*diffy0)-sz)/800.f, .04f));
                    arrow[last][0].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                    arrow[last][0].setRotation(180 - acos(diffx0/sqrt(diffx0*diffx0 + diffy0*diffy0)) * 180.0 / PI);

                    window.draw(arrow[last][0]);
                    window.draw(circle[last]);
                    window.draw(number[last][0]);
                    window.draw(number[last][1])  ;
                    window.draw(number[last][2]);
                    window.draw(number[last][3]);
                    window.display();
                    window.draw(arrow[last][0]);
                    window.draw(circle[last]);
                    window.draw(number[last][0]);
                    window.draw(number[last][1]);
                    window.draw(number[last][2]);
                    window.draw(number[last][3]);
                    window.display();

                    val1 = dp[_at-1][remaining];
                }
                else
                {
                    double mid = (left+right) / 2.0;
                    double x = mid;
                    double y = difference*depth+sz;

                    double levox = (left+mid)/2.0;
                    double levoy = (difference*(depth+1)+sz);

                    double desnox = (right+mid)/2.0;
                    double desnoy = (difference*(depth+1)+sz);

                    double diffx0 = x-levox;
                    double diffy0 = y-levoy;
                    double diffx1 = x-desnox;
                    double diffy1 = y-desnoy;

                    xx[_at-1][remaining] = levox;
                    yy[_at-1][remaining] = levoy;

                    arrow_image[last][0].loadFromFile(Figures::arrow);
                    arrow_image[last][0].setSmooth(true);

                    arrow[last][0].setTexture(arrow_image[last][0], true);
                    arrow[last][0].setOrigin(0.f,400.f);
                    arrow[last][0].setScale(sf::Vector2f((sqrt(diffx0*diffx0 + diffy0*diffy0)-sz)/800.f, .04f));
                    arrow[last][0].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                    arrow[last][0].setRotation(180 - acos(diffx0/sqrt(diffx0*diffx0 + diffy0*diffy0)) * 180.0 / PI);

                    window.draw(arrow[last][0]);
                    window.draw(circle[last]);
                    window.draw(number[last][0]);
                    window.draw(number[last][1])  ;
                    window.draw(number[last][2]);
                    window.draw(number[last][3]);
                    window.display();
                    window.draw(arrow[last][0]);
                    window.draw(circle[last]);
                    window.draw(number[last][0]);
                    window.draw(number[last][1]);
                    window.draw(number[last][2]);
                    window.draw(number[last][3]);
                    window.display();

                    val1 = dynamic(_at-1, remaining, left, mid, depth+1, window, background);
                    dp[_at-1][remaining] = val1;
                }

                val2 = 0;

                if(remaining - w[_at]>=0)
                {
                    if(dp[_at-1][remaining - w[_at]] == -1)
                    {
                        double mid = (left+right) / 2.0;
                        double x = mid;
                        double y = difference*depth+sz;

                        double levox = (left+mid)/2.0;
                        double levoy = (difference*(depth+1)+sz);

                        double desnox = (right+mid)/2.0;
                        double desnoy = (difference*(depth+1)+sz);

                        double diffx0 = x-levox;
                        double diffy0 = y-levoy;
                        double diffx1 = x-desnox;
                        double diffy1 = y-desnoy;

                        arrow_image[last][1].loadFromFile(Figures::arrow);
                        arrow_image[last][1].setSmooth(true);

                        arrow[last][1].setTexture(arrow_image[last][1], true);
                        arrow[last][1].setOrigin(0.f,400.f);
                        arrow[last][1].setScale(sf::Vector2f((sqrt(diffx1*diffx1 + diffy1*diffy1)-sz)/800.f, .04f));
                        arrow[last][1].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                        arrow[last][1].setRotation(acos(diffx0/sqrt(diffx1*diffx1 + diffy1*diffy1)) * 180.0 / PI);
                        xx[_at-1][remaining - w[_at]] = desnox;
                        yy[_at-1][remaining - w[_at]] = desnoy;

                        window.draw(arrow[last][1]);
                        window.display();
                        window.draw(arrow[last][1]);
                        window.display();

                        val2 = dynamic(_at-1, remaining-w[_at], mid, right, depth+1, window, background) + v[_at];
                        dp[_at-1][remaining - w[_at]] = val2 - v[_at];
                    }
                    else
                    {
                        double mid = (left+right) / 2.0;
                        double x = mid;
                        double y = difference*depth+sz;

                        double newx = xx[_at][remaining - w[_at]];
                        double newy = yy[_at][remaining - w[_at]];

                        double diffx0 = x-newx;
                        double diffy0 = y-newy;
                        arrow_image[last][1].loadFromFile(Figures::arrow);
                        arrow_image[last][1].setSmooth(true);

                        arrow[last][1].setTexture(arrow_image[last][1], true);
                        arrow[last][1].setOrigin(0.f,400.f);
                        arrow[last][1].setScale(sf::Vector2f((sqrt(diffx0*diffx0 + diffy0*diffy0)-sz)/800.f, .04f));
                        arrow[last][1].setPosition(x, y);//(circle[i].getTexture()->getSize().x*circle[i].getScale().x)*1.5);
                        arrow[last][1].setRotation(acos(diffx0/sqrt(diffx0*diffx0 + diffy0*diffy0)) * 180.0 / PI);

                        window.draw(arrow[last][1]);
                        window.draw(circle[last]);
                        window.draw(number[last][0]);
                        window.draw(number[last][1]);
                        window.display();
                        window.draw(arrow[last][1]);
                        window.draw(circle[last]);
                        window.draw(number[last][0]);
                        window.draw(number[last][1]);
                        window.display();

                        val2 = dp[_at-1][remaining - w[_at]];
                    }
                }

                int nn[4];
                for(int i=0; i<4; i++)
                    nn[i] = 0;

                int last1 = 3;
                int pp = std::max(val1, val2);
                while(pp>0)
                {
                    nn[last1] = pp%10;
                    pp/=10;
                    last1--;
                }

                for(int j=0; j<4; j++)
                {
                    num_image[last][j].loadFromFile(Figures::number[nn[j]]);
                    num_image[last][j].setSmooth(true);

                    num[last][j].setTexture(num_image[last][j], true);
                    num[last][j].setScale(sf::Vector2f(.02f, .02f));
                    num[last][j].setPosition((left+right)/2.0-20+10*j, difference*depth+46);
                }

                for(int i=0; i<4; i++)
                {
                    window.draw(num[last][i]);
                    window.display();
                    window.draw(num[last][i]);
                    window.display();
                }

                return std::max(val1, val2);
            }
            click = false;
        }
    }
}

void solve(sf::Sprite& background, sf::RenderWindow& window1)
{
    memset(dp, -1, sizeof(dp));
    int type = 1; // 0 = recursion, 1 = dynamic
    if(type == 0)
        rek(n-1, weight, 0.0, Figures::size, 0, window1, background);
    else if(type == 1)
        dynamic(n-1, weight, 0.0, Figures::size, 0, window1, background);

    while(1 == 1)
        window1.display();
}
}
