#include <sstream>
#include <SFML/Graphics.hpp>

const sf::Keyboard::Key controls[4] = {
    sf::Keyboard::A,  //Player1 UP
    sf::Keyboard::Z,  //Player1 DOWN
    sf::Keyboard::Up, //Player2 UP
    sf::Keyboard::Down//Player2 Down
};

//Parameters
const sf::Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float time_step = 0.017f; //60fps

// Objects of the game
sf::CircleShape ball;
sf::RectangleShape paddles[2];

void init() {
    // Set size and origin of paddles
    for (sf::RectangleShape& p : paddles) {
        p.setSize(paddleSize);
        p.setOrigin(paddleSize / 2.f);
    }

    // Set size ad origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius, ballRadius); // Half width and height (center)

    //reset paddle position
    paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f); // Left paddle
    paddles[1].setPosition(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f); // Right paddle

    //reset Ball Position
    ball.setPosition(gameWidth / 2.f, gameHeight / 2.f); //Center
}

void update(float dt) {
    //Player 1 movement
    float dir1 = 0.0f;
    if (sf::Keyboard::isKeyPressed(controls[0])) dir1 -= 1.f; 
    if (sf::Keyboard::isKeyPressed(controls[1])) dir1 += 1.f;
    paddles[0].move(0.f, dir1 * paddleSpeed * dt);

    //Player 2 movement
    float dir2 = 0.f;
    if (sf::Keyboard::isKeyPressed(controls[2])) dir2 -= 1.f;
    if (sf::Keyboard::isKeyPressed(controls[3])) dir2 += 1.f;
    paddles[0].move(0.f, dir2 * paddleSpeed * dt);

    //Optional: limit paddles so they dont move off-screen
    for (sf::RectangleShape& p : paddles) {
        sf::Vector2f pos = p.getPosition();
        if (pos.y - paddleSize.y / 2.f < 0)
            p.setPosition(pos.x, paddleSize.y / 2.f);
        else if (pos.y + paddleSize.y / 2.f > gameHeight)
            p.setPosition(pos.x, gameHeight - paddleSize.y / 2.f);
    }
}
 

void render(sf::RenderWindow& window) {
    // Draw everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

void clean() {
    //free up the memory if necessary.
}

int main() {
    //create the window
    sf::RenderWindow window(sf::VideoMode({ gameWidth, gameHeight }), "PONG");

    //initialise and load
    init();

    sf::Clock clock;

    //Game loop
    while (window.isOpen()) {
        // Handle window events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Calculate dt (delta time)
        float dt = clock.restart().asSeconds();

        //Update and render
        window.clear();
        update(dt);
        render(window);
        window.display();

        //wait for the time_step to finish before displaying the next frame.
        sf::sleep(sf::seconds(time_step));
    }
    
    //Unload and shutdown
    clean();
    return 0;
}