#pragma once

// ���̓{�^���̎��
enum class InputID
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LROLL,
	RROLL,
	SPACE,
	MAX
};

// ���̓g���K�[
enum class Trg
{
	Now,
	Old,
	MAX
};

static InputID begin(InputID) 
{
	return InputID::LEFT;
}
static InputID end(InputID)
{
	return InputID::MAX;
}
static InputID operator++(InputID& id)
{
	return (id = InputID
	(std::underlying_type<InputID>::type(id) + 1));
}
static InputID operator*(InputID id)
{
	return id;
}