#include "ChessUIQt.h"
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QApplication>
#include <QGroupBox>
#include <QVBoxLayout>
#include <fstream>

#include "ChessExceptions.h"

ChessUIQt::ChessUIQt(QWidget* parent)
	: QMainWindow(parent)
	, game(nullptr)
{

	//Widget containing everything
	QWidget* mainWidget = new QWidget();
	QGridLayout* mainGridLayout = new QGridLayout();

	InitializeBoard(mainGridLayout);
	InitializeMessage(mainGridLayout);
	InitializeButtons(mainGridLayout);
	InitializeTimers(mainGridLayout);
	InitializeHistory(mainGridLayout);
	InitializeCapturedPiecesDisplay(mainGridLayout);

	mainWidget->setLayout(mainGridLayout);
	this->setCentralWidget(mainWidget);

}

ChessUIQt::~ChessUIQt()
{
	//No delete?
	//https://doc.qt.io/qt-6/objecttrees.html
}

void ChessUIQt::InitializeMessage(QGridLayout* mainGridLayout)
{
	m_MessageLabel = new QLabel();
	m_MessageLabel->setText("Waiting for white player");
	m_MessageLabel->setAlignment(Qt::AlignCenter);
	m_MessageLabel->setStyleSheet("font-size: 20px; font-weight: bold;");

	mainGridLayout->addWidget(m_MessageLabel, 0, 2, 1, 1);
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
	mainGridLayout->addWidget(timerContainer, 2, 1, 1, 2, Qt::AlignCenter);
}

void ChessUIQt::InitializeHistory(QGridLayout* mainGridLayout)
{
	m_moveNumberList = new QListWidget(this);
	m_whiteMoveList = new QListWidget(this);
	m_blackMoveList = new QListWidget(this);

	m_moveNumberList->setFixedWidth(50);
	m_whiteMoveList->setFixedWidth(150);
	m_blackMoveList->setFixedWidth(150);

	// Create QLabel widgets for headers
	QLabel* moveNumberHeader = new QLabel("Nr.");
	QLabel* whiteMoveHeader = new QLabel("White Move");
	QLabel* blackMoveHeader = new QLabel("Black Move");

	moveNumberHeader->setAlignment(Qt::AlignCenter);
	whiteMoveHeader->setAlignment(Qt::AlignCenter);
	blackMoveHeader->setAlignment(Qt::AlignCenter);
	m_moveNumberList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_whiteMoveList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_blackMoveList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// Create the layout for the three group boxes
	QVBoxLayout* moveNumberLayout = new QVBoxLayout();
	moveNumberLayout->addWidget(moveNumberHeader);
	moveNumberLayout->addWidget(m_moveNumberList);

	QVBoxLayout* whiteMoveLayout = new QVBoxLayout();
	whiteMoveLayout->addWidget(whiteMoveHeader);
	whiteMoveLayout->addWidget(m_whiteMoveList);

	QVBoxLayout* blackMoveLayout = new QVBoxLayout();
	blackMoveLayout->addWidget(blackMoveHeader);
	blackMoveLayout->addWidget(m_blackMoveList);

	// Create the layout for the entire window
	QHBoxLayout* layout = new QHBoxLayout();
	layout->addLayout(moveNumberLayout);
	layout->addLayout(whiteMoveLayout);
	layout->addLayout(blackMoveLayout);

	mainGridLayout->addLayout(layout, 1, 0, 1, 1);
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
	mainGridLayout->addWidget(board, 1, 2, 1, 1);
}

void ChessUIQt::InitializeCapturedPiecesDisplay(QGridLayout* mainGridLayout)
{
	QGridLayout* leftCapturedPiecesGridLayout = new QGridLayout();
	QGridLayout* rightCapturedPiecesGridLayout = new QGridLayout();
	QWidget* leftCapturedPieces = new QWidget();
	QWidget* rightCapturedPieces = new QWidget();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_capturedPieces[0][i][j] = new CapturedPiecesCellDisplay(PieceType::none, PieceColor::none);
			m_capturedPieces[1][i][j] = new CapturedPiecesCellDisplay(PieceType::none, PieceColor::none);

			leftCapturedPiecesGridLayout->addWidget(m_capturedPieces[0][i][j], i, j, 1, 1);
			rightCapturedPiecesGridLayout->addWidget(m_capturedPieces[1][i][j], i, j, 1, 1);
		}
	}

	leftCapturedPieces->setLayout(leftCapturedPiecesGridLayout);
	rightCapturedPieces->setLayout(rightCapturedPiecesGridLayout);

	mainGridLayout->addWidget(leftCapturedPieces, 1, 1, 1, 1);
	mainGridLayout->addWidget(rightCapturedPieces, 1, 3, 1, 1);
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
	case EGameResult::WhiteWon:
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
	auto status = game->GetStatus();
	//At second click
	if (m_selectedCell.has_value())
	{
		//TODO COMPLETE ME...
		if (m_selectedCell->x == position.x && m_selectedCell->y == position.y)
		{
			//deselect cells
			m_grid[m_selectedCell.value().x][m_selectedCell.value().y]->setSelected(false);
			m_selectedCell.reset();
			auto possibleMoves = status->GetPossibleMoves(position);
			UnhighlightPossibleMoves(possibleMoves);
		}
		else
		{
			try
			{
				game->MakeMove(Position(m_selectedCell->x, m_selectedCell->y), position, false);
			}
			catch (ChessExceptions e)
			{
				QMessageBox msgBox;
				msgBox.setText(e.what());
				msgBox.exec();
			}

			//Unselect prev. pressed button and  unhighlight board
			m_grid[m_selectedCell.value().x][m_selectedCell.value().y]->setSelected(false);
			m_selectedCell.reset();
			UpdateBoard();
		}
	}
	//At first click
	else {
		if (ConvertColorEnum(status->GetCurrentPlayer()) == m_grid[position.x][position.y]->GetPieceColor())
		{
			m_selectedCell = position;
			m_grid[position.x][position.y]->setSelected(true);

			//TODO Show possible moves here
			HighlightPossibleMoves(status->GetPossibleMoves(position));
		}
	}
}

void ChessUIQt::OnSaveButtonClicked()
{
	QString fileSave = QFileDialog::getSaveFileName(this, "Save File", "", "FEN Files(*.fen);; PGN Files(*.pgn)");
	if (!fileSave.isEmpty()) {
		std::string data;

		QString fileExtension = QFileInfo(fileSave).suffix();
		if (fileExtension == "fen")
		{
			data = game->GetStatus()->GetFEN();
			std::ofstream outputFile(fileSave.toStdString());
			if (outputFile.is_open()) {
				outputFile << data;
				outputFile.close();
			}
		}
		if (fileExtension == "pgn")
		{
			//data = game->GetPGN();
			game->SaveToPGNFile(fileSave.toStdString());
		}
	}
}

void ChessUIQt::OnLoadButtonClicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "FEN Files (*.fen);; PGN Files (*.pgn)");
	if (!fileName.isEmpty()) {
		QFileInfo fileInfo(fileName);
		QString fileExtension = fileInfo.suffix().toLower();

		if (fileExtension == "fen") {
			QString fileData;
			QFile file(fileName);

			// this if should be in PGN builder 
			if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
				QTextStream stream(&file);
				fileData = stream.readAll();
				file.close();
			}

			OnRestartButtonClicked();
			game->InitializeGameFEN(fileData.toStdString());

			m_MessageLabel->setText(game->GetStatus()->GetCurrentPlayer() == EPieceColor::Black ? "Waiting for black player" : "Waiting for white player");
			UpdateCapturedPiecesDispay();
			UpdateBoard();
		}
		else if (fileExtension == "pgn") {
			
			OnRestartButtonClicked();

			game->LoadFromPGNFile(fileName.toStdString());

			UpdateCapturedPiecesDispay();
			UpdateBoard();
			UpdateHistory();
		}
		else {
			QMessageBox::critical(this, "Error", "Unsupported file extension: " + fileExtension, QMessageBox::Ok);
		}
	}
}

void ChessUIQt::ResetHistory()
{
	m_moveNumberList->clear();
	m_whiteMoveList->clear();
	m_blackMoveList->clear();
}

void ChessUIQt::ResetCapturedPiecesDisplay()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 2; j++)
		{
			m_capturedPieces[0][i][j]->Update(PieceType::none, PieceColor::none);
			m_capturedPieces[1][i][j]->Update(PieceType::none, PieceColor::none);
		}
}

void ChessUIQt::UpdateCapturedPiecesDispay()
{
	auto status = game->GetStatus();
	OnCaptureMade(EPieceColor::Black, status->GetCapturedPieces(EPieceColor::Black));
	OnCaptureMade(EPieceColor::White, status->GetCapturedPieces(EPieceColor::White));
}

void ChessUIQt::OnRestartButtonClicked()
{
	game->ResetGame();

	ResetCapturedPiecesDisplay();
	ResetHistory();

	m_MessageLabel->setText("Waiting for white player");

	UpdateBoard();
}

void ChessUIQt::OnDrawButtonClicked()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Draw proposal", "Do you accept a draw?", QMessageBox::Yes | QMessageBox::No);
	game->PlayerDrawComand(EDrawComand::Draw);

	if (reply == QMessageBox::Yes) {
		QMessageBox msgBox;
		msgBox.setText("Draw Accepted. Winner is: None.");
		msgBox.exec();
		game->PlayerDrawComand(EDrawComand::Accept);
	}
	else
		game->PlayerDrawComand(EDrawComand::Decline);
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
	//int index = m_historyTableWidget->currentRow();

	//TODO ...
}

void ChessUIQt::UpdateHistory()
{
	auto status = game->GetStatus();
	auto movesPGN = status->GetMovesPGN(status->GetPGNMovesSection());

	if (movesPGN.size())
	{
		if (status->GetCurrentPlayer() != EPieceColor::White)
		{
			QString itemText = QString::number(movesPGN.size());
			QListWidgetItem* item = new QListWidgetItem(itemText);
			item->setFlags(item->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			m_moveNumberList->addItem(item);

			QString moveTextW = QString::fromStdString(movesPGN[movesPGN.size() - 1]);
			QListWidgetItem* itemMoveW = new QListWidgetItem(moveTextW);
			itemMoveW->setFlags(itemMoveW->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			m_whiteMoveList->addItem(itemMoveW);

			QString moveTextB = QString::fromStdString("  ");
			QListWidgetItem* itemMoveB = new QListWidgetItem(moveTextB);
			itemMoveB->setFlags(itemMoveB->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			m_blackMoveList->addItem(itemMoveB);
		}
		else
		{
			QListWidgetItem* lastItem = m_blackMoveList->item(m_blackMoveList->count() - 1);
			lastItem->setText(QString::fromStdString(movesPGN[movesPGN.size() - 1]));
		}
	}
}

void ChessUIQt::UpdateBoard()
{
	auto status = game->GetStatus();
	PieceColor color;
	PieceType type;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if (status->GetPieceInfo(Position(i, j)))
			{
				type = ConvertTypeEnum(status->GetPieceInfo(Position(i, j))->GetType());
				color = ConvertColorEnum(status->GetPieceInfo(Position(i, j))->GetColor());
			}
			else
			{
				type = PieceType::none;
				color = PieceColor::none;
			}

			m_grid[i][j]->setPiece({ type, color });
			m_grid[i][j]->setSelected(false);
			m_grid[i][j]->setHighlighted(false);
		}
	}
}

void ChessUIQt::HighlightPossibleMoves(const PositionList& possibleMoves)
{
	for (const auto& position : possibleMoves) {
		m_grid[position.x][position.y]->setHighlighted(true);
	}
}

void ChessUIQt::UnhighlightPossibleMoves(const PositionList& possibleMoves)
{
	for (const auto& position : possibleMoves) {
		m_grid[position.x][position.y]->setHighlighted(false);
	}
}

void ChessUIQt::StartGame()
{
	UpdateBoard();
	UpdateHistory();
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

void ChessUIQt::SetGame(IGamePtr game)
{
	this->game = game;
}

void ChessUIQt::OnMoveMade(Position startPos, Position endPos, PositionList prevPossibleMoves)
{
	auto status = game->GetStatus();
	auto type = ConvertTypeEnum(status->GetPieceInfo(endPos)->GetType());
	auto color = ConvertColorEnum(status->GetPieceInfo(endPos)->GetColor());

	m_grid[endPos.x][endPos.y]->setPiece({ type, color });
	m_grid[endPos.x][endPos.y]->setSelected(false);
	m_grid[endPos.x][endPos.y]->setHighlighted(false);

	m_grid[startPos.x][startPos.y]->setPiece({ PieceType::none, PieceColor::none });
	m_grid[startPos.x][startPos.y]->setSelected(false);
	m_grid[startPos.x][startPos.y]->setHighlighted(false);

	auto bol = status->GetCurrentPlayer() == EPieceColor::Black;
	m_MessageLabel->setText(status->GetCurrentPlayer() == EPieceColor::Black ? "Waiting for black player" : "Waiting for white player");

	//update history
	UpdateHistory();
	UpdateBoard();
}

void ChessUIQt::OnPawnUpgrade()
{
	UpdateBoard();

	QList<QString> options;
	options.append("Rook");
	options.append("Bishop");
	options.append("Queen");
	options.append("Knight");

	while (true)
	{
		QInputDialog dialog;
		dialog.setComboBoxItems(options);
		dialog.setModal(true);
		int result = dialog.exec();

		// Process the user's selection
		if (result == QDialog::Accepted) {
			QString selectedPiece = dialog.textValue(); // Get the selected piece (e.g., "Rook", "Bishop", etc.)

			game->UpgradePawnTo(ConvetItemToEPieceType(selectedPiece));
			break;
		}
	}
	UpdateHistory();
	UpdateBoard();
}

void ChessUIQt::OnGameOver(EGameResult result)
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Game Over");
	QString str;
	str = ConvertEGameResultToQStr(result);
	msgBox.setText(str);

	// Add custom buttons
	QPushButton* Save = msgBox.addButton("Save", QMessageBox::AcceptRole);
	QPushButton* close = msgBox.addButton("Close", QMessageBox::AcceptRole);
	QPushButton* newGame = msgBox.addButton("New Game", QMessageBox::AcceptRole);

	QObject::connect(Save, &QPushButton::clicked, [&]() {
		OnSaveButtonClicked();
		});

	QObject::connect(close, &QPushButton::clicked, [&]() {
		});

	QObject::connect(newGame, &QPushButton::clicked, [&]() {
		OnRestartButtonClicked();
		});


	// Show the custom popup
	msgBox.exec();
}

void ChessUIQt::OnCaptureMade(EPieceColor color, IPieceInfoPtrList capturedPieces)
{
	if (!capturedPieces.empty())
	{
		int k = 0;
		for (int i = 0; i < 8 && k < capturedPieces.size(); i++)
		{
			for (int j = 0; j < 2 && k < capturedPieces.size(); j++)
			{
				auto capturedPieceColor = ConvertColorEnum(capturedPieces[k]->GetColor());
				auto capturedPieceType = ConvertTypeEnum(capturedPieces[k]->GetType());
				m_capturedPieces[(int)color][i][j]->Update(capturedPieceType, capturedPieceColor);
				k++;
			}
		}
	}
}

void ChessUIQt::OnDraw()
{
	OnRestartButtonClicked();
}

void ChessUIQt::OnPawnUpgradePGN()
{
	UpdateHistory();
}

