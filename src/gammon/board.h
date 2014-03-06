#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QVector>
#include <QSet>

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);

signals:

public slots:
    static QSet<int> PrintAllLegalMoves(const QVector<int> &vBoard, QVector<int> vDice, int iIndex);
    static void PrintBoard(const QVector<int>& vBoard);

protected:
    QVector<int> m_vBoard;

};

#endif // BOARD_H
