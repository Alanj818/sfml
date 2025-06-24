#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({600u, 500u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    window.setMinimumSize(window.getSize());
    
    
    sf::CircleShape circle(50.f);
    circle.setPosition({0.f, 0.f});
    sf::RectangleShape rectangle({100.f, 100.f}); 
    rectangle.setPosition({50.f, 200.f});
    
    
    
    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }
        }
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;
        float speed = 1.0f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            circle.move({speed, 0.f});

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            circle.move({-speed, 0.f});
            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            circle.move({0.f, -speed});
            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            circle.move({0.f, speed});
            
        }

        //movement for Rectange
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            rectangle.move({speed, 0.f});

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            rectangle.move({-speed, 0.f});
            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            rectangle.move({0.f, -speed});
            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            rectangle.move({0.f, speed});
            
        }
        
        
        //work on collision with circle and rectangle
        //The idea is that from the center of the sqaure, or base/2, and the radias of the circle both added are ever less
        //than they expell each other 
        const float Cx = circle.getPosition().x;
        const float Cy = circle.getPosition().y; 
        const float radi = circle.getRadius();
        circle.setOrigin({radi, radi});
        circle.setPosition({mouseX, mouseY});
        

        const float Sx = rectangle.getPosition().x; 
        const float Sy = rectangle.getPosition().y; 
        const float Sw = rectangle.getSize().x;
        const float Sh = rectangle.getSize().y;
        float distX = 0;
        float distY = 0;
        float acel = 0.8f;
        sf::Clock clock;


        //i want to try and implement a acceleration vector and a velocity vector
        float svx; 
        float svy; 
        float sax; 
        float say; 
        auto t = clock.getElapsedTime();
        
        std::cout << Cx << " + " << Cy << '\n' << std::endl;

        //con left side
        if(Cx < Sx)
        {
            //upper corner
            if(Cy < Sy)
            {
                distX = Sx - Cx;
                distY = Sy - Cy;
                float colliDist = sqrt((distX*distX) + (distY*distY));
                std::cout << colliDist << std::endl;

                if(colliDist <= radi)
                {
                    float displacement = radi - colliDist;
                    // circle.setPosition({(Cx - displacement), (Cy - displacement)});
                    // circle.setPosition({mouseX - displacement, mouseY - displacement});
                    //rectangle.setPosition({(Cx + displacement), (Cy + displacement)});
                    rectangle.setPosition({Sx + displacement, Sy + displacement});
                }
            }
            
            //lower Corner
            if(Cy > Sy + Sh)
            {
                distX = Sx - Cx;
                distY = (Sy + Sh) - Cy;
                float colliDist = sqrt((distX*distX) + (distY*distY));
                std::cout << colliDist << std::endl;

                if(colliDist <= radi)
                {
                    float displacement = radi - colliDist;
                    // circle.setPosition({(Cx - displacement), (Cy + displacement)});
                    // circle.setPosition({mouseX - displacement, mouseY + displacement});
                    rectangle.setPosition({(Sx + displacement), (Sy - displacement)});
                }
            }

            //in between
            if(Cy > Sy && Cy < Sy + Sh)
            {
                distX = Sx - Cx; 
                distY = Sy - Sy; 
                float colliDist = sqrt((distX*distX) + (distY*distY));
                std::cout << colliDist << std::endl;

                if(colliDist <= radi)
                {
                    float displacement = radi - colliDist;
                    // circle.setPosition({(Cx - displacement), (Cy)});
                    // circle.setPosition({mouseX - displacement, mouseY});
                    rectangle.setPosition({(Sx + displacement), (Sy)});
                }
            }
        }
        //on right side
        if(Cx > Sx + Sw)
        {
            //upper corner
            if(Cy < Sy)
            {
                distX = (Sx + Sw) - Cx; 
                distY = Sy - Cy; 
                float colliDist = sqrt((distX*distX) + (distY*distY));
                std::cout << colliDist << std::endl;

                if(colliDist <= radi)
                {
                    float displacement = radi - colliDist;
                    // circle.setPosition({(Cx + displacement), (Cy - displacement)});
                    // circle.setPosition({mouseX + displacement, mouseY - displacement});
                    rectangle.setPosition({(Sx - displacement), (Sy + displacement)});
                }
            }
            
            //lower Corner
            if(Cy > Sy + Sh)
            {
                distX = (Sx + Sw) - Cx; 
                distY = (Sy + Sh) - Cy; 
                float colliDist = sqrt((distX*distX) + (distY*distY));
                std::cout << colliDist << std::endl;

                if(colliDist <= radi)
                {
                    float displacement = radi - colliDist;
                    // circle.setPosition({(Cx + displacement), (Cy + displacement)});
                    // circle.setPosition({mouseX + displacement, mouseY + displacement});
                    rectangle.setPosition({(Sx - displacement), (Sy - displacement)});
                }
            }
            //in between
            if(Cy < Sy + Sh && Cy > Sy)
            {
                distX = (Sx + Sw) - Cx; 
                distY = Sy - Sy; 
                float colliDist = sqrt((distX*distX) + (distY*distY));
                std::cout << colliDist << std::endl;

                if(colliDist <= radi)
                {
                    float displacement = radi - colliDist;
                    // circle.setPosition({(Cx + displacement), (Cy)});
                    // circle.setPosition({mouseX + displacement, mouseY});
                    rectangle.setPosition({(Sx - displacement), (Sy)});
                }
            }
        }
        //on top
        if(Cx > Sx && Cx < (Sx + Sw) && Cy < Sy)
        {
            distX = Cx - Cx; 
            distY = Sy - Cy; 
            float colliDist = sqrt((distX*distX) + (distY*distY));
            std::cout << colliDist << std::endl;

            if(colliDist <= radi)
            {
                float displacement = radi - colliDist;
                // circle.setPosition({(Cx), (Cy - displacement)});
                // circle.setPosition({mouseX, mouseY - displacement});
                rectangle.setPosition({(Sx), (Sy + displacement)});
            }
        }
        //on bottom 
        if(Cx > Sx && Cx < Sx + Sw && Cy > Sy + Sh)
        {
            distX = Cx - Cx; 
            distY = (Sy + Sh) - Cy; 
            float colliDist = sqrt((distX*distX) + (distY*distY));
            std::cout << colliDist << std::endl;

            if(colliDist <= radi)
            {
                float displacement = radi - colliDist;
                // circle.setPosition({(Cx), (Cy + displacement)});
                // circle.setPosition({mouseX, mouseY + displacement});
                rectangle.setPosition({(Sx), (Sy - displacement)});
            }
        }

        window.clear();
        //here is where we draw
        
        window.draw(circle);
        window.draw(rectangle);
        window.draw(rectangle);

        window.display();
    }
}
