#pragma once
#ifndef DLL_H_INCLUDED
#define DLL_H_INCLUDED

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include<vector>
#include<fstream>
#include<tuple>
#include<random>
#include <chrono>


using std::cin;
using std::copy;
using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setprecision;
using std::setw;
using std::string;
using std::sort;
using std::rand;
using std::fixed;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::istringstream;
using std::stoi;
using std::tie;
using namespace::std;

using std::ostream;
class Humanc {
private:
    string vardas, pavarde;
public:
    Humanc() { vardas = ""; pavarde = ""; }
    inline string getVardas() const { return vardas; }
    inline string getPavarde() const { return pavarde; }
    inline void readvarpav(std::istream& in) { in >> vardas >> pavarde; }
    inline void setVardas(string temp) { vardas = temp; }
    inline void setPavarde(string temp) { pavarde = temp; }
    virtual void f() = 0;
    ~Humanc() {
        vardas = "";
        pavarde = "";
    }

};
class Studentasc :public Humanc {
private:
    vector<int> paz;
    int egz;
    double vid;
    double med;
    double galutinis;
    double galutinis2;
    double gal_vid;
public:
    Studentasc() :egz(0), vid(0.0), med(0.0), galutinis(0.0), galutinis2(0.0), gal_vid(0.0), Humanc() {}
    Studentasc(std::stringstream& str, int& l);
    Studentasc(const Studentasc& other);
    Studentasc(Studentasc&& other);

    // getteriai

    inline double getGal() const { return galutinis; }

    // setteriai
    inline void galbalas(double temp) { galutinis = temp; }
    inline void setEgz(int& e) { egz = e; }
    inline void InsertPaz(int& p) { paz.push_back(p); }
    inline void RemovePaz() { paz.pop_back(); }

    void readAll(std::stringstream& str);
    inline void readEgz(std::istream& in) { in >> egz; }
    vector<int>::iterator iterators(string& type);
    double mediana();
    double vidurkis();
    void galutinio_skaiciavimai(string tipas);
    Studentasc& operator=(Studentasc& other);
    Studentasc& operator=(Studentasc&& other);
    friend ostream& operator<<(ostream& out, const Studentasc& to_print);
    std::stringstream output_string();
    virtual void f() { egz = egz; }
    // destruktorius
    ~Studentasc() {
        paz.clear();
    }


};


struct stud {
    string vardas, pavarde;
    vector<int>pazymiai;
    int egzaminas;

};
class Timer {
private:
    using hrClock = std::chrono::high_resolution_clock;
    using durationDouble = std::chrono::duration<double>;
    std::chrono::time_point<hrClock> start;
public:
    Timer() : start{ hrClock::now() } {}
    void reset() {
        start = hrClock::now();
    }
    double elapsed() const {
        return durationDouble(hrClock::now() - start).count();
    }
};

void Skaitymas(vector<Studentasc>& temp, std::stringstream& temp2, Timer& t_vis);
void outf(vector<Studentasc>& temp);
void sukurtifaila(int filesize, int ndsk);
void isskaidymas(vector<Studentasc>& studentai, int tipas);
void out_failo_sukurimas(vector<Studentasc>& temp, string tipas);
void tipas2(vector<Studentasc>& studentai);
void tipas3(vector<Studentasc>& studentai);
bool paz_skirst(Studentasc& temp);
bool partition(Studentasc& temp);
void out_failo_sukurimas3(vector<Studentasc>& temp, string tipas, vector<Studentasc>::iterator it);

void Irasymasranka(Studentasc& temp, int paz_sk);
void out(Studentasc& temp);


bool palygintivardus(Studentasc& a, Studentasc& b);
bool palygintigalutinius(Studentasc& a, Studentasc& b);
bool palygintigalutiniusalt(Studentasc& a, Studentasc& b);


#endif
