#include "Player.h"
#include "../Level.h"
#include "../../LD32Application.h"

using namespace sparky;
using namespace maths;

Player::Player(float x, float y, sparky::graphics::Window* window)
	: Entity(x, y), m_Window(window), m_Speed(4.0f), m_Gravity(1.5f), m_MaxVerticalVelocity(24.0f), m_CanDoubleJump(true),
	m_SelectedItem(1), m_Group(new graphics::Group(mat4::identity())), m_Transformation(m_Group->getTransformRef()),
	m_Score(0), m_ShieldFall(false)
{
	m_Sprite = new graphics::Sprite(0, 0, 64, 64, graphics::TextureManager::get("Player"));
	m_Delta = maths::vec2(0, 0);
	m_ScreenPos = vec3(0, 0, 0);

	audio::SoundManager::add(new audio::Sound("Jump", "res/audio/jump.ogg"));
	m_Items.push_back(new Shield(this));

	m_Transformation = mat4::translation(m_Position);
	m_Group->add(m_Sprite);

	for (Item* item : m_Items)
	{
		m_Group->add(item->getSprite());
	}

	m_Renderable = m_Group;
	m_Type = PLAYER;
}

void Player::update()
{
	if (!State::isGameOver())
	{
		if (m_Window->isKeyPressed(GLFW_KEY_A))
		{
			if (m_Delta.x > -m_Speed)
				m_Delta.x -= 2.5f;
		}
		else if (m_Window->isKeyPressed(GLFW_KEY_D))
		{
			if (m_Delta.x < m_Speed)
				m_Delta.x += 2.5f;
		}

		if (m_Window->isKeyPressed(GLFW_KEY_W) && m_JumpTimer > 0.1f)
		{
			m_Delta.y = 12.0;
		}

		if (m_Window->isKeyTyped(GLFW_KEY_SPACE) && m_JumpTimer < 6.0f && m_CanDoubleJump)
		{
			m_Delta.y = 50.0f;
			m_CanDoubleJump = false;
		}
	}
	float xa = m_Delta.x;
	float ya = m_Delta.y;
	if (m_ShieldFall && ya < -5.0f)
		ya = -5.0f;
	move(xa, ya);

// 	if (m_Window->isKeyTyped(GLFW_KEY_W))
// 		audio::SoundManager::get("Jump")->play();

	if (m_Delta.x < 0.0f)
		m_Delta.x += 0.85f;
	else if (m_Delta.x > 0.0f)
		m_Delta.x -= 0.85f;

	if (m_Delta.x < 0.85f && m_Delta.x > -0.85f)
		m_Delta.x = 0.0f;

	m_Delta.y -= m_Gravity;

	if (m_Delta.y < -m_MaxVerticalVelocity)
		m_Delta.y = -m_MaxVerticalVelocity;

	if (m_Delta.y > m_MaxVerticalVelocity)
		m_Delta.y = m_MaxVerticalVelocity;

	if (m_CollisionDirection == BOTTOM)
	{
		m_JumpTimer = 6.0f;
		m_CanDoubleJump = true;
	}
	else
		m_JumpTimer -= 0.5f;

	const vec2& offset = m_Level->getOffset();
	if (m_Position.x - offset.x + xa > 766)
	{
		float x = m_Position.x - 766;
		m_Level->setOffset(vec2(x, 0));
	}
	else if (m_Position.x - offset.x + xa < 350)
	{
		float x = m_Position.x - 350;
		m_Level->setOffset(vec2(x, 0));
	}

	if (m_Window->isKeyTyped(GLFW_KEY_F))
		m_Level->generatePlatforms(1);

	if (m_SelectedItem > 0)
	{
		Item* item = m_Items[m_SelectedItem - 1];
		item->update();
	}

	if (m_Position.y < 0)
		State::setGameOver(true);

}

void Player::shoot()
{
	const maths::vec2& mouse = m_Window->getMousePosition();

	float angle = atan2(m_Window->getHeight() - mouse.y - m_ScreenPos.y - 32, mouse.x - m_ScreenPos.x - 32);
	m_Level->addProjectile(new TimeProjectile(m_Position.x + 32, m_Position.y + 32, angle, this));
}

void Player::render()
{
	const maths::vec2& offset = m_Level->getOffset();
	m_Transformation = mat4::translation(vec3(m_Position.x - offset.x, m_Position.y - offset.y, 0.0f));
	m_ScreenPos = vec3(m_Position.x - offset.x, m_Position.y - offset.y, 0.0f);

	if (m_SelectedItem > 0 && !State::isGameOver())
	{
		Item* item = m_Items[m_SelectedItem - 1];
		if (item->getType() == SHIELD)
		{
			Shield* shield = (Shield*)item;
			const maths::vec2& mouse = m_Window->getMousePosition();
			float angle = atan2(m_Window->getHeight() - mouse.y - m_ScreenPos.y - 32, mouse.x - m_ScreenPos.x - 32) - M_PI / 2.0f;
			shield->setAngle(angle);
			if (angle > -M_PI - 0.5f && angle < -M_PI + 0.5f)
				m_ShieldFall = true;
			else
				m_ShieldFall = false;
		}
		item->render();
	}
#if 0
	LD32Application::debugLayer->text(0) = "Pos: " + std::to_string(m_Position.x) + ", " + std::to_string(m_Position.y);
	LD32Application::debugLayer->text(1) = "Delta: " + std::to_string(m_Delta.x) + ", " + std::to_string(m_Delta.y);
	LD32Application::debugLayer->text(2) = "Level Offset: " + std::to_string(offset.x) + ", " + std::to_string(offset.y);
#endif
	if (m_Health < 0)
	{
		State::setGameOver(true);
		m_Health = 0.0f;
	}
	LD32Application::debugLayer->text(0) = std::to_string((int)m_Health) + "%";
	LD32Application::debugLayer->text(1) = std::to_string((int)m_Score);
}

void Player::setPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Player::addScore(unsigned int score)
{
	m_Score += score;
}
