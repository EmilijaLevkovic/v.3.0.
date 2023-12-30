#include "pch.h"
#include "Dll.h"
#include<iostream>

Studentasc::Studentasc(const Studentasc& other) {
    this->setVardas(other.getVardas());
    this->setPavarde(other.getPavarde());
    this->egz = other.egz;
    this->gal_vid = other.gal_vid;
    this->galutinis2 = other.galutinis2;
    this->galutinis = other.galutinis;
    this->med = other.med;
    this->paz = other.paz;
    this->vid = other.vid;
}

Studentasc& Studentasc::operator=(Studentasc& other) {
    if (this == &other) {
        return *this;
    }
    else {
        this->setVardas(other.getVardas());
        this->setPavarde(other.getPavarde());
        this->egz = other.egz;
        this->gal_vid = other.gal_vid;
        this->galutinis2 = other.galutinis2;
        this->galutinis = other.galutinis;
        this->med = other.med;
        this->paz = other.paz;
        this->vid = other.vid;
        return *this;
    }
}

Studentasc::Studentasc(Studentasc&& other) {
    // cout<<"movec\n";
    setVardas(other.getVardas());
    setPavarde(other.getPavarde());
    egz = other.egz;
    gal_vid = other.gal_vid;
    galutinis2 = other.galutinis2;
    galutinis = other.galutinis;
    med = other.med;
    if (other.paz.size() != 0)
        paz = std::move(other.paz);
    vid = other.vid;
    if (other.paz.size() != 0)paz = std::move(other.paz);
}

Studentasc& Studentasc::operator=(Studentasc&& other) {
    // cout<<"move\n";
    if (this == &other) {
        return *this;
    }
    else {
        this->setVardas(other.getVardas());
        this->setPavarde(other.getPavarde());
        this->egz = other.egz;
        this->gal_vid = other.gal_vid;
        this->galutinis2 = other.galutinis2;
        this->galutinis = other.galutinis;
        this->med = other.med;
        if (other.paz.size() != 0)
            this->paz = other.paz;
        this->vid = other.vid;
        // other.vardas=nullptr;
        // other.pavarde=nullptr;
        if (other.paz.size() != 0)this->paz = std::move(other.paz);
        return *this;
    }
}

vector<int>::iterator Studentasc::iterators(string& type) {
    vector<int>::iterator it;
    if (type == "begin") {
        it = paz.begin();
    }
    else if (type == "end") {
        it = paz.end();
    }
    return it;
}

double Studentasc::mediana() {
    double mm = paz.size();
    sort(paz.begin(), paz.end() - 1);
    if (paz.size() % 2 != 0) { med = paz.at((paz.size() / 2)); }
    else {
        med = (paz.at((paz.size() - 1) / 2) + paz.at(((paz.size() / 2)))) / 2.0;
    }
    return med;
}

double Studentasc::vidurkis() {
    double paz_sum = 0.0;
    double mm = paz.size();
    if (paz.size() == 0) {
        vid = 0.0;
    }
    else {
        for (int i = 0; i < mm; i++) {
            paz_sum += paz.at(i);
        }
        vid = paz_sum / (mm);
    }
    return vid;
}

void Studentasc::galutinio_skaiciavimai(string tipas) {
    if (tipas == "vid") {
        galutinis = (vid * 0.4 + egz * 0.6);
    }
    else if (tipas == "med") {
        galutinis = (med * 0.4 + egz * 0.6);
    }
    else if (tipas == "failas") {
        galutinis = (vid * 0.4 + egz * 0.6);
        galutinis2 = (med * 0.4 + egz * 0.6);
    }
}

Studentasc::Studentasc(std::stringstream& str, int& l) {
    int temp_paz = 0;
    string v, p;
    str >> v >> p;
    setVardas(v); setPavarde(p);
    for (int i = 0; i < l; i++) {
        paz.reserve(l);
        str >> temp_paz;
        paz.push_back(temp_paz);
        temp_paz = 0;
    }
    str >> egz;
    med = mediana();
    vid = vidurkis();
    paz.clear();
    galutinio_skaiciavimai("failas");
}

std::stringstream Studentasc::output_string() {
    std::stringstream str;
    string v = getVardas(), pav = getPavarde();
    str << left << setw(15) << v << setw(15) << pav << setw(16);
    str.precision(2);
    str << std::fixed;
    str << galutinis;
    return str;
}

ostream& operator<<(std::ostream& out, const Studentasc& to_print) {
    out << to_print.getVardas() << " " << to_print.getPavarde() << " " << to_print.galutinis << endl;
    return out;
}

bool palygintivardus(Studentasc& a, Studentasc& b) {
    string a_vardas = a.getVardas(), a_pavarde = a.getPavarde(), b_vardas = b.getVardas(), b_pavarde = b.getPavarde();
    return tie(a_vardas, a_pavarde) < tie(b_vardas, b_pavarde);
}
bool palygintigalutinius(Studentasc& a, Studentasc& b) {
    return a.getGal() > b.getGal();
}
bool palygintigalutiniusalt(Studentasc& a, Studentasc& b) {
    return a.getGal() < b.getGal();
}

#include <vector>

void Irasymasranka(Studentasc& temp, int paz_sk) {
    std::vector<int> arr(paz_sk);
    cout << "Irasykite studento varda ir pavarde: ";
    // cin>>temp.vardas>>temp.pavarde;
    temp.readvarpav(cin);
    cin.ignore(10000, '\n');
    char ran;
    cout << "Ar noresite atsitiktinai generuotu pazymiu? (y/n) ";
    //cin>>ran;
    while (true) {
        cin >> ran;
        cin.ignore(10000, '\n');
        if (ran == 'y' || ran == 'Y') {
            for (int i = 0; i < paz_sk; i++) {
                arr[i] = rand() % 11;
            }
            int ran = rand() % 11;
            temp.setEgz(ran);
            break;
        }
        else if (ran == 'n' || ran == 'N') {
            cout << "Iveskite studento pazymius, maksimum " << paz_sk << ", iveskite -1 noredami baigti ivesti: ";

            // temp.paz=new int[paz_sk];
            // for(int i=0;i<paz_sk;i++){
            //   arr[i]=0;
            // }
            int l, t = 0;
            while (cin >> l) {
                temp.InsertPaz(l);
                t++;
                if (!cin)cout << "Iveskite skaiciu nuo 0 iki 10";
                else if (t == (paz_sk)) {
                    if (l == -1) {
                        temp.RemovePaz();
                    }
                    break;
                }
                else if (l == -1) {
                    temp.RemovePaz();
                    break;
                }
                cin.clear();
            }
            cin.ignore(1000, '\n');
            cout << "Iveskite egzamino pazymi: ";
            temp.readEgz(cin);
            cin.ignore(10000, '\n');
            break;
        }
        else cout << "Iveskite y arba n: ";
    }

}


void out(Studentasc& temp) {
    cout << left << setw(15) << temp.getVardas() << setw(15) << temp.getPavarde() << setw(16);
    cout.precision(2);
    cout << std::fixed;
    cout << temp.getGal() << '\n';
    // cout<<temp.vid<<" "<<temp.med<<"\n";
}

void Skaitymas(vector<Studentasc>& temp, std::stringstream& temp2, Timer& t_vis) {
    int tipas;
    cout << "Kuria strategija naudoti?(1/2/3)"; cin >> tipas;
    int temp_paz, l = 0;
    // Studentasc temp3;
    string check, tp;
    temp2 >> check >> check;
    while (true) {
        temp2 >> check;
        if (check[0] == 'N')l++;
        else {
            break;
        }
    }
    Timer t_failas;
    while (!temp2.eof()) {
        Studentasc temp3(temp2, l);
        temp.push_back(temp3);
    }
    cout << "Failo skaitymas uztruko: " << t_failas.elapsed() << endl;
    isskaidymas(temp, tipas);
    cout << "Visas programos laikas: " << t_vis.elapsed() << endl;

}

void outf(vector<Studentasc>& temp) {
    ofstream fout("out.txt");
    fout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(16) << "Galutinis (Vid.) " << setw(16) << "Galutinis (Med.)\n";
    fout << "---------------------------------------------------------------\n";
    for (int i = 0; i < temp.size(); i++) {
        std::stringstream str = temp[i].output_string();
        string tekstas = str.str();
        fout << tekstas;
    }

    fout.close();
}

void sukurtifaila(int filesize, int ndsk) {
    int temp_egz;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 10);
    std::stringstream ss, nd;
    int paz_temp;
    double laikas;
    Timer t_dal;
    ss << "Stud" << filesize << ".txt";
    string failas = ss.str(), nd_tekstas;
    ofstream fout(failas);
    fout << setw(15) << left << "Vardas" << setw(15) << left << "Pavarde";
    for (int i = 0; i < ndsk; i++) {
        nd << "ND" << (i + 1);
        nd_tekstas = nd.str();
        fout << setw(4) << left << nd_tekstas;
        nd.str(string()); nd.clear();
    }
    fout << setw(4) << left << "Egz.\n";
    std::stringstream vardas, pavarde;
    for (int i = 0; i < filesize; i++) {
        vardas << "Vardas" << (i + 1);
        pavarde << "Pavarde" << (i + 1);
        fout << setw(15) << left << vardas.str() << setw(15) << left << pavarde.str();
        for (int j = 0; j < ndsk; j++) {
            fout << setw(4) << left << dist(mt);
            paz_temp = 0;
        }
        fout << setw(4) << left << dist(mt) << '\n';
        vardas.str(string()); vardas.clear();
        pavarde.str(string()); pavarde.clear();
    }
    fout.close();
    cout << "Failo kurimas uztruko: " << t_dal.elapsed() << endl;
}

void isskaidymas(vector<Studentasc>& studentai, int tipas) {
    bool skaidymo_zenkl = false;
    Timer t_dal;
    if (tipas == 2) tipas2(studentai);
    else if (tipas == 3)tipas3(studentai);
    else {
        sort(studentai.begin(), studentai.end() - 1, palygintigalutiniusalt);
        cout << "Studentu rikiavimas uztruko: " << t_dal.elapsed() << endl;
        t_dal.reset();
        vector<Studentasc> cringe, based;
        cringe.reserve(studentai.size() * 0.7); based.reserve(studentai.size() * 0.7);
        for (Studentasc& i : studentai) {
            if (i.getGal() < 5) {
                cringe.push_back(i);
            }
            else based.push_back(i);
        }
        cout << "Studentu suriusiavimas i 2 dalis uztruko: " << t_dal.elapsed() << endl;
        studentai.clear();
        t_dal.reset();
        out_failo_sukurimas(cringe, "cringe");
        cout << "'Cringe' studentu irasymas uztruko: " << t_dal.elapsed() << endl;
        t_dal.reset();
        out_failo_sukurimas(based, "based");
        cout << "'Based' studentu irasymas uztruko: " << t_dal.elapsed() << endl;
        cringe.clear(); based.clear();
    }

}

void out_failo_sukurimas(vector<Studentasc>& temp, string tipas) {
    string file;
    std::stringstream ss;
    ss << tipas << ".txt";
    file = ss.str();
    ofstream fout(file);
    fout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(13) << "Gal vid\n";
    fout << "-----------------------------------------------\n";
    for (Studentasc i : temp) {
        fout << setw(15) << left << i.getVardas() << setw(15) << left << i.getPavarde();
        fout.precision(2);
        fout << std::fixed;
        fout << i.getGal() << '\n';
    }
}

void tipas2(vector <Studentasc>& studentai) {
    Timer t_dal;
    sort(studentai.begin(), studentai.end() - 1, palygintigalutinius);
    cout << "Studentu rikiavimas uztruko: " << t_dal.elapsed() << endl;
    t_dal.reset();
    vector<Studentasc> cringe;
    cringe.reserve(studentai.size() * 0.7);
    vector<Studentasc>::size_type j = 0;
    for (int i = studentai.size(); i >= 0; i--) {
        if (studentai[i].getGal() < 5) {
            cringe.push_back(studentai[i]);
            studentai.pop_back();
        }
    }
    cout << "Studentu suriusiavimas i 2 dalis uztruko: " << t_dal.elapsed() << endl;
    t_dal.reset();
    out_failo_sukurimas(cringe, "cringe");
    cout << "'Cringe' studentu irasymas uztruko: " << t_dal.elapsed() << endl;
    t_dal.reset();
    out_failo_sukurimas(studentai, "based");
    cout << "'Based' studentu irasymas uztruko: " << t_dal.elapsed() << endl;
    cringe.clear();
    studentai.clear();
}

void tipas3(vector <Studentasc>& studentai) {
    Timer t_dal;
    sort(studentai.begin(), studentai.end() - 1, palygintigalutiniusalt);
    // vector<Studentasc>::iterator it=partition(studentai.begin(),studentai.end(),partition);
    cout << "Studentu rikiavimas uztruko: " << t_dal.elapsed() << endl;
    t_dal.reset();
    vector<Studentasc>::size_type j = 0;
    vector<Studentasc>::iterator it = find_if(studentai.begin(), studentai.end(), paz_skirst);
    cout << "Studentu suriusiavimas i 2 dalis uztruko: " << t_dal.elapsed() << endl;
    t_dal.reset();
    // out_failo_sukurimas(cringe,"cringe");
    out_failo_sukurimas3(studentai, "cringe", it);
    // cringe.clear();
    out_failo_sukurimas3(studentai, "based", it);
    studentai.clear();

}
bool paz_skirst(Studentasc& temp) {
    return((temp.getGal() == 5.0));
}
bool partition(Studentasc& temp) {
    return(temp.getGal() < 5);
}

void out_failo_sukurimas3(vector<Studentasc>& temp, string tipas, vector<Studentasc>::iterator it) {
    string file;
    std::stringstream ss;
    ss << tipas << ".txt";
    file = ss.str();
    ofstream fout(file);
    fout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(13) << "Gal vid\n";
    fout << "-----------------------------------------------\n";
    if (tipas == "based") {
        std::stringstream tekstas;
        for (; it < temp.end() - 1; ++it) {
            tekstas = it->output_string();
            string tekstas2 = tekstas.str();
            fout << tekstas2 << '\n';
            tekstas.str(string()); tekstas.clear();
        }
        tekstas.str(string()); tekstas.clear();
    }
    else if (tipas == "cringe") {
        std::stringstream tekstas;
        it--;
        for (; it > temp.begin(); --it) {
            tekstas = it->output_string();
            string tekstas2 = tekstas.str();
            fout << tekstas2 << '\n';
            tekstas.str(string()); tekstas.clear();
        }
        tekstas.str(string()); tekstas.clear();
    }
}

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
