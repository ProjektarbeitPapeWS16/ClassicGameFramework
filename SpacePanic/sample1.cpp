#pragma once

#include "SpacePanicModel.h"
#include "SpacePanicView.h"
#include "SpacePanicController.h"

#include "Session.h"
#include "Display.h"
#include "Renderer.h"

int main() {
	Session session;
	Physics physics;
	std::vector<Level> levels;
	Display display;
	Renderer renderer;

	levels.push_back(Level(15, 20, "level1.txt", physics));
	levels.push_back(Level(15, 20, "level2.txt", physics));
	levels.push_back(Level(15, 20, "level3.txt", physics));

	auto model = SpacePanicModel(session, physics);
	auto view = SpacePanicView(model, display, renderer);
	auto controller = SpacePanicController(view, model);

	controller.gameLoop();

	return 0;
}

