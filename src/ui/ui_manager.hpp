/**
 @file ui_window.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef UI_MANAGER_HPP_
#define UI_MANAGER_HPP_

#include "initiable_object.hpp"
#include "ui_window.hpp"

/**
 This class manages all the fixed and floating windows.
 */
class UiManager : public InitiableObject {
    
public :
    std::shared_ptr<UiWindow> environment_window_;
    std::shared_ptr<UiWindow> player_info_window_;
    std::shared_ptr<UiWindow> message_log_window_;
    std::shared_ptr<UiWindow> start_screen_window_;

    UiManager();
    
    /**
     Initializes the fixed windows.
     */
    void Initialize();
    
    /**
     Draw the windows on the consoles.
     */
    void Draw();
    
    void DrawStartScreen();
    
private :
    /**
     Initialize the environment window.
     */
    void InitializeEnvironmentWindow();
    
    /**
     Initialize the player info window.
     */
    void InitializePlayerInfoWindow();
    
    /**
     Initialize the message log window.
     */
    void InitializeMessageLogWindow();

    void InitializeStartScreenWindow();
};

#endif /* UI_MANAGER_HPP_ */
