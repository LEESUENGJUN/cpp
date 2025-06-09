#pragma once
#include "FileException.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct PlayInfo {
    std::string name;
    int nMove;
    double tElapsed;
    PlayInfo(const std::string& n = "Player", int m = 0, double t = 0.0)
        : name(n), nMove(m), tElapsed(t) {}
};

class RankingBoard {
    std::vector<PlayInfo> board;

public:
    RankingBoard() {}

    void store(const std::string& filename) {
        std::ofstream os(filename);
        if (!os)
            throw FileException(filename, false);

        for (const auto& p : board)
            os << p.name << " " << p.nMove << " " << p.tElapsed << "\n";
        os.close();
    }

    void load(const std::string& filename) {
        std::ifstream is(filename);
        if (!is)
            throw FileException(filename, true);

        board.clear();
        PlayInfo p;
        while (is >> p.name >> p.nMove >> p.tElapsed)
            board.push_back(p);
        is.close();
    }

    void add(const PlayInfo& p) {
        board.push_back(p);
    }

    void print(const std::string& title = "Ranking") const {
        std::cout << title << std::endl;
        for (const auto& p : board)
            std::cout << p.name << " " << p.nMove << " " << p.tElapsed << std::endl;
    }
};
