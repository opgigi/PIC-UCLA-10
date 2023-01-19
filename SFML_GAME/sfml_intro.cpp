#include <SFML/Graphics.hpp>



int main() {


    // creating the sf::RenderWindow object to make a window to print out the shape and background and messages what the homework instruction requires.
    // the object window has constructed as refreshing its images with the size of 400 x 400 and the title of window will be "Hello World."
    sf::RenderWindow window(sf::VideoMode(400, 400), "Hello World");

    // creating the object to set up font applied to the message
    sf::Font massage_font;

    // if the font object cannot be load from this file path, then throw the error that notify that the font file is failed to load.
    if (!massage_font.loadFromFile("comic.ttf"))
    {
        throw std::runtime_error("Font Loading Failed");
    }


    // creating the object to display the message
    sf::Text message_wants_to_show;

    // and set the font for the message object.
    message_wants_to_show.setFont(massage_font);

    // and set the color of the message
    message_wants_to_show.setFillColor(sf::Color{ 39, 116, 174, 255 });

    // set the size of the message
    message_wants_to_show.setCharacterSize(50);

    // this sets the actual content in the message object that you want to display
    message_wants_to_show.setString("PIC 10C");




    /*
        the point is that the origin is initially set on the upper left corner of the text object. then when we try to change the position of the text object, everything will be shifted its position based on the origin of the text object. therefore, the way to set the text message in the center of the window, is that we change the origin of the text object on the center of the text object not on the upper left corner.

        now I will use the getLocalBounds function to get the width and height of the message object to obtain the location of the text object right into the center.

        once you find the location of the center of the text object then use the setOrigin function to relocate its origin to the center of the text object.
     */
    message_wants_to_show.setOrigin(message_wants_to_show.getLocalBounds().width / 2, message_wants_to_show.getLocalBounds().height);


    // set the position of the text object in the center of the window object. since we relocate the origin of the text object it will go in the center of the circle object.
    message_wants_to_show.setPosition(200, 200);


    // now set the Circleshapre object and object name will be shape, and using constructor to initialize the radius of the circle and also how many side of the polygon has. I set the radius of 150 and let the shape has 100 sides on the shape.
    sf::CircleShape UCLA_gold_circle(150.f, 100.f);

    // set the color of the circleshape object and filled with UCLA gold.
    UCLA_gold_circle.setFillColor(sf::Color{ 255, 209, 0 , 255 });

    // relocate the origin of the circleshape object into the center of its object from the top left corner of the object.
    UCLA_gold_circle.setOrigin(150, 150);

    // move the origin of the circle into the center of the 400 x 400 window object.
    UCLA_gold_circle.setPosition(200, 200);

    // keep run this loop while the window object is open
    while (window.isOpen())
    {

        // create the object that controls the event in the window object.
        sf::Event event;

        /*
        The function pollEvent returns true if an event took place, placing the event details into the std::Event object; otherwise it returns false and the sf::Event object is unchanged.
        */
        while (window.pollEvent(event))
        {

            // if event object detect the window closure request, then run this condition statement.
            if (event.type == sf::Event::Closed)
            {
                // close the window object
                window.close();
            }

        }

        // sets the color of the window back ground with UCLA blue and refresh the window object.
        window.clear(sf::Color{ 39, 116, 174, 255 });

        // draw the circleshapre object on the window
        window.draw(UCLA_gold_circle);

        // print out the text object
        window.draw(message_wants_to_show);

        // Then display the window object with the circle and text object with it.
        window.display();


    }


    return 0;
}
