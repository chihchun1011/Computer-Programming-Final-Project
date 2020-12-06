#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;

string findspell (){
    static int lastmode=0;
    srand(time(0));
    int mode=0;
    static const string spellone("V:alohomora");    //keyword
    static const string spelltwo("V:lumos");
    static const string spellthree("V:aparecium");
    static const string spellfour="V:tarantallegra";
    static const string spellfive="V:expelliarmus";    //efficient way to win
    static const string spellsix="V:obliviate";
    static const string spellseven="V:rictusempra";
    static const string spelleight="V:impervious";
    static const string spellnine="V:mobiliarbus";
    static const string last="V:mobilicorpus";
    mode=rand()%10+1;
    while (lastmode == mode)
    {
        mode = rand()%10+1;
    }
    lastmode=mode;
    switch (mode){
        case 1:
            return spellone;
        case 2:
            return spelltwo;
        case 3:
            return spellthree;
        case 4:
            return spellfour;
        case 5:
            return spellfive;
        case 6:
            return spellsix;
        case 7:
            return spellseven;
        case 8:
            return spelleight;
        case 9:
            return spellnine;
        default:
            return last;

    }
}

bool comparison(string out, string in)
{
    bool judge = true;
    for (int i=1; out[i] != '\0' ; i++){
        if (out[i] != in [i]){
            judge = false;
            break;
        }
    }
    return judge;

}

string turntochar(int score)
{
    string charscore = "00000000";
    for (int i = 7; i >=0 && score!=0; i--)
    {
        charscore[i] = (score%10) + '0';
        score/=10;
    }
    return charscore;
}

