//	PODSTAWOWY (GOTOWY PROGRAM)
//  main.cpp
//  PROJEKT na Laboratoria z Podstaw Programowania
//	Projekt nr.2
/*
 1: Wczytujemy Dane z Pliku
 2: Kompresujemy dane algorytmem RLE
 3:	Uzywamy specjalnego sumbolu do oznaczania powtarzajacych sie znakow. Tym Znakiem bedzie ":"
 4: Stopien kompresji
 5: Zapisz ponownie do pliku, nowego pliku.
 */
//
//  Created by Rafal Szymanek on 07/12/2017.
//  Copyright © 2017 Rafal Szymanek. All rights reserved.
//
// To Do:
// 1: Zrob menu \/
// 2: Czy chce wsczytac z pliku czy wprowadzic†wlasne recznie dane \/
// 3: Wyswietlenie skompresowanych danych \/
// 4: Zapis do pliku z zapytaniem czy chce to zrobic \/
// 5: Dekompresja? \/
// 5: Zrob dokumentacje \/
// 6: Testy \/

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

#ifdef _WIN32 	// Bibloteka do funkcji sleep()
#include <cstdlib>		// Dla Windows
#include <conio.h>
#include <windows.h>
#include <sstream>

#else
#include <unistd.h>		// Dla Unix
#include <stdlib.h>
#endif



using namespace std;
#ifdef _WIN32
template <typename T>
string NumberToString ( T Number )
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}
#endif

void clearScreen() // Czyszczenie konsoli w zaleznosci od systemu operacujnego
{
#ifdef _WIN32
	system("cls");
#else
	system ("clear");
#endif
}

void sleepForSeconds(int n) // Usypianie programu na x sekund w zaleznosci od systemu operacyjnego
{
#ifdef _WIN32
	n *= 1000;		// Windows liczy w milisekundach
	Sleep(n);
#else
	sleep(n);
#endif
}

char getCharacter()	// Aby pobral tylko jednen znak i automatycznie wcisnal enter. Funkcja _getch()
{
	char n;
#ifdef _WIN32
	n = getch();
#else
	cin >> n;
#endif
	return n;
	
}

int LiczenieLiczbyLinijekPliku(string sciezka){
	fstream plik;
#ifdef _WIN32
	plik.open(sciezka.c_str(), ios::in);
#else
	plik.open(sciezka, ios::in);
#endif
	if (plik.good() == false) {		// Sprawdzamy czy plik istnieje
		clearScreen();
		cout << "Blad wczytywania pliku! Wpisales bledna sciezke." << endl;
		plik.close();
		return -1;					// Nie mozemy miec ujemnej liczby linijek
	}
	
	string linia; 		// Zmienna pomocnicza, do ktorej bedziemy zapisywac jedna linijke pliku
	int licznik = 0; 	// Zmienna pomocnicza, dzieki ktorej bedziemy poruszac sie po tablicy stringow
	while (getline(plik, linia)) {
		
		licznik++;
	}
	plik.close();
	// Zamykamy plik
	
	return licznik;
}



int WczytywanieDanychZPliku(string sciezka, string *tab){
	fstream plik;
#ifdef _WIN32
	plik.open(sciezka.c_str(), ios::in);
#else
	plik.open(sciezka, ios::in);
#endif
	if (plik.good() == false) {		// Sprawdzamy czy plik istnieje
		clearScreen();
		cout << "Blad wczytywania pliku! Wpisales bledna sciezke." << endl;
		plik.close();
		return 1;
	}
	
	string linia; 		// Zmienna pomocnicza, do ktorej bedziemy zapisywac jedna linijke pliku
	int licznik = 0; 	// Zmienna pomocnicza, dzieki ktorej bedziemy poruszac sie po tablicy stringow
	while (getline(plik, linia)) {
		tab[licznik] = linia;
		licznik++;
	}
	plik.close(); 					// Zamykamy plik
	
	return 0;
}

int ZapisDoPliku(string *tab, int liczbaLinijek, string sciezka)
{
	ofstream plik;	// Do utworzenia nowego pliku
#ifdef _WIN32
	plik.open(sciezka.c_str());
#else
	plik.open(sciezka);
#endif
	
	if (plik.good() == false) {	// Sprawdzamy czy plik sie dobrze wczytal
		clearScreen();
		cout << "Blad pliku!";
		plik.close();
		return 1;
	}
	for (int i=0; i < liczbaLinijek; i++) {
		plik << tab[i];
		plik << endl;
	}
	
	plik.close();
	return 0;
}

int ZapisDoPliku(string linia, string sciezka){
	ofstream plik;	// Do utworzenia nowego pliku
#ifdef _WIN32
	plik.open(sciezka.c_str());
#else
	plik.open(sciezka);
#endif
	
	if (plik.good() == false) {	// Sprawdzamy czy plik sie dobrze wczytal
		clearScreen();
		cout << "Blad pliku!";
		plik.close();
		return 1;
	}
	plik << linia;
	plik.close();
	return 0;
}

string ZamianaCiagowZnakow(string linia)
{
	int dlugosc = linia.length(), pomocnicza = 0; // pomocnicza sluzy nam do zapisania ile jest takich samych znakow pod rzad.
	string napis, skompresowany = "";
	
	for (int i = 0; i < dlugosc; i++) {
		skompresowany += linia[i];								// Zapisujemy przynajmniej jedna litere
		pomocnicza = 2;											// Jezeli znajdziemy kolejna to bedzie ona druga z rzedu
		if (i < dlugosc && linia[i] == linia[i+1]) {			// Pilnujemy aby nie wyszala poza tabele
			for (int j = i+1; j < dlugosc; j++) {				// Druga petla, ktora bedzie liczyc ile jest liter z rzedu
				if (j < dlugosc && linia[j] == linia[j+1]) {
					pomocnicza +=1;
					
				}
				else{
					i = j;										// Petla z "i" musi zaczac tam gdzie skonczyla petla z "j"
#ifdef _WIN32
					skompresowany += ":" + NumberToString(pomocnicza);// zapisujemy do skompresowanego pliku
#else
					skompresowany += ":" + to_string(pomocnicza);
#endif
					break; 										// Nastepne nie tworza jednego ciagu
				}
				
			}
			
		}
		
	}
	return skompresowany;
}

void Kompresja(string *tab, int liczbaLinijek, string *tabDocelowa){
	string linijkaPomocnicza;
	for (int i=0; i< liczbaLinijek; i++) {
		linijkaPomocnicza = tab[i]; 							// Bierzemy poszczegolna linijke z naszego calego pliku
		tabDocelowa[i] = ZamianaCiagowZnakow(linijkaPomocnicza);// Nasza pomocnicza linijke dajemy do kompresji i zapisujemy ja do tablicy gdzie zanajduje sie docelowo tekst skompresowany
		
	}
}

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

string Dekompresja(string fraza)
{
	string pomoc;
	int ilosc, licznik;
	float a=0;
	
	for (int i = 0; i < fraza.length(); i++) {
		licznik = 0;
		a = 0;
		if (fraza[i] == ':') {							// Znajdywanie separatora ":"
			for (int j = i+1; j < fraza.length(); j++) {// Zaczynamy od kolejnego wyrazu
				pomoc = fraza[j];
				if (is_number(pomoc)) {					// Jezeli jest numerem
					a += atoi(pomoc.c_str());			// Przekonwertuj to na int
					licznik++;							// Ile razy wykonalismy dana operacje
					a*=10;								// Musimy przesunac przecinek, aby mozna bylo odczytac dobra liczbe np. mamy liczbe 15. Najierw mamy 1 potem * 10 i dodajemy 5 = 15
				}
				else break;								// Jezeli nie jest liczba, przerywamy petle.
				
				
			}
			
			ilosc = (int)a/10;							// Musimy cofnac przecinek z ostatniej operacji oraz przekonwetowac na int
			
			pomoc = "";
			for (int j = 1; j < ilosc; j++) {			// Zapisujemy do zmiennej pomocniczej tyle razy dany wyraz ile razy ma wystapic a:3 - > aaa
				pomoc += fraza[i-1];
			}
			fraza.erase(i,licznik+1);					// Usuwamy zawartosc jaka jest separator i liczbe wystepujaca po nim. Plus wyraz jakim jest ":".
			fraza.insert(i, pomoc);						// Dodajemy nowa zawartosc, zdekompresowana
			
			i = 0;										// Najlepiej rozpoczac petle od zera, byc moze zmieni sie troche kolejnosc podczas dekompresji, nie kosztuje nas to duzo czasu.
			
		}
		
		
	}
	return fraza;										// Zwracamy zdekompresowana fraze
	
}

int sprawdzanieDlugosciZnakowWTablicy(string *tab,int &liczbaLinijek)
{
	int iloscZnakow = 0;
	
	for (int i = 0; i < liczbaLinijek; i++) {
		iloscZnakow += tab[i].length();
	}
	return iloscZnakow;
}

float liczeniePoziomuKompresji(int przedKompresja, int poKompresji)
{
	float wynik = float((poKompresji)*100)/przedKompresja;
	wynik *= 100;
	wynik = floor(wynik);
	wynik /= 100;
	return 100 - wynik;
}



/////////////////////////////////////////////////////////////////
//			Funkcja main()
/////////////////////////////////////////////////////////////////

int main() {
	int liczbaLinijek, status,liczbaZnakowPrzedKompresja ,liczbaZnakowPoKompresji, cnd = 1;
	char wyborUzytkownika;
	string sciezka, *daneZPliku, *skompresowaneDane, tekstDoSkompresowania, skompresowanyTekst, zdekompresowanyTekst, *zdekompresowaneDane, tekstDoDekompresji;
	
	
	cout << "Witaj w programie!" << endl << "Program ten bezstratnie kompresuje plik \".txt\""<< endl << endl;
	
	
	for(;;)
	{
		/////////////////////////////////////////////////////////////////
		// Menu glowne
		/////////////////////////////////////////////////////////////////
		cout << "Wybierz opcje: " << endl;
		cout << "1) Skompresuj gotowy plik" << endl;
		cout << "2) Skompresuj wpisaja fraze z klawiatury" << endl;
		cout << "3) Dekompresja pliku" << endl;
		cout << "4) Dekompresja wpisanej frazy z klawiatury" << endl;
		cout << "5) Wyjdz z programu" << endl;
		
		wyborUzytkownika = getCharacter();
		switch (wyborUzytkownika) {
			case '1':
				/////////////////////////////////////////////////////////////////
				// Skompresuj gotowy plik
				/////////////////////////////////////////////////////////////////
				clearScreen();
				status = 0;
				for(;;)
				{
					cout << "Skompresuj gotowy plik" << endl << endl;
					
#ifdef _WIN32
					
#else
					if(status==0) getchar();	// getchar() potrzebny tylko raz tylko w systemie UNIX! Poniewaz bez tego omija getline! Przy pozniejszych probach nie jest juz†to potrzebne
#endif
					
					cout << "Podaj sciezke do pliku: ";		// Przykladowa sciezka Mac OS -> /Users/Rafal_Szymanek/Documents/PlikiProjekt/plik.txt
					getline(cin, sciezka);					// Pliki moga miec jakies spacje
					
					
					
					liczbaLinijek = LiczenieLiczbyLinijekPliku(sciezka);	// Musimy wiedziec†ile liniej ma nasz plik
					status = 1;
					if (liczbaLinijek == -1) continue;
					
					daneZPliku = new string[liczbaLinijek];					// Dynamiczne alokowanie pamieci
					skompresowaneDane = new string[liczbaLinijek];
					status = WczytywanieDanychZPliku(sciezka, daneZPliku);
					
					if (status == 0) {
						break;
					}
				}
				
				
				Kompresja(daneZPliku, liczbaLinijek, skompresowaneDane);	// Kompresujemy dane
				
				
				liczbaZnakowPrzedKompresja = sprawdzanieDlugosciZnakowWTablicy(daneZPliku, liczbaLinijek);
				liczbaZnakowPoKompresji = sprawdzanieDlugosciZnakowWTablicy(skompresowaneDane, liczbaLinijek);
				
				clearScreen();
				
				
				
				cout << "Dane zostay skompresowane" << endl << endl;
				cout << "Poziom kompresji wyniosi: " << liczeniePoziomuKompresji(liczbaZnakowPrzedKompresja, liczbaZnakowPoKompresji) << "%" << endl;
				cnd = 1;
				while(cnd){
					cout << "Wybierz opcje:" << endl;
					cout << "1) Nadpisz plik"<< endl;
					cout << "2) Zapisz w nowym pliku"<< endl;
					cout << "3) Tylko wyswietl skompresowane dane" << endl;
					
					wyborUzytkownika = getCharacter();
					
					// Zapis skompresowanych danych do pliku
					
					switch (wyborUzytkownika) {
						case '1':
							ZapisDoPliku(skompresowaneDane, liczbaLinijek, sciezka);	// Zapisujemy skompresowane dane do pliku
							cout << "Dane zostaly zapisane, kliknij enter aby przejsc dalej" << endl << endl;
							getchar();
#ifdef _WIN32
							
#else
							getchar(); // System UNIX potrzebuje dwukrotnego użycia tej funkcji. Pierwszą opcje pomija.
#endif
							clearScreen();
							cnd = 0;
							break;
						case '2':
							clearScreen();
							cout << "Zapisz w nowym pliku" << endl;
							status = 0;
							for (;;) {
#ifdef _WIN32
								
#else
								if(status==0) getchar();		//getchar() potrzebny tylko raz! Poniewaz bez tego omija getline! Przy pozniejszych probach nie jest juz†to potrzebne
#endif
								cout << "Podaj sciezke: ";
								
								getline(cin, sciezka);
								status = ZapisDoPliku(skompresowaneDane, liczbaLinijek, sciezka);
								if (status == 1) continue; // Jezeli plik nie bedzie dobrze otworzony wroc na poczatek do podania sciezki.
								
								cout << "Dane zostaly zapisane, kliknij enter aby przejsc dalej";
								getchar();
								clearScreen();
								cnd = 0;
								break;
							}
							
							break;
						case '3':
							clearScreen();
							for (int i = 0; i < liczbaLinijek; i++) {	// Wyswietlamy dane w tablicy
								cout << skompresowaneDane[i] << endl;
							}
							cout << endl<< "Wcisnij enter aby przejsc dalej" ;
							getchar();
#ifdef _WIN32
							
#else
							getchar(); 	// System UNIX potrzebuje dwukrotnego użycia tej funkcji. Pierwszą opcje pomija.
#endif
							clearScreen();
							cnd = 0;
							break;
							
						default:
							clearScreen();
							cout << "Wpisales liczbe z poza zakresu!" << endl << endl;
							cnd = 1;
							break;
					}
				}
				
				//	Skasowanie pamiecy dynamicznej
				delete [] skompresowaneDane;
				delete [] daneZPliku;
				
				break;
				
			case '2':
				/////////////////////////////////////////////////////////////////
				// Skompresuj wpisana fraze z klawiatury
				/////////////////////////////////////////////////////////////////
				
				clearScreen();
				cout << "Wpisz tekst: "<< endl;
#ifdef _WIN32
				
#else
				getchar();		// System UNIX potrzebuje dwukrotnego użycia tej funkcji. Pierwszą opcje pomija.
#endif
				getline(cin, tekstDoSkompresowania);
				skompresowanyTekst = ZamianaCiagowZnakow(tekstDoSkompresowania);		// Kompresujemy nasza fraze
				
				liczbaZnakowPrzedKompresja = tekstDoSkompresowania.length();
				liczbaZnakowPoKompresji = skompresowanyTekst.length();
				
				clearScreen();
				cout << "Dane zotaly skompresowane" << endl << endl;
				
				cout << "Poziom kompresji wynosi: " << liczeniePoziomuKompresji(liczbaZnakowPrzedKompresja, liczbaZnakowPoKompresji) << "%" << endl;
				cnd = 1;
				while(cnd){
					cout << "Wybierz opcje:" << endl;
					cout << "1) Zapisz w nowym pliku"<< endl;
					cout << "2) Tylko wyswietl skompresowane dane" << endl;
					
					
					
					wyborUzytkownika = getCharacter();
					
					switch (wyborUzytkownika) {
						case '1':
							status = 0;
							for (;;) {
								if(status==0) getchar();	//getchar() potrzebny tylko raz! Poniewaz bez tego omija getline! Przy pozniejszych probach nie jest juz†to potrzebne
								cout << "Podaj sciezke: ";
								
								getline(cin, sciezka);
								status = ZapisDoPliku(skompresowanyTekst, sciezka);
								if (status == 1) {			// Jezeli plik sie nie otworzyl, wroc do podania sciezki.
									continue;
								}
								cout << "Dane zostaly zapisane, kliknij enter aby przejsc dalej";
								getchar();
								clearScreen();
								cnd = 0;
								break;
							}
							
							break;
						case '2':
							clearScreen();
							cout << skompresowanyTekst;
							cout << endl<< "Wcisnij enter aby przejsc dalej" ;
							getchar();
#ifdef _WIN32
							
#else
							getchar();		// System UNIX potrzebuje dwukrotnego użycia tej funkcji. Pierwszą opcje pomija.
#endif
							clearScreen();
							cnd = 0;
							break;
						default:
							clearScreen();
							cout << "Wpisales liczbe z poza zakresu" << endl;
							break;
					}
					
				}
				break;
				
				
			case '3':
				/////////////////////////////////////////////////////////////////
				// Dekompresja pliku
				/////////////////////////////////////////////////////////////////
				clearScreen();
				
				
				for(;;)
				{
					cout << "Dekompresuj gotowy plik" << endl << endl;
					
#ifdef _WIN32
					
#else
					if(status==0) getchar();
#endif
					// getchar() potrzebny tylko raz! Poniewaz bez tego omija getline! Przy pozniejszych probach nie jest juz†to potrzebne
					cout << "Podaj sciezke do pliku: ";		// Przykladowa sciezka Mac OS -> /Users/Rafal_Szymanek/Documents/PlikiProjekt/plik.txt
					getline(cin, sciezka);					// Pliki moga miec jakies spacje
					
					
					
					liczbaLinijek = LiczenieLiczbyLinijekPliku(sciezka);	// Musimy wiedziec†ile liniej ma nasz plik
					status = 1;
					if (liczbaLinijek == -1) continue;
					
					daneZPliku = new string[liczbaLinijek];					// Dynamiczne alokowanie pamieci
					zdekompresowaneDane = new string[liczbaLinijek];
					status = WczytywanieDanychZPliku(sciezka, daneZPliku);
					
					if (status == 0) {
						break;
					}
				}
				for (int i = 0; i < liczbaLinijek; i++) {				// Zapisanie zdekompresowanych danych do nowej tablicy
					zdekompresowaneDane[i] = Dekompresja(daneZPliku[i]);
				}
				
				
				
				
				
				clearScreen();
				cout << "Dane zostaly zdekompresowane!" << endl << endl;
				cnd = 1;
				while(cnd){
					cout << "Wybierz opcje:" << endl;
					cout << "1) Nadpisz plik"<< endl;
					cout << "2) Zapisz w nowym pliku"<< endl;
					cout << "3) Tylko wyswietl zdekompresowane dane" << endl;
					
					wyborUzytkownika = getCharacter();
					
					// Zapis zdekompresowanych danych do pliku
					
					switch (wyborUzytkownika) {
						case '1':
							ZapisDoPliku(zdekompresowaneDane, liczbaLinijek, sciezka);		// Zapis do pliku zdekompresowanych danych
							cout << "Dane zostaly zapisane, kliknij enter aby przejsc dalej";
							getchar();
#ifdef _WIN32
							
#else
							getchar();		// System UNIX potrzebuje dwukrotnego użycia tej funkcji. Pierwszą opcje pomija.
#endif
							clearScreen();
							cnd = 0;
							break;
						case '2':
							status = 0;
							clearScreen();
							for (;;) {
#ifdef _WIN32
								
#else
								if(status==0) getchar();	//getchar() potrzebny tylko raz! Poniewaz bez tego omija getline! Przy pozniejszych probach nie jest juz†to potrzebne
#endif
								
								cout << "Podaj sciezke: ";
								
								getline(cin, sciezka);
								
								status = ZapisDoPliku(zdekompresowaneDane, liczbaLinijek, sciezka);
								if (status == 1) {			// Jezeli plik sie nie otworzy, wroc do podania sciezki
									continue;
								}
								clearScreen();
								cout << "Dane zostaly zapisane, kliknij enter aby przejsc dalej";
								getchar();
								clearScreen();
								cnd = 0;
								break;
							}
							
							break;
						case '3':
							clearScreen();
							for (int i = 0; i < liczbaLinijek; i++) {	// Wypisanie zdekompresowanych danych na ekran
								cout << zdekompresowaneDane[i] << endl;
							}
							cout << endl<< "Wcisnij enter aby przejsc dalej" ;
							getchar();
#ifdef _WIN32
							
#else
							getchar();		// System UNIX potrzebuje dwukrotnego użycia tej funkcji. Pierwszą opcje pomija.
#endif
							clearScreen();
							cnd = 0;
							break;
							
						default:
							clearScreen();
							cout << "Wpisales liczbe z poza zakresu!" << endl << endl;
							cnd = 1;
							break;
					}
				}
				
				
				delete [] daneZPliku;		// Usuniecie pamieci dynamicznej
				delete [] zdekompresowaneDane;
				break;
				
			case '4':
				/////////////////////////////////////////////////////////////////
				// Dekompresja wpisanej frazy z klawiatury
				/////////////////////////////////////////////////////////////////
				clearScreen();
				cout << "Wpisz tekst: "<< endl;
#ifdef _WIN32
				
#else
				getchar();
#endif
				getline(cin, tekstDoDekompresji);
				zdekompresowanyTekst = Dekompresja(tekstDoDekompresji);		// Dekompresujemy fraze
				
				
				clearScreen();
				cout << "Dane zostay skompresowane" << endl << endl;
				
				cnd = 1;
				while (cnd) {
					cout << "Wybierz opcje:" << endl;
					cout << "1) Zapisz w nowym pliku"<< endl;
					cout << "2) Tylko wyswietl skompresowane dane" << endl;
					
					
					
					wyborUzytkownika = getCharacter();
					
					switch (wyborUzytkownika) {
						case '1':
							status = 0;
							for (;;) {
#ifdef _WIN32
								
#else
								if(status==0) getchar();	//getchar() potrzebny tylko raz! Poniewaz bez tego omija getline! Przy pozniejszych probach nie jest juz†to potrzebne
#endif
								clearScreen();
								cout << "Podaj sciezke: ";
								
								getline(cin, sciezka);
								status = ZapisDoPliku(zdekompresowanyTekst, sciezka);
								if (status == 1) {
									continue;			// Jezeli plik sie nie otworzy, wroc do podania sciezki.
								}
								clearScreen();
								cout << "Dane zostaly zapisane, kliknij enter aby przejsc dalej";
								getchar();
								clearScreen();
								cnd = 0;
								break;
							}
							
							break;
						case '2':
							clearScreen();
							cout << zdekompresowanyTekst;	// Wyswietlamy zdekompresowny tekst
							cout << endl<< "Wcisnij enter aby przejsc dalej" ;
							getchar();
#ifdef _WIN32
							
#else
							getchar();		// System UNIX potrzebuje dwukrotnego użycia tej funkcji. Pierwszą opcje pomija.
#endif
							clearScreen();
							cnd = 0;
							break;
						default:
							clearScreen();
							cout << "Wpisales liczbe z poza zakresu" << endl;
							break;
					}
				}
				break;
				
			case '5':
				/////////////////////////////////////////////////////////////////
				// Wyjscie
				/////////////////////////////////////////////////////////////////
				
				clearScreen();
				cout << "Wyjdz z programu"<< endl;
				cout << "3  ";
				sleepForSeconds(1);
				cout << "2  ";
				sleepForSeconds(1);
				cout << "1  "<< endl;
				sleepForSeconds(1);
				
				exit(0);
				
				break;
				
			default:
				clearScreen();
				cout << "Wpisales liczbe z poza zakresu" << endl;
				continue;
		}
	}
	return 0;
}

