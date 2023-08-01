#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qgridlayout.h>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "GridButton.h"
#include "CapturedPiecesCellDisplay.h"

#include "IGame.h"
#include "IGameListener.h"
#include "EGameResult.h"

#include <memory>

using ConfigGrid = std::array<std::array<GridButton*, 8>, 8>;
using ConfigCapturedPieces = std::array<std::array<std::array<CapturedPiecesCellDisplay*, 2>, 8>, 2>;

class ChessUIQt : public QMainWindow, public IGameListener
{
    Q_OBJECT

public:
    ChessUIQt(QWidget *parent = nullptr);
    ~ChessUIQt() override;

    void InitializeMessage(QGridLayout* mainGridLayout);
    void InitializeButtons(QGridLayout* mainGridLayout);
    void InitializeTimers(QGridLayout* mainGridLayout);
    void InitializeHistory(QGridLayout* mainGridLayout);
    void InitializeBoard(QGridLayout* mainGridLayout);
    void InitializeCapturedPiecesDisplay(QGridLayout* mainGridLayout);

    //Modify if necessary with your history representation
    void UpdateHistory();
    //Modify if necessary with your board representation
    void UpdateBoard();
    //Modify if necessary with your possible moves representation
    void HighlightPossibleMoves(const PositionList& possibleMoves);
    void UnhighlightPossibleMoves(const PositionList& possibleMoves);
    //Modify or delete
    void StartGame();
    void ShowPromoteOptions();

    void SetGame(IGamePtr game);

    // listener methods
    void OnMoveMade(Position startPos, Position endPos, PositionList prevPossibleMoves) override;
    void OnPawnUpgrade() override;
    void OnGameOver(EGameResult result) override;
    void OnCaptureMade(EPieceColor color, IPieceInfoPtrList capturedPieces) override;

private:
    void ResetCapturedPiecesDisplay();
    void UpdateCapturedPiecesDispay();

public slots:
    void OnButtonClicked(const Position& position);

    void OnSaveButtonClicked();
    void OnLoadButtonClicked();
    void OnRestartButtonClicked();
    void OnDrawButtonClicked();
    void OnCopyButtonClicked();
    void OnHistoryClicked(QListWidgetItem* item);
   

signals:
    void Exit();

private:
    ConfigGrid m_grid;
    ConfigCapturedPieces m_capturedPieces;
    std::optional<Position> m_selectedCell;
    QLabel* m_MessageLabel;
    QTableWidget* m_historyTableWidget;
    QLabel* m_BlackTimer, *m_WhiteTimer;
    IGamePtr game;
};