#include "Renderer.h"
#include "Constants.h"
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

void Renderer::gotoXY(int x, int y) {
    std::printf("\033[%d;%dH", y + 1, x + 1);
}

void Renderer::drawSelectStage(int stageIndex, int currency) {
    std::cout << CLEAR_SCREEN << CURSOR_HOME;
    std::cout << BOLD << CYAN << "===== SELECT STAGE =====" << RESET << std::endl;

    // 현재 보유 재화
    std::cout << YELLOW << "보유 재화: " << currency << RESET << "\n\n";

    // 스테이지 번호 출력
    std::cout << "    1     2     3" << std::endl;

    // 선택 화살표
    gotoXY(4 + stageIndex * 6, 4);
    std::cout << "↑" << std::endl;

    // 스테이지 입장 재화 표시
    std::cout << "\n입장 필요 재화: ";
    std::cout << " " << Constants::STAGE1_CURRENCY << "   ";
    std::cout << Constants::STAGE2_CURRENCY << "   ";
    std::cout << Constants::STAGE3_CURRENCY << std::endl;

    std::cout << "\n" << YELLOW << "화살표 ← →로 이동, ENTER로 선택" << RESET << std::endl;
}

void Renderer::drawGame(const Board& board, int score, int targetScore, int stage, int remainingTime, int lives) {
    std::cout << CURSOR_HOME;
    const auto& grid = board.getGrid(board.getCurrentBlock());

    std::cout << "\033[?25l"; // 커서 숨김
    int boardLeft = 3;
    int boardTop = 5;
    int infoLeft = Board::COLS * 2 + 15;

    for (int i = 4; i < Board::ROWS; ++i) {
        gotoXY(boardLeft, boardTop + (i - 4));

        for (int j = 0; j < Board::COLS; ++j) {
            BrickEnum type = grid[i][j].getBrickType();


            switch (type) {
            case BrickEnum::EmptyBrick:
                std::cout << WHITE << "□ " << RESET;
                break;
            case BrickEnum::RectangleBrick:
                std::cout << BLUE << "■ " << RESET;
                break;
            case BrickEnum::ReverseLBrick:
                std::cout << CYAN << "■ " << RESET;
                break;
            case BrickEnum::StickBrick:
                std::cout << BRIGHT_BLUE << "■ " << RESET;
                break;
            case BrickEnum::TBrick:
                std::cout << MAGENTA << "■ " << RESET;
                break;
            case BrickEnum::LBrick:
                std::cout << BRIGHT_YELLOW << "■ " << RESET;
                break;
            case BrickEnum::ZBrick:
                std::cout << RED << "■ " << RESET;
                break;
            case BrickEnum::SBrick:
                std::cout << GREEN << "■ " << RESET;
                break;
            case BrickEnum::BombBrick:
                std::cout << BRIGHT_RED << "▩ " << RESET;
                break;
            case BrickEnum::EnergyBrick:
                std::cout << BRIGHT_MAGENTA << "▣ " << RESET;
                break;
            case BrickEnum::WallBrick:
                std::cout << BRIGHT_BLACK << "■ " << RESET;
                break;
            default:
                std::cout << "  ";
                break;
            }
        }

        gotoXY(infoLeft, boardTop + (i - 4));

        switch (i) {
        case 4:  std::cout << BOLD << "Orbit Stabilizer" << RESET; break;
        case 6:  std::cout << "  Stage     : " << stage; break;
        case 7:  std::cout << "  Time Left : " << std::setw(3) << (remainingTime); break;
        case 9:  std::cout << "  Score:"; break;
        case 10: {
            int barLength = 24;
            int filled = std::min(barLength, static_cast<int>(score * 1.0 / targetScore * barLength));
            std::cout << "  [";
            for (int i = 0; i < barLength; ++i) {
                if (i < filled) std::cout << GREEN << "#" << RESET;
                else std::cout << "-";
            }
            std::cout << "]";

            break;
        }
        case 11: std::cout << "  " << score << " pts (목표: " << targetScore << " pts)"; break;
        case 13: {
            std:: cout << "  Life      : ";
            std::string lifeBar = "";
            for (int l = 0; l < lives; ++l) lifeBar += "♥";
            for (int l = lives; l < 3; ++l) lifeBar += " ";
            std::cout << std::setw(7) <<lifeBar;
            break;
        }
        case 14: std::cout << BRIGHT_RED << "▩ " << "  Explosive Block "; break;
        case 15: std::cout << BRIGHT_MAGENTA << "▣ " << "  Energy Core Block"; break;
        case 17: std::cout << "  Controls:"; break;
        case 18: std::cout << "  ← → ↓ : Move Block"; break;
        case 19: std::cout << "  ↑     : Rotate Block"; break;
        case 20: std::cout << "  Space : Hard Drop"; break;
        }
    }


    std::cout << "\033[?25h"; // 커서 표시
    gotoXY(10000000, 10000000);
}

void Renderer::showStageClear(int stage, int stabilizer, int score) {
    system("cls");
    std::string border = "==============================";
    std::cout << GREEN << border << "\n"
        << "|        STAGE CLEAR        |\n"
        << border << RESET << std::endl;
    std::cout << GREEN << "Stage " << stage + 1 << " Cleared!\n"
        << "You earned stabilizer: +" << stabilizer << RESET << std::endl;
    std::cout << GREEN << "You earned score: +" << score << RESET << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << YELLOW << "\nPress ENTER to continue..." << RESET << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Renderer::showGameOver() {
    system("cls");
    std::string border = "==============================";
    std::cout << RED << BOLD << border << "\n"
        << "|         GAME OVER         |\n"
        << border << RESET << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << YELLOW << "\nPress ENTER to continue..." << RESET << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Renderer::showIntro() {
    const std::string titleArt = R"(
   _______        _        _______           _______  _______  _______ 
  (  ____ \      ( \      (  ___  )|\     /|(  ____ \(  ____ \(  ____ \
  | (    \/      | (      | (   ) |( \   / )| (    \/| (    \/| (    \/
  | (_____       | |      | |   | | \ (_) / | (__    | (__    | (_____ 
  (_____  )      | |      | |   | |  ) _ (  |  __)   |  __)   (_____  )
        ) |      | |      | |   | | / ( ) \ | (      | (            ) |
  /\____) | _  __| |__  _ | (___) |( /   \ )| (____/\| (____/\/\____) |
  \_______)(_)(_______)(_)(_______)|/     \|(_______/(_______/\_______)
    )";

    const std::string frameTop = "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    const std::string frameBottom = "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";

    std::cout << CLEAR_SCREEN << CURSOR_HOME;
    std::cout << CYAN << frameTop << RESET << std::endl;

    std::istringstream artStream(titleArt);
    std::string line;
    while (std::getline(artStream, line)) {
        std::cout << CYAN << RESET << BOLD << line << RESET << CYAN <<  RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << CYAN << frameBottom << RESET << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "\n" << GREEN << BOLD
        << "우주 쓰레기와 위성 파편을 피해 블록을 쌓아 인류를 구하라!\n"
        << "시간 내로 구조를 완성하지 못하면 궤도는 붕괴된다..." << RESET << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "\n" << YELLOW << "Press ENTER to start..." << RESET << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void Renderer::showStory() {
    std::cout << CLEAR_SCREEN << CURSOR_HOME;
    std::string borderTop = "┌──────────────────────────────────────────────────────────────┐";
    std::string borderBottom = "└──────────────────────────────────────────────────────────────┘";

    std::cout << BOLD << CYAN << borderTop << RESET << std::endl;
    std::vector<std::string> lines = {
        " 인류는 우주로 진출했지만, 인공위성 파편과 우주 쓰레기로 인해       ",
        " 지구 궤도가 망가졌다. 임무는 간단하다: 구조 블록을 정확히        ",
        " 쌓아 궤도를 안정화시키자. 그러나 블록에는 폭탄과 에너지 코어가     ",
        " 포함되어 있다. 조심히 쌓지 않으면 궤도는 더 망가진다!            ",
        " 제한된 시간 안에 궤도를 지켜라!                                  "
    };
    for (const auto& line : lines) {
        std::cout << CYAN << line << RESET << std::endl;
    }
    std::cout << CYAN << borderBottom << RESET << std::endl;

    std::cout << YELLOW << "\nPress ENTER to continue..." << RESET << std::endl;
    std::cin.get();
}

void Renderer::showInsufficientCurrency(int required) {
    std::string border = "******************************";
    std::cout << RED << border << "\n"
        << "*      입장 불가 경고        *\n"
        << border << RESET << std::endl;
    std::cout << "[!] " << required << " 스태빌라이저가 필요합니다.\n"
        << "보유량이 부족합니다. 다른 스테이지를 선택해주세요." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Renderer::showStageEntryConfirm(int required) {
    std::string border = "==============================";
    std::cout << YELLOW << border << "\n"
        << "| STAGE ENTRY CONFIRMATION |\n"
        << border << RESET << std::endl;
    std::cout << "\n이 스테이지 입장에는 "
        << BOLD << required << RESET << YELLOW
        << " 스태빌라이저가 필요합니다.\n"
        << "입장하시겠습니까? (y/n): " << RESET;
}

void Renderer::showEnding() {
    std::cout << CLEAR_SCREEN << CURSOR_HOME;

    std::cout << BOLD << GREEN;
    std::cout << "=====================================\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "       임무 완료 - 궤도 안정화\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "=====================================\n\n";
    std::cout << RESET;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << CYAN;
    std::cout << "정해진 시간 안에 모든 구조 블록을 정리했어.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "지구 궤도는 안정됐고, 인류는 다시 통신을 되찾았지.\n\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "수많은 우주 쓰레기 사이에서 네 판단력과 집중력이\n";
    std::cout << "지구를 구했어. 정말 잘했어!\n";
    std::cout << RESET;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "\n" << BRIGHT_BLUE << "지금, 지구는 다시 숨을 쉬고 있어..." << RESET << "\n\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << YELLOW << "\nENTER를 누르면 메인 메뉴로 돌아갑니다...\n" << RESET << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Renderer::clearLine(const Board& board, int row)
{
    std::cout << CURSOR_HOME;
    const auto& grid = board.getGrid(board.getCurrentBlock());

    std::cout << "\033[?25l"; // 커서 숨김
    int boardLeft = 3;
    int boardTop = 5;
    int infoLeft = Board::COLS * 2 + 15;

    if (!(4 <= row && row < Board::ROWS)) {
        return;
    }

    gotoXY(boardLeft, boardTop + (row - 4));

    for (int j = 0; j < Board::COLS; ++j) {
        std::cout << BRIGHT_BLACK << "□ " << RESET;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    
    std::cout << "\033[?25h";
    gotoXY(10000000, 10000000);
}

void Renderer::drawBomb(const Board& board, list<pair<int, int>> bomb)
{
    std::cout << "\033[?25l"; // 커서 숨김
    int iterNum = 3; // 깜빡임 몇번 반복할지

    const auto& grid = board.getGrid(board.getCurrentBlock());

    int boardLeft = 3;
    int boardTop = 5;
    int infoLeft = Board::COLS * 2 + 15;

    //깜빡거리는 시간 ms
    int time = 300;
    for (int roop = 0; roop < iterNum; roop++) {
        
        for (auto i : bomb) {

            int row = i.first;

            gotoXY(boardLeft, boardTop + (row - 4));

            for (int j = 0; j < Board::COLS; ++j) {
                BrickEnum type = grid[row][j].getBrickType();

                if (grid[row][j].getIsExplosive()) {
                    std::cout << BRIGHT_BLACK << "□ " << RESET;
                    continue;
                }
                else {
                    switch (type) {
                    case BrickEnum::EmptyBrick:
                        std::cout << WHITE << "□ " << RESET;
                        break;
                    case BrickEnum::RectangleBrick:
                        std::cout << BLUE << "■ " << RESET;
                        break;
                    case BrickEnum::ReverseLBrick:
                        std::cout << CYAN << "■ " << RESET;
                        break;
                    case BrickEnum::StickBrick:
                        std::cout << BRIGHT_BLUE << "■ " << RESET;
                        break;
                    case BrickEnum::TBrick:
                        std::cout << MAGENTA << "■ " << RESET;
                        break;
                    case BrickEnum::LBrick:
                        std::cout << BRIGHT_YELLOW << "■ " << RESET;
                        break;
                    case BrickEnum::ZBrick:
                        std::cout << RED << "■ " << RESET;
                        break;
                    case BrickEnum::SBrick:
                        std::cout << GREEN << "■ " << RESET;
                        break;
                    case BrickEnum::BombBrick:
                        std::cout << BRIGHT_RED << "▩ " << RESET;
                        break;
                    case BrickEnum::EnergyBrick:
                        std::cout << BRIGHT_MAGENTA << "▣ " << RESET;
                        break;
                    case BrickEnum::WallBrick:
                        std::cout << BRIGHT_BLACK << "■ " << RESET;
                        break;
                    default:
                        std::cout << "  ";
                        break;
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(time));

        for (auto i : bomb) {

            int row = i.first;
            int col = i.second;

            gotoXY(boardLeft, boardTop + (row - 4));

            for (int j = 0; j < Board::COLS; ++j) {
                BrickEnum type = grid[row][j].getBrickType();


                switch (type) {
                case BrickEnum::EmptyBrick:
                    std::cout << WHITE << "□ " << RESET;
                    break;
                case BrickEnum::RectangleBrick:
                    std::cout << BLUE << "■ " << RESET;
                    break;
                case BrickEnum::ReverseLBrick:
                    std::cout << CYAN << "■ " << RESET;
                    break;
                case BrickEnum::StickBrick:
                    std::cout << BRIGHT_BLUE << "■ " << RESET;
                    break;
                case BrickEnum::TBrick:
                    std::cout << MAGENTA << "■ " << RESET;
                    break;
                case BrickEnum::LBrick:
                    std::cout << BRIGHT_YELLOW << "■ " << RESET;
                    break;
                case BrickEnum::ZBrick:
                    std::cout << RED << "■ " << RESET;
                    break;
                case BrickEnum::SBrick:
                    std::cout << GREEN << "■ " << RESET;
                    break;
                case BrickEnum::BombBrick:
                    std::cout << BRIGHT_RED << "▩ " << RESET;
                    break;
                case BrickEnum::EnergyBrick:
                    std::cout << BRIGHT_MAGENTA << "▣ " << RESET;
                    break;
                case BrickEnum::WallBrick:
                    std::cout << BRIGHT_BLACK << "■ " << RESET;
                    break;
                default:
                    std::cout << "  ";
                    break;
                }
                
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(300));

    }


}
