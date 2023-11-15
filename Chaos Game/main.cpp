// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>


// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "ChaosGame", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    //User interface
    Text instructionText;
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    instructionText.setFont(font);
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(Color::White);
    instructionText.setPosition(10, 10);
    instructionText.setString("Click on any three points to create the vertices for the triangle.\n"
        "Click on a fourth point to start the algorithm.");


    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        std::cout << "fourth click intialized:" << std::endl;
                        std::cout << "the left button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        /*
        ****************************************
        Update
        ****************************************
        */

        if (points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            int numOfPointsMade = 0;
            while (numOfPointsMade < 10)
            {
                random_device rd;
                uniform_int_distribution<int> dist(0, 2);
                int randVertexSelect = dist(rd);;
                Vector2f randVertex = vertices.at(randVertexSelect);
                //select last point in vector
                Vector2f lastPoint = points.back();
                ///calculate midpoint between random vertex and the last point in the vector
                int midPoint_x = (randVertex.x + lastPoint.x) / 2;
                int midPoint_y = (randVertex.y + lastPoint.y) / 2;
                ///push back the newly generated coord.
                points.push_back(Vector2f(midPoint_x, midPoint_y));
                cout << "point generated at" << midPoint_x << ", " << midPoint_y << "from Vertex " << randVertexSelect << endl;
                numOfPointsMade++;
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();
        //display the instruction text
        window.draw(instructionText);
        //display the 3 intial points of verticies as blue
        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }
        //display the point generated as red
        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(1, 1));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }
        window.display();
    }
}
