#include "TestEngine.h"
#include "RenderEngine.h"
#include "InputEngine.h"

using namespace std;

extern "C" {
	DLL_EXPORT void nbConnectCore( nb::CoreEngineManager* manager )
	{
		manager->addEngine<nb::TestEngine>();
		manager->addEngine<nb::RenderEngine>();
		manager->addEngine<nb::InputEngine>();
	}
}
