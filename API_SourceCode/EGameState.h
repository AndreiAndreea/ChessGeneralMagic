#pragma once
/**
 * @brief Enumeration of game states.
 *
 * This enum class defines different possible states of a chess game.
 * Each state represents a specific phase or condition of the game, such as
 * ongoing play, a draw proposal, victory for one of the players, and more.
 *
 */
enum class EGameState {
    Playing,                /**< The game is currently in progress. */
    DrawProposed,           /**< A draw has been proposed by one of the players. */
    WhiteWon,               /**< The white player has won the game. */
    BlackWon,               /**< The black player has won the game. */
    Draw,                   /**< The game ended in a draw. */
    WaitingForPawnUpgrade,  /**< A pawn upgrade is pending for one of the players. */
    Paused                  /**< The game is paused. */
};

