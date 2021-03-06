#include "Puzle.h"
#include <DxLib.h>
#include<algorithm>

Puzle::Puzle()
{
    Init();
}
Puzle::~Puzle()
{
}

void Puzle::Init(void)
{
    map.resize(SIZE_X * SIZE_Y);
    mode = MODE::MOVE;
    downTime = 0.5;
    timelimit = 120.0;
    bang = false;
    score = 0;
    chain = 0;

    PIECE mpart;
    for (int a = 1; a >= 0; --a)
    {
        mpart.pos = { a + 2,1 };
        mpart.color = static_cast<P_C>(rand() % 8 + 1);
        mpart.kill = false;
        mpart.bombL = false;
        piece.insert(piece.begin(), mpart);
    }
    aPiece = 1;
    for (int a = 0; a < 4; ++a)
    {
        mpart.color = static_cast<P_C>(rand() % 8 + 1);
        mpart.kill = false;
        mpart.bombL = false;
        nPiece.insert(nPiece.begin(), mpart);
    }

    pieceImage.resize(9);
    LoadDivGraph("image/puzle/piece.png", 9, 3, 3, 60, 60, &(pieceImage[0]));

    screen = MakeScreen(pieceSize.x_ * SIZE_X, pieceSize.y_ * SIZE_Y);
}

PIECE Puzle::GetNext(void)
{
    PIECE part;

    part = *(nPiece.begin());
    nPiece.pop_front();

    PIECE mpart;

    mpart.color = static_cast<P_C>(rand() % 8 + 1);
    mpart.kill = false;
    mpart.bombL = false;
    nPiece.emplace_back(mpart);

    return part;
}

bool Puzle::FallCheck(PIECE part)
{
    if (part.pos.y_>= SIZE_Y - 1) return false;
    if (MapPieceCheck({part.pos.x_,part.pos.y_ + 1 })) return false;
    return true;
}

void Puzle::Move(KeyDate keyData)
{
    if (keyData[InputID::LEFT][Trg::Now] &&
        !keyData[InputID::LEFT][Trg::Old])
    {
        if (piece[0].pos.x_ != 0 && piece[1].pos.x_ != 0)
        {
            --piece[0].pos.x_;
            --piece[1].pos.x_;
        }
    }
    else if (keyData[InputID::RIGHT][Trg::Now] &&
        !keyData[InputID::RIGHT][Trg::Old])
    {
        if (piece[0].pos.x_ != 5 && piece[1].pos.x_ != 5)
        {
            ++piece[0].pos.x_;
            ++piece[1].pos.x_;
        }
    }
    else if (keyData[InputID::DOWN][Trg::Now])
    {
        downTime = 0.0;
    }
    else if (keyData[InputID::UP][Trg::Now] &&
        !keyData[InputID::UP][Trg::Old])
    {
        while (FallCheck(piece[0]) && FallCheck(piece[1]))
        {
            ++piece[0].pos.y_;
            ++piece[1].pos.y_;
        }
    }
    else if (keyData[InputID::LROLL][Trg::Now] &&
        !keyData[InputID::LROLL][Trg::Old])
    {
        LRool();
    }
    else if (keyData[InputID::RROLL][Trg::Now] &&
        !keyData[InputID::RROLL][Trg::Old])
    {
        RRool();
    }
     
   if (keyData[InputID::SPACE][Trg::Now] &&
        !keyData[InputID::SPACE][Trg::Old])
    {
       if (hPiece.size() == 0)
       {
          hPiece.insert(hPiece.begin(), GetNext());
          hPiece.insert(hPiece.begin(), GetNext());
       }
       std::iter_swap(piece.begin() + ((aPiece + 1) % 2), hPiece.begin());
       std::iter_swap(piece.begin() + aPiece, hPiece.begin() + 1);

       piece[0].pos = { 2,1 };
       piece[1].pos = { 3,1 };
       aPiece = 1;
    }

    while (downTime <= 0.0)
    {
        downTime += 0.5;
        if (FallCheck(piece[0]) && FallCheck(piece[1]))
        {
            ++piece[0].pos.y_;
            ++piece[1].pos.y_;
        }
        else
        {
            mode = MODE::DROP;
            modeTime = 0.1;
            break;
        }
    }
}
void Puzle::Drop(void)
{
    if (modeTime <= 0.0)
    {
        modeTime = 0.1;

        bool next = true;

        std::for_each(piece.rbegin(), piece.rend(), [&](PIECE& part)
            {
                if (FallCheck(part))
                {
                    map[part.mapPos()] = P_C::NON;
                    ++part.pos.y_;
                    next = false;
                }
                else
                {
                    map[part.mapPos()] = part.color;
                }
            });

        if (next) mode = MODE::KILL;
    }
}
void Puzle::Kill(void)
{
    bool nMove = true;
    std::vector<bool> allkillMap;
    allkillMap.resize(SIZE_X * SIZE_Y);

    std::for_each(piece.rbegin(), piece.rend(), [&](PIECE& part)
    {
        if (map[part.mapPos()] != P_C::NON && map[part.mapPos()] != P_C::BOMB &&
            map[part.mapPos()] != P_C::JYAMA && map[part.mapPos()] != P_C::ALL)
        {
            killMap.clear();
            killMap.resize(SIZE_X * SIZE_Y);

            if (CheckKill(map[part.mapPos()], part.mapPos(),0) >= 4)
            {
                int cnt = 0;
                for (auto& part : piece)
                {
                    if (killMap[part.mapPos()] != P_C::NON)
                    {
                        ++cnt;
                        if (killMap[part.mapPos()] != P_C::ALL)
                            map[part.mapPos()] = P_C::NON;
                        else allkillMap[part.mapPos()] = true;

                        part.kill = true;
                        JyamaKill(part.mapPos() + 1);
                        JyamaKill(part.mapPos() - 1);
                        JyamaKill(part.mapPos() + SIZE_X);
                        JyamaKill(part.mapPos() - SIZE_X);
                    }
                }
                score += (chain * 2 + 1) * cnt;
                nMove = false;
            }
        }
    });

    if (nMove)
    {
        chain = 0;
        if (MissCheck())
        {
            mode = MODE::FINISH;
        }
        else
        {
            if (bang)
            {
                bang = false;
                for (auto& part : piece)
                {
                    if (part.bombL)
                    {
                        int vec = part.mapPos();
                        PieceVecKill(vec);
                        PieceVecKill(vec - SIZE_X - 1);
                        PieceVecKill(vec - SIZE_X);
                        PieceVecKill(vec - SIZE_X + 1);
                        PieceVecKill(vec + SIZE_X - 1);
                        PieceVecKill(vec + SIZE_X);
                        PieceVecKill(vec + SIZE_X + 1);
                        PieceVecKill(vec - 1);
                        PieceVecKill(vec + 1);
                    }
                }
                auto o = std::remove_if(piece.begin(), piece.end(), [](PIECE& part) {return part.kill; });
                for (auto itr = o; itr != piece.end(); ++itr)
                {
                    map[itr->mapPos()] = P_C::NON;
                }
                piece.erase(o, piece.end());
                mode = MODE::DROP;
            }
            else
            {
                downTime = 0.5;
                
               piece.insert(piece.begin(), GetNext());
               piece.insert(piece.begin(), GetNext());
               piece[0].pos = { 2,1 };
               piece[1].pos = { 3,1 };
               aPiece = 1;
              mode = MODE::MOVE;
            }
        }
    }
    else
    {
        for (auto& part : piece)
        {
            if(allkillMap[part.mapPos()])
                map[part.mapPos()] = P_C::NON;
        }
        ++chain;
        auto o = std::remove_if(piece.begin(), piece.end(), [](PIECE& part) {return part.kill; });
        for (auto itr = o; itr != piece.end(); ++itr)
        {
            map[itr->mapPos()] = P_C::NON;
        }
        piece.erase(o, piece.end());
        mode = MODE::DROP;
    }
}

void Puzle::PieceVecKill(int vec)
{
    if (vec >= SIZE_X * SIZE_Y) return;
    map[vec] = P_C::NON;
    for (auto& part : piece)
    {
        if (part.mapPos() == vec)
        {
            part.kill = true;
            break;
        }
    }
}

int Puzle::CheckKill(P_C id, int vec, int cnt)
{
    if (vec >= SIZE_X * SIZE_Y || vec < 0) return cnt;
    if (killMap[vec] == P_C::NON)
    {
        if (map[vec] == id || map[vec] == P_C::ALL)
        {
            cnt++;
            killMap[vec] = map[vec];
            cnt = CheckKill(id, vec + 1,cnt);
            cnt = CheckKill(id, vec - 1,cnt);
            cnt = CheckKill(id, vec + SIZE_X,cnt);
            cnt = CheckKill(id, vec - SIZE_X,cnt);
        }
    }

    return cnt;
}

bool Puzle::MapPieceCheck(Vector2 vec)
{
    if (vec.x_ >= SIZE_X || vec.x_ < 0 ||
        vec.y_ >= SIZE_Y || vec.y_ < 0) return true;

    return map[vec.y_ * SIZE_X + vec.x_] != P_C::NON;
}

void Puzle::JyamaKill(int vec)
{
    if (vec >= SIZE_X * SIZE_Y) return;
    if (map[vec] == P_C::JYAMA)
    {
        PieceVecKill(vec);
    }
    else if (map[vec] == P_C::BOMB)
    {
        for (auto& part : piece)
        {
            if (part.mapPos() == vec)
            {
                part.bombL = true;
                bang = true;
                return;
            }
        }
    }
}
bool Puzle::MissCheck(void)
{
    if (map[8] == P_C::NON && map[9] == P_C::NON) return false;
    return true;
}

void Puzle::LRool(void)
{
    int sPiece = (aPiece + 1) % 2;
    Vector2 aPos = piece[sPiece].pos;
    Vector2 sPos = piece[sPiece].pos;
    bool chenge;
    if (piece[1].pos.y_ == piece[0].pos.y_)
    {
        chenge = true;
        if (aPiece == 0) ++aPos.y_;
        else             --aPos.y_;

        if (aPos.y_ >= SIZE_Y || MapPieceCheck(aPos))
        {
            --sPos.y_;
            --aPos.y_;
        }
    }
    else
    {
        chenge = false;
        if (aPiece == 0)
        {
            --aPos.x_;
            if (aPos.x_ < 0 || MapPieceCheck(aPos))
            {
                if (!MapPieceCheck({ sPos.x_ + 1,sPos.y_ }))
                {
                    ++sPos.x_;
                    ++aPos.x_;
                }
                else return;
            }
        }
        else
        {
            ++aPos.x_;
            if (aPos.x_ >= SIZE_X || MapPieceCheck(aPos))
            {
                if (!MapPieceCheck({ sPos.x_ - 1,sPos.y_ }))
                {
                    --sPos.x_;
                    --aPos.x_;
                }
                else return;
            }
        }
    }

    piece[aPiece].pos = aPos;
    piece[sPiece].pos = sPos;
    if (chenge)
    {
        aPiece = (aPiece + 1) % 2;
        std::iter_swap(piece.begin(), piece.begin() + 1);
    }
}

void Puzle::RRool(void) 
{
    int sPiece = (aPiece + 1) % 2;
    Vector2 aPos = piece[sPiece].pos;
    Vector2 sPos = piece[sPiece].pos;
    bool chenge;
    if (piece[1].pos.y_ == piece[0].pos.y_)
    {
        chenge = false;
        if (aPiece == 0) --aPos.y_;
        else             ++aPos.y_;

        if (aPos.y_ >= SIZE_Y || MapPieceCheck(aPos))
        {
            --sPos.y_;
            --aPos.y_;
        }
    }
    else
    {
        chenge = true;
        if (aPiece == 1)
        {
            --aPos.x_;
            if (aPos.x_ < 0 || MapPieceCheck(aPos))
            {
                if (!MapPieceCheck({ sPos.x_ + 1,sPos.y_ }))
                {
                    ++sPos.x_;
                    ++aPos.x_;
                }
                else return;
            }
        }
        else
        {
            ++aPos.x_;
            if (aPos.x_ >= SIZE_X || MapPieceCheck(aPos))
            {
                if (!MapPieceCheck({ sPos.x_ - 1,sPos.y_ }))
                {
                    --sPos.x_;
                    --aPos.x_;
                }
                else return;
            }
        }
    }

    piece[aPiece].pos = aPos;
    piece[sPiece].pos = sPos;
    if (chenge)
    {
        aPiece = (aPiece + 1) % 2;
        std::iter_swap(piece.begin(), piece.begin() + 1);
    }
}

int Puzle::UpDate(KeyDate keyData,double delta)
{
    downTime -= delta;
    modeTime -= delta;

    switch (mode)
    {
    case MODE::MOVE:
        timelimit -= delta;
        Move(keyData);
        break;
    case MODE::DROP:
        Drop();
        break;
    case MODE::KILL:
        Kill();
        break;
    default:
        break;
    }

    if (timelimit <= 0.0 || mode == MODE::FINISH)
    {
        return score * 1.5;
    }

    return -1;
}

void Puzle::Draw(void)
{
    DrawFormatString(600, 500, 0xffffff, "%.2f", timelimit);
    DrawFormatString(600, 530, 0xffffff, "SCORE:%d", score);

    SetDrawScreen(screen);
    ClsDrawScreen();

    DrawBox(0, 0, pieceSize.x_ * SIZE_X, pieceSize.y_ * SIZE_Y, 0xffffff, true);

    for (auto part : piece)
    {
        DrawGraph((part.pos.x_) * pieceSize.x_, (part.pos.y_) * pieceSize.y_,
            GetPieceImage(part.color,part.bombL), true);
    }

    SetDrawScreen(DX_SCREEN_BACK);

    DrawGraph(64, -(pieceSize.y_ / 2), screen, true);

    Vector2 holdOff = { 0,0 };
    int cnt = 0;
    for (auto part : hPiece)
    {
        DrawGraph(holdOff.x_, holdOff.y_ + (cnt * pieceSize.y_),
            GetPieceImage(part.color,false), true);
        ++cnt;
    }

    Vector2 nextOff = { 480,0 };
    cnt = 0;
    for (auto part : nPiece)
    {
        int nCnt = cnt < 2 ? 0 : 1;

        DrawGraph(nextOff.x_ + (nCnt * pieceSize.x_), nextOff.y_ + (cnt * pieceSize.y_) + 5,
                GetPieceImage(part.color, false), true);
        ++cnt;
    }

    DrawString(0, 0, "PuzleScene", 0xffffff);
}

int Puzle::GetPieceImage(P_C color_,bool on)
{
    int color = 0;

    if (color_ == P_C::RED)     color = pieceImage[0];
    if (color_ == P_C::BULE)    color = pieceImage[1];
    if (color_ == P_C::GREEN)   color = pieceImage[2];
    if (color_ == P_C::YELLOW)  color = pieceImage[3];
    if (color_ == P_C::PURPLE)  color = pieceImage[4];
    if (color_ == P_C::JYAMA)   color = pieceImage[5];
    if (color_ == P_C::ALL)     color = pieceImage[6];
    if (color_ == P_C::BOMB)
    {
        if (on) color = pieceImage[7];
        else    color = pieceImage[8];
    }

    if (color == 0)
    { 
        int vsni = 0;
    }

    return color;
}