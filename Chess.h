/**
 * Raymond Curtis
 * CS 124
 * Section Z
 *
 * Fixed from project 1, also properly renamed this header file
 * Whitespace before :: and curly brackets have all been reformatted to a consistent style
 *
 * All code produced is mine, and utilized the framework provided by the instructor
 */

#ifndef CHESS_H
#define CHESS_H

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

/**
 * Class showing data of 20,000 chess games and their varying statistics See: https://www.kaggle.com/datasnaek/chess for additional details
 *
 * Fields (naming follows abbreviations used in CSV file):
 *     num_moves: number of moves performed in the game
 *     rated: boolean value showing if the game was rated or not
 *     created_at and last_move_at: represents the start and end time of the game
 *     turns: number of turns for the whole game
 *     victory_status: status of the game outcome
 *     winner: shows which player won the game, or resulted in a draw
 *     incremental_Code: unknown
 *     white_id: player who played the white piece's Lichess user ID
 *     white_rating: player who played the white piece's standard chess elo rating
 *     black_id: player who played the black piece's Lichess user ID
 *     black_rating: player who played the black piece's standard chess elo rating
 *     moves: the entire game's moves listed in chess algebraic notation
 *     opening_eco: a standardized code for openings
 *     opening_name: the name of the chess opening played, i.e. Sicilian Defense or Scandinavian Defense
 *     opening_ply: the number of moves it takes to move out of the early game
 */

class Chess{
    // private fields
private:
    std::string game_id;
    std::string rated;
    std::string created_at;
    std::string last_move_at;
    int turns;
    std::string victory_status;
    std::string winner;
    std::string increment_code;
    std::string white_id;
    int white_rating;
    std::string black_id;
    int black_rating;
    std::string moves;
    std::string opening_eco;
    std::string opening_name;
    int opening_ply;




public:
    // time to move into our public fields
    // default constructor
    Chess(){
        turns = white_rating = black_rating = opening_ply = 0;
        created_at = "INVALID";
        last_move_at = "INVALID";
        game_id = "rvcurtis";
        victory_status = "draw";
        winner = "draw";
        increment_code = "15+2";
        white_id = "magnus_carlsen";
        black_id = "hikaru";
        moves = "e4 c5";
        opening_eco = "D10";
        opening_name = "Sicilian Defense";
        rated = "true";
    }

    Chess(std::string game_id,
    std::string rated,
    std::string created_at,
    std::string last_move_at,
    int turns,
    std::string victory_status,
    std::string winner,
    std::string increment_code,
    std::string white_id,
    int white_rating,
    std::string black_id,
    int black_rating,
    std::string moves,
    std::string opening_eco,
    std::string opening_name,
    int opening_ply)
    {
        this->game_id = game_id;
        this->rated = rated;
        this->created_at = created_at;
        this->last_move_at = last_move_at;
        this->turns = turns;
        this->victory_status = victory_status;
        this->winner = winner;
        this->increment_code = increment_code;
        this->white_id = white_id;
        this->white_rating = white_rating;
        this->black_id = black_id;
        this->black_rating = black_rating;
        this->moves = moves;
        this->opening_eco = opening_eco;
        this->opening_name = opening_name;
        this->opening_ply = opening_ply;
    }

    // Setters and Getters
    // Const means the method cannot change the object

    //getters

    std::string getGame_id() const{
        return game_id;
    }

    std::string getRated() const{
        return rated;
    }

    std::string getCreated_at() const{
        return created_at;
    }

    std::string getLast_move_at() const{
        return last_move_at;
    }

    int getTurns() const{
        return turns;
    }

    std::string getVictory_Status() const{
        return victory_status;
    }

    std::string getWinner() const{
        return winner;
    }

    std::string getIncrement_code() const{
        return increment_code;
    }

    std::string getWhite_id() const{
        return white_id;
    }

    int getWhite_rating() const{
        return white_rating;
    }

    std::string getBlack_id() const{
        return black_id;
    }

    int getBlack_rating() const{
        return black_rating;
    }

    std::string getMoves() const{
        return moves;
    }

    std::string getOpening_eco() const{
        return opening_eco;
    }

    std::string getOpening_name() const{
        return opening_name;
    }

    int getOpening_ply() const{
        return opening_ply;
    }


    //setters
    void setGame_id(std::string game_id){
        this->game_id = game_id;
    }

    void setRated(std::string rated){
        this->rated = rated;
    }

    void setCreated_at(std::string created_at){
        this->created_at = created_at;
    }

    void setLast_move_at(std::string last_move_at){
        this->last_move_at = last_move_at;
    }

    void setTurns(int turns){
        this->turns= (turns <0) ?0: turns;
    }

    void setVictory_status(std::string victory_status) {
        this->victory_status = victory_status;
    }

    void setWinner(std::string winner) {
        this->winner = winner;
    }

    void setIncrement_code(std::string increment_code) {
        this->increment_code = increment_code;
    }

    void setWhite_id(std::string white_id){
        this->white_id= white_id;
    }

    void setWhite_rating(int white_rating) {
        this->white_rating= (white_rating < 0) ?0: white_rating;
    }

    void setBlack_id(std::string black_id){
        this->black_id= black_id;
    }

    void setBlack_rating(int black_rating){
        this->black_rating= (black_rating <0) ?0: black_rating;
    }

    void setMoves(std::string moves){
        this->moves= moves;
    }

    void setOpening_eco(std::string opening_eco){
        this->opening_eco= opening_eco;
    }

    void setOpening_name(std::string opening_name){
        this->opening_name= opening_name;
    }

    void setOpening_ply(int opening_ply){
        this->opening_ply= (opening_ply <0) ?0: opening_ply;
    }




    // We are going to overload the << operator to have our printed results be pretty
    friend std::ostream& operator << (std::ostream& outs, const Chess& game){
        outs << std::fixed
             << std::left
             << std::setprecision(4)
             << std::setw(20)<< game.getGame_id()
             << std::setw(10) << game.getRated()
             << std::right
             << std::setw(10) << game.getCreated_at()
             << std::setw(10) << game.getLast_move_at()
             << std::setw(5) << game.getTurns()
             << std::setw(20) << game.getVictory_Status()
             << std::setw(10) << game.getWinner()
             << std::setw(10) << game.getIncrement_code()
             << std::setw(5) << game.getWhite_rating()
             << std::setw(30) << game.getWhite_id()
             << std::setw(30) << game.getBlack_rating()
             << std::setw(30) << game.getBlack_id()
             << std::setw(10) << game.getMoves()
             << std::setw(20) << game.getOpening_eco()
             << std::setw(10) << game.getOpening_name()
             << std::setw(5) << game.getOpening_ply();

        return outs;
    }


};

    bool loadFromFile(std::string fn, std::vector<Chess>& objs){
        std::ifstream fin;
        fin.open(fn);

        if(!fin){
            // means that this is a bad file and couldn't open it
            return false;
        }

        // Get rid of that first header line
        std::string header = "";
        getline(fin, header);


        // Similar to class and example project, we want to read the data in while the file is still good
        int counter = 1;
        while(fin && fin.peek() != EOF){
            // We are going to set sentinel values to assure that created values are good to go
            std::string game_id = "INVALID";
            std::string created_at = "INVALID";
            std::string last_move_at = "INVALID";
            std::string rated = "true";
            int turns = -1;
            std::string victory_status = "INVALID";
            std:: string winner = "INVALID";
            std::string increment_code = "INVALID";
            std::string white_id = "INVALID";
            int white_rating = -1;
            std::string black_id = "INVALID";
            int black_rating = -1;
            std::string moves = "INVALID";
            std::string opening_eco = "INVALID";
            std::string opening_name = "INVALID";
            int opening_ply = -1;
            std::string junk;  // CBC

            char comma = ',';


            // start reading
            getline(fin, game_id, comma);
            getline(fin, rated, comma);
            getline(fin, created_at, comma);
            getline(fin, last_move_at, comma);

            //first int
            fin >> turns;
            fin >> comma;

            getline(fin, victory_status, comma);
            getline(fin, winner, comma);
            getline(fin, increment_code, comma);
            getline(fin, white_id, comma);

            fin >> white_rating;
            fin >> comma;

            getline(fin, black_id, comma);

            fin >> black_rating;
            fin >> comma;

            getline(fin, moves, comma);
            getline(fin, opening_eco, comma);
            getline(fin, opening_name, comma);

            if (fin.peek() != '\r' && fin.peek() != '\n') {
                fin >> opening_ply;
            }
            getline(fin, junk);


            // create a chess object and add it to the vector
            Chess game(game_id, rated, created_at, last_move_at, turns, victory_status, winner, increment_code, white_id, white_rating,
                       black_id, black_rating, moves, opening_eco, opening_name, opening_ply);
            objs.push_back(game);
            counter += 1;
        }
        fin.close();
        return true;
    }


void showVictory_status_stats(std::vector<Chess>& objs){
    int mates = 0;
    int out_of_time = 0;
    int draws = 0;
    int resigns = 0;
    int other = 0;
    int total;
    // counting the various outcomes of chess games, I expect it will be mostly draws due to the higher level of games this data set contains

    for (Chess& ch : objs) {
        std::string victory = ch.getVictory_Status();
        if (victory.compare("mate") == 0) {
            mates += 1;
        } else if (victory.compare("resign") == 0) {
            resigns += 1;
        } else if (victory.compare("draw") == 0) {
            draws += 1;
        } else if (victory.compare("outoftime") == 0) {
            out_of_time += 1;
        } else {
            // This should never happen! If this is anything other than
            // 0 we know something unexpected has occurred, e.g., some
            // value for KOI disposition not included in the above.
            other += 1;
        }
    }

    total = mates + resigns + draws + out_of_time + other;

    std::cout << std::endl;
    std::cout << "Victory statistics" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "mates" << std::right << std::setw(15)
              << mates << std::endl;
    std::cout << "resigns" << std::right << std::setw(16)
              << resigns << std::endl;
    std::cout << "draws" << std::right << std::setw(10)
              << draws << std::endl;
    std::cout << "out_of_time" << std::right << std::setw(8)
              << out_of_time << std::endl;
    std::cout << "Other" << std::right << std::setw(20)
              << other << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Total" << std::right << std::setw(20)
              << total << std::endl;
    std::cout << "==========================" << std::endl;
}


 void ChessTest(){
        Chess testObject = Chess();

        testObject.setGame_id("rvcurtis");
        assert(testObject.getGame_id() == "rvcurtis");

        testObject.setRated("true");
        assert(testObject.getRated() == "true");

        testObject.setCreated_at("1.50E +12");
        assert(testObject.getCreated_at() == "1.50E +12");

        testObject.setLast_move_at("1.70E +12");
        assert(testObject.getLast_move_at() == "1.70E +12");

        testObject.setTurns(1);
        assert(testObject.getTurns() == 1);

        testObject.setVictory_status("draw");
        assert(testObject.getVictory_Status() == "draw");

        testObject.setWinner("black");
        assert(testObject.getWinner() == "black");

        testObject.setIncrement_code("30+3");
        assert(testObject.getIncrement_code() == "30+3");

        testObject.setWhite_id("kasparov");
        assert(testObject.getWhite_id() == "kasparov");

        testObject.setWhite_rating(1200);
        assert(testObject.getWhite_rating() == 1200);

        testObject.setBlack_id("Beth Harmon");
        assert(testObject.getBlack_id() == "Beth Harmon");

        testObject.setBlack_rating(1200);
        assert(testObject.getBlack_rating() == 1200);

        testObject.setMoves("e4 c5");
        assert(testObject.getMoves() == "e4 c5");

        testObject.setOpening_eco("C50");
        assert(testObject.getOpening_eco() == "C50");

        testObject.setOpening_name("Sicilian Defense");
        assert(testObject.getOpening_name() == "Sicilian Defense");

        testObject.setOpening_ply(5);
        assert(testObject.getOpening_ply() == 5);

        // Second test object
        Chess testObject2 = Chess("game2", "false", "1.20E+12", "1.30E+12", 37, "mate", "white", "15+2","gotham", 2500, "northernlion",
                                  1500, "e4 e5", "B00", "Queen's Gambit", 10);
        assert(testObject2.getGame_id() == "game2");
        assert(testObject2.getRated() == "false");
        assert(testObject2.getCreated_at() == "1.20E+12");
        assert(testObject2.getLast_move_at() == "1.30E+12");
        assert(testObject2.getTurns() == 37);
        assert(testObject2.getVictory_Status() == "mate");
        assert(testObject2.getWinner() == "white");
        assert(testObject2.getIncrement_code() == "15+2");
        assert(testObject2.getWhite_id() == "gotham");
        assert(testObject2.getWhite_rating() == 2500);
        assert(testObject2.getBlack_id() == "northernlion");
        assert(testObject2.getBlack_rating() == 1500);
        assert(testObject2.getMoves() == "e4 e5");
        assert(testObject2.getOpening_eco() == "B00");
        assert(testObject2.getOpening_name() == "Queen's Gambit");
        assert(testObject2.getOpening_ply() == 10);
    }


    // I am adding to these overloaded operators for
    //overloaded the == operator in order to correctly compare 2 chess objects
    bool operator == (const Chess& Obj1, const Chess& Obj2){
        return Obj1.getGame_id() == Obj2.getGame_id();
    }

    // <= overloaded operator
    bool operator <= (const Chess& Obj1, const Chess Obj2){
        return Obj1.getGame_id() <= Obj2.getGame_id();
    }

    // >= overloaded operator
    bool operator >= (const Chess& Obj1, const Chess Obj2){
        return Obj1.getGame_id() >= Obj2.getGame_id();
    }

    // < overloaded operator
    bool operator < (const Chess& Obj1, const Chess Obj2){
        return Obj1.getGame_id() < Obj2.getGame_id();
    }

    // > overloaded operator
    bool operator > (const Chess& Obj1, const Chess Obj2){
        return Obj1.getGame_id() > Obj2.getGame_id();
    }

#endif





