#ifndef UI_MANAGER_HPP_
#define UI_MANAGER_HPP_

#include "ui_window.hpp"

class UiManager {
    
public :
    std::shared_ptr<UiWindow> environment_window_;
    std::shared_ptr<UiWindow> player_info_window_;
    std::shared_ptr<UiWindow> message_log_window_;

    UiManager();
    
    void Draw();
    void Initialize();
    
private :
    bool initialized_;
    
    // Fixed windows
    void InitializeEnvironmentWindow();
    void InitializePlayerInfoWindow();
    void InitializeMessageLogWindow();

};

#endif /* UI_MANAGER_HPP_ */
