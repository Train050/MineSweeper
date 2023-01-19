#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include "TileData.h"
#include "Random.h"
#include "TextureManager.h"
using namespace std;

int main()
{
    //Read file contents to get size of window
    string fileName = "boards/config.cfg";
    string inputLine = "";
    int heightSize = 0;
    int widthSize = 0;
    int numOfMines = 0;
    int gameVersion = 0;
    int totalMines = 0;
    int expectedFlags = 0;
    int totalTiles = 0;
    bool debugStatus = false;
    bool endCondition = false;
    bool hitMine = false;
    bool bypassSettings = false;

    ifstream file(fileName);

    if (!file.is_open())
    {
        file.open(fileName);
    }

    //gets the width, length, and number of mines
    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            file >> widthSize;
        }
        else if (i == 1)
        {
            file >> heightSize;
        }
        else
        {
            file >> numOfMines;
        }
    }

    file.close();

    //Get all of the sprites that could be used
    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite digits(TextureManager::GetTexture("digits"));
    sf::Sprite face_happy(TextureManager::GetTexture("face_happy"));
    sf::Sprite face_lose(TextureManager::GetTexture("face_lose"));
    sf::Sprite face_win(TextureManager::GetTexture("face_win"));
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    sf::Sprite number_1(TextureManager::GetTexture("number_1"));
    sf::Sprite number_2(TextureManager::GetTexture("number_2"));
    sf::Sprite number_3(TextureManager::GetTexture("number_3"));
    sf::Sprite number_4(TextureManager::GetTexture("number_4"));
    sf::Sprite number_5(TextureManager::GetTexture("number_5"));
    sf::Sprite number_6(TextureManager::GetTexture("number_6"));
    sf::Sprite number_7(TextureManager::GetTexture("number_7"));
    sf::Sprite number_8(TextureManager::GetTexture("number_8"));
    sf::Sprite test_1(TextureManager::GetTexture("test_1"));
    sf::Sprite test_2(TextureManager::GetTexture("test_2"));
    sf::Sprite test_3(TextureManager::GetTexture("test_3"));
    sf::Sprite tile_hidden(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite tile_revealed(TextureManager::GetTexture("tile_revealed"));

    //window which contains everything
    sf::RenderWindow window(sf::VideoMode((widthSize * 32), ((heightSize * 32) + 100)), "Minesweeper");

    vector<vector<TileData>> Tiles;

    for (int row = 0; row < heightSize; row++)
    {
        vector<TileData> tempTiles;

        for (int col = 0; col < widthSize; col++)
        {
            TileData tempTile;
            tempTiles.push_back(tempTile);
        }

        Tiles.push_back(tempTiles);
    }

    //will run as long as the window is open
    while (window.isOpen())
    {
        //default game state with randomly generated mines
        if (gameVersion == 0)
        {
            if (bypassSettings == false)
            {
                fileName = "boards/config.cfg";
                ifstream file(fileName);

                if (!file.is_open())
                {
                    file.open(fileName);
                }

                //gets the width, length, and number of mines
                for (int i = 0; i < 3; i++)
                {
                    if (i == 0)
                    {
                        file >> widthSize;
                    }
                    else if (i == 1)
                    {
                        file >> heightSize;
                    }
                    else
                    {
                        file >> numOfMines;
                    }
                }

                file.close();

                totalMines = numOfMines;

                //for the number of mines, will set random ones as mine status
                while (totalMines > 0)
                {
                    for (int r = 0; r < Tiles.size(); r++)
                    {
                        for (int c = 0; c < Tiles[r].size(); c++)
                        {
                            if (Random::Int(0, 20) == 15 && Tiles[r][c].getMineStatus() == false && totalMines > 0)
                            {
                                Tiles[r][c].setMineStatus(true);
                                totalMines--;
                            }
                        }
                    }
                }
                totalMines = numOfMines;
                expectedFlags = numOfMines;
                totalTiles = (widthSize * heightSize) - numOfMines;
            }
        }
        //will load in custom board 1
        else if (gameVersion == 1)
        {
            if (bypassSettings == false)
            {
                numOfMines = 0; 

                //fileName = "boards/lots_o_mines.brd";
                //fileName = "boards/recursion_test.brd";
                fileName = "boards/testboard1.brd";

                ifstream anotherFile(fileName);

                if (!anotherFile.is_open())
                {
                    anotherFile.open(fileName);
                }

                for (int r = 0; r < Tiles.size(); r++)
                {
                    anotherFile >> inputLine;
                    for (int c = 0; c < Tiles[r].size(); c++)
                    {
                        int tempValue = stoi(inputLine.substr(0, 1));
                        inputLine = inputLine.substr(1);

                        if (tempValue == 1)
                        {
                            Tiles[r][c].setMineStatus(true);
                            numOfMines++;
                        }
                    }
                }

                anotherFile.close();
            }

        }
        //will load in custom board 2
        else if (gameVersion == 2)
        {
            if (bypassSettings == false)
            {
                numOfMines = 0;

                fileName = "boards/testboard2.brd";
                ifstream anotherFile(fileName);

                if (!anotherFile.is_open())
                {
                    anotherFile.open(fileName);
                }

                for (int r = 0; r < Tiles.size(); r++)
                {
                    anotherFile >> inputLine;
                    for (int c = 0; c < Tiles[r].size(); c++)
                    {
                        int tempValue = stoi(inputLine.substr(0, 1));
                        inputLine = inputLine.substr(1);

                        if (tempValue == 1)
                        {
                            Tiles[r][c].setMineStatus(true);
                            numOfMines++;
                        }
                    }
                }

                anotherFile.close();
            }
        }
        //will load in custom board 3
        else if (gameVersion == 3)
        {
            if (bypassSettings == false)
            {
                numOfMines = 0;

                fileName = "boards/testboard3.brd";
                ifstream anotherFile(fileName);

                if (!anotherFile.is_open())
                {
                    anotherFile.open(fileName);
                }

                for (int r = 0; r < Tiles.size(); r++)
                {
                    anotherFile >> inputLine;
                    for (int c = 0; c < Tiles[r].size(); c++)
                    {
                       int tempValue = stoi(inputLine.substr(0, 1));
                       inputLine = inputLine.substr(1);

                       if (tempValue == 1)
                       {
                           Tiles[r][c].setMineStatus(true);
                           numOfMines++;
                       }
                    }
                }

                anotherFile.close();
            }
        }

        if (bypassSettings == false)
        {
            //will execute regardless of boards
            for (int r = 0; r < Tiles.size(); r++)
            {
                for (int c = 0; c < Tiles[r].size(); c++)
                {
                    int surroundingMines = 0;

                    //assigns the values of each tile depending on how many mines are around it
                    if (Tiles[r][c].getMineStatus() == false)
                    {
                        if (r == 0)
                        {
                            //top left corner case
                            if (c == 0)
                            {
                                if ((Tiles[r + 1][c].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r + 1][c + 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if (Tiles[r][c + 1].getMineStatus() == true)
                                {
                                    surroundingMines++;
                                }
                            }
                            //top row case
                            else if (c > 0 && c < Tiles[r].size() - 1)
                            {
                                if ((Tiles[r + 1][c + 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r + 1][c].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r + 1][c - 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r][c - 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r][c + 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                            }
                            //top right corner case
                            else if (c == Tiles[r].size() - 1)
                            {
                                if ((Tiles[r + 1][c - 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r + 1][c].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if (Tiles[r][c - 1].getMineStatus() == true)
                                {
                                    surroundingMines++;
                                }
                            }
                        }
                        else if (c == 0)
                        {
                            //left wall case
                            if (r > 0 && r < Tiles.size() - 1)
                            {
                                if ((Tiles[r - 1][c].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r - 1][c + 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if (Tiles[r][c + 1].getMineStatus() == true)
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r + 1][c + 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r + 1][c].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                            }
                            //bottom left corner case
                            else if (r == Tiles.size() - 1)
                            {
                                if ((Tiles[r - 1][c].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r - 1][c + 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if (Tiles[r][c + 1].getMineStatus() == true)
                                {
                                    surroundingMines++;
                                }
                            }
                        }
                        else if (c == Tiles[r].size() - 1)
                        {
                            //right wall case
                            if (r > 0 && r < Tiles.size() - 1)
                            {
                                if ((Tiles[r - 1][c].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r - 1][c - 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if (Tiles[r][c - 1].getMineStatus() == true)
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r + 1][c - 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r + 1][c].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                            }
                            //bottom right corner case
                            else if (r == Tiles.size() - 1)
                            {
                                if ((Tiles[r - 1][c].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r - 1][c - 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if (Tiles[r][c - 1].getMineStatus() == true)
                                {
                                    surroundingMines++;
                                }
                            }
                        }
                        else if (r == Tiles.size() - 1)
                        {
                            //bottom row of board case
                            if (c > 0 && c < Tiles[r].size() - 1)
                            {
                                if ((Tiles[r][c - 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r - 1][c - 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if (Tiles[r - 1][c].getMineStatus() == true)
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r - 1][c + 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                                if ((Tiles[r][c + 1].getMineStatus() == true))
                                {
                                    surroundingMines++;
                                }
                            }
                        }
                        //as long as a tile isn't a corner or edge
                        else
                        {
                            if ((Tiles[r + 1][c + 1].getMineStatus() == true))
                            {
                                surroundingMines++;
                            }
                            if ((Tiles[r - 1][c - 1].getMineStatus() == true))
                            {
                                surroundingMines++;
                            }
                            if ((Tiles[r + 1][c - 1].getMineStatus() == true))
                            {
                                surroundingMines++;
                            }
                            if ((Tiles[r - 1][c + 1].getMineStatus() == true))
                            {
                                surroundingMines++;
                            }
                            if ((Tiles[r][c + 1].getMineStatus() == true))
                            {
                                surroundingMines++;
                            }
                            if ((Tiles[r + 1][c].getMineStatus() == true))
                            {
                                surroundingMines++;
                            }
                            if ((Tiles[r][c - 1].getMineStatus() == true))
                            {
                                surroundingMines++;
                            }
                            if ((Tiles[r - 1][c].getMineStatus() == true))
                            {
                                surroundingMines++;
                            }
                        }
                    }
                    //will resize vector to number of mines
                    Tiles[r][c].setNumOfNeighbors(surroundingMines);
                }
            }
            //updates all data as different game versions need updates
            totalMines = numOfMines;
            expectedFlags = numOfMines;
            totalTiles = (widthSize * heightSize) - numOfMines;
            bypassSettings = true;
        }

        window.clear(sf::Color::White);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);

            //first checks is a mouse is pressed
            if (event.type == sf::Event::MouseButtonPressed)
            {
                //left clicking
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::FloatRect toggleDebug = debug.getGlobalBounds();
                    sf::FloatRect firstTest = test_1.getGlobalBounds();
                    sf::FloatRect secondTest = test_2.getGlobalBounds();
                    sf::FloatRect thirdTest = test_3.getGlobalBounds();

                    //ensures mouse is within the window
                    if ((currentMousePosition.y / 32) < heightSize && (currentMousePosition.x / 32) < widthSize && (currentMousePosition.y / 32) >= 0 && (currentMousePosition.x / 32) >= 0)
                    {
                        TileData& currentTile = Tiles[currentMousePosition.y / 32][currentMousePosition.x / 32];

                        //sets reveal status
                        if (currentTile.getRevealStatus() == false && currentTile.getFlagStatus() == false && endCondition == false)
                        {
                            currentTile.setRevealStatus(true);
                        }
                    }

                    //toggles debug button
                    if (toggleDebug.contains(currentMousePosition.x, currentMousePosition.y) && endCondition == false)
                    {
                        if (debugStatus == false)
                        {
                            debugStatus = true;
                        }
                        else
                        {
                            debugStatus = false;
                        }
                    }

                    //toggles happy face button restart
                    if (endCondition != true)
                    {
                        sf::FloatRect happyFace = face_happy.getGlobalBounds();

                        if (happyFace.contains(currentMousePosition.x, currentMousePosition.y) && endCondition == false)
                        {
                            gameVersion = 0;
                            endCondition = false;
                            bypassSettings = false;
                            hitMine = false;
                            totalTiles = (widthSize * heightSize) - numOfMines;

                            for (int r = 0; r < Tiles.size(); r++)
                            {
                                for (int c = 0; c < Tiles[r].size(); c++)
                                {
                                    Tiles[r][c].setMineStatus(false);
                                    Tiles[r][c].setFlagStatus(false);
                                    Tiles[r][c].setRevealStatus(false);
                                    Tiles[r][c].setCountedStatus(false);
                                    Tiles[r][c].setNumOfNeighbors(0);
                                }
                            }
                        }
                    }
                    //toggles the win face button reset
                    else if (endCondition == true && hitMine == false && totalTiles == 0)
                    {
                        sf::FloatRect winFace = face_win.getGlobalBounds();

                        if (winFace.contains(currentMousePosition.x, currentMousePosition.y) && endCondition == true)
                        {
                            gameVersion = 0;
                            endCondition = false;
                            bypassSettings = false;
                            hitMine = false;
                            totalTiles = (widthSize * heightSize) - numOfMines;

                            for (int r = 0; r < Tiles.size(); r++)
                            {
                                for (int c = 0; c < Tiles[r].size(); c++)
                                {
                                    Tiles[r][c].setMineStatus(false);
                                    Tiles[r][c].setFlagStatus(false);
                                    Tiles[r][c].setRevealStatus(false);
                                    Tiles[r][c].setCountedStatus(false);
                                    Tiles[r][c].setNumOfNeighbors(0);
                                }
                            }
                        }
                    }
                    //toggles the lose face button reset
                    else if (endCondition == true && hitMine == true)
                    {
                        sf::FloatRect loseFace = face_lose.getGlobalBounds();

                        if (loseFace.contains(currentMousePosition.x, currentMousePosition.y) && endCondition == true)
                        {
                            gameVersion = 0;
                            endCondition = false;
                            bypassSettings = false;
                            hitMine = false;
                            totalTiles = (widthSize * heightSize) - numOfMines;

                            for (int r = 0; r < Tiles.size(); r++)
                            {
                                for (int c = 0; c < Tiles[r].size(); c++)
                                {
                                    Tiles[r][c].setMineStatus(false);
                                    Tiles[r][c].setFlagStatus(false);
                                    Tiles[r][c].setRevealStatus(false);
                                    Tiles[r][c].setCountedStatus(false);
                                    Tiles[r][c].setNumOfNeighbors(0);
                                }
                            }
                        }
                    }
                    //toggles the first game test button
                    if (firstTest.contains(currentMousePosition.x, currentMousePosition.y))
                    {
                        gameVersion = 1;
                        endCondition = false;
                        bypassSettings = false;
                        hitMine = false;
                        totalTiles = (widthSize * heightSize) - numOfMines;

                        for (int r = 0; r < Tiles.size(); r++)
                        {
                            for (int c = 0; c < Tiles[r].size(); c++)
                            {
                                Tiles[r][c].setMineStatus(false);
                                Tiles[r][c].setFlagStatus(false);
                                Tiles[r][c].setRevealStatus(false);
                                Tiles[r][c].setCountedStatus(false);
                                Tiles[r][c].setNumOfNeighbors(0);
                            }
                        }
                    }
                    //toggles the second game test button
                    if (secondTest.contains(currentMousePosition.x, currentMousePosition.y))
                    {
                        gameVersion = 2;
                        endCondition = false;
                        bypassSettings = false;
                        hitMine = false;
                        totalTiles = (widthSize * heightSize) - numOfMines;

                        for (int r = 0; r < Tiles.size(); r++)
                        {
                            for (int c = 0; c < Tiles[r].size(); c++)
                            {
                                Tiles[r][c].setMineStatus(false);
                                Tiles[r][c].setFlagStatus(false);
                                Tiles[r][c].setRevealStatus(false);
                                Tiles[r][c].setCountedStatus(false);
                                Tiles[r][c].setNumOfNeighbors(0);
                            }
                        }
                    }
                    //toggles the third game test button
                    if (thirdTest.contains(currentMousePosition.x, currentMousePosition.y))
                    {
                        gameVersion = 3;
                        endCondition = false;
                        bypassSettings = false;
                        hitMine = false;
                        totalTiles = (widthSize * heightSize) - numOfMines;

                        for (int r = 0; r < Tiles.size(); r++)
                        {
                            for (int c = 0; c < Tiles[r].size(); c++)
                            {
                                Tiles[r][c].setMineStatus(false);
                                Tiles[r][c].setFlagStatus(false);
                                Tiles[r][c].setRevealStatus(false);
                                Tiles[r][c].setCountedStatus(false);
                                Tiles[r][c].setNumOfNeighbors(0);
                            }
                        }
                    }
                }

                //right clicking
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    //as long as the mouse is within the game tile window
                    if ((currentMousePosition.y / 32) < heightSize && (currentMousePosition.x / 32) < widthSize && (currentMousePosition.y / 32) >= 0 && (currentMousePosition.x / 32) >= 0)
                    {
                        TileData& currentTile = Tiles[currentMousePosition.y / 32][currentMousePosition.x / 32];

                        //enables flag to be placed
                        if (currentTile.getFlagStatus() == false && currentTile.getRevealStatus() == false && endCondition == false)
                        {
                            currentTile.setFlagStatus(true);
                            expectedFlags--;
                        }
                        //removes the flag
                        else if (currentTile.getFlagStatus() == true && currentTile.getRevealStatus() == false && endCondition == false)
                        {
                            currentTile.setFlagStatus(false);
                            expectedFlags++;
                        }
                    }
                }
            }
        }

        //runs for all of the cells in the board over and over
        for (int r = 0; r < Tiles.size(); r++)
        {
            for (int c = 0; c < Tiles[r].size(); c++)
            {
                //if tile is hidden shows hidden cell every time
                if (Tiles[r][c].getRevealStatus() == false)
                {
                    tile_hidden.setPosition(c * 32, r * 32);
                    window.draw(tile_hidden);

                    //draws flag over hidden tile
                    if (Tiles[r][c].getFlagStatus() == true)
                    {
                        flag.setPosition(c * 32, r * 32);
                        window.draw(flag);
                    }

                    //draws bombs over hidden tiles if debug is active
                    if (debugStatus == true)
                    {
                        if (Tiles[r][c].getMineStatus() == true)
                        {
                            mine.setPosition(c * 32, r * 32);
                            window.draw(mine);
                        }
                    }
                }
                //always draws a revealed tile if the tile is condition revealed
                else if (Tiles[r][c].getRevealStatus() == true)
                {
                    tile_revealed.setPosition(c * 32, r * 32);
                    window.draw(tile_revealed);

                    //counts each revealed tile for the victory condition a single time
                    if (Tiles[r][c].getCountedStatus() == false && Tiles[r][c].getMineStatus() == false)
                    {
                        totalTiles--;
                        Tiles[r][c].setCountedStatus(true);
                    }

                    //revealing algorithm
                    if (Tiles[r][c].getNumOfNeighbors() == 0 && Tiles[r][c].getMineStatus() == false)
                    {
                        //special case of edges is gone through and then normal inner tiles
                        if (r == 0)
                        {
                            if (c == 0)
                            {
                                //same order as the algorithm that checks surrounding tiles for bombs and assigns number, top left
                                if ((Tiles[r + 1][c].getMineStatus() == false) && Tiles[r + 1][c].getFlagStatus() == false && Tiles[r + 1][c].getRevealStatus() == false)
                                {
                                    Tiles[r + 1][c].setRevealStatus(true);
                                }
                                if ((Tiles[r + 1][c + 1].getMineStatus() == false) && Tiles[r + 1][c + 1].getFlagStatus() == false && Tiles[r + 1][c + 1].getRevealStatus() == false)
                                {
                                    Tiles[r + 1][c + 1].setRevealStatus(true);
                                }
                                if (Tiles[r][c + 1].getMineStatus() == false && Tiles[r][c + 1].getFlagStatus() == false && Tiles[r][c + 1].getRevealStatus() == false)
                                {
                                    Tiles[r][c + 1].setRevealStatus(true);
                                }
                            }
                            else if (c > 0 && c < Tiles[r].size() - 1)
                            {
                                if ((Tiles[r + 1][c + 1].getMineStatus() == false) && Tiles[r + 1][c + 1].getFlagStatus() == false && Tiles[r + 1][c + 1].getRevealStatus() == false)
                                {
                                    Tiles[r + 1][c + 1].setRevealStatus(true);
                                }
                                if ((Tiles[r + 1][c].getMineStatus() == false) && Tiles[r + 1][c].getFlagStatus() == false && Tiles[r + 1][c].getRevealStatus() == false)
                                {
                                    Tiles[r + 1][c].setRevealStatus(true);
                                }
                                if ((Tiles[r + 1][c - 1].getMineStatus() == false) && Tiles[r + 1][c - 1].getFlagStatus() == false && Tiles[r + 1][c - 1].getRevealStatus() == false)
                                {
                                    Tiles[r + 1][c - 1].setRevealStatus(true);
                                }
                                if ((Tiles[r][c - 1].getMineStatus() == false) && Tiles[r][c - 1].getFlagStatus() == false && Tiles[r][c - 1].getRevealStatus() == false)
                                {
                                    Tiles[r][c - 1].setRevealStatus(true);
                                }
                                if (Tiles[r][c + 1].getMineStatus() == false && Tiles[r][c + 1].getFlagStatus() == false && Tiles[r][c + 1].getRevealStatus() == false)
                                {
                                    Tiles[r][c + 1].setRevealStatus(true);
                                }
                            }
                            else if (c == Tiles[r].size() - 1)
                            {
                                if ((Tiles[r + 1][c - 1].getMineStatus() == false) && Tiles[r + 1][c - 1].getFlagStatus() == false && Tiles[r + 1][c - 1].getRevealStatus() == false)
                                {
                                    Tiles[r + 1][c - 1].setRevealStatus(true);
                                }
                                if ((Tiles[r + 1][c].getMineStatus() == false) && Tiles[r + 1][c].getFlagStatus() == false && Tiles[r + 1][c].getRevealStatus() == false)
                                {
                                    Tiles[r + 1][c].setRevealStatus(true);
                                }
                                if (Tiles[r][c - 1].getMineStatus() == false && Tiles[r][c - 1].getFlagStatus() == false && Tiles[r][c - 1].getRevealStatus() == false)
                                {
                                    Tiles[r][c - 1].setRevealStatus(true);
                                }
                            }
                        }
                        else if (c == 0)
                        {
                            if (r > 0 && r < Tiles.size() - 1)
                            {
                                if ((Tiles[r - 1][c].getMineStatus() == false) && Tiles[r - 1][c].getFlagStatus() == false && Tiles[r - 1][c].getRevealStatus() == false)
                                {
                                    Tiles[r - 1][c].setRevealStatus(true);
                                }
                                if ((Tiles[r - 1][c + 1].getMineStatus() == false) && Tiles[r - 1][c + 1].getFlagStatus() == false && Tiles[r - 1][c + 1].getRevealStatus() == false)
                                {
                                    Tiles[r - 1][c + 1].setRevealStatus(true);
                                }
                                if (Tiles[r][c + 1].getMineStatus() == false && Tiles[r][c + 1].getFlagStatus() == false && Tiles[r][c + 1].getRevealStatus() == false)
                                {
                                    Tiles[r][c + 1].setRevealStatus(true);
                                }
                                if ((Tiles[r + 1][c + 1].getMineStatus() == false) && Tiles[r + 1][c + 1].getFlagStatus() == false && Tiles[r + 1][c + 1].getRevealStatus() == false)
                                {
                                    Tiles[r + 1][c + 1].setRevealStatus(true);
                                }
                                if ((Tiles[r + 1][c].getMineStatus() == false) && Tiles[r + 1][c].getFlagStatus() == false && Tiles[r + 1][c].getRevealStatus() == false)
                                {
                                    Tiles[r + 1][c].setRevealStatus(true);
                                }
                            }
                            else if (r == Tiles.size() - 1)
                            {
                                if ((Tiles[r - 1][c].getMineStatus() == false) && Tiles[r - 1][c].getFlagStatus() == false && Tiles[r - 1][c].getRevealStatus() == false)
                                {
                                    Tiles[r - 1][c].setRevealStatus(true);
                                }
                                if ((Tiles[r - 1][c + 1].getMineStatus() == false) && Tiles[r - 1][c + 1].getFlagStatus() == false && Tiles[r - 1][c + 1].getRevealStatus() == false)
                                {
                                    Tiles[r - 1][c + 1].setRevealStatus(true);
                                }
                                if (Tiles[r][c + 1].getMineStatus() == false && Tiles[r][c + 1].getFlagStatus() == false && Tiles[r][c + 1].getRevealStatus() == false)
                                {
                                    Tiles[r][c + 1].setRevealStatus(true);
                                }
                            }
                        }
                        else if (c == Tiles[r].size() - 1)
                        {
                            if (r > 0 && r < Tiles.size() - 1)
                            {
                                if ((Tiles[r - 1][c].getMineStatus() == false) && Tiles[r - 1][c].getFlagStatus() == false && Tiles[r - 1][c].getRevealStatus() == false)
                                {
                                    Tiles[r - 1][c].setRevealStatus(true);
                                }
                                if ((Tiles[r - 1][c - 1].getMineStatus() == false) && Tiles[r - 1][c - 1].getFlagStatus() == false && Tiles[r - 1][c - 1].getRevealStatus() == false)
                                {
                                    Tiles[r - 1][c - 1].setRevealStatus(true);
                                }
                                if (Tiles[r][c - 1].getMineStatus() == false && Tiles[r][c - 1].getFlagStatus() == false && Tiles[r][c - 1].getRevealStatus() == false)
                                {
                                    Tiles[r][c - 1].setRevealStatus(true);
                                }
                                if ((Tiles[r + 1][c - 1].getMineStatus() == false) && Tiles[r + 1][c - 1].getFlagStatus() == false && Tiles[r + 1][c - 1].getRevealStatus() == false)
                                {
                                    Tiles[r + 1][c - 1].setRevealStatus(true);
                                }
                                if ((Tiles[r + 1][c].getMineStatus() == false) && Tiles[r + 1][c].getFlagStatus() == false && Tiles[r + 1][c].getRevealStatus() == false)
                                {
                                    Tiles[r + 1][c].setRevealStatus(true);
                                }
                            }
                            else if (r == Tiles.size() - 1)
                            {
                                if ((Tiles[r - 1][c].getMineStatus() == false) && Tiles[r - 1][c].getFlagStatus() == false && Tiles[r - 1][c].getRevealStatus() == false)
                                {
                                    Tiles[r - 1][c].setRevealStatus(true);
                                }
                                if ((Tiles[r - 1][c - 1].getMineStatus() == false) && Tiles[r - 1][c - 1].getFlagStatus() == false && Tiles[r - 1][c - 1].getRevealStatus() == false)
                                {
                                    Tiles[r - 1][c - 1].setRevealStatus(true);
                                }
                                if (Tiles[r][c - 1].getMineStatus() == false && Tiles[r][c - 1].getFlagStatus() == false && Tiles[r][c - 1].getRevealStatus() == false)
                                {
                                    Tiles[r][c - 1].setRevealStatus(true);
                                }
                            }
                        }
                        else if (r == Tiles.size() - 1)
                        {
                            if (c > 0 && c < Tiles[r].size() - 1)
                            {
                                if ((Tiles[r][c - 1].getMineStatus() == false) && Tiles[r][c - 1].getFlagStatus() == false && Tiles[r][c - 1].getRevealStatus() == false)
                                {
                                    Tiles[r][c - 1].setRevealStatus(true);
                                }
                                if ((Tiles[r - 1][c - 1].getMineStatus() == false) && Tiles[r - 1][c - 1].getFlagStatus() == false && Tiles[r - 1][c - 1].getRevealStatus() == false)
                                {
                                    Tiles[r - 1][c - 1].setRevealStatus(true);
                                }
                                if (Tiles[r - 1][c].getMineStatus() == false && Tiles[r - 1][c].getFlagStatus() == false && Tiles[r - 1][c].getRevealStatus() == false)
                                {
                                    Tiles[r - 1][c].setRevealStatus(true);
                                }
                                if ((Tiles[r - 1][c + 1].getMineStatus() == false) && Tiles[r - 1][c + 1].getFlagStatus() == false && Tiles[r - 1][c + 1].getRevealStatus() == false)
                                {
                                    Tiles[r - 1][c + 1].setRevealStatus(true);
                                }
                                if ((Tiles[r][c + 1].getMineStatus() == false) && Tiles[r][c + 1].getFlagStatus() == false && Tiles[r][c + 1].getRevealStatus() == false)
                                {
                                    Tiles[r][c + 1].setRevealStatus(true);
                                }
                            }
                        }
                        //any tile that isn't on a border or edge
                        else
                        {
                            if ((Tiles[r + 1][c + 1].getMineStatus() == false) && Tiles[r + 1][c + 1].getFlagStatus() == false && Tiles[r + 1][c + 1].getRevealStatus() == false)
                            {
                                Tiles[r + 1][c + 1].setRevealStatus(true);
                            }
                            if ((Tiles[r - 1][c - 1].getMineStatus() == false) && Tiles[r - 1][c - 1].getFlagStatus() == false && Tiles[r - 1][c - 1].getRevealStatus() == false)
                            {
                                Tiles[r - 1][c - 1].setRevealStatus(true);
                            }
                            if ((Tiles[r + 1][c - 1].getMineStatus() == false) && Tiles[r + 1][c - 1].getFlagStatus() == false && Tiles[r + 1][c - 1].getRevealStatus() == false)
                            {
                                Tiles[r + 1][c - 1].setRevealStatus(true);
                            }
                            if ((Tiles[r - 1][c + 1].getMineStatus() == false) && Tiles[r - 1][c + 1].getFlagStatus() == false && Tiles[r - 1][c + 1].getRevealStatus() == false)
                            {
                                Tiles[r - 1][c + 1].setRevealStatus(true);
                            }
                            if ((Tiles[r][c + 1].getMineStatus() == false) && Tiles[r][c + 1].getFlagStatus() == false && Tiles[r][c + 1].getRevealStatus() == false)
                            {
                                Tiles[r][c + 1].setRevealStatus(true);
                            }
                            if ((Tiles[r + 1][c].getMineStatus() == false) && Tiles[r + 1][c].getFlagStatus() == false && Tiles[r + 1][c].getRevealStatus() == false)
                            {
                                Tiles[r + 1][c].setRevealStatus(true);
                            }
                            if ((Tiles[r][c - 1].getMineStatus() == false) && Tiles[r][c - 1].getFlagStatus() == false && Tiles[r][c - 1].getRevealStatus() == false)
                            {
                                Tiles[r][c - 1].setRevealStatus(true);
                            }
                            if ((Tiles[r - 1][c].getMineStatus() == false) && Tiles[r - 1][c].getFlagStatus() == false && Tiles[r - 1][c].getRevealStatus() == false)
                            {
                                Tiles[r - 1][c].setRevealStatus(true);
                            }
                        }
                    }

                    //if a tile isn't a mine, then it needs to have it's number drawn to the board
                    if (Tiles[r][c].getMineStatus() == false)
                    {
                        if (Tiles[r][c].getNumOfNeighbors() == 1)
                        {
                            number_1.setPosition(c * 32, r * 32);
                            window.draw(number_1);
                        }
                        else if (Tiles[r][c].getNumOfNeighbors() == 2)
                        {
                            number_2.setPosition(c * 32, r * 32);
                            window.draw(number_2);
                        }
                        else if (Tiles[r][c].getNumOfNeighbors() == 3)
                        {
                            number_3.setPosition(c * 32, r * 32);
                            window.draw(number_3);
                        }
                        else if (Tiles[r][c].getNumOfNeighbors() == 4)
                        {
                            number_4.setPosition(c * 32, r * 32);
                            window.draw(number_4);
                        }
                        else if (Tiles[r][c].getNumOfNeighbors() == 5)
                        {
                            number_5.setPosition(c * 32, r * 32);
                            window.draw(number_5);
                        }
                        else if (Tiles[r][c].getNumOfNeighbors() == 6)
                        {
                            number_6.setPosition(c * 32, r * 32);
                            window.draw(number_6);
                        }
                        else if (Tiles[r][c].getNumOfNeighbors() == 7)
                        {
                            number_7.setPosition(c * 32, r * 32);
                            window.draw(number_7);
                        }
                        else if (Tiles[r][c].getNumOfNeighbors() == 8)
                        {
                            number_8.setPosition(c * 32, r * 32);
                            window.draw(number_8);
                        }
                    }
                    //if a mine is hit
                    else if (Tiles[r][c].getMineStatus() == true)
                    {
                        //draw that mine
                        mine.setPosition(c * 32, r * 32);
                        window.draw(mine);

                        //draw all other mines on the board and updates logic
                        for (int a = 0; a < Tiles.size(); a++)
                        {
                            for (int b = 0; b < Tiles[a].size(); b++)
                            {
                                if (Tiles[a][b].getMineStatus() == true)
                                {
                                    Tiles[a][b].setRevealStatus(true);
                                }
                            }
                        }
                        hitMine = true;
                        endCondition = true;
                    }
                }
            }
        }

        //victory condition, flags any mine locations and sets the win condition
        if (totalTiles == 0)
        {
            endCondition = true;
            expectedFlags = 0;

            for (int r = 0; r < Tiles.size(); r++)
            {
                for (int c = 0; c < Tiles[r].size(); c++)
                {
                    if (Tiles[r][c].getMineStatus() == true)
                    {
                        flag.setPosition(c * 32, r * 32);
                        window.draw(flag);
                    }
                }
            }
        }
        
        //negative sign
        if (expectedFlags < 0)
        {
            digits.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
            digits.setPosition(0, heightSize * 32);
            window.draw(digits);
        }

        //displays hundreds digit
        int hundredsDigit = expectedFlags / 100;
        if (hundredsDigit < 0)
        {
            hundredsDigit *= -1;
        }
        digits.setTextureRect(sf::IntRect(21 * hundredsDigit, 0, 21, 32));
        digits.setPosition((1 * 21), heightSize * 32);
        window.draw(digits);

        //displays ten digit
        int tensDigit = (expectedFlags / 10) % 10;
        if (tensDigit < 0)
        {
            tensDigit *= -1;
        }
        digits.setTextureRect(sf::IntRect(21 * tensDigit, 0, 21, 32));
        digits.setPosition((2 * 21), heightSize * 32);
        window.draw(digits);

        //displays ones digit
        int onesDigit = expectedFlags % 10;
        if (onesDigit < 0)
        {
            onesDigit *= -1;
        }
        digits.setTextureRect(sf::IntRect(21 * onesDigit, 0, 21, 32));
        digits.setPosition((3 * 21), heightSize * 32);
        window.draw(digits);

        //debug and test buttons shown regardless of version, always present
        test_3.setPosition(((widthSize / 2.0) + 9) * 32, heightSize * 32);
        window.draw(test_3);
        test_2.setPosition(((widthSize / 2.0) + 7) * 32, heightSize * 32);
        window.draw(test_2);
        test_1.setPosition(((widthSize / 2.0) + 5) * 32, heightSize * 32);
        window.draw(test_1);
        debug.setPosition(((widthSize / 2.0) + 3) * 32, heightSize * 32);
        window.draw(debug);

        //shows happy face if game isn't over
        if (endCondition != true)
        {
            face_happy.setPosition((widthSize / 2.0 - 1) * 32, heightSize * 32);
            window.draw(face_happy);
        }
        //shows win face if game is over and there are no unseen tiles
        else if (endCondition == true && hitMine == false && totalTiles == 0)
        {
            face_win.setPosition((widthSize / 2.0 - 1) * 32, heightSize * 32);
            window.draw(face_win);
        }
        //shows lose face if game is over and mine is hit
        else if (endCondition == true && hitMine == true)
        {
            face_lose.setPosition((widthSize / 2.0 - 1) * 32, heightSize * 32);
            window.draw(face_lose);
        }

        window.display();
    }

    return 0;
}