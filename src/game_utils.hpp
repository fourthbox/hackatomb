#ifndef GAME_UTILS_HPP_
#define GAME_UTILS_HPP_

struct Utils {
    static inline void LogDebug(std::string const &message) {
        
        printf("%s\n", message.c_str());
    }
    
    static inline void LogDebug(std::string const &context, std::string const &message) {
        
        printf("%s:: %s\n", context.c_str(), message.c_str());
    }
    
    static inline void LogWarning(std::string const &context, std::string const &message) {
        
        printf("[WARNING] %s:: %s\n", context.c_str(), message.c_str());
    }
    
    static inline void LogError(std::string const &context, std::string const &message) {
        
        printf("[ERROR] %s:: %s\n", context.c_str(), message.c_str());
    }
};

#endif /* GAME_UTILS_HPP_ */
