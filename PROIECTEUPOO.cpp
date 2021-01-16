#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
//clasa unde sunt stocate datele din scrisorile copiilor
class Copii
{
private:
    string nume;
    string prenume;
    int varsta;
    string oras;
    vector<string> wishlist;
    string culoare;

public:
    friend class Elf;
    friend class Troli;
    friend class DnaCraciun;
    Copii(string nume, string prenume, int varsta, string oras, vector<string> wishlist, string culoare)
    {
        this->nume = nume;
        this->prenume = prenume;
        this->varsta = varsta;
        this->oras = oras;
        this->wishlist = wishlist;
        this->culoare = culoare;
    }
    Copii()
    {

    }
    ~Copii()
    {
        wishlist.clear();
    }
};
//clasa pentru jucarii:denumire si pret
class Jucarii
{
private:
    string jucarie;
    int pret;

public:
    friend class Elf;
    friend class DnaCraciun;
    Jucarii(string jucarie, int pret)
    {
        this->jucarie = jucarie;
        this->pret = pret;
    }
};
//clasa pentru status:nume,prenume,status si buget
class Status
{
private:
    string nume;
    string prenume;
    string status;
    int buget;

public:
    friend class Elf;
    friend class Troli;
    friend class DnaCraciun;
    Status(string nume, string prenume, string status, int buget)
    {
        this->nume = nume;
        this->prenume = prenume;
        this->status = status;
        this->buget = buget;
    }
};

class Elf
{
private:
    //vectori pentru a stoca informatiile din fisiere
    vector<Status> listaStatus;
    vector<Jucarii> listaJucarii;
    vector<Copii> listaCopii;

public:
    Elf()
    {

    }
    ~Elf()
    {
        listaCopii.clear();
        listaJucarii.clear();
        listaStatus.clear();
    }
    //citirile din fisier si afisarea lor pe eran, pentru verificare
    void citireCopii()
    {
        ifstream f("Copii.txt");
        try
        {
            if (f)
            {
                string nume, prenume, oras, varsta, temp, culoare;

                vector<string> wishes;
                while (getline(f, nume, ' '))
                {
                    getline(f, prenume, ',');
                    getline(f, varsta, ',');
                    getline(f, oras, ',');
                    getline(f, temp, ',');

                    stringstream ss(temp);

                    string alsotemp;

                    while (getline(ss, alsotemp, '-'))
                    {
                        wishes.push_back(alsotemp);
                    }

                    getline(f, culoare, '\n');

                    listaCopii.push_back(Copii(nume, prenume, stoi(varsta), oras, wishes, culoare));
                    wishes.clear();
                }
            }
            else
            {
                throw 505;
            }
        }
        catch (...)
        {
            cout << "Nu s-a putut deschide fisierul Copii.txt.\n";
            exit(1);
        }

        f.close();
    }

    void afisareListaCopii()
    {
        cout << "Lista copiilor:\n";
        for (int i = 0; i < listaCopii.size(); i++)
        {
            cout << listaCopii[i].nume << " " << listaCopii[i].prenume << "," << listaCopii[i].varsta << "," << listaCopii[i].oras << ",";
            for (int j = 0; j < listaCopii[i].wishlist.size() - 1; j++)
            {
                cout << listaCopii[i].wishlist[j] << "-";
            }
            cout << listaCopii[i].wishlist[listaCopii[i].wishlist.size() - 1] << "," << listaCopii[i].culoare << endl;
        }
    }

    void citireJucarii()
    {
        ifstream f("Jucarii.txt");
        try
        {
            if (f)
            {
                string obiect;
                string valoare;
                while (getline(f, obiect, ' '))
                {
                    getline(f, valoare, '\n');

                    listaJucarii.push_back(Jucarii(obiect, stoi(valoare)));
                }
            }
            else
            {
                throw 505;
            }
        }
        catch (...)
        {
            cout << "Nu s-a putut deschide fisierul Jucarii.txt.\n"
                 << endl;
            exit(1);
        }

        f.close();
    }

    void afisareListaJucarii()
    {
        cout << endl
             << "Lista jucariilor:\n";
        for (int i = 0; i < listaJucarii.size(); i++)
        {
            cout << listaJucarii[i].jucarie << " " << listaJucarii[i].pret << endl;
        }
    }
    void citireStatus()
    {
        ifstream f("Status.txt");
        try
        {
            if (f)
            {
                string nume, prenume, status, buget;
                while (getline(f, nume, ' '))
                {
                    getline(f, prenume, ' ');
                    getline(f, status, ' ');
                    getline(f, buget, '\n');

                    listaStatus.push_back(Status(nume, prenume, status, stoi(buget)));
                }
            }
            else
            {
                throw 505;
            }
        }
        catch (...)
        {
            cout << "Nu s-a putut deschide fisierul Status.txt.\n"
                 << endl;
            exit(1);
        }

        f.close();
    }
    void afisareListaStatus()
    {
        cout << endl
             << "Lista statusurilor:\n";
        for (int i = 0; i < listaStatus.size() - 1; i++)
        {
            cout << listaStatus[i].nume << " " << listaStatus[i].prenume << " " << listaStatus[i].status << " " << listaStatus[i].buget << endl;
        }
    }
    //algoritmul de impartire a cadourilor in functie de status, buget, dorinte si disponibilitate
    void ImpartireCadouri()
    {
        cout << "\nImpartirea cadourilor:\n";

        for (int i = 0; i < listaCopii.size(); i++)
        {
            for (int j = 0; j < listaStatus.size(); j++)
            {

                if (listaCopii[i].nume == listaStatus[j].nume && listaCopii[i].prenume == listaStatus[j].prenume)
                {
                    if (listaStatus[j].status == "cuminte")
                    {
                        int buget = 100;
                        cout << "Copilul " << listaStatus[j].nume << " " << listaStatus[j].prenume << " va primi ";
                        for (int k = 0; k < listaCopii[i].wishlist.size(); k++)
                        {
                            for (int l = 0; l < listaJucarii.size(); l++)
                            {
                                if (listaCopii[i].wishlist[k] == listaJucarii[l].jucarie)
                                {

                                    if (listaJucarii[l].pret <= buget)
                                    {
                                        cout << listaJucarii[l].jucarie << " ";
                                        buget = buget - listaJucarii[l].pret;
                                    }
                                }
                            }
                        }

                        if (buget == 100)
                            cout << "Cadou default de 100 de dolari!";
                        else if (buget > 0)
                        {
                            cout << buget << " acadele";
                        }
                        cout << endl;
                    }
                }
            }
        }

        for (int i = 0; i < listaCopii.size(); i++)
        {
            for (int j = 0; j < listaStatus.size(); j++)
            {

                if (listaCopii[i].nume == listaStatus[j].nume && listaCopii[i].prenume == listaStatus[j].prenume)
                {
                    if (listaStatus[j].status == "rau")
                    {
                        int buget = 10;
                        cout << "Copilul " << listaStatus[j].nume << " " << listaStatus[j].prenume << " va primi ";
                        for (int k = 0; k < listaCopii[i].wishlist.size(); k++)
                        {
                            for (int l = 0; l < listaJucarii.size(); l++)
                            {
                                if (listaCopii[i].wishlist[k] == listaJucarii[l].jucarie)
                                {

                                    if (listaJucarii[l].pret <= buget)
                                    {
                                        cout << listaJucarii[l].jucarie << " ";
                                        buget = buget - listaJucarii[l].pret;
                                    }
                                }
                            }
                        }

                        if (buget == 10)
                            cout << "Cadou default de 10 de dolari!";
                        else if (buget > 0)
                        {
                            cout << buget << " acadele";
                        }
                        cout << endl;
                    }
                }
            }
        }
    }
};

class Troli
{
private:
    int roz = 0;
    int albastru = 0;
    int carbuni = 0;
    vector<Status> listaStatus_troli;
    vector<Copii> listaCopii_troli;

public:
Troli()
{

}
~Troli()
{
    listaCopii_troli.clear();
    listaStatus_troli.clear();
}
    //citirile din fisier
    void citireCopii_troli()
    {
        ifstream f("Copii.txt");
        try
        {
            if (f)
            {
                string nume, prenume, oras, varsta, temp, culoare;

                vector<string> wishes;
                while (getline(f, nume, ' '))
                {
                    getline(f, prenume, ',');
                    getline(f, varsta, ',');
                    getline(f, oras, ',');
                    getline(f, temp, ',');

                    stringstream ss(temp);

                    string alsotemp;

                    while (getline(ss, alsotemp, '-'))
                    {
                        wishes.push_back(alsotemp);
                    }

                    getline(f, culoare, '\n');

                    listaCopii_troli.push_back(Copii(nume, prenume, stoi(varsta), oras, wishes, culoare));
                    wishes.clear();
                }
            }
            else
            {
                throw 505;
            }
        }
        catch (...)
        {
            cout << "Nu s-a putut deschide fisierul Copii.txt.\n";
            exit(1);
        }

        f.close();
    }

    void afisareListaCopii_troli()
    {
        cout << "Lista copiilor pentru troli:\n";
        for (int i = 0; i < listaCopii_troli.size(); i++)
        {
            cout << listaCopii_troli[i].nume << " " << listaCopii_troli[i].prenume << "," << listaCopii_troli[i].varsta << "," << listaCopii_troli[i].oras << ",";
            for (int j = 0; j < listaCopii_troli[i].wishlist.size() - 1; j++)
            {
                cout << listaCopii_troli[i].wishlist[j] << "-";
            }
            cout << listaCopii_troli[i].wishlist[listaCopii_troli[i].wishlist.size() - 1] << "," << listaCopii_troli[i].culoare << endl;
        }
    }
    void citireStatus_troli()
    {
        ifstream f("Status.txt");
        try
        {
            if (f)
            {
                string nume, prenume, status, buget;
                while (getline(f, nume, ' '))
                {
                    getline(f, prenume, ' ');
                    getline(f, status, ' ');
                    getline(f, buget, '\n');

                    listaStatus_troli.push_back(Status(nume, prenume, status, stoi(buget)));
                }
            }
            else
            {
                throw 505;
            }
        }
        catch (...)
        {
            cout << "Nu s-a putut deschide fisierul Status.txt.\n"
                 << endl;
            exit(1);
        }

        f.close();
    }
    //ambalarea cadourilor in functie de status si gen
    void ambalare()
    {
        for (int i = 0; i < listaCopii_troli.size(); i++)
        {
            for (int j = 0; j < listaStatus_troli.size(); j++)
            {

                if (listaCopii_troli[i].nume == listaStatus_troli[j].nume && listaCopii_troli[i].prenume == listaStatus_troli[j].prenume)
                {
                    if (listaStatus_troli[j].status == "cuminte")
                    {
                        if (listaCopii_troli[i].culoare == "roz")
                        {
                            roz++;
                        }
                        else if (listaCopii_troli[i].culoare == "albastru")
                        {
                            albastru++;
                        }
                    }
                    else if (listaStatus_troli[j].status == "rau")
                    {
                        if (listaCopii_troli[i].culoare == "roz")
                        {
                            roz++;
                            carbuni++;
                        }
                        else if (listaCopii_troli[i].culoare == "albastru")
                        {
                            albastru++;
                            carbuni++;
                        }
                    }
                }
            }
        }
        cout << endl
             << "Trolii au folosit " << roz << " ambalaje roz.\n";
        cout << "Trolii au folosit " << albastru << " ambalaje albastre.\n";
        cout << "Trolii au folosit " << carbuni << " carbuni.\n";
    }
};
class DnaCraciun
{
private:
    float bugetcarb;
    vector<Status> listaStatus_DnaCraciun;
    vector<Jucarii> listaJucarii_DnaCraciun;
    vector<Copii> listaCopii_DnaCraciun;

public:
DnaCraciun()
{

}
~DnaCraciun()
{
    listaCopii_DnaCraciun.clear();
    listaJucarii_DnaCraciun.clear();
    listaStatus_DnaCraciun.clear();
}
    vector<string> plecare, sosire;
    //citirile din fisiere
    void citireJucarii_DnaCraciun()
    {
        ifstream f("Jucarii.txt");
        try
        {
            if (f)
            {
                string obiect;
                string valoare;
                while (getline(f, obiect, ' '))
                {
                    getline(f, valoare, '\n');

                    listaJucarii_DnaCraciun.push_back(Jucarii(obiect, stoi(valoare)));
                }
            }
            else
            {
                throw 505;
            }
        }
        catch (...)
        {
            cout << "Nu s-a putut deschide fisierul Jucarii.txt.\n"
                 << endl;
            exit(1);
        }

        f.close();
    }
    void citireCopii_DnaCraciun()
    {
        ifstream f("Copii.txt");
        try
        {
            if (f)
            {
                string nume, prenume, oras, varsta, temp, culoare;

                vector<string> wishes;
                while (getline(f, nume, ' '))
                {
                    getline(f, prenume, ',');
                    getline(f, varsta, ',');
                    getline(f, oras, ',');
                    getline(f, temp, ',');

                    stringstream ss(temp);

                    string alsotemp;

                    while (getline(ss, alsotemp, '-'))
                    {
                        wishes.push_back(alsotemp);
                    }

                    getline(f, culoare, '\n');

                    listaCopii_DnaCraciun.push_back(Copii(nume, prenume, stoi(varsta), oras, wishes, culoare));
                    wishes.clear();
                }
            }
            else
            {
                throw 505;
            }
        }
        catch (...)
        {
            cout << "Nu s-a putut deschide fisierul Copii.txt.\n";
            exit(1);
        }

        f.close();
    }
    void citireStatus_DnaCraciun()
    {
        ifstream f("Status.txt");
        try
        {
            if (f)
            {
                string nume, prenume, status, buget;
                while (getline(f, nume, ' '))
                {
                    getline(f, prenume, ' ');
                    getline(f, status, ' ');
                    getline(f, buget, '\n');

                    listaStatus_DnaCraciun.push_back(Status(nume, prenume, status, stoi(buget)));
                }
            }
            else
            {
                throw 505;
            }
        }
        catch (...)
        {
            cout << "Nu s-a putut deschide fisierul Status.txt.\n"
                 << endl;
            exit(1);
        }

        f.close();
    }
    //calculul bugetelor extra
    void bugetele()
    {
        int carb = 0;
        for (int i = 0; i < listaStatus_DnaCraciun.size(); i++)
        {
            if (listaStatus_DnaCraciun[i].status == "rau")
            {
                carb++;
            }
        }
        bugetcarb = carb / 2;
        cout << endl
             << "Bugetul extra pentru carbuni este de " << bugetcarb << " dolari.\n";

        int acadele1 = 0, acadele2 = 0;
        for (int i = 0; i < listaCopii_DnaCraciun.size(); i++)
        {
            for (int j = 0; j < listaStatus_DnaCraciun.size(); j++)
            {

                if (listaCopii_DnaCraciun[i].nume == listaStatus_DnaCraciun[j].nume && listaCopii_DnaCraciun[i].prenume == listaStatus_DnaCraciun[j].prenume)
                {
                    if (listaStatus_DnaCraciun[j].status == "cuminte")
                    {
                        int buget = 100;

                        for (int k = 0; k < listaCopii_DnaCraciun[i].wishlist.size(); k++)
                        {
                            for (int l = 0; l < listaJucarii_DnaCraciun.size(); l++)
                            {
                                if (listaCopii_DnaCraciun[i].wishlist[k] == listaJucarii_DnaCraciun[l].jucarie)
                                {

                                    if (listaJucarii_DnaCraciun[l].pret <= buget)
                                    {

                                        buget = buget - listaJucarii_DnaCraciun[l].pret;
                                    }
                                }
                            }
                        }

                        if (buget > 0 && buget < 100)
                        {

                            acadele1 = acadele1 + buget;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < listaCopii_DnaCraciun.size(); i++)
        {
            for (int j = 0; j < listaStatus_DnaCraciun.size(); j++)
            {

                if (listaCopii_DnaCraciun[i].nume == listaStatus_DnaCraciun[j].nume && listaCopii_DnaCraciun[i].prenume == listaStatus_DnaCraciun[j].prenume)
                {
                    if (listaStatus_DnaCraciun[j].status == "rau")
                    {
                        int buget = 10;

                        for (int k = 0; k < listaCopii_DnaCraciun[i].wishlist.size(); k++)
                        {
                            for (int l = 0; l < listaJucarii_DnaCraciun.size(); l++)
                            {
                                if (listaCopii_DnaCraciun[i].wishlist[k] == listaJucarii_DnaCraciun[l].jucarie)
                                {

                                    if (listaJucarii_DnaCraciun[l].pret <= buget)
                                    {

                                        buget = buget - listaJucarii_DnaCraciun[l].pret;
                                    }
                                }
                            }
                        }

                        if (buget > 0 && buget < 10)
                        {

                            acadele2 = acadele2 + buget;
                        }
                    }
                }
            }
        }
        cout << "Bugetul pentru acadele este de " << acadele1 + acadele2 << " dolari." << endl;
        cout << "Bugetul extra total(acadele+carbuni) calculat de dna Craciun este de " << bugetcarb + acadele1 + acadele2 << " dolari." << endl;
    }
};
//traseul parcurs
#define edge pair<int, int>
class MosCraciun
{
private:
    vector<pair<float, edge>> G;
    vector<pair<float, edge>> T;
    int *parinte;
    int V;

public:
    MosCraciun(int V)
    {
        parinte = new int[V];

        for (int i = 0; i < V; i++)
            parinte[i] = i;

        G.clear();
        T.clear();
    }
    void Adaugare(int u, int v, float w)
    {
        G.push_back(make_pair(w, edge(u, v)));
    }
    int find_set(int i)
    {

        if (i == parinte[i])
            return i;
        else

            return find_set(parinte[i]);
    }
    void union_set(int u, int v)
    {
        parinte[u] = parinte[v];
    }
    void kruskal()
    {
        int i;
        float uRep, vRep;
        sort(G.begin(), G.end());
        for (i = 0; i < G.size(); i++)
        {
            uRep = find_set(G[i].second.first);
            vRep = find_set(G[i].second.second);
            if (uRep != vRep)
            {
                T.push_back(G[i]);
                union_set(uRep, vRep);
            }
        }
    }
    void print(DnaCraciun *a, DnaCraciun *b)
    {
        string orase[10] = {"random", "Kumanovo", "Bistola", "Ohrid", "Gostivar", "Skopje"};
        cout << endl
             << "Lista oraselor este:" << endl;
        float distTot = 0;
        float distLaponiaMacedonia = 2720.30;
        for (int i = 0; i < T.size(); i++)
        {
            a->plecare.push_back(orase[T[i].second.first]);
            b->sosire.push_back(orase[T[i].second.second]);
            cout << orase[T[i].second.first] << " - " << orase[T[i].second.second] << " : "
                 << T[i].first;
            distTot += T[i].first;

            cout << endl;
        }
        cout << "Distanta totala parcusra de Mos Craciun este de " << (distTot + distLaponiaMacedonia) << " km" << endl;
    }
};

int main()
{
    Elf elf1;
    elf1.citireCopii();
    elf1.afisareListaCopii();
    elf1.citireJucarii();
    elf1.afisareListaJucarii();
    elf1.citireStatus();
    elf1.afisareListaStatus();
    elf1.ImpartireCadouri();

    Troli trol;
    trol.citireCopii_troli();
    trol.citireStatus_troli();
    trol.ambalare();

    DnaCraciun cra;
    cra.citireStatus_DnaCraciun();
    cra.citireCopii_DnaCraciun();
    cra.citireJucarii_DnaCraciun();
    cra.bugetele();

    DnaCraciun *sos = new DnaCraciun[10];
    DnaCraciun *plec = new DnaCraciun[10];

    MosCraciun g(6);
    cout << endl
         << "Orasele vizitate pentru a obtine drumul minim sunt:" << endl;
    g.Adaugare(1, 5, 28);
    g.Adaugare(5, 4, 48.79);
    g.Adaugare(4, 3, 75.75);
    g.Adaugare(3, 2, 46.59);
    g.Adaugare(2, 1, 126.89);
    g.Adaugare(2, 5, 107.79);
    g.Adaugare(2, 4, 92.6);
    g.Adaugare(1, 3, 136.24);
    g.kruskal();
    g.print(sos, plec);
    cout << "Drumul pe care Mos Craciun il impartateste cu Doamna Craciun!" << endl;
    for (int i = 0; i < sos->plecare.size(); i++)
        cout << sos->plecare.at(i) << "-" << plec->sosire.at(i) << endl;
    cout << "Traseul pe care l-am calculat ca fiind cel mai scurt este Rovaniemi-Kumanovo-Skopje-Gostivar-Ohrid-Bistola. Prin comparatie cu ce am obtinut prin algoritmul de calcul, putem observa ca este acelasi traseu!";
}