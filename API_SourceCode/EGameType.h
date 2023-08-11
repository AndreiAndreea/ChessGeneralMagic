#pragma once
/**
 * @brief Enumeration of game types.
 *
 * This enum class defines different types of chess games, each associated with
 * a specific time control or play style. Players can choose between rapid,
 * blitz, bullet, or playing with no timer.
 *
 */
enum class EGameType {
    Rapid,      /**< Rapid chess: 30 minutes time control. */
    Blitz,      /**< Blitz chess: 10 minutes time control. */
    Bullet,     /**< Bullet chess: 3 minutes time control. */
    NoTimer     /**< Playing with no timer. */
};