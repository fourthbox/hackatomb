/**
 @file game_utils.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef GAME_UTILS_HPP_
#define GAME_UTILS_HPP_

/**
 Class containing only static funtions for generic Utilisies, like logs.
 */
struct Utils {
    /**
     Print a single debug log message on the system console.
     @param message The message to print.
     */
    static inline void LogDebug(std::string const &message) {
        
        printf("%s\n", message.c_str());
    }
    
    /**
     Print a single debug log message on the system console.
     @param message The message to print.
     @param context The context of the message.
     */
    static inline void LogDebug(std::string const &context, std::string const &message) {
        
        printf("%s:: %s\n", context.c_str(), message.c_str());
    }
    
    /**
     Print a single debug log message with a warning flag on the system console.
     @param message The message to print.
     @param context The context of the message.
     */
    static inline void LogWarning(std::string const &context, std::string const &message) {
        
        printf("[WARNING] %s:: %s\n", context.c_str(), message.c_str());
    }
    
    /**
     Print a single debug log message with an error flag on the system console.
     @param message The message to print.
     @param context The context of the message.
     */
    static inline void LogError(std::string const &context, std::string const &message) {
        
        printf("[ERROR] %s:: %s\n", context.c_str(), message.c_str());
    }
};

#endif /* GAME_UTILS_HPP_ */
