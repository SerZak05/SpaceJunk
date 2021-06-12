#include "widget.h"

#include "merrors.h"

Widget::Widget(UI* ui) :ui(ui) {}

Widget::~Widget() {
	while (!children.empty()) {
		delete (*children.rbegin());
		children.pop_back();
	}
}

void Widget::processEvent(const InputEvent* ev) {
	mErr::oerr() << "Widget::processEvent(" << (int)ev->type << ")" << std::endl;
}

std::list<InputEventType> Widget::acceptTypes() const {
	return std::list<InputEventType>();
}

void Widget::update() {
	for (Widget* child : children) {
		child->update();
	}
}

int Widget::getFlags() const {
	return flags;
}

void Widget::setFlagToTrue(WidgetFlag f) {
	flags |= f;
}

void Widget::setFlagToFalse(WidgetFlag f) {
	flags &= (~f);
}

void Widget::toggleFlag(WidgetFlag f) {
	flags ^= f;
}

void Widget::draw(Drawer* dr) const {
	for (Widget* child : children) {
		child->draw(dr);
	}
}

void Widget::cleanup() {
	for (Widget* child : children) {
		child->cleanup();
	}
}
