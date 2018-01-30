#ifndef UI_MANAGER_HPP_
#define UI_MANAGER_HPP_

#include "ui_window.hpp"

class UiManager {
    
    public :
    UiManager();
    
    void Draw();
    void Initialize();
    
    private :
    bool initialized_;
    
    // Fixed windows
    UiWindow* environment_window_;
    UiWindow* player_info_window_;
    UiWindow* message_log_window_;
    
    void InitializeEnvironmentWindow();
    void InitializePlayerInfoWindow();
    void InitializeMessageLogWindow();

};

#endif /* UI_MANAGER_HPP_ */
