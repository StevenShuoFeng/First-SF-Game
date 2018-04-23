
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"


// Create the main window
sf::RenderWindow* win; // = new window(sf::VideoMode(1280, 640), "Jessie's Escape");
sf::Music *music;

sf::Texture txtBackground;
sf::Texture txtChar;

sf::Sprite spriteBackground;
sf::Sprite spriteCharacter;
sf::Sprite* spriteCharDisp;
sf::Sprite spriteCharl, spriteCharr, spriteCharu, spriteChard;

namespace
{
    int initlize()
    {
        win = new sf::RenderWindow(sf::VideoMode(1600, 900), "Jessie's Escape");
        music = new sf::Music;
        
        // Set the Icon
        sf::Image icon;
        if (!icon.loadFromFile(resourcePath() + "icon.png")) {
            return EXIT_FAILURE;
        }
        win->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        
        // Load a music to play        
        if (!music->openFromFile(resourcePath() + "music.ogg")) {
            return EXIT_FAILURE;
        }
        
        // load textures
        if (!txtBackground.loadFromFile(resourcePath() + "background.png")){
            return EXIT_FAILURE;
        }
        
        if (!txtChar.loadFromFile(resourcePath() + "character.png")){
            return EXIT_FAILURE;
        }
        
        spriteBackground.setTexture(txtBackground);
        spriteCharacter.setTexture(txtChar);
        
        spriteCharr = spriteCharacter; spriteCharr.setTextureRect(sf::IntRect(50, 20, 90, 180));
        spriteChard = spriteCharacter; spriteChard.setTextureRect(sf::IntRect(150, 20, 120, 180));
        spriteCharl = spriteCharacter; spriteCharl.setTextureRect(sf::IntRect(280, 20, 90, 180));
        spriteCharu = spriteCharacter; spriteCharu.setTextureRect(sf::IntRect(370, 20, 120, 180));
        
        const float scaleRatioChar = 0.5f;
        spriteCharr.setScale(scaleRatioChar, scaleRatioChar);
        spriteChard.setScale(scaleRatioChar, scaleRatioChar);
        spriteCharl.setScale(scaleRatioChar, scaleRatioChar);
        spriteCharu.setScale(scaleRatioChar, scaleRatioChar);
        
        spriteCharDisp = &spriteChard;
        
        return EXIT_SUCCESS;
    }
}

void shutdown()
{
    delete music;
    delete win;
}

int main(int, char const**)
{
    if (initlize() == EXIT_FAILURE){
        shutdown();
        return EXIT_FAILURE;
    }

    // Play the music
    music->play();
    
    // Start the game loop
    while (win->isOpen())
    {
        // Process events
        sf::Event event;
        while (win->pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                win->close();
                break;
            }
            
            
            int deltaMove = 20;
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    {win->close(); continue;}
                
                if (event.key.code == sf::Keyboard::Left)
                {
                    spriteCharl.setPosition(spriteCharDisp->getPosition());
                    spriteCharDisp = &spriteCharl;
                    spriteCharDisp->move(-deltaMove,0);
                }
                
                if (event.key.code == sf::Keyboard::Right)
                {
                    spriteCharr.setPosition(spriteCharDisp->getPosition());
                    spriteCharDisp = &spriteCharr;
                    spriteCharDisp->move(deltaMove,0);
                    
                }
                
                if (event.key.code == sf::Keyboard::Up)
                {
                    spriteCharu.setPosition(spriteCharDisp->getPosition());
                    spriteCharDisp = &spriteCharu;
                    spriteCharDisp->move(0, -deltaMove);
                }
                
                if (event.key.code == sf::Keyboard::Down)
                {
                    spriteChard.setPosition(spriteCharDisp->getPosition());
                    spriteCharDisp = &spriteChard;
                    spriteCharDisp->move(0, deltaMove);
                }
            }
        }
        
        if (!win->isOpen()) continue;
        
        // Clear screen
        win->clear();

        // Draw the sprite
        win->draw(spriteBackground);
        win->draw(*spriteCharDisp);

        // Update the window
        win->display();
    }

    shutdown();
    
    return EXIT_SUCCESS;
}
