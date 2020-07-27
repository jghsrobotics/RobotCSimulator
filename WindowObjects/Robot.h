#pragma once
#include <SFML\Graphics.hpp>
#include "../Utility/TextureSprite.h"
#include "../Utility/DeltaClock.h"
#include "../stdafx.h"
#include "../RobotC.h"

using namespace RobotC::Peripherals;
using namespace RobotC::Types;



class Robot : public TextureSprite {
public:

	Robot() : SPEED(50), renderICC(false) {
		LoadTextureFromFile("Assets/Clawbot.png");
		SetRectSize(sf::Vector2f(50, 100));

		// Origin defines the midpoint of the wheels. 
		setOrigin(sf::Vector2f(rectangleShape.getLocalBounds().width / 2, rectangleShape.getLocalBounds().height / 2));
		setPosition(sf::Vector2f(1000, 500));
	};

	float GetRadians() {
		return getRotation() * (M_PI / 180.0f);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		TextureSprite::draw(target, states);

		if(renderICC) {
			sf::CircleShape ICC;
			ICC.setRadius(2.0f);
			ICC.setOrigin(sf::Vector2f(2.0f, 2.0f));
			ICC.setPosition(ICCPosition);
			ICC.setFillColor(sf::Color::Red);
			target.draw(ICC);
		}
	}

	void ImGuiDraw() override {
		auto delta = DeltaClock::GetDelta();
		ImGui::Begin("Robot");
		ImGui::Text("Position x (px): %g", getPosition().x);
		ImGui::Text("Position y (px): %g", getPosition().y);
		ImGui::Text("Velocity (px/s): %g", sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) / delta);
		ImGui::Checkbox("Render ICC: ", &renderICC);
		ImGui::End();
	}

	void Update() override {
		auto delta = DeltaClock::GetDelta();

		// Scale raw motor values down to emulate speed
		float leftMotorValue =  (motor[leftMotorPort] / 127.0f)  * SPEED;
		float rightMotorValue = (motor[rightMotorPort] / 127.0f) * SPEED;

		sf::Vector2f position = getPosition();

		if(abs(rightMotorValue - leftMotorValue) >= 2) {
			float L = rectangleShape.getLocalBounds().width;
			float R = (L / 2) * ((leftMotorValue + rightMotorValue) / (rightMotorValue - leftMotorValue));
			float rotationalSpeed = (rightMotorValue - leftMotorValue) / L;
		
			ICCPosition.x = getPosition().x + (sin(GetRadians()) * R);
			ICCPosition.y = getPosition().y - (cos(GetRadians()) * R);

			setRotation(getRotation() - (rotationalSpeed * delta * 360));

			position.x = ICCPosition.x + (-sin(GetRadians()) * R);
			position.y = ICCPosition.y + (cos(GetRadians()) * R);

			velocity.x = position.x - getPosition().x;
			velocity.y = position.y - getPosition().y;
		}
		else {
			position.x += (leftMotorValue * cos(GetRadians()) * delta) * 5;
			position.y += (leftMotorValue * sin(GetRadians()) * delta) * 5;

			velocity.x = position.x - getPosition().x;
			velocity.y = position.y - getPosition().y;
		}
		setPosition(position);
	};

private:
	MotorPort leftMotorPort = port1;
	MotorPort rightMotorPort = port5;

	sf::Vector2f ICCPosition;
	sf::Vector2f velocity;

	bool renderICC;

	const int SPEED;
};