#include "Transakcija.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <iomanip>

using namespace std;

std::vector<std::string> zaNalog;


void Transakcija::setImePrimaoca()
{
    std::cout << "\nUnesite ime i prezime primaoca: ";
	getline(std::cin, this->imePrimaoca);
}

void Transakcija::setImeUplatioca()
{
    std::cout << "\nUnesite ime i prezime ulatioca: ";
    getline(std::cin, this->ImeUplatioca);
}

void Transakcija::setImeBlagajnikaTransakcije(std::string ime)
{
	ifstream blagajnik("blagajnici.txt");
	std::string imeB, temp;

	if (blagajnik.is_open()) {
		
		while (blagajnik >> temp) {
			if (temp == "Blagajnik:") {
				blagajnik >> temp;
				imeB.clear();
				do {
					imeB += temp + " ";
					blagajnik >> temp;
				} while (temp != "Korisnicko");	
			}

			if (temp == ime) {
				break;
			}
			
		}

		this->imeBlagajnikaTransakcije = imeB;
	}
	else {
		throw "Datoteka se ne moze otvoriti!\n";
	}
	this->imeBlagajnikaTransakcije = imeB;
	blagajnik.close();
}

void Transakcija::setVrstaTransakcije()
{
	std::unique_ptr<int> x = std::make_unique<int>(0);
	do {
		std::cout << "Vrsta transakcije je:\n";
		std::cout << "1. Uplata\n";
		std::cout << "2. Isplata\n";
		std::cout << "Izbor: ";
		std::cin >> *x;
	} while (*x < 1 || *x>2);
	std::cin.ignore();
	this->transakcija = VrstaTransakcije((*x-1));
}

void Transakcija::setBrojRacuna()
{
	std::cout << "\nUnesite broj racuna (13 karaktera)\n";
	bool ispravan = false;
	do {
		std::cout << "Unos: ";
		getline(cin, this->brRacuna);
		if (this->brRacuna.size() > 13 || this->brRacuna.size() < 13) {
			std::cout << "Netacan broj racuna!\n";
		}
		else {
			ispravan = true;
		}

	} while (!ispravan);
}

void Transakcija::setHitno()
{
	std::unique_ptr<int> x = std::make_unique<int>(0);
	do {
		std::cout << "\nHitna transakcija:\n";
		std::cout << "1. Ne\n";
		std::cout << "2. Da\n";
		std::cout << "Izbor: ";
		std::cin >> *x;
	} while (*x < 1 || *x>2);
	std::cin.ignore();
	this->hitnost = Hitno((*x - 1));
}

void Transakcija::ispisNaloga()
{
	Transakcija temp;
	std::cout << temp;

	std::fstream dnevnik;
	dnevnik.open(this->getImeTrenutnogDnevnika().c_str(), ios::in);

	if (dnevnik.is_open())
	{
		std::unique_ptr<int> opcija = std::make_unique<int>(0);

		std::cout << "\n\nUnesite redni broj naloga";
		do
		{
			std::cout << "\nUnos: ";
			std::cin >> *opcija;

		} while (*opcija < 1 || *opcija > zaNalog.size());

		std::vector<std::string> niz;
		std::string imeNaloga, temp, ime, strNalog;

		strNalog = zaNalog[*opcija - 1];
		stringstream strstream(strNalog);
	
		strstream >> temp;
		if (temp == "Rbr:") 
		{
			strstream >> temp;
			niz.push_back(temp);		
		}
		temp.clear();
		strstream >> temp;
		if (temp == "Vrsta:")
		{
			strstream >> temp;
			niz.push_back(temp);
		}
		temp.clear();
		strstream >> temp;
		if (temp == "Datum:")
		{
			strstream >> temp;
			niz.push_back(temp);
		}
		temp.clear();
		strstream >> temp;
		if (temp == "Ime:")
		{
			strstream >> temp;
			do
			{
				ime += temp + " ";
				strstream >> temp;
			} while (temp != "Racun:");
			niz.push_back(ime);
			ime.clear();
		}

		if (temp == "Racun:")
		{
			temp.clear();
			strstream >> temp;
			niz.push_back(temp);
		}

		temp.clear();
		strstream >> temp;
		if (temp == "ImeB:")
		{
			strstream >> temp;
			do
			{
				ime += temp + " ";
				strstream >> temp;
			} while (temp != "Opis:");
			niz.push_back(ime);
			ime.clear();
		}
		if (temp == "Opis:")
		{
			strstream >> temp;
			do
			{
				ime += temp + " ";
				strstream >> temp;
			} while (temp != "Iznos:");
			niz.push_back(ime);
			ime.clear();
		}
			
		if (temp == "Iznos:")
		{
			strstream >> temp;
			niz.push_back(temp);
		}

		if (niz[1] == "Uplata")
		{
			this->transakcija = Uplata;
		}
		else
		{
			this->transakcija = Isplata;
		}

		std::string racunPrimaoca, racunPosiljaoca, ucesnik, rbr;

		switch (this->transakcija)
		{
			case Uplata:
				ucesnik = "Univerzitet u Zenici";
				racunPrimaoca = "0000000000111";
				racunPosiljaoca = niz[4];
				imeNaloga = "uplatnica-" + niz[4] + "-" + niz[0] + "-" + this->getImeTrenutnogDnevnika();
				break;
			case Isplata:
				ucesnik = niz[3];
				niz[3] = "Univerzitet u Zenici";
				racunPrimaoca = niz[4];
				racunPosiljaoca = "0000000000111";
				imeNaloga += "isplatnica-" + niz[4] + "-" + niz[0] + "-" + this->getImeTrenutnogDnevnika();
				break;

		}

		this->setHitno();

		fstream nalog;
		nalog.open(imeNaloga.c_str(), ios::out | ios::trunc);
		nalog << "--------------------------------------------------------------------------------------------------\n";
		nalog << "\t\t\t\t\t::" << niz[1] << "::\n";
		nalog << "--------------------------------------------------------------------------------------------------\n\n";
		nalog << "Uplatio je " << left << setw(42) << niz[3];
		nalog << "Racun primaoca:   |";
		for (int i = 0; i < 13; i++)
		{
			if (i < racunPrimaoca.length())nalog << racunPrimaoca[i] << "|";
			else nalog << "/|";
		}
		nalog << endl;
		nalog << "Svrha doznake: " << left << setw(38) << niz[6]; 
		nalog << "Racun posiljaoca: |";
		for (int i = 0; i < 13; i++)
		{
			if (i < racunPosiljaoca.length()) nalog << racunPosiljaoca[i] << "|";
			else nalog << "/|";
		}
		nalog << endl;
		nalog << "Primalac/Primatelj: " << ucesnik << endl;
		nalog << "Mjesto i datum uplate: Zenica, " << left << setw(22) << niz[2]; 
		nalog << "KM  " << setw(20) << niz[7];
		switch (this->getHitno()) {
		case Ne:
			nalog << "[]HITNO" << endl;
			break;
		case Da:
			nalog << "[X]HITNO" << endl;
			break;
		}
		nalog << "\n\n_________________________________________________\n";
		nalog << "Potpis i pecat nalogodavca (" << this->getImeBlagajnikaTransakcije() << ")\n";
		nalog << "\n\n_________________________________________________\n";
		nalog << "Potpis ovlastenog lica\n";	

		std::cout << "\n\tUspjesno kreiran nalog!\n";

		nalog.close();
		racunPrimaoca.clear();
		racunPosiljaoca.clear();
		strstream.clear();
		zaNalog.clear();
	}
	else
	{
		dnevnik.close();
		throw "[GRESKA] Dnevnik nije otvoren!\n";
	}

	system("pause>0");
}



std::string Transakcija::getImePrimaoca()
{
    return this->imePrimaoca;
}

std::string Transakcija::getImeUplatioca()
{
    return this->ImeUplatioca;
}

std::string Transakcija::getImeBlagajnikaTransakcije()
{
    return this->imeBlagajnikaTransakcije;
}

VrstaTransakcije Transakcija::getVrstaTransakcije()
{
    return this->transakcija;
}

std::string Transakcija::getBrojRacuna()
{
    return this->brRacuna;
}

Hitno Transakcija::getHitno()
{
	return this->hitnost;
}

std::ostream& operator<<(std::ostream& stream, Transakcija& t)
{
	std::ifstream dnevnik, prebroji;
	int br = 0, br2 = 0;
	float sum = 0, temp, sum_uplata = 0, sum_isplata = 0;
	std::string check, imePrimalcaUplatioca, imeBlagajnika;

	std::string strNalozi;

	prebroji.open(t.getImeTrenutnogDnevnika().c_str(), std::ios::in);

	if (prebroji.is_open())
	{
		while (getline(prebroji, check))
		{
			br2++;
		}
	}
	else 
	{
		br2 = 0; 
	}

	prebroji.close();
	std::cout << "\n";
	if (br2 > 1)
	{
		stream << std::left << std::setw(15) << "Redni broj" << std::left << std::setw(23) << "Vrsta transakcije" << std::left << std::setw(18)
			<< "Datum" << std::left << std::setw(24) << "Uplatioc/Primalac" << std::left << std::setw(27) << "Broj racuna" << std::left << std::setw(26) << "Blagajnik"
			<< std::left << std::setw(38) << "Opis" << std::left << std::setw(20) << "Iznos" << std::endl;
		stream << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		dnevnik.open(t.getImeTrenutnogDnevnika().c_str(), std::ios::in);
		if (dnevnik.is_open())
		{
			zaNalog.clear();

			while (!dnevnik.eof() || br < br2)
			{
				dnevnik >> check;

				if (check == "Redni")
				{
					dnevnik >> check;
					if (check == "broj:")
					{
						dnevnik >> check;
						stream << setw(1) << " " << left << setw(14) << check;
						strNalozi += "Rbr: " + check + " ";
					}
				}
				dnevnik >> check;
				if (check == "Vrsta")
				{
					dnevnik >> check;
					if (check == "transakcije:")
					{
						
						dnevnik >> check;
						stream << left << setw(23) << check;
						strNalozi += "Vrsta: " + check + " ";
						if (check == "Uplata")
						{
							t.transakcija = Uplata;
						}
						else
						{
							t.transakcija = Isplata;
						}
					}
				}
				dnevnik >> check;
				if (check == "Datum:")
				{
					dnevnik >> check;
					stream << left << setw(18) << check;
					strNalozi += "Datum: " + check + " ";
				}
				dnevnik >> check;
				if (check == "Primalac:" || check == "Uplatioc:")
				{
					dnevnik >> check;
					do
					{
						imePrimalcaUplatioca += check + " ";
						dnevnik >> check;
					} while (check != "Broj");
					stream << left << setw(24) << imePrimalcaUplatioca;
					strNalozi += "Ime: " + imePrimalcaUplatioca;
					dnevnik >> check;
				}
				if (check == "racuna:")
				{
					dnevnik >> check;
					stream << left << setw(27) << check;
					strNalozi += "Racun: " + check + " ";
				}
				dnevnik >> check;
				if (check == "Blagajnik:")
				{
					dnevnik >> check;
					do
					{
						imeBlagajnika += check + " ";
						dnevnik >> check;
					} while (check != "Vrsta");
					stream << left << setw(26) << imeBlagajnika;
					strNalozi += "ImeB: " + imeBlagajnika + " ";
					imeBlagajnika.clear();
				}
				dnevnik >> check;
				t.vrsta_transakcije.clear();
				if (check == "isplate:" || check == "uplate:")
				{
					dnevnik >> check;
					do
					{
						t.vrsta_transakcije += check + " ";
						dnevnik >> check;
					} while (check != "Iznos:");

					stream << left << setw(38) << t.vrsta_transakcije;
					strNalozi += "Opis: " + t.vrsta_transakcije + " ";
				}

				if (check == "Iznos:")
				{
					dnevnik >> check;
					stream << left << setw(12) << check << left << setw(26) << " KM" << endl;
					strNalozi += "Iznos: " + check + " ";

					stringstream str(check);
					str >> temp;
					switch (t.transakcija)
					{
					case Uplata:
						sum_uplata += temp;
						break;
					case Isplata:
						sum_isplata += temp;
						break;
					}
					sum += temp;
					str.clear();
				}
				br++;
				t.vrsta_transakcije.clear();
				imePrimalcaUplatioca.clear();
				t.imeBlagajnikaTransakcije.clear();

				zaNalog.push_back(strNalozi);
				strNalozi.clear();
			}

			dnevnik.close();

			stream << "\n\n\n\tDobitak: " << setprecision(2) << fixed << sum_uplata << " KM";
			stream << "\n\tGubitak: " << setprecision(2) << fixed << sum_isplata << " KM";
			stream << "\n\tSaldo:  " << setprecision(2) << fixed << sum_uplata - sum_isplata << " KM" << endl;		
		}
		else 
		{
			system("cls");
			throw "Greska pri otvaranju datoteke!\n";
		}
		dnevnik.close();
	}
	else 
	{
		throw "Ovaj dnevnik nema sadrzaja!\n";
		system("pause>0");
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, Transakcija& t)
{
	t.setImePrimaoca();
	t.setImeUplatioca();
	t.setVrstaTransakcije();
	t.setBrojRacuna();

	return stream;
}

void Transakcija::uplate_isplate_unos()
{
	fstream datoteka;
	datoteka.open(this->getImeTrenutnogDnevnika().c_str(), std::ios::in);
	string temp;
	int br = 0;
	if (datoteka.is_open()) {
		while (datoteka  >> temp) {
			if (temp == "Redni") {
				br++;
			}
		}
	}
	else {
		std::cout << "Datoteka se ne moze otvoriti!\n";
	}
	datoteka.close();
	fstream datotekaUnos;
	datotekaUnos.open(this->getImeTrenutnogDnevnika().c_str(), ios::out | ios::app);

	if (datotekaUnos.is_open()) {
		this->setVrstaTransakcije();

		if (this->getVrstaTransakcije() == Uplata) {
			this->vrsta_transakcije = "Uplata";
		}
		else {
			this->vrsta_transakcije = "Isplata";
		}

		datotekaUnos << "Redni broj: " << ++br << "\n";
		datotekaUnos << "Vrsta transakcije: " << this->vrsta_transakcije << endl;
		this->datum.postaviDatum();
		cin.ignore();
		datotekaUnos << "Datum: " << this->datum.getDan() << "." << this->datum.getMjesec() << "." << this->datum.getGodina() << ".\n";
		if (getVrstaTransakcije() == Uplata) {
			this->setImeUplatioca();
			datotekaUnos << "Uplatioc: " << this->getImeUplatioca() << endl;
			
		}
		else {
			this->setImePrimaoca();
			datotekaUnos << "Primalac: " << this->getImePrimaoca() << endl;
		}
				  

		this->setBrojRacuna();
		datotekaUnos << "Broj racuna: " << this->getBrojRacuna() << endl;
		datotekaUnos << "Blagajnik: " << this->getImeBlagajnikaTransakcije() << endl;
		float iznos;
		std::cout << "\nIznos uplate/isplate\n";
		std::cout << "Iznos: ";
		std::cin >> iznos;
		std::cin.ignore();


		int odabir;
		switch ((VrstaTransakcije)transakcija)
		{
			case Uplata:
				std::cout << "\nUnesite vrstu uplate:\n\t1. Polog gotovine\n\t2. Podizanje gotovine cekom\n\t3. Povrat vise isplacenih sredstava\n\t4. Ostalo";
				do
				{
					std::cout << "\n\nOdabir: ";
					cin >> odabir;
				} while (odabir < 1 || odabir>4);
				datotekaUnos << "Vrsta uplate: ";
				switch (odabir)
				{
					case 1:
						datotekaUnos << "Polog gotovine" << endl;
						break;
					case 2:
						datotekaUnos << "Podizanje gotovine cekom" << endl;
						break;
					case 3:
						datotekaUnos << "Povrat vise isplacenih sredstava" << endl;
						break;
					case 4:
						datotekaUnos << "Ostalo" << endl;
				}
				break;

			case Isplata:
				std::cout << "Unesite vrstu isplate:\n\t1. Placanje nabavljenih dobara\n\t2. Isplata akontacije\n\t3. Isplata dnevnice\n\t4. Isplata toplog obroka\n\t5. Ostalo";
				do
				{
					std::cout << "\n\nOdabir: ";
					cin >> odabir;
				} while (odabir < 1 || odabir>5);
				datotekaUnos << "Vrsta isplate: ";
				switch (odabir)
				{
					case 1:
						datotekaUnos << "Placanje nabavljenih dobara" << endl;
						break;
					case 2:
						datotekaUnos << "Isplata akontacije" << endl;
						break;
					case 3:
						datotekaUnos << "Isplata dnevnice" << endl;
						break;
					case 4:
						datotekaUnos << "Isplata toplog obroka" << endl;
						break;
					case 5:
						datotekaUnos << "Ostalo" << endl;
				}
				break;
		}
		datotekaUnos << "Iznos: " << iznos << endl;
		datotekaUnos.close();


	}
	else {
		throw "Datoteka se ne moze otvoriti!\n";
	}
}

Transakcija::~Transakcija()
{
}


