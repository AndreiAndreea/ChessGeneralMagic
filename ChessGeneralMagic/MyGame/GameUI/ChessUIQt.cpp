#include "ChessUIQt.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QApplication>

#include "ChessExceptions.h"

ChessUIQt::ChessUIQt(QWidget *parent)
    : QMainWindow(parent)
    , game (nullptr)
{

    //Widget containing everything
    QWidget* mainWidget = new QWidget();
    QGridLayout* mainGridLayout = new QGridLayout();
    
    InitializeBoard(mainGridLayout);
    InitializeMessage(mainGridLayout);
    InitializeButtons(mainGridLayout);
    InitializeTimers(mainGridLayout);
    InitializeHistory(mainGridLayout);

    mainWidget->setLayout(mainGridLayout);
    this->setCentralWidget(mainWidget);

}

ChessUIQt::~ChessUIQt()
{
    //No delete?
    //https://doc.qt.io/qt-6/objecttrees.html
}

void ChessUIQt::InitializeMessage(QGridLayout * mainGridLayout)
{
    m_MessageLabel = new QLabel();
    m_MessageLabel->setText("Waiting for white player");
    m_MessageLabel->setAlignment(Qt::AlignCenter);
    m_MessageLabel->setStyleSheet("font-size: 20px; font-weight: bold;");

    mainGridLayout->addWidget(m_MessageLabel, 0, 1, 1, 1);
}

void ChessUIQt::InitializeButtons(QGridLayout* mainGridLayout)
{
    QPushButton* saveButton = new QPushButton("Save");
    QPushButton* loadButton = new QPushButton("Load");
    QPushButton* restartButton = new QPushButton("Restart");
    QPushButton* drawButton = new QPushButton("Draw");
	QPushButton* copyButton = new QPushButton("Copy");


    QWidget* buttonContainer = new QWidget();
    QGridLayout* btnGrid = new QGridLayout();

    btnGrid->addWidget(saveButton, 0, 0);
    btnGrid->addWidget(loadButton, 0, 1);
    btnGrid->addWidget(restartButton, 0, 2);
    btnGrid->addWidget(drawButton, 0, 3);
	btnGrid->addWidget(copyButton, 0, 4);

    connect(saveButton, &QPushButton::pressed, this, &ChessUIQt::OnSaveButtonClicked);
    connect(loadButton, &QPushButton::pressed, this, &ChessUIQt::OnLoadButtonClicked);
    connect(restartButton, &QPushButton::pressed, this, &ChessUIQt::OnRestartButtonClicked);
    connect(drawButton, &QPushButton::pressed, this, &ChessUIQt::OnDrawButtonClicked);
	connect(copyButton, &QPushButton::pressed, this, &ChessUIQt::OnCopyButtonClicked);

    buttonContainer->setLayout(btnGrid);
    mainGridLayout->addWidget(buttonContainer, 0, 0, 1, 1);
}

void ChessUIQt::InitializeTimers(QGridLayout* mainGridLayout)
{
    QWidget* timerContainer = new QWidget();
    QGridLayout* timerGrid = new QGridLayout();

    QLabel* blackTimerLbl = new QLabel("Black timer: ");
    m_BlackTimer = new QLabel("00:00:00");

    QPushButton* pauseTimerBtn = new QPushButton(" Pause | Resume");
    //TODO Create slot and connect button

    QLabel* whiteTimerLbl = new QLabel("    White timer: ");
    m_WhiteTimer = new QLabel("00:00:00");

    timerContainer->setFixedWidth(400);

    timerGrid->addWidget(blackTimerLbl, 0, 0);
    timerGrid->addWidget(m_BlackTimer, 0, 1);
    timerGrid->addWidget(pauseTimerBtn, 0, 2);
    timerGrid->addWidget(whiteTimerLbl, 0, 3);
    timerGrid->addWidget(m_WhiteTimer, 0, 4);

    timerContainer->setLayout(timerGrid);
    mainGridLayout->addWidget(timerContainer, 2, 0, 1, 2, Qt::AlignCenter);
}

void ChessUIQt::InitializeHistory(QGridLayout* mainGridLayout)
{
    m_MovesList = new QListWidget();
    m_MovesList->setMinimumWidth(320);
    m_MovesList->setMaximumWidth(420);
    connect(m_MovesList, &QListWidget::itemActivated, this, &ChessUIQt::OnHistoryClicked);
    mainGridLayout->addWidget(m_MovesList, 1, 0, 1, 1);
}

void ChessUIQt::InitializeBoard(QGridLayout* mainGridLayout)
{
    QGridLayout* chessGridLayout;
    chessGridLayout = new QGridLayout();
    QWidget* board = new QWidget();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_grid[i][j] = new GridButton({ i,j }, PieceType::none, PieceColor::none);
            chessGridLayout->addWidget(m_grid[i][j], i, j, 1, 1);
            connect(m_grid[i][j], &GridButton::Clicked, this, &ChessUIQt::OnButtonClicked);
        }
    }

    board->setLayout(chessGridLayout);
    mainGridLayout->addWidget(board, 1, 1, 1, 1);
}

PieceColor ConvertColorEnum(EPieceColor color)
{
    if ((int)color)
        return PieceColor::black;
    if (!(int)color)
        return PieceColor::white;
    return PieceColor::none;
}

PieceType ConvertTypeEnum(EPieceType type)
{
    switch (type)
    {
    case EPieceType::Rook:
        return PieceType::rook;
        break;
    case EPieceType::Bishop:
        return PieceType::bishop;
        break;
    case EPieceType::Knight:
        return PieceType::knight;
        break;
    case EPieceType::King:
        return PieceType::king;
        break;
    case EPieceType::Queen:
        return PieceType::queen;
        break;
    case EPieceType::Pawn:
        return PieceType::pawn;
        break;
    case EPieceType::None:
        return PieceType::none;
        break;
    }
}

 static QString ConvertEGameResultToQStr(EGameResult result)
{
    switch (result)
    {
    case EGameResult::WhiteWon :
        return "The winner is: Player white";
        break;
    case EGameResult::BlackWon:
		return "The winner is: Player black";
        break;
    case EGameResult::Draw:
		return "The winner is: None";
        break;
    }
}

void ChessUIQt::OnButtonClicked(const Position& position)
{
    //At second click
    if (m_selectedCell.has_value()) 
    {
        //TODO COMPLETE ME...
        if (m_selectedCell->first == position.first && m_selectedCell->second == position.second)
        {
            //deselect cells
			m_grid[m_selectedCell.value().first][m_selectedCell.value().second]->setSelected(false);
			m_selectedCell.reset();
            auto possibleMoves = game->GetPossibleMoves(position);
            UnhighlightPossibleMoves(possibleMoves);
        }
        else
        {
			try
			{
				game->MakeMove(Position(m_selectedCell->first, m_selectedCell->second), position);
			}
			catch (ChessExceptions e)
			{
				QMessageBox msgBox;
				msgBox.setText(e.what());
				msgBox.exec();
			}

			//Unselect prev. pressed button and  unhighlight board
			m_grid[m_selectedCell.value().first][m_selectedCell.value().second]->setSelected(false);
			m_selectedCell.reset();
            UpdateBoard();
        }
    }
    //At first click
    else {
        if (ConvertColorEnum(game->GetCurrentPlayer()) == m_grid[position.first][position.second]->GetPieceColor())
        {
            m_selectedCell = position;
            m_grid[position.first][position.second]->setSelected(true);

            //TODO Show possible moves here
            HighlightPossibleMoves(game->GetPossibleMoves(position));
        }
    }
}

void ChessUIQt::OnSaveButtonClicked()
{
    //TODO ...

}

void ChessUIQt::OnLoadButtonClicked()
{
    //TODO ...
}

void ChessUIQt::OnRestartButtonClicked()
{
    game->ResetGame();

    m_MessageLabel->setText("Waiting for white player");
	UpdateBoard();
}

void ChessUIQt::OnDrawButtonClicked()
{
    //TODO MODIFY ME

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Draw proposal", "Do you accept a draw?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
		QMessageBox msgBox;
		msgBox.setText("Draw Accepted. Winner is: None.");
		msgBox.exec();
        OnRestartButtonClicked();
    }
}

static char PieceInfoToChar(PieceType type, PieceColor color)
{
    std::string letters = "-krbqnp";
    if (color == PieceColor::black)
        return toupper(letters[(int)type]);
    if (color == PieceColor::white)
        return tolower(letters[(int)type]);
    return letters[(int)type];
}

void ChessUIQt::OnCopyButtonClicked()
{
    QClipboard* clipboard = QApplication::clipboard();
    QString boardConfig = "{ \n";

    for (int i = 0; i < 8; i++)
    {
        boardConfig += '{';
        for (int j = 0; j < 8; j++)
        {
            boardConfig += QString('\'') + PieceInfoToChar(m_grid[i][j]->GetPieceType(), m_grid[i][j]->GetPieceColor()) + '\'';
			if (j != 7)
				boardConfig += ", ";
        }
        boardConfig += '}';
        if (i != 7)
            boardConfig += ", \n";
    }
    boardConfig += "\n }";

    clipboard->setText(boardConfig);
}

void ChessUIQt::OnHistoryClicked(QListWidgetItem* item)
{
    int index = m_MovesList->currentRow();
    
    //TODO ...
}

void ChessUIQt::UpdateHistory()
{
    m_MovesList->clear();

    //TODO modify me...
    int numMoves = 10;
    for (int i = 0; i < numMoves; i++) {
        m_MovesList->addItem("#1   Color: Black   Move: A1 A2");
    }
}

void ChessUIQt::UpdateBoard()
{
    PieceColor color;
    PieceType type;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (game->GetPieceInfo(Position(i, j)))
            {
                type = ConvertTypeEnum(game->GetPieceInfo(Position(i, j))->GetType());
                color = ConvertColorEnum(game->GetPieceInfo(Position(i, j))->GetColor());
            }
            else
            {
                type = PieceType::none;
                color = PieceColor::none;
            }

            m_grid[i][j]->setPiece({type, color});
            m_grid[i][j]->setSelected(false);
            m_grid[i][j]->setHighlighted(false);
        }
    }
}

void ChessUIQt::HighlightPossibleMoves(const PositionList& possibleMoves)
{
    for (const auto& position : possibleMoves) {
        m_grid[position.first][position.second]->setHighlighted(true);
    }
}

void ChessUIQt::UnhighlightPossibleMoves(const PositionList& possibleMoves)
{
	for (const auto& position : possibleMoves) {
		m_grid[position.first][position.second]->setHighlighted(false);
	}
}

void ChessUIQt::StartGame()
{
    UpdateBoard();
}

EPieceType ConvetItemToEPieceType(QString item)
{
    if (item == "Rook")
        return EPieceType::Rook;
	if (item == "Bishop")
		return EPieceType::Bishop;
	if (item == "Queen")
		return EPieceType::Queen;
	if (item == "Knight")
		return EPieceType::Knight;
}

void ChessUIQt::ShowPromoteOptions()
{
    QInputDialog dialog;
    QList<QString> options;
    options.append("Rook");
    options.append("Bishop");
    options.append("Queen");
    options.append("Knight");

    dialog.setComboBoxItems(options);
    dialog.setModal(true);

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Pawn promote"),
        tr("Promote pawn to: "), options, 0, false, &ok);

    if (ok && !item.isEmpty())
    {
        //TODO
        game->UpgradePawnTo(ConvetItemToEPieceType(item));

        //TODO DELETE ME...
        QMessageBox notification;
        notification.setText("You selected " + item);
        notification.exec();
    }
}

void ChessUIQt::SetGame(IGamePtr game)
{
    this->game = game;
}

void ChessUIQt::OnMoveMade(Position startPos, Position endPos, PositionList prevPossibleMoves)
{   
    auto type = ConvertTypeEnum(game->GetPieceInfo(endPos)->GetType());
    auto color = ConvertColorEnum(game->GetPieceInfo(endPos)->GetColor());

    m_grid[endPos.first][endPos.second]->setPiece({ type, color });
	m_grid[endPos.first][endPos.second]->setSelected(false);
	m_grid[endPos.first][endPos.second]->setHighlighted(false);

    m_grid[startPos.first][startPos.second]->setPiece({ PieceType::none, PieceColor::none });
	m_grid[startPos.first][startPos.second]->setSelected(false);
	m_grid[startPos.first][startPos.second]->setHighlighted(false);


    auto bol = game->GetCurrentPlayer() == EPieceColor::Black;
    m_MessageLabel->setText(game->GetCurrentPlayer() == EPieceColor::Black ? "Waiting for black player" : "Waiting for white player");
}

void ChessUIQt::OnPawnUpgrade() 
{
	ShowPromoteOptions();
}

void ChessUIQt::OnGameOver(EGameResult result)
{
	QMessageBox msgBox;
	QString str;
	str = ConvertEGameResultToQStr(result);
	msgBox.setText(str);
	msgBox.exec();

	//reset board and turn. new game
	OnRestartButtonClicked();
}

