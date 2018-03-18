/**
 @file initiable_object.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef INITIABLE_OBJECT_HPP_
#define INITIABLE_OBJECT_HPP_

#include <cassert>

/**
 This abstract class force all child classes to set initialized_ to true.
 */
class InitiableObject {
public:
    InitiableObject() : initialized_ {false} { assert(!initialized_); }
    
protected:
    bool initialized_;  /**< Utility switch for initialization security checks. */
};

#endif /* INITIABLE_OBJECT_HPP_ */
