#include "Shooting.h"
#include <DxLib.h>

Shooting::Shooting()
{
    Init();
}
Shooting::~Shooting()
{
}

void Shooting::Init(void)
{
    player.pos = { 50,360 };
    player.shot = SHOTMODE::NORMAL;
    player.stayTime = 0.0;
    player.reStartTime = 0.0;

    ENEMY enemy;
    enemy.life = 100;
    enemy.vec = { 0,0 };
    enemy.pos = { 1000,360 };
    enemy.type = ENENYTYPE::Boss;
    enemy.time = 0.0;
    enemys.push_back(enemy);
}

void Shooting::PlayerMove(KeyDate keyData, double delta)
{
    if (player.stayTime > 0.0)
        player.stayTime -= delta;

    if (keyData[InputID::UP][Trg::Now])
    {
        player.pos.y_ -= 10;
    }
    if (keyData[InputID::DOWN][Trg::Now])
    {
        player.pos.y_ += 10;
    }
    if (keyData[InputID::LEFT][Trg::Now])
    {
        player.pos.x_ -= 10;
    }
    if (keyData[InputID::RIGHT][Trg::Now])
    {
        player.pos.x_ += 10;
    }

    if (player.reStartTime <= 0.0)
    {
        if (keyData[InputID::SPACE][Trg::Now])
        {
            if (player.stayTime <= 0.0)
            {
                makeShot();
            }
        }

        for (auto enemy : enemys)
        {
            if (HitCheck(player.pos - Vector2F{ 32.0f,32.0f }, player.pos + Vector2F{ 32.0f,32.0f },
                enemy.pos - Vector2F{ 16.0f,16.0f }, enemy.pos + Vector2F{ 16.0f,16.0f }))
            {
                player.reStartTime = 5.0;
                return;
            }
        }
        for (auto& shot : eShots)
        {
            if (HitCheck(player.pos - Vector2F{ 32.0f,32.0f }, player.pos + Vector2F{ 32.0f,32.0f },
                shot.pos - Vector2F{ 8.0f,8.0f }, shot.pos + Vector2F{ 8.0f,8.0f }))
            {
                player.reStartTime = 5.0;
                shot.kill = true;
                return;
            }
        }
    }
    else player.reStartTime -= delta;
}

void Shooting::ShotMove(void)
{
    for (auto& shot : pShots)
    {
        shot.pos += shot.vec;

        if (shot.pos.x_ > 1288 || shot.pos.x_ < 0 ||
            shot.pos.y_ > 720 || shot.pos.y_ < 0) shot.kill = true;
    }
    auto p = std::remove_if(pShots.begin(), pShots.end(), [](SHOT& shot) {return shot.kill; });
    pShots.erase(p, pShots.end());
    for (auto& shot : eShots)
    {
        shot.pos += shot.vec;

        if (shot.pos.x_ > 1288 || shot.pos.x_ < 0 ||
            shot.pos.y_ > 720 || shot.pos.y_ < 0) shot.kill = true;
    }
    auto e = std::remove_if(eShots.begin(), eShots.end(), [](SHOT& shot) {return shot.kill; });
    eShots.erase(e, eShots.end());
}

void Shooting::EnemyMove(double delta)
{
    for (auto& enemy : enemys)
    {
        enemy.stayTime -= delta;
        enemy.time += delta;

        switch (enemy.type)
        {
        case ENENYTYPE::RUSH:
            RushMove(enemy);
            break;
        case ENENYTYPE::BOX:
            BoxMove(enemy);
            break;
        case ENENYTYPE::NORMAL:
            NormalMove(enemy);
            break;
        case ENENYTYPE::TRIPLE:
            TripleMove(enemy);
            break;
        case ENENYTYPE::Boss:
            BossMove(enemy);
            break;
        }

        for (auto& shot : pShots)
        {
            if (HitCheck(enemy.pos - Vector2F{ 16.0f,16.0f }, enemy.pos + Vector2F{ 16.0f,16.0f },
                shot.pos - Vector2F{ 8.0f,8.0f }, shot.pos + Vector2F{ 8.0f,8.0f }))
            {
                --enemy.life;
                if (!shot.penetra) shot.kill = true;
                return;
            }
        }
        if (enemy.pos.x_ < -16 || enemy.pos.y_ < -16) enemy.life = 0;
    }

    auto o = std::remove_if(enemys.begin(), enemys.end(), [](ENEMY& enemy) {return enemy.life <= 0; });
    enemys.erase(o, enemys.end());
}

void Shooting::makeShot(void)
{
    SHOT make;
    Vector2F pPos = player.pos;
    
    switch (player.shot)
    {
    case SHOTMODE::TRIPLE:

        make.pos.x_ = pPos.x_ - 40;
        make.pos.y_ = pPos.y_ + 40;
        make.penetra = false;
        make.vec = { -10,10 };
        make.kill = false;
        pShots.emplace_back(make);

        make.pos.x_ = pPos.x_ - 40;
        make.pos.y_ = pPos.y_ - 40;
        make.penetra = false;
        make.vec = { -10,-10 };
        make.kill = false;
        pShots.emplace_back(make);

    case SHOTMODE::NORMAL:

        make.pos.x_ = pPos.x_ + 40;
        make.pos.y_ = pPos.y_;
        make.penetra = false;
        make.vec = { 10,0 };
        make.kill = false;
        pShots.emplace_back(make);

        player.stayTime = 0.2;
        break;
    case SHOTMODE::SIDE:

        make.pos.x_ = pPos.x_;
        make.pos.y_ = pPos.y_ + 40;
        make.penetra = false;
        make.vec = { 10,0 };
        make.kill = false;
        pShots.emplace_back(make);

        make.pos.x_ = pPos.x_;
        make.pos.y_ = pPos.y_ - 40;
        make.penetra = false;
        make.vec = { 10,0 };
        make.kill = false;
        pShots.emplace_back(make);

        player.stayTime = 0.2;
        break;
    case SHOTMODE::PENETRA:

        make.pos.x_ = pPos.x_ + 40;
        make.pos.y_ = pPos.y_;
        make.penetra = true;
        make.vec = { 10,0 };
        make.kill = false;
        pShots.emplace_back(make);

        player.stayTime = 0.5;
        break;
    }
}

void Shooting::RushMove(ENEMY& enemy)
{
    int oldPos = enemy.pos.x_;
    enemy.pos -= enemy.vec;

    if (enemy.vec.y_ == 0)
    {
        if (oldPos >= player.pos.x_ && 
            enemy.pos.x_ <= player.pos.x_)
        {
            enemy.vec.y_ = enemy.vec.x_;
            enemy.vec.x_ = 0;
        }
    }
}

void Shooting::NormalMove(ENEMY& enemy)
{
    enemy.pos.x_ -= enemy.vec.x_;
    enemy.pos.y_ = (sin(enemy.time * 2) * 300) + 360;

    if (enemy.stayTime <= 0)
    {
        enemy.stayTime = 1.0;
        Vector2F ePos = enemy.pos;
        SHOT make;

        make.pos.x_ = ePos.x_ - 16;
        make.pos.y_ = ePos.y_;
        make.penetra = false;
        make.vec = { -15,0 };
        make.kill = false;
        eShots.emplace_back(make);
    }
}

void Shooting::TripleMove(ENEMY& enemy)
{
    enemy.pos -= enemy.vec;

    if (enemy.stayTime <= 0)
    {
        enemy.stayTime = 1.0;
        Vector2F ePos = enemy.pos;
        SHOT make;

        make.pos.x_ = ePos.x_ - 16;
        make.pos.y_ = ePos.y_;
        make.penetra = false;
        make.vec = { -15,0 };
        make.kill = false;
        eShots.emplace_back(make);

        make.pos.y_ = ePos.y_ - 16;
        make.vec.y_ = -10 ;
        eShots.emplace_back(make);

        make.pos.y_ = ePos.y_ + 16;
        make.vec.y_ = +10;
        eShots.emplace_back(make);
    }
}

void Shooting::BoxMove(ENEMY& enemy)
{
    enemy.pos -= enemy.vec;
}

void Shooting::BossMove(ENEMY& enemy)
{
    if (enemy.stayTime <= 0)
    {
        ++enemy.shotCnt;
        enemy.stayTime = 0.3;
        makeBossShot(enemy);
    }
    if ((enemy.shotCnt / 3) % 3 == 0 && enemy.life < 25)
    {
        SHOT make;

        make.pos = enemy.pos;
        make.penetra = false;
        make.kill = false;
        make.vec = { -10.0f,0.0f };

        eShots.emplace_back(make);
    }

    if (enemy.time > 60.0)
    {
        enemy.life = 0;
    }
}

void Shooting::makeBossShot(ENEMY enemy)
{
    Vector2F shotPos[2] = { enemy.pos - Vector2F{0, 200},enemy.pos + Vector2F{0, 200} };

    SHOT make;
    make.penetra = false;
    make.kill = false;

    for (int a = 0; a < 2; ++a)
    {
        make.pos = shotPos[a];

        for (int a = 0; a < 16; ++a)
        {
            make.vec = { cosf(a * (DX_PI_F / 8)) * 10.0f,sinf(a * (DX_PI_F / 8)) * 10.0f };
            eShots.emplace_back(make);
        }

        if (enemy.life < 50)
        {
            Vector2F dir = player.pos - shotPos[a];
            float mat = hypot(dir.x_, dir.y_);
            dir.x_ /= mat;
            dir.y_ /= mat;
            make.vec = { dir.x_ * 10.0f,dir.y_ * 10.0f };
            eShots.emplace_back(make);
        }

        DrawBox(shotPos[a].x_ - 16, shotPos[a].y_ - 16,
            shotPos[a].x_ + 16, shotPos[a].y_ + 16,
            0x00ff00, true);
    }
}

bool Shooting::HitCheck(Vector2F mLU, Vector2F mRD, Vector2F yLU, Vector2F yRD)
{
    return (mLU.x_ < yRD.x_&& mRD.x_ > yLU.x_ &&
            mLU.y_ < yRD.y_&& mRD.y_ > yLU.y_);
}

void Shooting::MOVEYOU(void)
{
    ENEMY enemy;

    switch (nvr % 4)
    {
    case 0:
        enemy.life = 1;
        enemy.vec = { 15,0 };
        enemy.pos = { 1300,600 };
        enemy.type = ENENYTYPE::RUSH;
        enemys.push_back(enemy);
        break;
    case 1:
        enemy.life = 1;
        enemy.vec = { 5,0 };
        enemy.pos = { 1300,550 };
        enemy.stayTime = .0;
        enemy.type = ENENYTYPE::TRIPLE;
        enemys.push_back(enemy);
        break;
    case 2:
        enemy.life = 1;
        enemy.vec = { 10,0 };
        enemy.pos = { 1300,360 };
        enemy.type = ENENYTYPE::BOX;
        enemys.push_back(enemy);
        break;
    case 3:
        enemy.life = 1;
        enemy.pos = { 1300,360 };
        enemy.vec = { 10,0 };
        enemy.time = 0.0;
        enemy.stayTime = 0.0;
        enemy.type = ENENYTYPE::NORMAL;
        enemys.push_back(enemy);
        break;
    }
    nvr++;
}

int Shooting::UpDate(KeyDate keyData, double delta)
{

    PlayerMove(keyData,delta);
    EnemyMove(delta);
    ShotMove();

    return -1;
}

void Shooting::Draw(void)
{
    DrawString(0, 0, "ShootingScene", 0xffffff);
    DrawBox(player.pos.x_ - 32, player.pos.y_ - 32,
        player.pos.x_ + 32, player.pos.y_ + 32,
        GetColor(255, 255, 255 * player.stayTime), player.reStartTime <= 0);

    for (auto shot : pShots)
    {
        DrawBox(shot.pos.x_ - 8, shot.pos.y_ - 8,
            shot.pos.x_ + 8, shot.pos.y_ + 8,
            0xff0000, true);
    }
    for (auto shot : eShots)
    {
        DrawBox(shot.pos.x_ - 8, shot.pos.y_ - 8,
            shot.pos.x_ + 8, shot.pos.y_ + 8,
            0x00ffff, true);
    }
    for (auto enemy : enemys)
    {
        DrawBox(enemy.pos.x_ - 16, enemy.pos.y_ - 16,
            enemy.pos.x_ + 16, enemy.pos.y_ + 16,
            0x00ff00, true);
        DrawLine(100, 20, 9 * enemy.life + 100, 20,
            0xffffff, 5);
    }
}