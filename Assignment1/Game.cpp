#include "Game.h"

const std::string star_25 = "*************************";
const std::string hyphen_25 = "-------------------------";

const char available_pieces[12] = { 'P', 'R', 'N', 'B', 'Q', 'K', 'p', 'r', 'n', 'b', 'q', 'k' };

namespace chess
{
    void Print27Spaces(std::ostream& os, std::string message, size_t message_size)
    { // 출력할 때 *과 * 사이 25칸을 만들고 그 사이에 원하는 문자열을 출력할 수 있게 해주는 함수
        os << '*';
        for (int i = 0; i < message_size; i++)
        {
            os << message[i];
        }
        for (int i = message_size; i < 25; i++)
        {
            os << ' ';
        }
        os << '*' << std::endl;
    }

    void MainMenu(std::istream& is, std::ostream& os)
    {
        Print27Spaces(os, star_25, 25);
        for (int i = 1; i < 26; i += 2)
        {
            char star[26];
            for (int j = 0; j < i; j++)
            {
                star[j] = ' ';
            }
            for (int j = i; j < 25; j++)
            {
                star[j] = '*';
            }
            star[25] = '\0';
            Print27Spaces(os, star, 25);
        }
        Print27Spaces(os, star_25, 25);
        Print27Spaces(os, " SWTube CHESS ENGINE", sizeof(" SWTube CHESS ENGINE") / sizeof('a') - 1);
        Print27Spaces(os, " Minha Ju", sizeof(" Minha Ju") / sizeof('a') - 1);
        Print27Spaces(os, " 2021 / 07 / 05", sizeof(" 2021 / 07 / 05") / sizeof('a') - 1);
        Print27Spaces(os, star_25, 25);
        os << std::endl;
        Print27Spaces(os, star_25, 25);

        int command = 0;
        do
        {
            Print27Spaces(os, " 1. PrintBoard", sizeof(" 1. PrintBoard") / sizeof('a') - 1);
            Print27Spaces(os, " 2. LoadBoard", sizeof(" 2. LoadBoard") / sizeof('a') - 1);
            Print27Spaces(os, " 3. PrintGameInformation", sizeof(" 3. PrintGameInformation") / sizeof('a') - 1);
            Print27Spaces(os, " 4. Exit", sizeof(" 4. Exit") / sizeof('a') - 1);
            Print27Spaces(os, hyphen_25, 25);

            std::string command_string;
            os << "  Command: ";
            is >> command_string;

            if (command_string[0] - '0' > 0 && '5' - command_string[0] > 0 && command_string[1] == '\0')
            {
                command = command_string[0] - '0';
            }
            else
            {
                command = 0;
            }

            switch (command)
            {
            case 1:
                PrintInitialBoard(os);
                Print27Spaces(os, hyphen_25, 25);
                break;
            case 2:
                LoadBoard(is, os);
                Print27Spaces(os, hyphen_25, 25);
                break;
            case 3:
                PrintGameInformation(is, os);
                Print27Spaces(os, hyphen_25, 25);
                break;
            case 4:
                Print27Spaces(os, hyphen_25, 25);
                Print27Spaces(os, " THANK YOU FOR PLAYING!", sizeof(" THANK YOU FOR PLAYING!") / sizeof('a') - 1);
                Print27Spaces(os, star_25, 25);
                break;
            default:
                Print27Spaces(os, hyphen_25, 25);
                Print27Spaces(os, " INVALID INPUT!", sizeof(" INVALID INPUT!") / sizeof('a') - 1);
                Print27Spaces(os, " PLEASE TRY AGAIN!", sizeof(" PLEASE TRY AGAIN!") / sizeof('a') - 1);
                Print27Spaces(os, hyphen_25, 25);
                break;
            }
        } while (command != 4);
    }

    void PrintInitialBoard(std::ostream& os)
    {
        os << std::endl;
        char chess_board[8][8];
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                chess_board[i][j] = ' ';
            }
        }
        chess_board[0][0] = 'R';
        chess_board[0][1] = 'N';
        chess_board[0][2] = 'B';
        chess_board[0][3] = 'K';
        chess_board[0][4] = 'Q';
        chess_board[0][5] = 'B';
        chess_board[0][6] = 'N';
        chess_board[0][7] = 'R';
        for (int i = 0; i < 8; i++)
        {
            chess_board[1][i] = 'P';
        }
        chess_board[7][0] = 'r';
        chess_board[7][1] = 'n';
        chess_board[7][2] = 'b';
        chess_board[7][3] = 'k';
        chess_board[7][4] = 'q';
        chess_board[7][5] = 'b';
        chess_board[7][6] = 'n';
        chess_board[7][7] = 'r';
        for (int i = 0; i < 8; i++)
        {
            chess_board[6][i] = 'p';
        }

        Print27Spaces(os, hyphen_25, 25);
        Print27Spaces(os, "   abcdefgh", 11);
        Print27Spaces(os, "  +--------+", 12);
        for (int i = 0; i < 8; i++)
        {
            char message[13] = { ' ' };
            message[1] = '0' + i;
            message[2] = '|';
            for (int j = 0; j < 8; j++)
            {
                message[3 + j] = chess_board[i][j];
            }
            message[11] = '|';
            message[12] = '\0';
            Print27Spaces(os, message, 12);
        }
        Print27Spaces(os, "  +--------+", 12);
    }

    void LoadBoard(std::istream& is, std::ostream& os)
    {
        os << std::endl;
        std::string file_name;
        is >> file_name;

        int black[6] = { 0 };
        int black_max[6] = { 8, 2, 2, 2, 1, 1 };
        int white[6] = { 0 };
        int white_max[6] = { 8, 2, 2, 2, 1, 1 };

        char chess_board[8][8];
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                chess_board[i][j] = ' ';
            }
        }

        std::ifstream fin(file_name);
        if (fin.is_open())
        {
            while (!fin.eof())
            {
                char chess_one_piece;
                char x;
                int y;
                fin >> chess_one_piece >> x >> y;


                int chess_piece_index = -1;
                for (int i = 0; i < 12; i++)
                {
                    if (chess_one_piece == available_pieces[i])
                    {
                        chess_piece_index = i;
                    }
                }

                if (x >= 'A' && x <= 'H')
                {
                    x -= 'A' - 'a';
                }

                if ((chess_piece_index > -1 && chess_piece_index < 12) && (x >= 'a' && x <= 'h') && (y >= 0 && y <= 7) && chess_board[y][x - 'a'] == ' ')
                {
                    if (chess_piece_index < 6)
                    { //black
                        if (black[chess_piece_index] == black_max[chess_piece_index])
                        {
                            continue;
                        }
                        ++black[chess_piece_index];
                    }
                    else
                    { //white
                        if (white[chess_piece_index - 6] == white_max[chess_piece_index - 6])
                        {
                            continue;
                        }
                        ++white[chess_piece_index - 6];
                    }
                    chess_board[y][x - 'a'] = chess_one_piece;
                }
            }
        }

        Print27Spaces(os, hyphen_25, 25);
        Print27Spaces(os, "   abcdefgh", 11);
        Print27Spaces(os, "  +--------+", 12);
        for (int i = 0; i < 8; i++)
        {
            char message[13] = { ' ' };
            message[1] = '0' + i;
            message[2] = '|';
            for (int j = 0; j < 8; j++)
            {
                message[3 + j] = chess_board[i][j];
            }
            message[11] = '|';
            message[12] = '\0';
            Print27Spaces(os, message, 12);
        }
        Print27Spaces(os, "  +--------+", 12);
        ;
    }

    void PrintGameInformation(std::istream& is, std::ostream& os)
    {
        os << std::endl;
        std::string file_name;
        is >> file_name;

        int black[6] = { 0 };
        int black_max[6] = { 8, 2, 2, 2, 1, 1 };
        int black_sum = 0;
        std::string black_name[6] = { " Black pawns:   ", " Black rooks:   ", " Black knights: ", " Black bishops: ", " Black queen:   ", " Black king:    " };

        int white[6] = { 0 };
        int white_max[6] = { 8, 2, 2, 2, 1, 1 };
        int white_sum = 0;
        std::string white_name[6] = { " White pawns:   ", " White rooks:   ", " White knights: ", " White bishops: ", " White queen:   ", " White king:    " };

        char chess_board[8][8];
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                chess_board[i][j] = ' ';
            }
        }

        std::ifstream fin(file_name);
        if (fin.is_open())
        {
            while (!fin.eof())
            {
                char chess_one_piece;
                char x;
                int y;
                fin >> chess_one_piece >> x >> y;

                int chess_piece_index = -1;
                for (int i = 0; i < 12; i++)
                {
                    if (chess_one_piece == available_pieces[i])
                    {
                        chess_piece_index = i;
                    }
                }

                if (x >= 'A' && x <= 'H')
                {
                    x -= 'A' - 'a';
                }

                if ((chess_piece_index > -1 && chess_piece_index < 12) && (x >= 'a' && x <= 'h') && (y >= 0 && y <= 7) && chess_board[y][x - 'a'] == ' ')
                {
                    if (chess_piece_index < 6)
                    { //black
                        if (black[chess_piece_index] == black_max[chess_piece_index])
                        {
                            continue;
                        }
                        ++black[chess_piece_index];
                    }
                    else
                    { //white
                        if (white[chess_piece_index - 6] == white_max[chess_piece_index - 6])
                        {
                            continue;
                        }
                        ++white[chess_piece_index - 6];
                    }
                    chess_board[y][x - 'a'] = chess_one_piece;
                }
            }
        }

        black_sum = black[0] * 100 + black[1] * 500 + black[2] * 320 + black[3] * 330 + black[4] * 900 + black[5] * 20000;
        white_sum = white[0] * 100 + white[1] * 500 + white[2] * 320 + white[3] * 330 + white[4] * 900 + white[5] * 20000;

        Print27Spaces(os, hyphen_25, 25);
        for (int i = 0; i < 6; i++)
        {
            char message[18] = {};
            message[17] = '\0';
            for (int j = 0; j < 16; j++)
            {
                message[j] = black_name[i][j];
            }
            message[16] = '0' + black[i];
            Print27Spaces(os, message, 17);
        }
        for (int i = 0; i < 6; i++)
        {
            char message[18] = {};
            message[17] = '\0';
            for (int j = 0; j < 16; j++)
            {
                message[j] = white_name[i][j];
            }
            message[16] = '0' + white[i];
            Print27Spaces(os, message, 17);
        }
        if (black[5] > 0 && white[5] > 0)
        {
            Print27Spaces(os, " Result: ON GOING GAME", sizeof(" Result: ON GOING GAME") / sizeof('a') - 1);
        }
        else if (black[5] > 0)
        {
            Print27Spaces(os, " Result: BLACK WIN", sizeof(" Result: BLACK WIN") / sizeof('a') - 1);
        }
        else if (white[5] > 0)
        {
            Print27Spaces(os, " Result: WHITE WIN", sizeof(" Result: WHITE WIN") / sizeof('a') - 1);
        }
        if (black_sum == white_sum)
        {
            Print27Spaces(os, " Who is winning?: NONE", sizeof(" Who is winning?: NONE") / sizeof('a') - 1);
        }
        else if (black_sum > white_sum)
        {
            Print27Spaces(os, " Who is winning?: BLACK", sizeof(" Who is winning?: BLACK") / sizeof('a') - 1);
        }
        else
        {
            Print27Spaces(os, " Who is winning?: WHITE", sizeof(" Who is winning?: WHITE") / sizeof('a') - 1);
        }

    }
}
