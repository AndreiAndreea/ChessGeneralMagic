#include "ChessUIQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto ui = std::make_shared<ChessUIQt>();
    auto game = IGame::Produce();

    game->AddListener(ui);

    ui->SetGame(game);

    ui->show();
    ui->StartGame();

    QObject::connect(ui.get(), &ChessUIQt::Exit, &a, &QApplication::quit);

    auto result = a.exec();
    game->RemoveListener(ui.get());
    return result;
}
