#include "EngineView.h"
//#include <functional>
//#include <glfw3.h>

EngineView::EngineView( EngineModel& model,  Display& display,  Renderer& renderer): model(model),
                                                                                                    display(display),
                                                                                                    renderer(renderer)
{
	glfwSetKeyCallback(renderer.window, key_callback);
}

void EngineView::key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS && keyPressedListeners.find(key) != keyPressedListeners.end())
	{
		keyPressedListeners.at(key)();
	}
	else if (action == GLFW_RELEASE && keyReleasedListeners.find(key) != keyReleasedListeners.end())
	{
		keyReleasedListeners.at(key)();
	}
}

EngineView::~EngineView()
{
}

void EngineView::addKeyPressedListener(Key GLFW_KEY, std::function<void()> listener)
{
	keyPressedListeners[GLFW_KEY] = listener;
}
void EngineView::addKeyReleasedListener(Key GLFW_KEY, std::function<void()> listener)
{
	keyReleasedListeners[GLFW_KEY] = listener;
}
void EngineView::removeKeyPressedListener(Key GLFW_KEY)
{
	if (keyPressedListeners.find(GLFW_KEY) != keyPressedListeners.end())
	{
		keyPressedListeners.erase(GLFW_KEY);
	}
}

void EngineView::removeKeyReleasedListener(Key GLFW_KEY)
{
	if (keyReleasedListeners.find(GLFW_KEY) != keyReleasedListeners.end())
	{
		keyReleasedListeners.erase(GLFW_KEY);
	}
}

void EngineView::update()
{
	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	glfwPollEvents();


	//TODO generate display
	renderer.render(this->display);
}