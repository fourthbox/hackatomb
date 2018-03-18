/**
 @file ui_window.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef UI_MANAGER_HPP_
#define UI_MANAGER_HPP_

#include "ui_window.hpp"

/**
 This class manages all the fixed and floating windows.
 */
class UiManager {
    
public :
    std::shared_ptr<UiWindow> environment_window_;
    std::shared_ptr<UiWindow> player_info_window_;
    std::shared_ptr<UiWindow> message_log_window_;

    UiManager();
    
    /**
     Initializes the fixed windows.
     */
    void Initialize();
    
    /**
     Draw the windows on the consoles.
     */
    void Draw();
    
private :
    bool initialized_;  /**< Utility switch for initialization security checks. */
    
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

};

#endif /* UI_MANAGER_HPP_ */
