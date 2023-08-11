#pragma once

#include "IGameStatus.h"
#include "IGameListener.h"
#include "EPieceType.h"
#include "EComand.h"
#include "Position.h"
#include "EGameType.h"


#include <memory>
#include <string>
#include <vector>
#include <utility>

/**
 * @brief Alias for a shared pointer to a class representing a game.
 */
using IGamePtr = std::shared_ptr<class IGame>;

/**
 * @brief Represents a full move consisting of two move strings.
 *
 * A full move consists of a move string for the white player and a move string for the black player.
 */
using FullMove = std::pair<MoveStr, MoveStr>;

/**
 * @brief A list of full moves.
 *
 * This type defines a vector of FullMove pairs, representing a sequence of moves in a game.
 */
using FullMoveList = std::vector<FullMove>;

class IGame
{
public:

	/**
	* @brief Produces game of the specified type.
	*
	* @param type Represents the type of game to be produced.
	*
	* @return A shared pointer to an object Game.
	*/
	static IGamePtr Produce(EGameType type);

	/**
	* @brief Adds a game listener to the list of observers.
	*
	* This function adds the provided game listener to the vector of observers.
	* The listener will receive notifications about game events and changes.
	*
	* @param listener A shared pointer to the game listener to be added.
	*/
	virtual void AddListener(IGameListenerPtr listener) = 0;

	/**
	* @brief Removes a game listener from the list of observers.
	*
	* This function searches for the specified game listener in the vector of observers
	* and removes it if found. The listener will no longer receive notifications.
	*
	* @param listener A pointer to the game listener to be removed.
	*/
	virtual void RemoveListener(IGameListener* listener) = 0;


	/**
	 * @brief Resets the chess game to its initial state.
	 *
	 * This function resets the chess game by performing the following actions:
	 * - Sets the turn to the starting player.
	 * - Clears the PGN (Portable Game Notation) data.
	 * - Resets the PGN builder used to construct the game's move history.
	 * - Clears the vector of PGN moves.
	 * - Resets the move counter to 1.
	 * - Updates the game state to "Playing".
	 * - Resets the game board to the initial position.
	 * - Resets and resumes the game timer.
	 *
	 * This function is typically called when starting a new game or restarting an ongoing game.
	 */
	virtual void ResetGame() = 0;

	/**
	 * @brief Virtual destructor for the IGame interface.
	 *
	 * This virtual destructor is provided as a base destructor for classes that implement
	 * the IGame interface. It ensures proper destruction of derived classes when deleting
	 * objects through a base pointer. The destructor is set to the default behavior, allowing
	 * derived classes to provide their own specialized destructors if needed.
	 *
	 */
	virtual ~IGame() = default;

	//Game Actions

	/**
	 * @brief Executes a game command based on the specified command type.
	 *
	 * This function processes different game commands based on the provided command type.
	 * It updates the game state and performs corresponding actions for each command.
	 *
	 * @param command The command type to be executed.
	 * @throws NotStatePlayingException if the command is not valid in the current game state.
	 * @throws NotStateDrawProposedException if the command requires a draw proposal state.
	 * @throws NotStatePausedException if the command requires a paused game state.
	 */
	virtual void PlayerComand(EComand respons) = 0;

	/**
	 * @brief Makes a chess move on the game board and updates the game state accordingly.
	 *
	 * This function processes a chess move from the specified starting position to the ending position.
	 * It validates the move, updates the board, handles capturing, pawn promotion, and checks for various
	 * endgame conditions such as checkmate, stalemate, threefold repetition draw, and insufficient material.
	 * The game timer is also updated based on the move.
	 *
	 * @param startPos The starting position of the move.
	 * @param endPos The ending position of the move.
	 * @param isLoadingPGN Specifies if the move is being made while loading a PGN game.
	 * @throws NotStatePlayingException if the game state is not in a valid playing state.
	 * @throws OutOfBoundException if the positions are not valid board coordinates.
	 * @throws InvalidStartPositionExcepton if the starting position does not contain the player's piece.
	 */
	virtual void MakeMove(Position startPos, Position endPos, bool isLoadingPGN = 0) = 0;

	/**
	 * @brief Upgrades a pawn to a specified piece type after reaching the opposing end of the board.
	 *
	 * This function is used to promote a pawn to a specified piece type (e.g., Queen, Rook, Bishop, or Knight)
	 * when it reaches the opposite end of the board. The function ensures the validity of the upgrade and updates
	 * the game state, board, PGN, and turn information accordingly.
	 *
	 * @param type The type of piece to which the pawn is upgraded.
	 * @throws NotStateWaitingForPawnUpdate if the game state is not in the waiting-for-pawn-upgrade state.
	 * @throws InvalidUpgradeType if the specified piece type is not valid for pawn promotion.
	 * 
	 * @details After successfully upgrading the pawn, this function updates the turn to the next player's turn and
	 *			    updates the timer. The move is considered to be over after the upgrade is done.
	 * 
	 */
	virtual void UpgradePawnTo(EPieceType type) = 0;


	/**
	 * @brief Initializes the game state and board using the specified FEN string.
	 *
	 * This function initializes the game state and chess board using the provided FEN (Forsyth-Edwards Notation) string.
	 * It populates the board with pieces according to the FEN string and sets the castling rights and current player's turn based on the FEN.
	 *
	 * @param strFEN The FEN string representing the initial board state and game parameters.
	 *
	 */
	virtual void InitializeGameFEN(const std::string& strFEN) = 0;
	/**
	 * @brief Initializes the game state and board using the specified PGN (Portable Game Notation) string.
	 *
	 * This function resets the game state and chess board, then replays the moves from the provided PGN string.
	 * It parses the PGN string to convert each move into the corresponding board position and piece type, and applies the moves.
	 *
	 * @param pgnStr The PGN string representing a sequence of chess moves.
	 *
	 * @details The function parses the PGN string to recreate the game's move sequence. It applies each move on the board,
	 *          and if a pawn promotion occurs, it upgrades the pawn. The resulting game state matches the state after
	 *          all moves from the PGN string have been played. This is useful for loading and replaying saved games.
	 */
	virtual void InitializeGamePGN(const std::string& movesPGN) = 0;

	/**
	 * @brief Loads a chess game from a PGN file and initializes the game state and board.
	 *
	 * This function by calling the function InitializeGamePGN reads the content of the specified PGN file, extracts the PGN moves section, and initializes
	 * the game state and board using the extracted PGN moves. It makes use of the InitializeGamePGN function to apply
	 * the parsed moves and set up the game state accordingly.
	 *
	 * @param filePath The file path of the PGN file to load the chess game from.
	 * 
	 */
	virtual void LoadFromPGNFile(const std::string& filePath) = 0;
	/**
	 * @brief Saves the current chess game state and moves to a PGN file.
	 *
	 * This function generates a PGN-formatted string representing the current game state and moves, and then saves it to
	 * the specified file path. The PGN builder is used to construct the PGN string, which includes information about the
	 * game state, players' moves, and any additional details.
	 *
	 * @param filePath The file path where the PGN file will be saved.
	 *
	 * @details Saving the game state to a PGN file allows players to resume the game later and analyze their moves. The
	 *          PGN format is widely used for storing and sharing chess games in a human-readable format.
	 */
	virtual void SaveToPGNFile(const std::string& filePath) = 0;

	//Game Status

	/**
	 * @brief Returns a constant pointer to the game's status information through the IGameStatus interface.
	 *
	 * @return A constant pointer to an object implementing the IGameStatus interface, providing access to
	 *         various getter functions for retrieving the game's status.
	 */
	virtual const IGameStatus* GetStatus() const = 0;

};