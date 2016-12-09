#include "EngineController.h"
#include "EngineModel.h"
#include "EngineView.h"
#include "main.h"

int main() {
	
	EngineModel model = EngineModel();
	EngineView view = EngineView(&model);

	EngineController controller = EngineController(&view, &model);
}