/**
 This class act as a proxy for the TCODConsole
 @file console_proxy.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef CONSOLE_PROXY_HPP_
#define CONSOLE_PROXY_HPP_

#include "libtcod.hpp"

class ConsoleProxy {
public:
    TCODConsole* console_;

    ConsoleProxy();
    ~ConsoleProxy();

    void Initialize(size_t width, size_t height);
    void SetChar(size_t x, size_t y, int sprite, TCODColor color);
    
private:
    bool initialized_;
    
};

#endif /* CONSOLE_PROXY_HPP_ */
