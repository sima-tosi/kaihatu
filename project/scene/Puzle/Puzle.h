#pragma once
#include "../Game.h"
#include "../../Vector2.h"
#include <vector>
#include <list>

#define SIZE_X 6
#define SIZE_Y 13

enum class MODE
{
    MOVE,
    DROP,
    KILL,
    FINISH
};

enum class P_C
{
    NON,
    RED,
    BULE,
    GREEN,
    YELLOW,
    PURPLE,
    JYAMA,
    ALL,
    BOMB,
};

struct PIECE
{
    P_C color;
    Vector2 pos;
    bool kill;
    bool bombL;

    int mapPos(void)
    { return pos.y_ * SIZE_X + pos.x_; };
};

class Puzle :
    public Game
{
public:
    Puzle();
    ~Puzle();
    int UpDate(KeyDate keyData, double delta);
    void Draw(void) override;
private:
    void Init(void);
    void SetPart(void);
    PIECE GetNext(void);
    bool FallCheck(PIECE part);

    void Move(KeyDate keyData);
    void Drop(void);
    void Kill(void);

    int GetPieceImage(P_C color_, bool on);

    void PieceVecKill(int vec);
    int CheckKill(P_C id, int vec, int cnt);
    bool MapPieceCheck(Vector2 vec);
    void JyamaKill(int vec);
    bool MissCheck(void);
    void LRool(void);
    void RRool(void);

    MODE mode;
    double downTime;
    double timelimit;
    double modeTime;

    std::vector<P_C> map;
    std::vector<P_C> killMap;

    std::vector<int> pieceImage;
    std::vector<PIECE> piece;
    std::vector<PIECE> hPiece;
    std::list<PIECE> nPiece;
    int aPiece;
    bool bang;

    Vector2 pieceSize = { 60,60 };

    int score;
    int chain;
    int screen;
};

