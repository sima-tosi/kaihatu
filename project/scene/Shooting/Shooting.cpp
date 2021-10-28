#include "Shooting.h"
#include "ShPlayer.h"
#include "ShShot.h"
#include "ShBoss.h"
#include "Enemy/ShCurve.h"
#include "Enemy/ShTackle.h"
#include "Enemy/ShItem.h"
#include "Enemy/ShTreasure.h"
#include "Enemy/ShTriple.h"
#include "ShTMX.h"
#include "../../input/Control.h"
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
    player = new ShPlayer(this);
    SetEnemyVec();
}

void Shooting::SetEnemyVec(void)
{
    ShTMX* tmx = new ShTMX();
    enemyVec = tmx->GetEnemyData();
    delete tmx;
}

int Shooting::UpDate(KeyDate keyData, double delta)
{
    downTime += delta;
    player->UpDate(keyData, delta);
    for (auto& shot : eShots)
    {
        shot->UpData(delta);
        if (player->ShotHit(shot->GetPos(), shot->GetSize()))
        {
            shot->KillSet();
        }
    }
    auto es = std::remove_if(eShots.begin(), eShots.end(), [](std::unique_ptr<ShShot>& shot) {return shot->GetKill(); });
    eShots.erase(es, eShots.end());

    if (Boss)
    {
        boss->UpDate(delta);
        if (boss->PlayerHit(player->GetPos(), player->GetHitSize()))
        {
            player->Kill();
        }

        for (auto& shot : pShots)
        {
            shot->UpData(delta);
            if (boss->ShotHit(shot->GetPos(), shot->GetSize()))
            {
                shot->KillSet();
                score += SCORE_UP;
            }
        }
        auto ps = std::remove_if(pShots.begin(), pShots.end(), [](std::unique_ptr<ShShot>& shot) {return shot->GetKill(); });
        pShots.erase(ps, pShots.end());

        if (boss->finish())
        {
            if(eShots.size() == 0)
            return score;
        }
    }
    else
    {
        Stage();
        for (auto& enemy : enemys)
        {
            enemy->UpData(delta);
            if (enemy->PlayerHit(player->GetPos(), player->GetHitSize()))
            {
                player->Kill();
            }
        }
        auto en = std::remove_if(enemys.begin(), enemys.end(), [](std::unique_ptr<ShEnemy>& enemy) {return enemy->GetKill(); });
        enemys.erase(en, enemys.end());

        for (auto& shot : pShots)
        {
            shot->UpData(delta);
            for (auto& enemy : enemys)
            {
                if (enemy->ShotHit(shot->GetPos(), shot->GetSize()))
                {
                    shot->KillSet();
                    score += SCORE_UP;
                    break;
                }
            }
        }
        auto ps = std::remove_if(pShots.begin(), pShots.end(), [](std::unique_ptr<ShShot>& shot) {return shot->GetKill(); });
        pShots.erase(ps, pShots.end());

    }

    return -1;
}
void Shooting::Draw(void)
{
    DrawFormatString(0, 0, 0xffffff,"%d",score);

    player->Draw();
    for (auto& shot : pShots)
    {
        shot->Draw();
    }

    if (Boss)
    {
        boss->Draw();
        for (auto& shot : eShots)
        {
            shot->Draw();
        }
    }
    else
    {
        for (auto& enemy : enemys)
        {
            enemy->Draw();
        }
        for (auto& shot : eShots)
        {
            shot->Draw();
        }
    }
}

void Shooting::Stage(void)
{
    if (enemyVec.size() == spawnCnt)
    {
        if (enemys.size() == 0 && eShots.size() == 0)
        {
            Boss = true;
            boss = std::make_unique<ShBoss>(this, player);
        }
        return;
    }
    while(enemyVec[spawnCnt].downTime < downTime)
    {
        std::unique_ptr<ShEnemy> enemy;
        Vector2F ePos = { 1024 + 32,0 };
        ePos.x_ -= enemyVec[spawnCnt].pos.x_;
        ePos.y_ += enemyVec[spawnCnt].pos.y_;
        switch (enemyVec[spawnCnt].type)
        {
        case EnemyType::Curve:
            enemy = std::make_unique<ShCurve>(this, ePos);
            break;
        case EnemyType::Triple:
            enemy = std::make_unique<ShTriple>(this, ePos);
            break;
        case EnemyType::Tackle:
            enemy = std::make_unique<ShTackle>(player, ePos);
            break;
        case EnemyType::Treasure:
            enemy = std::make_unique<ShTreasure>(this, ePos);
            break;
        }
        enemys.emplace_back(std::move(enemy));
        ++spawnCnt;

        if (enemyVec.size() == spawnCnt) return;
    }
}

void Shooting::EnemyMakeShot(Vector2F pos, Vector2F vec)
{
    std::unique_ptr<ShShot> shot;
    shot = std::make_unique<ShShot>(pos,vec);
    eShots.push_back(std::move(shot));
}
void Shooting::PlayerMakeShot(Vector2F pos, Vector2F vec)
{
    std::unique_ptr<ShShot> shot;
    shot = std::make_unique<ShShot>(pos, vec);
    pShots.push_back(std::move(shot));
}

void Shooting::SpawnItem(Vector2F ePos)
{
    std::unique_ptr<ShEnemy> enemy;
    enemy = std::make_unique<ShItem>(player, ePos);
    enemys.emplace_back(std::move(enemy));

}
