#pragma once

/**
 * @brief The Command enum represents the different commands.
 *
 * This enum is used to represent a variety commands 
 * besides the actual move of a piece
 * 
 */

enum class EComand
{
	Draw,     /**< Request to draw the game. */
	Accept,   /**< Acceptance of a draw request. */
	Decline,  /**< Decline of a draw request. */
	Pause,    /**< Pause the game. */
	Resume    /**< Resume the paused game. */
};