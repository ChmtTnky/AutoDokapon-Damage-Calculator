#include "MainClasses.h"

Fighter::Fighter(int address, DolphinAccessor* game)
{
    mainadd = address;
    Game = game;
}

void Fighter::populateadd()
{
    char* datablock = new char[56];
    Game->readFromRAM((u32) mainadd, datablock, 56, false);

    structadd = hextonum(datablock, 4) - 0x80000000;
    wpadd = hextonum(datablock + 4, 4) - 0x80000000;
    shadd = hextonum(datablock + 8, 4) - 0x80000000;
    acadd = hextonum(datablock + 12, 4) - 0x80000000;
    jobadd = hextonum(datablock + 16, 4) - 0x80000000;
    omadd = hextonum(datablock + 20, 4) - 0x80000000;
    dmadd = hextonum(datablock + 24, 4) - 0x80000000;

    jobid = hextonum(datablock + 36, 4);

    curhealth = hextonum(datablock + 44, 4);
    maxhealth = hextonum(datablock + 48, 4);

    nameadd = hextonum(datablock + 52, 4) - 0x80000000;

    delete datablock;
}

void Fighter::calcstats()
{
    if (structadd >= 0x00552430)
        isplayer = true;
    else
        isplayer = false;

    attack = 0;
    defense = 0;
    magic = 0;
    speed = 0;
    offmag = 0;
    defmag = 0;
    profbonus = false;

    char* stats = new char[8];
    Game->readFromRAM((u32)(structadd + 0x44), stats, 8, false);

    attack += (short)hextonum(stats, 2);
    defense += (short)hextonum(stats + 2, 2);
    magic += (short)hextonum(stats + 4, 2);
    speed += (short)hextonum(stats + 6, 2);

    if (isplayer)
    {
        if (wpadd != -0x80000000)
        {
            Game->readFromRAM((u32)(wpadd + 0x3C), stats, 8, false);

            attack += (short)hextonum(stats, 2);
            defense += (short)hextonum(stats + 2, 2);
            magic += (short)hextonum(stats + 4, 2);
            speed += (short)hextonum(stats + 6, 2);
        }

        if (shadd != -0x80000000)
        {
            Game->readFromRAM((u32)(shadd + 0x3C), stats, 8, false);

            attack += (short)hextonum(stats, 2);
            defense += (short)hextonum(stats + 2, 2);
            magic += (short)hextonum(stats + 4, 2);
            speed += (short)hextonum(stats + 6, 2);
        }

        if (acadd != -0x80000000)
        {
            Game->readFromRAM((u32)(acadd + 0x3C), stats, 8, false);

            attack += (short)hextonum(stats, 2);
            defense += (short)hextonum(stats + 2, 2);
            magic += (short)hextonum(stats + 4, 2);
            speed += (short)hextonum(stats + 6, 2);
        }

        Game->readFromRAM((u32)(jobadd), stats, 8, false);
        attack += (short)hextonum(stats, 2);
        defense += (short)hextonum(stats + 2, 2);
        magic += (short)hextonum(stats + 4, 2);
        speed += (short)hextonum(stats + 6, 2);

        delete stats;

        char* jobbyte = new char[1];
        Game->readFromRAM((u32)(wpadd + 0x55), jobbyte, 1, false);

        jobbyte[0] -= 1;

        if (jobbyte[0] == 0)
        {
            if (jobid == 0 || jobid == 4 || jobid == 6 || jobid == 10)
                profbonus = true;
        }
        else if (jobbyte[0] == 1)
        {
            if (jobid == 1 || jobid == 4 || jobid == 5 || jobid == 9 || jobid == 10)
                profbonus = true;
        }
        else if (jobbyte[0] == 2 && jobid == 2)
            profbonus = true;
        else if (jobbyte[0] == 3 && jobid == 3)
            profbonus = true;
        else if (jobbyte[0] == 4 && jobid == 8)
            profbonus = true;
        else if (jobbyte[0] == 5 && jobid == 7)
            profbonus = true;
        else if (jobbyte[0] == 6 && jobid == 6)
            profbonus = true;
        else if (jobbyte[0] == 7 && jobid == 9)
            profbonus = true;

        delete jobbyte;
    }

    char* magpower = new char[2];

    if (omadd != -0x80000000)
    {
        Game->readFromRAM((u32)(omadd + 0x4A), magpower, 2, false);
        offmag = (short)hextonum(magpower, 2);
    }
    if (dmadd != -0x80000000)
    {
        Game->readFromRAM((u32)(dmadd + 0x4A), magpower, 2, false);
        defmag = (short)hextonum(magpower, 2);
    }

    delete magpower;

    string namechars;
    char* namechar = new char [32];
    Game->readFromRAM((u32)(nameadd), namechar, 32, false);

    for (int i = 0; namechar[i] != 0; i++)
        namechars += namechar[i];

    name = namechars;

    delete namechar;
}

void Fighter::dispstats()
{
    cout << name << endl <<
    "Health: " << curhealth << "/" << maxhealth << endl <<
    "Attack: " << attack << endl <<
    "Defense: " << defense << endl <<
    "Magic: " << magic << endl <<
    "Speed: " << speed << endl <<
    "Off. Magic: " << offmag << endl <<
    "Def. Magic: " << defmag << endl <<
    "Prof. Bonus: ";
    if (profbonus)
        cout << "True";
    else
        cout << "False";
    cout << endl << endl;
}

bool Fighter::newfighter()
{
    char* structbytes = new char [4];
    Game->readFromRAM((u32) mainadd, structbytes, 4, false);
    int address = hextonum(structbytes, 4) - 0x80000000;
    delete structbytes;

    if (address == structadd)
        return false;
    return true;
}
