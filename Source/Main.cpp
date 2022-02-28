using namespace std;

#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include "WindowsDolphinProcess.cpp"
#include "MemoryCommon.cpp"
#include "DolphinAccessor.cpp"

using namespace DolphinComm;
using namespace Common;

int hextonum(char*, int);

#include "MainClasses.cpp"

void calcdamage(Fighter, Fighter);

int ATTACKERADDRESS = 0x0057caec;
int DEFENDERADDRESS = 0x0057cb2c;

int main()
{
    DolphinAccessor dokapon;
    dokapon.hook();

    Fighter Attacker(ATTACKERADDRESS, &dokapon);
    Fighter Defender(DEFENDERADDRESS, &dokapon);

    chrono::seconds delay(1);

    while(true)
    {
        cout << endl << endl;

        Attacker.populateadd();
        Attacker.calcstats();
        Attacker.dispstats();

        Defender.populateadd();
        Defender.calcstats();
        Defender.dispstats();

        calcdamage(Attacker, Defender);

        while (!Attacker.newfighter() && !Defender.newfighter())
            this_thread::sleep_for(delay);
    }
}

int hextonum(char* buffer, int size)
{
    int output = 0;
    for (int i = 0; i < size; i++)
            output += ((int)((unsigned char)buffer[i])) * pow(256, size - 1 - i);
    return output;
}

void calcdamage(Fighter attacker, Fighter defender)
{
    double AttDef = ((attacker.attack * 2.8) - (defender.defense * 1.2)) * (1 + (0.3 * attacker.profbonus));
    double AttMag = ((attacker.attack * 2.8) - (defender.defense * 1.2)) * 1.4 * (1 + (0.3 * attacker.profbonus));
    double AttCou = ((attacker.attack * 2.8) - (defender.defense * 1.2)) * 1.8 * (1 + (0.3 * attacker.profbonus));
    double AttNil = ((attacker.attack * 2.8) - (defender.defense * 1.2)) * 2.0 * (1 + (0.3 * attacker.profbonus));
    double MagDef = ((attacker.magic * 2.4) - (defender.magic)) * (attacker.offmag / 100.0) * 1.4 * ((100 - defender.defmag) / 100.0);
    double MagMag = ((attacker.magic * 2.4) - (defender.magic)) * (attacker.offmag / 100.0) * ((100 - defender.defmag) / 100.0);
    double MagCou = ((attacker.magic * 2.4) - (defender.magic)) * (attacker.offmag / 100.0) * 1.8 * ((100 - defender.defmag) / 100.0);
    double MagNil = ((attacker.magic * 2.4) - (defender.magic)) * (attacker.offmag / 100.0) * 2.0 * ((100 - defender.defmag) / 100.0);
    double StrDef = ((2.5*(attacker.attack + attacker.magic + attacker.speed)) - (defender.defense + defender.magic + defender.speed)) * 1.6 * (1 + (0.3 * attacker.profbonus));
    double StrMag = ((2.5*(attacker.attack + attacker.magic + attacker.speed)) - (defender.defense + defender.magic + defender.speed)) * 1.7 * (1 + (0.3 * attacker.profbonus));
    double StrCou = ((2.0 * (defender.attack + defender.magic + defender.speed)) + (attacker.attack - attacker.defense)) * 2.0 * (1 + (0.3 * attacker.profbonus));
    double StrNil = ((2.5*(attacker.attack + attacker.magic + attacker.speed)) - (defender.defense + defender.magic + defender.speed)) * 2.5 * (1 + (0.3 * attacker.profbonus));
    double Accuracy = ((attacker.speed / ((attacker.speed + defender.speed) / 100.0)) + 25);

    cout << setprecision(5) <<
    attacker.name << " -> " << defender.name << endl << endl <<
    "Att -> Def: " << min(max(round(AttDef * 0.95), 0.0), 9999.0) << " - " << min(max(round(AttDef * 1.05), 0.0), 9999.0) << endl <<
    "Att -> Mag: " << min(max(round(AttMag * 0.95), 0.0), 9999.0) << " - " << min(max(round(AttMag * 1.05), 0.0), 9999.0) << endl <<
    "Att -> Cou: " << min(max(round(AttCou * 0.95), 0.0), 9999.0) << " - " << min(max(round(AttCou * 1.05), 0.0), 9999.0) << endl <<
    "Att -> Nil: " << min(max(round(AttNil * 0.95), 0.0), 9999.0) << " - " << min(max(round(AttNil * 1.05), 0.0), 9999.0) << endl << endl <<
    "Mag -> Def: " << min(max(round(MagDef * 0.95), 0.0), 9999.0) << " - " << min(max(round(MagDef * 1.05), 0.0), 9999.0) << endl <<
    "Mag -> Mag: " << min(max(round(MagMag * 0.95), 0.0), 9999.0) << " - " << min(max(round(MagMag * 1.05), 0.0), 9999.0) << endl <<
    "Mag -> Cou: " << min(max(round(MagCou * 0.95), 0.0), 9999.0) << " - " << min(max(round(MagCou * 1.05), 0.0), 9999.0) << endl <<
    "Mag -> Nil: " << min(max(round(MagNil * 0.95), 0.0), 9999.0) << " - " << min(max(round(MagNil * 1.05), 0.0), 9999.0) << endl << endl <<
    "Str -> Def: " << min(max(round(StrDef * 0.95), 0.0), 9999.0) << " - " << min(max(round(StrDef * 1.05), 0.0), 9999.0) << endl <<
    "Str -> Mag: " << min(max(round(StrMag * 0.95), 0.0), 9999.0) << " - " << min(max(round(StrMag * 1.05), 0.0), 9999.0) << endl <<
    "Str <- Cou: " << min(max(round(StrCou * 0.95), 0.0), 9999.0) << " - " << min(max(round(StrCou * 1.05), 0.0), 9999.0) << endl <<
    "Str -> Nil: " << min(max(round(StrNil * 0.95), 0.0), 9999.0) << " - " << min(max(round(StrNil * 1.05), 0.0), 9999.0) << endl << endl << setprecision(3) <<
    "Accuracy: " << min(max(Accuracy, 50.0), 100.0) << "%" << endl << endl;
}
