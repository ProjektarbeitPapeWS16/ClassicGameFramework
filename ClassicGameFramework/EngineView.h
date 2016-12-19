#pragma once

#include "EngineModel.h"
#include "Renderer.h"
#include <glfw3.h>
#include <map>
#include "Config.h"
#include <functional>

using namespace std;

class EngineView
{
protected:
	EngineModel model;
	Display display;
	static map<int, function<void()>> keyPressedListeners;
	static map<int, std::function<void()>> keyReleasedListeners;
	Renderer renderer;

public:
	EngineView(const EngineModel& model, const Display& display, const Renderer& renderer);

	static void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode);

	~EngineView();


	/// <summary>
	/// Adds a key listener
	/// </summary>
	/// <param name="GLFW_KEY">The key to listen to</param>
	/// <param name="listener">An implemented listener</param>
	static void addKeyPressedListener(Key GLFW_KEY, std::function<void()> listener);

	/// <summary>
	/// Adds a key listener
	/// </summary>
	/// <param name="GLFW_KEY">The key to listen to</param>
	/// <param name="listener">An implemented listener</param>
	static void addKeyReleasedListener(Key GLFW_KEY, std::function<void()> listener);

	/// <summary>
	/// Removes a key listener
	/// </summary>
	/// <param name="GLFW_KEY">The key to stop listening to</param>
	static void removeKeyPressedListener(Key GLFW_KEY);

	/// <summary>
	/// Removes a key listener
	/// </summary>
	/// <param name="GLFW_KEY">The key to stop listening to</param>
	static void removeKeyReleasedListener(Key GLFW_KEY);

	/// <summary>
	/// Updates the view components
	/// </summary>
	void update();

};

