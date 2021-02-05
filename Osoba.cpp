#include "Osoba.h"
Osoba::Osoba()
{
}

void Osoba::setIme()
{
    std::cout << "Unesite ime: ";
    getline(std::cin, this->ime);
}

void Osoba::setPrezime()
{
    std::cout << "\t\tUnesite prezime: ";
    getline(std::cin, this->prezime);
}



std::string Osoba::getIme()
{
    return this->ime;
}

std::string Osoba::getPrezime()
{
    return this->prezime;
}


Osoba::~Osoba()
{
}
