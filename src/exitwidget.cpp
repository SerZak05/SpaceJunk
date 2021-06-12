#include "exitwidget.h"
#include "actionmanager.h"

ExitWidget::ExitWidget(UI* ui) : Widget(ui) {
	ActionManager::getInst()->userEventLoop.subscribe(this);
}

void ExitWidget::processEvent(const InputEvent*) {
	ui->eventLoop.pushEvent(new Event(EXIT_EVENT));
}

std::list<InputEventType> ExitWidget::acceptTypes() const
{
	return {InputEventType::QUIT};
}
