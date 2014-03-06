#include "board.h"
#include <iostream>
#include <QList>

using namespace std;

Board::Board(QObject *parent) :
    QObject(parent)
{
    // make space for the entire board
    QVector<int> vBoard(26, 0);
    QVector<int> vDice;

    // make some default board
    vBoard[3] = 2;
    vBoard[6] = -1;
    vBoard[9] = 2;
    vBoard[12] = 1;

    // example of a pair of ones
    vDice.push_back(1);
    vDice.push_back(1);
    vDice.push_back(1);
    vDice.push_back(1);

    // example of unpaired dice
    //    vDice.push_back(2);
    //    vDice.push_back(3);

    int iIndexOfPieceLifted = 12;

    QSet<int> moves = PrintAllLegalMoves(vBoard, vDice, iIndexOfPieceLifted);

    for(QSet<int>::iterator iter = moves.begin();iter != moves.end();++iter)
    {
        cout << *iter << " " ;
    }
}

QSet<int> Board::PrintAllLegalMoves(const QVector<int> &vBoard, QVector<int> vDice, int iIndex)
{
    QSet<int> vLegalMoves;

    // make sure this is someones piece
    if(vBoard[iIndex] == 0)
    {
        return vLegalMoves;
    }

    // identify the piece by the polarity of the chosen piece (could be an input)
    int iDirection = 1;
    if(vBoard[iIndex] < 0)
    {
        iDirection = -1;
        for(int i = 0;i < vDice.size();++i)
        {
            vDice[i] *= iDirection;
        }
    }

    // if we have matching, the question is simply, how many hops can we do
    if(vDice.size() == 4)
    {
        // account for the direction
        int iDiceValue = vDice[0];
        int iCurrIndex = iIndex + iDiceValue;

        // make sure we only use the proper number of dice
        int iNumberDiceUsed = 0;
        while(iCurrIndex < vBoard.size() && iCurrIndex >= 0 && iNumberDiceUsed < vDice.size())
        {
            // if the next space is available
            if((iDirection * vBoard[iCurrIndex]) >= 0)
            {
                // found a legal move, document it
                cout << iIndex << " moved to " << iCurrIndex << endl;
                vLegalMoves.insert(iCurrIndex);

                // try to do another move
                iCurrIndex += iDiceValue;
                iNumberDiceUsed++;
            }
            else
            {
                // no more legal moves
                break;
            }
        }
    }

    // if the dice do not match
    if(vDice.size() == 2)
    {
        // try them in order first
        // first dice first
        // bounds check
        if((vDice[0] + iIndex) < vBoard.size() && (vDice[0] + iIndex) >= 0)
        {
            // if legal move
            if((iDirection * vBoard[vDice[0] + iIndex]) >= 0)
            {
                // add the first move
                vLegalMoves.insert(vDice[0] + iIndex);

                // try the second dice
                // bounds check
                if(vDice[0] + vDice[1] + iIndex < vBoard.size() && (vDice[0] + vDice[1] + iIndex) >= 0)
                {
                    // if legal move
                    if((iDirection * vBoard[vDice[0] + vDice[1] + iIndex]) >= 0)
                    {
                        vLegalMoves.insert(vDice[0] + vDice[1] + iIndex);
                    }
                }
            }
        }

        // second dice first
        // bounds check
        if((vDice[1] + iIndex) < vBoard.size() && (vDice[1] + iIndex) >= 0)
        {
            // if legal move
            if((iDirection * vBoard[vDice[1] + iIndex]) >= 0)
            {
                // add the first move
                vLegalMoves.insert(vDice[1] + iIndex);

                // try the second dice
                // bounds check
                if(vDice[0] + vDice[1] + iIndex < vBoard.size() && (vDice[0] + vDice[1] + iIndex) >= 0)
                {
                    // if legal move
                    if((iDirection * vBoard[vDice[0] + vDice[1] + iIndex]) >= 0)
                    {
                        vLegalMoves.insert(vDice[0] + vDice[1] + iIndex);
                    }
                }
            }
        }
    }

    // if there is only 1 die
    if(vDice.size() == 1)
    {
        // bounds check
        int iNewLocation = vDice[0] + iIndex;
        if(iNewLocation < vBoard.size() && iNewLocation >= 0)
        {
            // if the new space is available
            if(vBoard[iNewLocation] > -1)
            {
                vLegalMoves.insert(iNewLocation);
            }
        }
    }

    return vLegalMoves;
}

void Board::PrintBoard(const QVector<int> &vBoard)
{
    // print out the board indices
    for(int i = 0;i < vBoard.size();++i)
    {
        cout << i << " - " << vBoard[i] << endl;
    }
}
