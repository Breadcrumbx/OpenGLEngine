#include "Mouse.h"

double Mouse::x = 0;
double Mouse::y = 0;

double Mouse::lastX = 0;
double Mouse::lastY = 0;

double Mouse::dy = 0;
double Mouse::dx = 0;

double Mouse::scrollDX = 0;
double Mouse::scrollDY = 0;

bool Mouse::firstMouse = true;

bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = { 0 };

void Mouse::CursorPositionCallback(GLFWwindow* window, double _x, double _y)
{
	x = _x;
	y = _y;

	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	dx = x - lastX;
	dy = lastY - y; // Inverted as top left is ( 0 , 0 )

	lastX = x;
	lastY = y;

}

void Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action != GLFW_RELEASE)
	{
		if (!buttons[button])
		{
			buttons[button] = true;
		}
	}
	else
		buttons[button] = false;

	buttonsChanged[button] = action != GLFW_REPEAT;
}

void Mouse::MouseWheelCallback(GLFWwindow* window, double _dx, double _dy)
{
	scrollDX = _dx;
	scrollDY = _dy;
}

double Mouse::GetMouseX()
{
	return x;
}

double Mouse::GetMouseY()
{
	return y;
}

double Mouse::GetMouseDX()
{
	double _dx = dx;
	dx = 0;
	return _dx;
}

double Mouse::GetMouseDY()
{
	double _dy = dy;
	dy = 0;
	return _dy;
}

double Mouse::GetMouseScrollDX()
{
	double _dx = scrollDX;
	scrollDX = 0;
	return _dx;
}

double Mouse::GetMouseScrollDY()
{
	double _dy = scrollDY;
	scrollDY = 0;
	return _dy;
}

bool Mouse::Button(int button)
{
	return false;
}

bool Mouse::ButtonChanged(int button)
{
	return false;
}

bool Mouse::IsButtonUp(int button)
{
	return false;
}

bool Mouse::IsButtonDown(int button)
{
	return false;
}
