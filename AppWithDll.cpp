#include <iostream>
#include "../Dll/Dll.h"

int main() {
    srand(time(NULL));
    int n = 1;
    int paz_sk;
    int programos_tipas;
    string tipas, failas_ar_ranka, failas;
    char pabaiga;
    Studentasc temp2;
    while (true) {
        // cout<<"ar noresite duomenis skaityti is failo ar irasyti ranka? (failas/ranka) ";
        cout << "1. duomenu irasymas ranka\n2. duomenu skaitymas is failo\n3. failo sukurimas\n";
        // cin>>failas_ar_ranka;
        cin >> programos_tipas;
        cin.ignore(1000, '\n');
        if (programos_tipas == 1 || programos_tipas == 2 || programos_tipas == 3)break;
    }
    std::stringstream eilute;
    vector <Studentasc> grupe;
    grupe.reserve(1000000);
    if (programos_tipas == 1) {
        while (true) {
            cout << "Skaiciuoti vidurki ar mediana?(vid/med): ";
            cin >> tipas;
            cin.ignore(10000, '\n');
            if (tipas == "vid" || tipas == "med")break;
        }
        while (true) {
            cout << "Kiek daugiausiai namu darbu pazymiu turi studentai?:  ";
            cin >> paz_sk;
            cin.ignore(10000, '\n');
            if (cin)break;
        }
        Irasymasranka(temp2, paz_sk);
        grupe.push_back(temp2);
        while (true) {
            cout << "Ar norite testi ivesti? (y/n) ";
            cin >> pabaiga;
            cin.ignore(10000, '\n');
            if (pabaiga == 'y' || pabaiga == 'Y') {
                n++;
                // grupe.resize(n);
                Irasymasranka(temp2, paz_sk);
                grupe.push_back(temp2);
            }
            else if (pabaiga == 'n' || pabaiga == 'N')break;
            else cout << "Iveskite y arba n: ";
        }
        if (tipas == "vid") {
            cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(16) << "Galutinis (Vid.)\n";
            cout << "----------------------------------------------\n";
        }
        else if (tipas == "med") {
            cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(16) << "Galutinis (Med.)\n";
            cout << "----------------------------------------------\n";
        }
        for (int i = 0; i < n; i++)
        {
            if (tipas == "vid") {
                grupe[i].vidurkis();
                grupe[i].galutinio_skaiciavimai("vid");

            }
            else if (tipas == "med") {
                grupe[i].mediana();
                grupe[i].galutinio_skaiciavimai("med");
            }
            out(grupe[i]);
        }
    }
    else if (programos_tipas == 2) {
        cout << "Iveskite failo pavadinima: ";
        cin >> failas;
        ifstream fin;

        try {
            fin.open(failas);
            if (!fin) {
                throw std::runtime_error("Failo nera.");
            }
            cout << "Failas atidarytas." << endl;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << endl;
        }
        Timer t_vis;
        eilute << fin.rdbuf();
        cout << t_vis.elapsed() << endl;
        Skaitymas(grupe, eilute, t_vis);
        fin.close();
    }
    else if (programos_tipas == 3) {
        int failo_dydis, nd_skaicius;
        cout << "Kokio dydzio faila norite sukurti?\n";
        cin >> failo_dydis;
        cin.ignore(1000, '\n');
        cout << "Kiek namu darbu turi studentai?\n";
        cin >> nd_skaicius;
        cin.ignore(1000, '\n');
        sukurtifaila(failo_dydis, nd_skaicius);
    }
    grupe.clear();
}
