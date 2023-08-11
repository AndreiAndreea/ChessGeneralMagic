#pragma once
/**
 * @brief Enumeration of piece types.
 *
 * This enum class defines different types of chess pieces, including the standard
 * pieces such as pawn, rook, knight, bishop, queen, and king, as well as a "None".
 * 
 * This final enumeration component is particularly valuable in scenarios such as loading a PGN File.
 * It informs the program that no pawn promotion is required.
 * 
 */
enum class EPieceType {
    Pawn,       /**< The pawn chess piece. */
    Rook,       /**< The rook chess piece. */
    Knight,     /**< The knight chess piece. */
    Bishop,     /**< The bishop chess piece. */
    Queen,      /**< The queen chess piece. */
    King,       /**< The king chess piece. */
    None        /**< Represents an empty square on the chess board. */
};