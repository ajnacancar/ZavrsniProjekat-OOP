#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <iomanip>

#include "Blagajnik.h"
#include "Administrator.h"
#include "Transakcija.h"

int menu(std::vector<std::string>& opcije)
{
	bool enter = false;
	int red = 1;
	do
	{
		std::cout << "\t\t--------------------------------------------\n";
		std::cout << "\t\t|\t\t::MENI::\t\t   |\n";
		std::cout << "\t\t--------------------------------------------\n";
		std::cout << "\n";
		for (int i = 0; i < opcije.size(); i++)
		{
			if (i == red - 1)
			{
				std::cout  << std::setw(16) << ">" << std::setw(40) << std::left <<  opcije[i] << std::setw(3) << std::right << "<" << "\n";
			}
			else
			{
				std::cout << "\t\t " << opcije[i] << "\n";
			}
		}
		cout << "\t\t--------------------------------------------\n";

		switch (_getch())
		{
		case 72: case 'w': case 'W'://ASCII gornja strijela
			if (red == 1) red = opcije.size();
			else red--;
			break;
		case 80: case 's': case 'S'://donja
			if (red == opcije.size()) red = 1;
			else red++;
			break;
		case 13://enter ascii
			enter = true;
			break;
		default:
			break;
		}

		system("cls");
	} while (!enter);

	return red;
}

void loadingBar()
{
	cout << "\n\n\n\n   Ucitavanje\n   ";
	for (int i = 0; i < 50; i++)
	{
		cout << "*";
		Sleep(16);
	}
	system("cls");
}


const int broj_pokusaja = 4;

int main()
{
	std::vector<std::string> opcijeMenija = { "1. Unos uplate|isplate", "2. Stanje blagajne - dnevnika", "3. Nalog uplate|isplate" , "4. Otvori drugi dnevnik" , "5. Napravi novi dnevnik", "6. Izbrisi dnenvik", "7. Odjava iz programa", "8. Odjava i izlaz iz programa" };

	std::vector<std::string> predMeni = { "1.-Prijava|login", "2.-Registracija novog korisnika", "3.-Izlaz" };

	std::vector<std::string> regMeni = { "1. Registra administratora", "2. Registracija blagajnika", "3. Odjava" };

	bool krajprograma = false;
	char unos, znak;
	int pokusaj, h;
	std::string lozinka, korisnicko_ime;

	Transakcija t;
	Blagajnik b;
	Administrator a;
	
	loadingBar();

	logOut:

	switch (menu(predMeni))
	{
		case 1:
			pokusaj = 0;
			do
			{
				system("cls");
				std::cout << "\t\t===========================================\n\n";
				std::cout << "\t\t\t      PRIJAVA|LOG-IN\n";
				std::cout << "\n\t\t==========================================\n\n";

				korisnicko_ime.clear(), lozinka.clear();
				if (pokusaj > 0)
				{
					cout << "\t\t--------------------------------------\n"
						<< "\t\t|Pogresna lozinka ili korisnicko ime.|\n\t\t|Molimo pokusajte ponovo!\t     |"
						<< "\n\t\t--------------------------------------\n";
		
					cout << "\t\tBroj preostalih pokusaja: " << broj_pokusaja - pokusaj << "\n\n";
					if ((broj_pokusaja - pokusaj) == 0)
					{	
						system("cls");
						goto logOut;
					}
				}

				cout << "\t\tKorisnicko ime: ";
				getline(std::cin, korisnicko_ime);
				cout << "\t\t       Lozinka: ";

				znak = _getch();
				do
				{
					if (znak != 8) 
					{
						lozinka += znak;
						cout << 'x';
					}
					znak = _getch();

				} while (znak != 13);
				
				pokusaj++;
			} while (!b.login(korisnicko_ime, lozinka));
			
			system("cls");
			try
			{
				t.setImeBlagajnikaTransakcije(korisnicko_ime);
				
				for (int i = 0; i < 3; i++) 
				{
					cout << "\n\n\n\t\t\tPrijava";

					for (int j = 0; j < 10; j++)
					{
						if (j < 3) cout << ".";
						Sleep(100);
					}
					system("cls");
				}

				cout << "\n\n\t\t------------------------------------------\n";
				cout << "\t\t|Prijavljeni ste kao " << std::left << std::setw(20) << t.getImeBlagajnikaTransakcije() << "|";
				cout << "\n\t\t------------------------------------------\n\n";
				system("pause>0");
				system("cls");

				t.setImetrenutnogDnevnika();
			}
			catch (const char* error)
			{
				std::cout << error;
				t.napraviDnevnik();
				t.setImetrenutnogDnevnika();
			}

			break;

		case 2:
			std::cin.ignore();
			pokusaj = 0;
			do
			{
				system("cls");
				std::cout << "\t\t===========================================\n\n";
				std::cout << "\t\t\t      REGISTRACIJA|SIGN-UP\n";
				std::cout << "\n\t\t==========================================\n\n";
				std::cout << "\n\t\t----------------------------------------------------------------------\n"
					<< "\t\t|Napomena! Samo administratori mogu registrovati korisnike!\t     |"
					<< "\n\t\t----------------------------------------------------------------------\n";

				korisnicko_ime.clear(), lozinka.clear();
				if (pokusaj > 0)
				{
					cout << "\t\t--------------------------------------\n"
						<< "\t\t|Pogresna lozinka ili korisnicko ime.|\n\t\t|Molimo pokusajte ponovo!\t     |"
						<< "\n\t\t--------------------------------------\n";

					cout << "\t\tBroj preostalih pokusaja: " << broj_pokusaja - pokusaj << "\n\n";
					if ((broj_pokusaja - pokusaj) == 0)
					{
						system("cls");
						goto logOut;
					}
				}

				cout << "\t\tKorisnicko ime: ";
				getline(std::cin, korisnicko_ime);
				cout << "\t\t       Lozinka: ";

				znak = _getch();
				do
				{
					if (znak != 8)
					{
						lozinka += znak;
						cout << 'x';
					}
					znak = _getch();

				} while (znak != 13);

				pokusaj++;
			} while (!a.login(korisnicko_ime, lozinka));
			system("cls");

			for (int i = 0; i < 3; i++)
			{
				cout << "\n\n\n\t\t\tPrijava";

				for (int j = 0; j < 10; j++)
				{
					if (j < 3) cout << ".";
					Sleep(100);
				}
				system("cls");
			}

			while (!krajprograma)
			{
				try {

					switch (menu(regMeni)) {
					case 1:
						system("cls");
						std::cout << "\t\t---------------------------------------------------------\n";
						std::cout << "\t\t|\t\t::Registracija admistratora::\t\t\t|\n";
						std::cout << "\t\t---------------------------------------------------------\n\n";
						if (a.signup()) {
							std::cout << "\t\tREGISTRACIJA USPJESNA!\n";
						}
						else {
							std::cout << "\t\tREGISTRACIJA NIJE USPJESNA!\n";
						}
						system("pause>0");
						break;

					case 2:
						system("cls");
						std::cout << "\t\t---------------------------------------------------------\n";
						std::cout << "\t\t|\t\t::Registracija blagajnika::\t\t|\n";
						std::cout << "\t\t---------------------------------------------------------\n\n";
						if (b.signup()) {
							cout << "\t\tREGISTRACIJA USPJESNA!\n";
						}
						else {
							cout << "\t\tREGISTRACIJA NIJE USPJESNA!\n";

						}
						system("pause>0");
						break;

					case 3:

						cout << "\n\t\tDa li ste sigurni da zelite da se odjavite?(y/n)\n\t\tIzbor: ";
						cin >> unos;
						if (unos == 'y' || unos == 'Y')
						{
							system("cls");
							for (int i = 0; i < 3; i++) 
							{
								cout << "\n\n\n\t\t\tOdjava";

								for (int j = 0; j < 10; j++)
								{
									if (j < 3) cout << ".";
									Sleep(100);
								}
								system("cls");
							}
							std::cin.ignore();
							goto logOut;
						}
						else continue;

						break;
						

					}

				}
				catch (const char* error)
				{
					std::cout << error << std::endl;
					system("pause>0");
				}
				catch (...)
				{
					system("cls");
					std::cout << "[GRESKA] Nepoznata greska!\n";
					system("pause>0");
				}

				system("cls");
			}
			
			

			break;
		case 3:
			krajprograma = true;
			break;
	}

	system("cls");
	loadingBar();
	//Glavni program
	while(!krajprograma)
	{
		system("cls");

		try
		{ 
			switch (menu(opcijeMenija))
			{
				case 1:
					system("cls");
					cout << "\t\t---------------------------------------------------------\n";
					cout << "\t\t|\t\t::Unos uplate|isplate::\t\t\t|\n";
					cout << "\t\t---------------------------------------------------------\n\n";
					t.setImeBlagajnikaTransakcije(korisnicko_ime);
					t.uplate_isplate_unos();
					system("pause>0");
					break;
				case 2:
					system("cls");
					cout << "\t\t---------------------------------------------------------\n";
					cout << "\t\t|\t\t::Stanje blagajne|Dnevnik::\t\t|\n";
					cout << "\t\t---------------------------------------------------------\n";
					cout << "\t\t|NAPOMENA: Povecajte prozor za bolje iskustvo." << std::right << std::setw(12) << "|\n";
					cout << "\t\t|Za puni pregled tabele potreban veliki monitor!   " << std::right << std::setw(7) << "|\n";
					cout << "\t\t---------------------------------------------------------\n\n\n\n";
					cout << std::right << std::setw(5) << " " << "Ispis iz dnevnika '" << t.getImeTrenutnogDnevnika() << "'\n\n";

					cout << t;

					system("pause>0");
					break;
				case 3:
					system("cls");
					cout << "\t-------------------------------------------------\n";
					cout << "\t|\t\t::Nalog uplate|isplate::\t|\n";
					cout << "\t-------------------------------------------------\n\n";
					t.ispisNaloga();
					system("pause>0");
					break;
				case 4:
					system("cls");
					cout << "\t-------------------------------------------------\n";
					cout << "\t|\t::Otvoranje drugog dnevnika::\t\t|\n";
					cout << "\t-------------------------------------------------\n\n";
					t.setImetrenutnogDnevnika();
					system("pause>0");
					break;
				case 5:
					system("cls");
					cout << "\t-------------------------------------------------\n";
					cout << "\t|\t\t::Novi dnevnik::\t\t|\n";
					cout << "\t-------------------------------------------------\n\n";
					t.napraviDnevnik();
					system("pause>0");
					break;
				case 6:
					system("cls");
					cout << "\t-------------------------------------------------\n";
					cout << "\t|\t\t::Brisanje dnevnika::\t\t|\n";
					cout << "\t-------------------------------------------------\n\n";
					t.izbrisiDnevnik();
					system("pause>0");
					break;
				case 7:
					cout << "\n\t\tDa li ste sigurni da zelite da se odjavite?(y/n)\n\t\tIzbor: ";
					cin >> unos;
					if (unos == 'y' || unos == 'Y')
					{
						system("cls");
						for (int i = 0; i < 3; i++)
						{
							cout << "\n\n\n\t\t\tOdjava";

							for (int j = 0; j < 10; j++)
							{
								if (j < 3) cout << ".";
								Sleep(100);
							}
							system("cls");
						}
						std::cin.ignore();
						goto logOut;
					}
					else continue;
					break;
				case 8:
					cout << "\n\t\tDa li ste sigurni da zelite da se odjavite?(y/n)\n\t\tIzbor: ";
					cin >> unos;
					if (unos == 'y' || unos == 'Y')
					{
						system("cls");
						for (int i = 0; i < 3; i++)
						{
							cout << "\n\n\n\t\t\tOdjava";

							for (int j = 0; j < 10; j++)
							{
								if (j < 3) cout << ".";
								Sleep(100);
							}
							system("cls");
						}
						krajprograma = true;
					}
					else continue;
				default:
					break;
			}
		}
		catch (const char* error)
		{
			std::cout << error << std::endl;
			system("pause>0");
		}
		catch(...)
		{
			system("cls");
			std::cout << "[GRESKA] Nepoznata greska!\n";
			system("pause>0");
		}

		system("cls");
	}

	return 0;
}