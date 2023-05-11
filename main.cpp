#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#define windowWidth  800
#define windowHeight 600


class AnimatedSprite : public sf::Sprite {
public:
    AnimatedSprite(const int fps, const std::string& path) : fps_(fps) //make an initializer list for fps_
    {

        if (!texture_.loadFromFile(path)) {
            std::cerr << "Could not load texture" << path << std::endl;
        }
        // TODO:  set the texture here
        setTexture(texture_);
        // TODO:  set the texture rectangle here
        setTextureRect(sf::IntRect(50,0,50,37));
    }

    void setSpeed(const int& x_speed, const int& y_speed, const int & ro_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
        ro_speed_ = ro_speed;
    }

    void fall(const sf::Time &elapsed){
        float dt = elapsed.asSeconds();

        // Calculate duration of falling

        // TODO:  move(0,0);
    }




    void animate(const sf::Time &elapsed){
        bounce();
        float dt = elapsed.asSeconds();

        // TODO:  t_ is equal to t_ + dt
        t_+=+dt;
        // TODO:  if t_ became bigger than duration between two frames, then fragments_index would be added by one
        if (t_>1/fps_){
            fragments_index++;
            t_ = 0.0;
        }
        // TODO:  if fragments_index reached the end of the vector, fragments_index becaomes zero
        if(fragments_index == running_frames.size())    fragments_index=0;
        // TODO:  now setTextureRect by rectangle of the current index of the vector of rectangles
        setTextureRect(running_frames[fragments_index]);

        move(x_speed_*dt,y_speed_*dt);
    }

    void setBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        l_bound_  = l_bound  ;
        r_bound_  = r_bound  ;
        u_bound_  = u_bound  ;
        d_bound_  = d_bound  ;
    }

    void add_animation_frame(const sf::IntRect& frame){
        // TODO:  add the rectangle frame to the vector of rectangle frames
        running_frames.push_back(frame);
    }

private:
    sf::Texture texture_;
    int fps_;
    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    int ro_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;
    float t_ = 0.0;
    float t_falling = 0.0;
    unsigned int fragments_index = 0;
    // TODO: create a vector of sf::IntRect
    std::vector<sf::IntRect> running_frames;




    void bounce(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
        }

        if(rectangle_bounds.left <= l_bound_ ){
            x_speed_ = abs(x_speed_);
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_) * -1;
        }
    }


};





int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "My window");


    AnimatedSprite hero(10, "sprites/Character/character.png");
    hero.setBounds(0, window.getSize().x, 0, window.getSize().y);
    hero.setSpeed(15,15,0);


    hero.add_animation_frame(sf::IntRect(0, 0, 50, 37)); // hero standing frame 1
    hero.add_animation_frame(sf::IntRect(50, 0, 50, 37)); // hero standing frame 2
    hero.add_animation_frame(sf::IntRect(100, 0, 50, 37)); // hero standing frame 3
    hero.add_animation_frame(sf::IntRect(150, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(200, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(250, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(300, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(350, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(400, 0, 50, 37)); // hero running frame 1



    sf::Clock clock;



    // run the program as long as the window is open
    while (window.isOpen()) {
//    hero.setTextureRect(sf::IntRect(50, 0, 50, 37));
        hero.setScale(1.5,1.5);

        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // TODO:  pressing Right on keyboard would call hero.animate
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            std::cout <<"has to move"<<std::endl;
            hero.animate(elapsed);

        }
        // TODO: pressing Down on keyboard would call hero.fall
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            hero.fall(elapsed);
        }


        // bonus TO DO: when Down was released duration of falling is back to zero


        window.clear(sf::Color::Black);

        sf::Texture texture;
        if (!texture.loadFromFile("grass.png")) {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }
        sf::Sprite sprite;

        texture.setRepeated(true);
        texture.setSmooth(true);
        sf::Sprite grass(texture);
        grass.setTextureRect(sf::IntRect(0, 0, windowWidth, windowHeight));

        // draw everything here...
        window.draw(grass);
        window.draw(sprite);
        window.draw(hero);



        // end the current frame
        window.display();
    }

    return 0;
}