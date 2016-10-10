//--------------------------------------------

#include "source.h"

//#define FROM_FILE    // do test�w z IDE, kompilacja ostateczna bez tej dyrektywy

//--------------------------------------------

void curr_time( int size ) {

   time_t  timev;
   time(&timev);
   cout << ctime( &timev )<< " Rozmiar n=" << size << endl; 		  // godzina i data uruchomienia programu

}

//--------------------------------------------

int main(int argc, char** argv) {

//	system ("chcp 1250"); system("cls");			// polskie znaki w konsoli (spowalnia)

	ios_base::sync_with_stdio(0);					// wymaganie przez Organizator�w (przy�piesza strumienie)

	unsigned size = 0;								// ilo�� Alejek, Basen�w
	char * *p_array = NULL;							// mapa basenu 2D

	#ifdef FROM_FILE
		size = load_from_file_new( p_array );                       // UWAGA: wymaga zdefiniowania �cie�ki do pliku wewn�trz funkcji
	#else
		size = get_pool_map_cin( p_array );
	#endif

	if ( size <= 0 )	cout << "B�EDNA WARTO�� size: " << size << endl;        // punkt kontrolny

	curr_time( size );
	upperB( p_array, size );						// must be after load 2D map, czyli po get_pool_map(...)
	draw( size, p_array );							// wy�wietla map� basen�w (kolorowana)

	if ( size <= 3 )
	{
		cout << "dla \"n\" mniejszego od 3, najwi�kszy basen to : " <<
						for_size_lower_than_3( size, p_array ) << endl;      	system("pause");	// UWAGA: na mapie 3x3 dla liczby p�l basenik�w od 2 do 4 w��cznie wynik jest uzyskiwany metod� losow�
//		return for_size_lower_than_3( size, p_array );
		return 0;
	}
	cout <<	"Najwi�kszy basen: " << biggest( p_array, size ) << endl;

	FreeMemory( p_array, size );
	system("pause");

	return 0;
//	return biggest( p_array, size );
}

//---------------------------------------------------------------------------


/* OLD

#include "source.h"
						// Metoda wprowadzenia mapy
#define FROM_CIN

//#define SET_PARAMS
//#define FROM_FILE
#define STREAMS
		get_pool_map_cin();
//--------------------------------------------

void initialize( int &argc, char** &argv) {

	system ("chcp 1250"); system("cls");		// polskie znaki w konsoli

#ifdef SET_PARAMS
	#ifdef FROM_FILE
		MessageBoxA(0, "Zdefiniowano dwie dyrektywy wprowadzania\n\nPopraw w pliku \"main.cpp\"", "Error", 0);
	#endif
#endif

	// ma�e oszustwo
#ifdef SET_PARAMS
	argc   += 5;
	argv[1] = "1";  // wymiary tablicy
	argv[2] = "abbbb";
	argv[3] = "abbbb";
	argv[4] = "0123456789";
	argv[5] = "12b45";
	argv[6] = "bss245e";
#endif

#ifdef FROM_FILE
	argc = 2; argv[1] = (char*) "example.txt";//argv[1] = (char*) "D:\\Dev-C++\\PAR\\example.txt";		// dodaje parametr pliku z tablic�
#endif
}
//--------------------------------------------

int main(int argc, char** argv) {

	initialize(argc, argv);
	ios_base::sync_with_stdio(0);					// wymaganie przez Organizator�w

	unsigned size = 0;								// ilo�� Alejek, Basen�w
	char * *p_array = NULL;							// mapa basenu 2D
#ifdef FROM_CIN
	size = get_pool_map_cin( p_array );
#endif
#ifdef SET_PARAMS
	size = load_from_param( argc, argv, p_array );	// funkcja nie ostateczna (b��dna) na olimpiade (z lini polece�)
#endif
#ifdef FROM_FILE
	size = load_from_file( argc, argv, p_array );	// tablica jest w pliku (pierwsza linia pliku to liczba kolumn i wierszy)
#endif
	if ( size <= 0 )
	{
		get_size_from_user(size);					// r�czne deklarowanie dynamiczenej tablicy
		cin.ignore();

		p_array = new char *[ size ];				// deklaracja dynamicznych tablic

		get_pool_map( p_array, size );				// wype�nianie tablic r�cznie
		system("cls");
	}

	if ( size <= 3 ) return for_size_lower_than_3( size, p_array );

	upperB( p_array, size );						// must be after load 2D map, czyli po get_pool_map(...)
	draw( size, p_array );							// wy�wietla map� basen�w(kolorowana)

	cout <<	"Najwiekszy basen: " << biggest( p_array, size ) << endl;

	FreeMemory( p_array, size );

	system("pause");

//	return 0;
	return biggest( p_array, size );
}

*/
