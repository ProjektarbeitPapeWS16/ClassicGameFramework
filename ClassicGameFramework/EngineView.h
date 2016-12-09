#pragma once

#include "KeyPressedListener.h"
#include "KeyReleasedListener.h"
#include "EngineModel.h"
#include <vector>

using namespace std;

class EngineView
{
private:
	EngineModel* model;
	vector<KeyPressedListener> keyPressedListeners;
	vector<KeyReleasedListener> keyReleasedListeners;
public:
	EngineView(EngineModel* model);
	void addKeyPressedListener(KeyPressedListener listener);
	void addKeyReleasedListener(KeyReleasedListener listener);
	~EngineView();
};

