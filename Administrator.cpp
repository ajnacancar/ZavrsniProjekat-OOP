#include "Administrator.h"
#include <fstream>

int Administrator::brojAdministratora = 0;

Administrator::Administrator()
{
	this->setBrojAdministratora();
}

void Administrator::setBrojAdministratora()
{
	try
	{
		Administrator::brojAdministratora = this->brojAdministratore();
	}
	catch (const char* greska)
	{
		std::cout << greska << "\n";
	}
}

int Administrator::getBrojAdministratora()
{
	return Administrator::brojAdministratora;
}

int Administrator::brojAdministratore()
{
	int broj = 0;
	std::string check;
	std::fstream file;
	file.open("administratori.txt", std::ios::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> check;
			if (check == "Administrator:")
			{
				broj++;
			}
		}

		return broj;
	}
	else
	{
		file.close();
		throw "[GRESKA] Datoteka nije otvorena!\n";
	}
}

bool Administrator::login(std::string korisnicko_ime, std::string lozinka)
{

	std::fstream readFile;
	readFile.open("administratori.txt", std::ios::in);
	std::string temp1, temp2, check;

	while (!readFile.eof())
	{
		readFile >> check;
		if (check == "Administrator:")
		{
			readFile >> check;
			do
			{
				temp1 += check + " ";
				readFile >> check;
			} while (check != "Administrator");
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

bool Administrator::signup()
{
	std::fstream noviKorisnik;
	noviKorisnik.open("administratori.txt", std::ios::out | std::ios::app);
	std::string check, sifra;

	if (noviKorisnik.is_open())
	{
		cout << "\t\tUnesite ime i prezime\n\t\t ";
		this->osoba.setIme();
		this->osoba.setPrezime();
		noviKorisnik << "Administrator: " << this->osoba.getIme() << " " << this->osoba.getPrezime() << "\n";


		if (this->osoba.getIme().size() > 0 && this->osoba.getIme().size() < 20) 
		{ 
				noviKorisnik << "Administrator ime: Administrator"<< this->getBrojAdministratora() + 1 << std::endl; 
		}


		cout << "\t\tUnesite lozinku (max 10 karaktera):\n\t\t ";
		do
		{
			getline(cin, sifra);
			if (sifra.size() > 0 && sifra.size() < 10)
			{
				noviKorisnik << "Lozinka: " << enkriptiraj(sifra) << "\n";
			}
			else
			{
				cout << "\t\tMozete unijeti samo 10 karaktera!\n\t\t ";
			}

		} while (sifra.size() < 1 || sifra.size() > 10);

		cout << "\t\tVase korisnicko ime je: Administrator" << this->getBrojAdministratora() + 1 << "\n";
		return true;
	}
	else
	{
		noviKorisnik.close();
		throw "Greska pri otvaranju datoteke!\n";
	}
	noviKorisnik.close();
}

std::string Administrator::enkriptiraj(std::string lozinka)
{
	for (int i = 0; i < lozinka.size(); i++)
	{
		lozinka[i] += 4;
	}

	for (int i = 0; i < lozinka.size(); i++)
	{
		lozinka[i] -= 3;
	}
	return lozinka;
}

std::string Administrator::dekriptiraj(std::string lozinka)
{
	for (int i = 0; i < lozinka.size(); i++)
	{
		lozinka[i] += 3;
	}

	for (int i = 0; i < lozinka.size(); i++)
	{
		lozinka[i] -= 4;
	}

	return lozinka;
}

Administrator::~Administrator()
{
}
