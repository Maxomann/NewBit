#include "GuiEngine.h"
using namespace std;
using namespace sf;
using namespace tgui;
using namespace nb;

void nb::GuiEngine::init()
{
	r_graphicsEngine = getCore()->engines.getEngine<GraphicsEngine>();
	m_gui.setWindow( r_graphicsEngine->getWindow() );

	r_graphicsEngine->s_beforeDisplay.connect( [&]( sf::RenderWindow& window ) {
		m_gui.draw();
	} );
	cout << "init" << endl;
}

bool nb::GuiEngine::update()
{
	return true;
}
