/**
 @file ui_window.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef UI_MANAGER_HPP_
#define UI_MANAGER_HPP_

#include "actor.hpp"
#include "initiable_object.hpp"
#include "turn_manager.hpp"
#include "ui_inventory.hpp"
#include "ui_window.hpp"

/**
 This class manages all the fixed and floating windows.
 */
class UiManager : public InitiableObject {
    
public :
    UiManager();
    
    /**
     Initializes the fixed windows.
     */
    void Initialize(InventoryManager &inventory_manager);
    
    /**
     Draw the windows on the consoles.
     */
    void Draw();
    
    UiWindow *GetEnvironmentWindow(), *GetPlayerInfoWindow(), *GetMessageLogWindow(), *GetInventoryWindow();
    
    bool UpdateLabel(std::string const &label_id, std::string const &label_text);
    
    /**
     Class that manages all the functions for logging messages.
     */
    class LogManager {
    public:
        /**
         Clears the message queue
         */
        void CleanupQueue() { message_queue_.clear(); }
        
        /**
         Log a simple string
         @param message The message to show
         */
        void AddMessage(std::string const &message) { message_queue_.push_front(message); }

        /**
         Log a simple attack.
         @param source The actor attacker.
         @param target The actor being attacked.
         @param damage The damage inflicted.
         */
        void LogAttack(Actor &source, Actor &target, int damage);
        
        /**
         Get strings from the bottom of the top of the deque
         @param position The position, 0 being the string on top
         @return The string requested
         */
        std::string GetStringFromTop(size_t position);
        
    private:
        std::deque<std::string> message_queue_;
    } log_manager_;
        
private :
    std::unique_ptr<UiWindow> environment_window_, player_info_window_, message_log_window_;
    std::unique_ptr<UiInventory> inventory_window_;

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
    
    void InitializeInventoryWindow(InventoryManager &inventory_manager);

    void InitializeStartScreenWindow();
};

#endif /* UI_MANAGER_HPP_ */
