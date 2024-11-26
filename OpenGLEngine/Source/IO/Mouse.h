#ifndef MOUSE_H
#define MOUSE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mouse
{
public:
	// Callbacks
	static void CursorPositionCallback(GLFWwindow* window, double _x, double _y);

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	static void MouseWheelCallback(GLFWwindow* window, double _dx, double _dy);

	// Accessors

	static double GetMouseX();

	static double GetMouseY();

	static double GetMouseDX();

	static double GetMouseDY();

	static double GetMouseScrollDX();

	static double GetMouseScrollDY();

	static bool Button(int button);

	static bool ButtonChanged(int button);

	static bool IsButtonUp(int button);

	static bool IsButtonDown(int button);

private:
	static double x;
	static double y;

	static double lastX;
	static double lastY;

	static double dx;
	static double dy;

	static double scrollDX;
	static double scrollDY;

	static bool firstMouse;

	static bool buttons[];
	static bool buttonsChanged[];
};
#endif

