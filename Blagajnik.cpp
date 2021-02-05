#include "Blagajnik.h"
#include <fstream>
#include <conio.h>

Blagajnik::Blagajnik()
{
}

bool Blagajnik::login(std::string korisnicko_ime, std::string lozinka)
{
	std::fstream readFile;
	readFile.open("blagajnici.txt", std::ios::in);
	std::string temp1, temp2, check;
	

	while (!readFile.eof())
	{
		readFile >> check;
		if (check == "Blagajnik:")
		{
			readFile >> check;
			do
			{
				temp1 += check + " ";
				readFile >> check;
			} while (check != "Korisnicko");
			readFile >> check;
		}

		if (check == "ime:")
		{
			readFile >> check;
			if (check == korisnicko_ime)
			{
				readFile >> check;
				if (check == "Lozinka:")
				{
					readFile >> check;
					check = dekriptiraj(check);
					if (check == lozinka)
					{
						readFile.close();
						return true;
					}
				}
			}
		}
	}
	temp1.clear();

	readFile.close();
	return false;
}

bool Blagajnik::signup()
{
	std::fstream noviKorisnik;
	noviKorisnik.open("blagajnici.txt", std::ios::out | std::ios::app);
	std::string check, sifra;
	std::string korisnicko_ime;

	if (noviKorisnik.is_open())
	{
		cout << "\t\tUnesite ime i prezime\n\t\t ";
		this->osoba.setIme();
		this->osoba.setPrezime();
		noviKorisnik << "Blagajnik: " << this->osoba.getIme() << " " << this->osoba.getPrezime() << "\n";
		cout << "\t\tUnesite korisnicko ime (do 20 karaktera):\n\t\t ";
		cout << "Unos: ";
		do
		{
			
			std::getline(std::cin, korisnicko_ime);

			if (this->osoba.getIme().size() > 0 && this->osoba.getIme().size() < 20 && Provjera_Korisnickog_Imena(korisnicko_ime)) {

				noviKorisnik << "Korisnicko ime: " << korisnicko_ime << std::endl;
			break;
		}
			else
			{
				cout << "\t\tMozete unijeti samo 20 karaktera!\n\t\tUnos: ";
			}
		} while (korisnicko_ime.size() < 1 || korisnicko_ime.size() > 20 || !Provjera_Korisnickog_Imena(korisnicko_ime));
		cout << "\t\tUnesite lozinku (max 10 karaktera):\n\t\t ";
		cout << "Unos: ";
		do
		{
			getline(cin, sifra);
			if (sifra.size() > 0 && sifra.size() < 10)
			{
				noviKorisnik << "Lozinka: " << enkriptiraj(sifra) << "\n";
			}
			else
			{
				cout << "\t\tMozete unijeti samo 10 karaktera!\n\t\tUnos: ";
			}

		} while (sifra.size() < 1 || sifra.size() > 10);
		

	}
	else
	{
		noviKorisnik.close();
		throw "Greska pri otvaranju datoteke!\n";
	}
	noviKorisnik.close();
	return true;
}

bool Blagajnik::Provjera_Korisnickog_Imena(std::string korisnicko_ime)
{
	std::ifstream datoteka("blagajnici.txt");
	std::string temp;
	int br = 0;
	if (datoteka.is_open()) {
		while (datoteka >> temp) {
			if (temp == korisnicko_ime) {
				br++;
			}
		}


	}
	else {
		throw "Datoteka se ne moze otvoriti!\n";
	}

	datoteka.close();

	if (br == 0) {
		return true;
	}
	else {
		return false;
	}
}

std::string Blagajnik::enkriptiraj(std::string lozinka)
{
	for (int i = 0; i < lozinka.size(); i++)
	{
		lozinka[i] += 1;
	}

	return lozinka;
}

std::string Blagajnik::dekriptiraj(std::string lozinka)
{

	for (int i = 0; i < lozinka.size(); i++)
	{
		lozinka[i] -= 1;
	}

	return lozinka;
}