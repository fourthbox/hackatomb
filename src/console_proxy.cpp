#include "console_proxy.hpp"

#include <cassert>

ConsoleProxy::ConsoleProxy() :
initialized_ {false} {
    assert(!initialized_);
}

ConsoleProxy::~ConsoleProxy() {
    assert(initialized_);

    delete console_;
}

void ConsoleProxy::Initialize(size_t width, size_t height) {
    assert(!initialized_);

    console_ = new TCODConsole((int)width, (int)height);
    
    initialized_ = true;
}

void ConsoleProxy::SetChar(size_t x, size_t y, int sprite, TCODColor color) {
    assert(initialized_);
    
    console_->setChar((int)x, (int)y, sprite);
    console_->setCharForeground((int)x, (int)y, color);
}
