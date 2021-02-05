#include "Dnevnik.h"
#include <iostream>
#include <fstream>
#include <vector>

std::string Dnevnik::trenutniDnevnik = "";

Dnevnik::Dnevnik()
{
}

void Dnevnik::setImetrenutnogDnevnika()
{
    std::fstream bazaDnevnika;
    std::string line;
    std::vector<std::string> imenaDnevnika;
    this->trenutniDnevnik;
    std::cout << "\n\n\tOdaberite dnenvik koji zelite otvoriti: \n\n";
  
    int i;
    bazaDnevnika.open("dnevnici.txt", std::ios::in);

    if (bazaDnevnika.is_open())
    {
        for (i = 0; getline(bazaDnevnika, line); i++)
        {
            std::cout << "\t" << i + 1 << ". " << line << std::endl;
            imenaDnevnika.push_back(line);
        }

        if (i == 0)
        {
            bazaDnevnika.close();
            throw "[GRESKA] Nema dostupnih dnevnika za otvoriti\n";
        }

        int izbor;
        do
        {
            std::cout << "\n\tUnesite redni broj dnevnika: ";
            std::cin >> izbor;

            if (izbor < 1 || izbor > i)
            {
                std::cout << "Netacan unos!\n";
                std::cin.clear();
                std::cin.ignore();
            }

        } while (izbor < 1 || izbor > i);

        std::cin.ignore();
        Dnevnik::trenutniDnevnik = imenaDnevnika[izbor - 1] + ".txt";
    }
    else
    {
        system("cls");
        bazaDnevnika.close();
        throw "[GRESKA] Datoteka nije otvorena!\n";
    }

    bazaDnevnika.close();
}

std::string Dnevnik::getImeTrenutnogDnevnika()
{
    return Dnevnik::trenutniDnevnik;
}

void Dnevnik::napraviDnevnik()
{
    std::string imeNovogDnevnika, line;
    std::vector<std::string> imenaDnevnika;
    std::fstream noviDnevnik, bazaDnevnika;

    bazaDnevnika.open("dnevnici.txt", std::ios::in);

    if (bazaDnevnika.is_open())
    {
        while (getline(bazaDnevnika, line))
        {
            imenaDnevnika.push_back(line);
        }
        
        bazaDnevnika.close();

        bool izadji = false;
        int br;
        std::cout << "\tUnesite ime dnevnika za napraviti\n";
        do
        {
            imeNovogDnevnika.clear();
            std::cout << "\tUnos: ";
            getline(std::cin, imeNovogDnevnika);

            br = 0;

            for (int i = 0; i < imenaDnevnika.size(); i++)
            {
                if (imenaDnevnika[i] == imeNovogDnevnika)
                {
                    std::cout << "\n\tIme tog dnevnika vec postoji\n\tMolimo vas unesite drugo ime!\n\n";
                    br++;
                }
            }

            if (br == 0) { izadji = true; }

        } while (!izadji);

        imenaDnevnika.push_back(imeNovogDnevnika);
        imeNovogDnevnika += ".txt";
        noviDnevnik.open(imeNovogDnevnika.c_str(), std::ios::out);

        if (noviDnevnik.is_open())
        {
            bazaDnevnika.open("dnevnici.txt", std::ios::out | std::ios::trunc);
            for (int i = 0; i < imenaDnevnika.size(); i++)
            {
                bazaDnevnika << imenaDnevnika[i] << std::endl;
            }

            std::cout << "\n\tNovi dnevnik je uspjesno napravljen!";
            noviDnevnik.close();
            bazaDnevnika.close();
        }
        else
        {

            noviDnevnik.close();
            throw "[GRESKA] Novi dnevnik nije napravljen!\n";
        }
    }
    else
    {
        bazaDnevnika.close();
        throw "[GRESKA] Datoteka nije otvorena!\n";
    }
}

void Dnevnik::izbrisiDnevnik()
{
    std::fstream bazaDnevnika;
    std::string line, imeDnevnikaZaBrisati;
    std::vector<std::string> imenaDnevnika;

    std::cout << "\tOdaberite dnevnik koji zelite izbrisati: \n\n";

    int i;
    bazaDnevnika.open("dnevnici.txt", std::ios::in);

    if (bazaDnevnika.is_open())
    {
        for (i = 0; getline(bazaDnevnika, line); i++)
        {
            std::cout << "\t" << i + 1 << ". " << line << std::endl;
            imenaDnevnika.push_back(line);
        }

        bazaDnevnika.close();

        if (i == 0) { throw "[GRESKA] Nema dostupnih dnevnika\n"; }

        int izbor;
        do
        {
            std::cout << "\n\tUnesite redni broj dnevnika: ";
            std::cin >> izbor;
            if (izbor < 1 || izbor > i)
            {
                std::cin.clear();
                std::cin.ignore();
            }

        } while (izbor < 1 || izbor > i);

         std::cin.ignore();

         imeDnevnikaZaBrisati = imenaDnevnika[izbor - 1] + ".txt";

         if (remove(imeDnevnikaZaBrisati.c_str()) != 0)
         {
             throw "[GRESKA] Dnevnik nije izbrisan!\n";
         }
         else
         {
             imenaDnevnika.erase(imenaDnevnika.begin() + (izbor - 1));
             std::cout << "\n\tDnevnik uspjesno izbrisan!\n";
             
             bazaDnevnika.open("dnevnici.txt", std::ios::out | std::ios::trunc);

             for (int i = 0; i < imenaDnevnika.size(); i++)
             {
                 bazaDnevnika << imenaDnevnika[i] << "\n";
             }

             bazaDnevnika.close();
         }
    }
    else
    {
        bazaDnevnika.close();
        throw "[GRESKA] Datoteka nije otvorena!\n";
    }

    bazaDnevnika.close();
    
}

Dnevnik::~Dnevnik()
{
}
