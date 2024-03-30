#include <iostream>
#include <map>

#include "ChessLib/Chess.hpp"

using namespace std;

void draw(Chess::Chess& game)
{
    map<int, string> FigCh = {{1, "P "}, {2, "R "}, {3, "Kn"}, {4, "B "}, {5, "Q "}, {6, "K "}};
    system("cls");

    std::cout << "  ";
    for (int i = 0; i < 8; ++i)
    {
        std::cout << ' ' << i << ' ';
    }
    std::cout   << "\t Move color: "
                << ((game.getBoard().moveColor == Chess::PieceColor::Black) ? "Black" : "White")
                << "\n\n";

    for (int i = 0; i < 8; ++i)
    {
        std::cout << i << " ";
        for (int j = 0; j < 8; ++j)
        {
            const Chess::Figure* fig = game.get(Chess::Position(j, i));
            if (fig != nullptr)
            {
                std::cout   << ((fig->color == Chess::PieceColor::Black) ? " \x1B[37m" : " \033[2;47;30m")
                            << FigCh[(long long)(fig->type)]
                            << "\033[0m";
            }
            else
                std::cout << " - ";
        }
        std::cout << "\n";
    }
}

int main()
{
    Chess::PieceType (*getNewTypeWhite)() = []() -> Chess::PieceType { return Chess::PieceType::Queen;};
    Chess::PieceType (*getNewTypeBlack)() = []() -> Chess::PieceType { return Chess::PieceType::Queen;};

    Chess::Chess game(getNewTypeWhite, getNewTypeBlack);
    while (game.getResult() == Chess::PieceColor::Null)
    {
        draw(game);
        int x1, y1, x2, y2;
        std::cout << "\nEnter a move (x1, y1, x2, y2)\n";
        std::cin >> x1 >> y1 >> x2 >> y2;
        Chess::Position pos1(x1, y1);
        Chess::Position pos2(x2, y2);
        game.moving(pos1, pos2);
    }
    draw(game);

    std::cout   << "\nWin "
                << ((game.getResult() == Chess::PieceColor::Black) ? "Black" : "White")
                << "\n";

    return 0;
}
