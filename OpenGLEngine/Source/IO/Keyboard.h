#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Keyboard
{
public:
	// Key state callback
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	// Accessors
	static bool Key(int key);

	static bool KeyChanged(int key);

	static bool IsKeyUp(int key);

	static bool IsKeyDown(int key);

private:
	static bool keys[];
	static bool keysChanged[];
};

#endif