#ifndef TURN_MANAGER_HPP_
#define TURN_MANAGER_HPP_

/**
 Enumerator that defines the phases of the turn.
 */
enum struct TurnPhase {
    IDLE_,   /**< The game is idle. Waiting for a player input to procede. */
    ACTION_, /**< The player has performed an action. Every actor will perform an action. */
    GAME_OVER_, /**< The game is over. Show game over screen */
    AIM_ /**< The game is in aim mode. */
};


class TurnManager {
public:
    TurnManager() : current_turn_phase_ {TurnPhase::IDLE_} {}
    
    void ActionPerformed() { current_turn_phase_ = TurnPhase::ACTION_; }
    void StartTurn() { current_turn_phase_ = TurnPhase::IDLE_; }
    void GameOver() { current_turn_phase_ = TurnPhase::GAME_OVER_; }
    void SwitchToAimMode() { current_turn_phase_ = TurnPhase::AIM_; }
    
    TurnPhase GetCurrentTurnPhase() const { return current_turn_phase_; }

private:
    TurnPhase current_turn_phase_;                  /**< Keeps the current turn phase */

};

#endif /* TURN_MANAGER_HPP_ */