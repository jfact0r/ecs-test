/* Includes ***************************************************************************************/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <map>
#include <iostream>

#include "Engine/Engine.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Comps/CInput.hpp"

#include "CInputTester.hpp"
#include "CQuitter.hpp"

/* Using ******************************************************************************************/
using namespace engine;
using namespace std;
using namespace game;

/*
** Entry point of the application.
*/
int main(int argc, char** argv) {
	// Setup Engine
	Engine engine = Engine::GetEngine();
	engine.SetTitle("Hello World");

	// Setup Entities
	Entity *e = new Entity();

	e->GetValueProp<int>("Health", 100);
	e->GetValueProp<int>("Ammo", 40);
	e->GetValueProp<const string>("Name", "Monster");
	e->GetMessageProp<int>("Test");

	CInput *c1 = new CInput();
	CInput *c2 = new CInput();

	e->AddComp(c1);
	e->AddComp(c2);

	// Debug test
	cout << *e << endl;

	std::string name;
	Prop *prop;
	do {
		cout << "Enter a property name:" << endl;
		cin >> name;
	} while (!(prop = e->FindProp(name)));

	cout << "= " << *prop << endl;

	cout << sizeof string << endl;
	cout << sizeof ValueProp<int> << endl;

	// Run
	engine.Run();

	/*Entity *e = new Entity();

	Prop* prop;

	e->GetValueProp<int>("Health", 100);
	e->GetValueProp<int>("Ammo", 40);
	e->GetValueProp<const string>("Name", "Monster");
	e->GetMessageProp<int>("Test");

	CInput *c1 = new CInput();
	CInput *c2 = new CInput();

	e->AddComp(c1);
	e->AddComp(c2);

	cout << *e << endl;

	std::string name;

	do {
		cout << "Enter a property name:" << endl;
		cin >> name;
	} while (!(prop = e->FindProp(name)));


	cout << "= " << *prop << endl;

	cout << sizeof string << endl;
	cout << sizeof ValueProp<int> << endl;

	// Defines PI
	const float PI = 3.14159f;

    // Create the window of the application
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Pong");

    // Load the sounds used in the game
    sf::SoundBuffer BallSoundBuffer;
    if (!BallSoundBuffer.LoadFromFile("data/pong/ball.wav"))
    {
        return EXIT_FAILURE;
    }
    sf::Sound BallSound(BallSoundBuffer);

    // Load the images used in the game
    sf::Image BackgroundImage, LeftPaddleImage, RightPaddleImage, BallImage;
    if (!BackgroundImage.LoadFromFile("data/pong/background.jpg")    ||
        !LeftPaddleImage.LoadFromFile("data/pong/paddle_left.png")   ||
        !RightPaddleImage.LoadFromFile("data/pong/paddle_right.png") ||
        !BallImage.LoadFromFile("data/pong/ball.png"))
    {
        return EXIT_FAILURE;
    }

    // Load the text font
    sf::Font Cheeseburger;
    if (!Cheeseburger.LoadFromFile("data/post-fx/cheeseburger.ttf"))
        return EXIT_FAILURE;

	// Initialize the end text
	sf::String End;
    End.SetFont(Cheeseburger);
	End.SetSize(60.f);
    End.Move(150.f, 200.f);
    End.SetColor(sf::Color(50, 50, 250));

    // Create the sprites of the background, the paddles and the ball
    sf::Sprite Background(BackgroundImage);
    sf::Sprite LeftPaddle(LeftPaddleImage);
    sf::Sprite RightPaddle(RightPaddleImage);
    sf::Sprite Ball(BallImage);

    LeftPaddle.Move(10, (App.GetView().GetRect().GetHeight() - LeftPaddle.GetSize().y) / 2);
    RightPaddle.Move(App.GetView().GetRect().GetWidth() - RightPaddle.GetSize().x - 10, (App.GetView().GetRect().GetHeight() - RightPaddle.GetSize().y) / 2);
    Ball.Move((App.GetView().GetRect().GetWidth() - Ball.GetSize().x) / 2, (App.GetView().GetRect().GetHeight() - Ball.GetSize().y) / 2);

    // Define the paddles properties
    sf::Clock AITimer;
	const float AITime     = 0.1f;
    float LeftPaddleSpeed  = 400.f;
    float RightPaddleSpeed = 400.f;

    // Define the ball properties
    float BallSpeed = 300.f;
    float BallAngle;
    do
    {
        // Make sure the ball initial angle is not too much vertical
        BallAngle = sf::Randomizer::Random(0.f, 2 * PI);
    } while (std::abs(std::cos(BallAngle)) < 0.7f);

	bool IsPlaying = true;
    while (App.IsOpened())
    {
        // Handle events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Window closed or escape key pressed : exit
            if ((Event.Type == sf::Event::Closed) || 
               ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)))
            {
                App.Close();
                break;
            }
        }

        if (IsPlaying)
		{
			// Move the player's paddle
            if (App.GetInput().IsKeyDown(sf::Key::Up) && (LeftPaddle.GetPosition().y > 5.f))
				LeftPaddle.Move(0.f, -LeftPaddleSpeed * App.GetFrameTime());
            if (App.GetInput().IsKeyDown(sf::Key::Down) && (LeftPaddle.GetPosition().y < App.GetView().GetRect().GetHeight() - LeftPaddle.GetSize().y - 5.f))
				LeftPaddle.Move(0.f, LeftPaddleSpeed * App.GetFrameTime());

			// Move the computer's paddle
            if (((RightPaddleSpeed < 0.f) && (RightPaddle.GetPosition().y > 5.f)) ||
                ((RightPaddleSpeed > 0.f) && (RightPaddle.GetPosition().y < App.GetView().GetRect().GetHeight() - RightPaddle.GetSize().y - 5.f)))
            {
                RightPaddle.Move(0.f, RightPaddleSpeed * App.GetFrameTime());
            }

            // Update the computer's paddle direction according to the ball position
            if (AITimer.GetElapsedTime() > AITime)
            {
                AITimer.Reset();
                if ((RightPaddleSpeed < 0) && (Ball.GetPosition().y + Ball.GetSize().y > RightPaddle.GetPosition().y + RightPaddle.GetSize().y))
                    RightPaddleSpeed = -RightPaddleSpeed;
                if ((RightPaddleSpeed > 0) && (Ball.GetPosition().y < RightPaddle.GetPosition().y))
                    RightPaddleSpeed = -RightPaddleSpeed;
            }

			// Move the ball
			float Factor = BallSpeed * App.GetFrameTime();
            Ball.Move(std::cos(BallAngle) * Factor, std::sin(BallAngle) * Factor);

			// Check collisions between the ball and the screen
			if (Ball.GetPosition().x < 0.f)
			{
				IsPlaying = false;
				End.SetText("You lost !\n(press escape to exit)");
			}
			if (Ball.GetPosition().x + Ball.GetSize().x > App.GetView().GetRect().GetWidth())
			{
				IsPlaying = false;
				End.SetText("You won !\n(press escape to exit)");
			}
			if (Ball.GetPosition().y < 0.f)
			{
				BallSound.Play();
				BallAngle = -BallAngle;
				Ball.SetY(0.1f);
			}
			if (Ball.GetPosition().y + Ball.GetSize().y > App.GetView().GetRect().GetHeight())
			{
				BallSound.Play();
				BallAngle = -BallAngle;
				Ball.SetY(App.GetView().GetRect().GetHeight() - Ball.GetSize().y - 0.1f);
			}

			// Check the collisions between the ball and the paddles
			// Left Paddle
			if (Ball.GetPosition().x < LeftPaddle.GetPosition().x + LeftPaddle.GetSize().x && 
				Ball.GetPosition().x > LeftPaddle.GetPosition().x + (LeftPaddle.GetSize().x / 2.0f) &&
				Ball.GetPosition().y + Ball.GetSize().y >= LeftPaddle.GetPosition().y &&
				Ball.GetPosition().y <= LeftPaddle.GetPosition().y + LeftPaddle.GetSize().y)
			{
				BallSound.Play();
				BallAngle = -PI / 4.0f;
				BallAngle +=
					(Ball.GetPosition().y + Ball.GetSize().y/2.0f  - LeftPaddle.GetPosition().y)
					/  LeftPaddle.GetSize().y * PI/2.0f;
				Ball.SetX(LeftPaddle.GetPosition().x + LeftPaddle.GetSize().x + 0.1f);

				BallSpeed += 20.0f;
			}

			// Right Paddle
			if (Ball.GetPosition().x + Ball.GetSize().x > RightPaddle.GetPosition().x &&
				Ball.GetPosition().x + Ball.GetSize().x < RightPaddle.GetPosition().x + (RightPaddle.GetSize().x / 2.0f) &&
				Ball.GetPosition().y + Ball.GetSize().y >= RightPaddle.GetPosition().y &&
				Ball.GetPosition().y <= RightPaddle.GetPosition().y + RightPaddle.GetSize().y)
			{
				BallSound.Play();
				BallAngle = PI / 4.0f;
				BallAngle +=
					(Ball.GetPosition().y + Ball.GetSize().y/2.0f  - RightPaddle.GetPosition().y)
					/  RightPaddle.GetSize().y * PI/2.0f;
				Ball.SetX(RightPaddle.GetPosition().x - Ball.GetSize().x - 0.1f);

				BallSpeed += 20.0f;
			}
		}

        // Clear the window
        App.Clear();

        // Draw the background, paddles and ball sprites
        App.Draw(Background);
        App.Draw(LeftPaddle);
        App.Draw(RightPaddle);
        App.Draw(Ball);

        // If the game is over, display the end message
        if (!IsPlaying)
            App.Draw(End);

        // Display things on screen
        App.Display();
    }*/

    return EXIT_SUCCESS;
}