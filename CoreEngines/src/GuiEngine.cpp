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
	r_graphicsEngine->s_onEvent.connect( [&]( const sf::Event& sfEvent ) {
		m_gui.handleEvent( sfEvent );
	} );
}

bool nb::GuiEngine::update()
{
	return true;
}

tgui::Gui * nb::GuiEngine::getGui()
{
	return &m_gui;
}

bool nb::GuiEngine::isGuiFocused() const
{
	const auto& widgets = m_gui.getWidgets();
	return any_of( widgets.begin(), widgets.end(), [&]( const shared_ptr<Widget>& el ) {return el->isFocused(); } );
}
