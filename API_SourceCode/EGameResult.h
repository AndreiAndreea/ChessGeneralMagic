#pragma once
/**
 * @brief Enumeration of game results.
 *
 * This enum class defines different possible outcomes of a chess game.
 * Each result represents the outcome of the game, such as a draw or victory for
 * either the white or black player.
 *
 */
enum class EGameResult {
    Draw,       /**< The game ended in a draw. */
    WhiteWon,   /**< The white player won the game. */
    BlackWon    /**< The black player won the game. */
};