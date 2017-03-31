#include "TestEngine.h"
#include "GraphicsEngine.h"
#include "InputEngine.h"
#include "ResourceEngine.h"
#include "InitEngine.h"
#include "WorldGenerationEngine.h"
#include "GuiEngine.h"

using namespace std;

extern "C" {
	DLL_EXPORT void nbConnectCore( nb::CoreEngineManager* manager )
	{
		manager->addEngine<nb::InitEngine>();

		manager->addEngine<nb::ResourceEngine>();
		manager->addEngine<nb::TestEngine>();
		manager->addEngine<nb::GraphicsEngine>();
		manager->addEngine<nb::GuiEngine>(); // before InputEngine (due to signal callbacks from GraphicsEngine)
		manager->addEngine<nb::InputEngine>();

		manager->addEngine<nb::WorldGenerationEngine>();
	}
}
