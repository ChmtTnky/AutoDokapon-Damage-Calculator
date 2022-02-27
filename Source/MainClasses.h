#ifndef MAINCLASSES_H_INCLUDED
#define MAINCLASSES_H_INCLUDED

class Fighter
{
private:
    DolphinAccessor* Game;
    int mainadd;
    int structadd;
    int wpadd;
    int shadd;
    int acadd;
    int jobadd;
    int omadd;
    int dmadd;
    int nameadd;
public:
    bool isplayer;
    bool profbonus = false;
    string name;
    int maxhealth;
    int curhealth;
    int attack = 0;
    int defense = 0;
    int magic = 0;
    int speed = 0;
    int offmag = 0;
    int defmag = 0;
    int jobid;

    Fighter(int, DolphinAccessor*);

    void populateadd();
    void calcstats();
    void dispstats();
    bool newfighter();
};

#endif // MAINCLASSES_H_INCLUDED
