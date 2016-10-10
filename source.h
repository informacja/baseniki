//-----------------------------------------------------------------------------------

 	// funkcje main'a

#ifndef SOURCE_H
#define SOURCE_H

#include "load.h"	// func wczytywanie mapy basenik�w do programu
#include "code.h"   // includy, func wy�wietlaj�ce (kolorowanie)
#include "Map.h"    // klasa



//-----------------------------------------------------------------------------------

//srand(time(0));


// if(Key == 'C' && Shift.Contains( ssCtrl ))
//  {
//        ShowMessage("Wci�ni�to kombinacj� klawiszy Ctrl+C");
//  }


//-----------------------------------------------------------------------------------

void get_size_from_user(unsigned &size) {

	string buff;

	cout << "Podaj wielko�� maksymaln� basen�w (1 - 16 010): ";
	cin >> buff;
	size = atoi(buff.c_str());

	while ( size < 1 || size >=  16010 + 1 ) {								// z przedzia�u (w��cznie) <1 ; 16 010> // na zapas
		cout << "warto�� (" << buff << ") jest nie poprawna, podaj inn�: ";
		cin >> buff;
		size = atoi(buff.c_str());
	}
}
//-----------------------------------------------------------------------------------

string example( unsigned ilosc ) 						// pokazuje przyk�adow� mask� "lini/wiersza" basenu
{
	string a;
	for(ilosc; ilosc > 0; ilosc--)

		a += ( rand()%2 ) ? "A" : "B";

	return a;
}

// -----------------------------------------------------------

void get_pool_map( char* *p_array, unsigned &size ) {

	for(int i = 0; i < size; i++ )
 	{
 		p_array[i] = new char[size];
		system("cls");

//#ifdef zero_memory
//	 	for (int h = 0; h < size; h++) p_array[i][h] = NULL;				// NULLowanie pami�ci czyszczenie z "krzaczk�w"
//#endif
// 		cin.ignore();

	// dla pierwszego wprowadzenia losuje przyk�adowe wej�cie
	if ( i == 0 )
		cout << "Podaj uklad " << i + 1 << " (" << example(size)  << ") : " << endl << "               ";

	// wypisuje w nawiasie poprzednio wprowadzon� poziom� linie mapy
	 else
	 {	cout << "Podaj uklad " << i + 1 << " (";
		for (int j = 0; j < size; j++)
			cout << p_array[i-1][j];
		cout << ") : " << endl << "               ";
	 }

	 cin.getline( p_array[i], size + 1 );

//		if( *p_array[ i ] != '\n' ) 								// niepotrzebne
//		{
//            cout << "Wczytano:      " << p_array[i] << endl << endl;
//        }
	}
}
//-----------------------------------------------------------------------------------

unsigned get_pool_size_at( char** array, int size, unsigned X, unsigned Y) {

		// UWAGA: Dzia�a tylko dla kwadratowych basen�w (takich jak na wej�ciu)
//		#ifndef FINAL
//		if( array[X][Y] != 'B'){
//			MessageBox( 0, "parametry nie wskazuj� na pole basenu 'B'\n(b��d kontrolny)\nunsigned* Map::get_pool_size_at()", "B��d", MB_OK );
//			red(X); red(Y);
//			}
//		#endif
		 int inf[5] = {0};
			memset( inf, 0, sizeof(inf) ); // sprz�ta przed zabaw�
			// inf[] zwracana tablica, [0] pole basenu do kt�rego nale�y pozycja podana w param, [1][2] pozycja pocz�tku basenu, [3][4] pozycja ko�ca(prawy dolny r�g)

			if ( array[X][Y] != 'B' ) {

//                inf[1] = -1;	// by wysz�o poza map�
				return 0;
			}


			while ( array[X][Y] == 'B')	if ( X == 0) break; else X--;		// w g�re
				inf[1] = ( array[X][Y] == 'B') ? X : ++X;					// je�li pod t� pozycj� jest 'B'(Bez zmian), je�li nie to przes�wamy si� o jeden // preinkrementacja jest wymagana

			while ( array[X][Y] == 'B')	if ( Y == 0) break; else Y--; 		// w lewo
				inf[2] = ( array[X][Y] == 'B') ? Y : ++Y;

			while ( array[X][Y] == 'B')	if ( X+1 >= size) break; else X++;	// w d�   // mo�e troszk� nie optymalne i�� od g�ry do do�u
				inf[3] = ( array[X][Y] == 'B') ? X : --X;

			while ( array[X][Y] == 'B')	if ( Y+1 >= size) break; else Y++; 	// w prawo
				inf[4] = ( array[X][Y] == 'B') ? Y : --Y;

			inf[0] = (inf[3] - inf[1]+1) * (inf[4] - inf[2]+1);		 		// pole prostok�tnego basenu

//		cout << "[0] rozmiar spr. basenu, [1][2] pozycja lewa g�rna, [3][4] pozycja prawa dolna\n";
//		for (int e = 0; e < sizeof(inf)/4; e++) 				// debug wy�wietla zawarto�� obliczonego powy�ej
//			cout << inf[e] << " ";	cout << endl;

	return  inf[0];
}

//-----------------------------------------------------------------------------------
int los( unsigned size, char **arr ) {

//	srand( time( NULL ) );

	int x, y, max = 0;

	do {
		x = rand() % size;
		y = rand() % size;

	} while ( arr[x][y] == 'B' );         // a� znajdzie alejk�(nie basenik)

	if (0 < x)	   	max += get_pool_size_at( arr, size, x-1, y);
	if (x < size)  	max += get_pool_size_at( arr, size, x+1, y);
	if (0 < y)	   	max += get_pool_size_at( arr, size, x, y-1);
	if (y < size)  	max += get_pool_size_at( arr, size, x, y+1);

	return max;
}
//-------------------------------------------
unsigned brutal_for_3( unsigned size, char **arr )
{
	int pool_cout = 0;

	for (int i = 0; i < 3; i++)
		for(int e = 0; e < 3; e++)	if ( arr[i][e] == 'B' )		pool_cout++;

	switch ( pool_cout ) {

		case 0: return 2;
		case 1: return 3;

						   //to do
		case 2:
		case 3:
		case 4:
			{
				static int max;
				for (int i = 0; i < 500; i++) {

					int buff = 0;
					buff = los( size, arr );
					max = ( buff > max) ?  buff : max;
				}
				return max+2;
			}
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:  if ( pool_cout < 9 ) pool_cout++;
				 if ( pool_cout < 9 ) pool_cout++;

	default:

	;
	}


	return pool_cout;
}

//-----------------------------------------------------------------------------------

unsigned for_size_lower_than_3( unsigned size, char ** arr) {

	switch( size )
	{
		case 0: return 0; break;
		case 1: return 1; break;
		case 2:
		{

			size = 0; 									// ma si� wykona� 4 razy (2*2)

			for (int i = 0; i < 2; i++)
				for (int e = 0; e < 2; e++)
					if ( arr[i][e] == 'B' ) size++;

			if ( size < 4 ) size++;												// przydzielanie dw�ch basenik�w
			if ( size < 4 ) size++;

			return size;	break;
		}
		case 3:	return brutal_for_3( size, arr );

		break;

	default : return 0;
	}
}
//-----------------------------------------------------------------------------------

void upperB(char **p_array, unsigned size) {

	for ( int i = 0; i < size; i++ )
		for(int o = 0; o < size; o++ )
			if ( p_array[i][o] == 'b') 	 p_array[i][o] = 'B';
}
//-----------------------------------------------------------------------------------

void draw( int rozmiar, char * arr[])				// rysuje mape zagospodarowania w 2D
{
	 int o;
 	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	char a[2] {' ',' '};

	cout << endl << "  ";
	putchar (' ');
	for ( int z = 0; z < rozmiar; z++ ) {
			putchar (' '); red(z); // numerowanie czerwony
	}
	cout << endl;      putchar (' '); putchar (' ');
	for ( int i = 0; i < rozmiar; i++ ) {
//	putchar ((char)i);
		red(i);   // numerowanie
		for( o = 0; o < rozmiar; o++ ) {

//			a[1] = (arr[i][o]);
//			string b = &arr[i][o];

			putchar (' ');
			if ( ((char)toupper(arr[i][o])) == 'B' )
			{
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
				putchar ('B');
//				printf("%s" , " B");	// powoduje pikanie (systemowe), nie do wy��czenia
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
			}
			else
			{

				putchar ( toupper(arr[i][o]) );
//				printf("%s" , &a);
			}

//  SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
//	system("Color 2B");
//	else cout << " "<<((char)toupper(arr[i][o])); // printf drukuje w tej samej lini cout ale na pocz�tku (kolorowanie nie dziala na strumienieniach bez endl)
		}
		cout << endl << "  ";
	}
	cout << endl;
}

//-----------------------------------------------------------------------------------

unsigned biggest(char **p_array, const unsigned size) {

	Map pool( size, p_array);

	pool.brutal_1();
//	cout << "\nBrutal_1() max size: " << pool.Get_MAX();
//	pool.draw();

	pool.brutal_2(); // musi by� po brutal_1
	pool.draw();
	cout << "\nBrutal_2() max size: " << pool.Get_MAX() << endl;

	pool.brutal_3();
	pool.draw();

//draw( size, pool.Get_ptr() );
//	pool.~Map();

	return pool.Get_MAX();
}

//-----------------------------------------------------------------------------------

void FreeMemory( char* *p_array, unsigned &size ) {

	cout << "\n--------------------------------"
		 << "\nkontrola (wielk��) = " << size
		 << "\n *** Usuwam *** : ";

// cout << "\n" << sizeof(&p_array) << "\t" << size << " end \n";

	for (int i = size-1; i >= 0; i--) {

		delete [] p_array[i];
		cout << " " << i;
	}

	delete [] p_array;
}

//-----------------------------------------------------------------------------------

unsigned __fastcall load_from_file_new( char** &p_array ) {

	 string line;
	 ifstream myfile ( "D:\\Dev-C++\\PAR - Kopia dla CODEBLOCKS\\map" );
	 cout << "File: " << "map";


	 if( myfile.good() == false ) cout << "\nNie mozna otworzyc pliku!\n\n";

	 if (myfile.is_open())
	 {
		getline (myfile,line);
  	 	const int i = atoi(line.c_str());								// wymiary tablicy  max 16000(z zapasem), teoretyczne 16384

  	 	if ( i <= 0 ) {

			cout << "\n\nPierwsza linia pliku jest niepoprawna: \"" << line << "\""<< endl;
			#ifndef FINAL
//			exit();
		}
		else if( i > 16011 ) {

			cout << "\nWielko�� tablicy jest zbyt du�a. MAX 16 000 (" << i << ")\n";
//			exit();
			#endif
		}
		else cout << "\t(" << i << ")\n\n";								// warto�� w nawiasie to warto�� n, czyli bok kwadratoweja tablicy

  	 	p_array = new char *[ i ];

  	 	for (int j = 0; j < i; j++)
  	 	{
  	 		line = "";   					// czy��i linie w przypadku braku lini w pliku powtarza�o ostatni�
			getline (myfile,line);

  	 		if ( line != "")	cout << line << endl;					// wy�wietla zawarto�� pliku

     		p_array[j] = new char[i];

     		for (int a = 0; a < i; a++)
     			p_array[j][a] =  ( a < line.size() ) ? line.at(a) : 'A';   // wype�nianie
		}

//    	while (! myfile.eof() )
//    	{
//    	getline (myfile,line);
//     	cout <<  line;
////     if (line = something)
////      {
////      // read next line and print it... but how?
//    	}
		myfile.close();
//      	cout << endl;
		for ( int a = 1; a < i*2; a++) cout << "_";
      	cout << "EOF" << endl;

		return i;
	 }
	 else return 0; 	// cout << "Unable to open file";
//	}
//	return 0; 		// program wywo�ano bez parametr�w
}


unsigned __fastcall load_from_file( int argc, char** argv, char** &p_array ) {

	if ( 1 < argc) {													// je�li s� parametry pliku (pierwszy parametr to nazwa programu)

	 cout << "File: " << argv[argc-1] ;// << "\t(" << argc << ")\n" <<  endl ;		// drukuje �cie�k� pliku i numer parametru

	 string line;
	 ifstream myfile ( argv[argc-1] );

	 if( myfile.good() == false ) cout << "\nNie mozna otworzyc pliku!\n\n";

  	 if (myfile.is_open())
  	 {
  	 	getline (myfile,line);
  	 	const int i = atoi(line.c_str());								// wymiary tablicy  max 16000(z zapasem), teoretyczne 16384

  	 	if ( i <= 0 ) {

			cout << "\n\nPierwsza linia pliku jest niepoprawna: \"" << line << "\""<< endl;
			#ifndef FINAL
//			exit();
		}
		else if( i > 16011 ) {

			cout << "\nWielko�� tablicy jest zbyt du�a. MAX 16 000 (" << i << ")\n";
//			exit();
			#endif
		}
		else cout << "\t(" << i << ")\n\n";								// warto�� w nawiasie to warto�� n, czyli bok kwadratoweja tablicy

  	 	p_array = new char *[ i ];

  	 	for (int j = 0; j < i; j++)
  	 	{
  	 		line = "";   					// czy��i linie w przypadku braku lini w pliku powtarza�o ostatni�
  	 		getline (myfile,line);

  	 		if ( line != "")	cout << line << endl;					// wy�wietla zawarto�� pliku

     		p_array[j] = new char[i];

     		for (int a = 0; a < i; a++)
     			p_array[j][a] =  ( a < line.size() ) ? line.at(a) : 'A';   // wype�nianie
		}

//    	while (! myfile.eof() )
//    	{
//    	getline (myfile,line);
//     	cout <<  line;
////     if (line = something)
////      {
////      // read next line and print it... but how?
//    	}
      	myfile.close();
//      	cout << endl;
		for ( int a = 1; a < i*2; a++) cout << "_";
      	cout << "EOF" << endl;

    	return i;
  	 }
  	 else return 0; 	// cout << "Unable to open file";
	}
	return 0; 		// program wywo�ano bez parametr�w
}


//-----------------------------------------------------------------------------------
unsigned __fastcall load_from_param ( int argc, char** argv, char** &p_array ) {

	if ( 1 < argc) {

		const int i = atoi(argv[1]);
		#ifndef FINAL
		if ( i == 0 ) cout << "\nNie rozpoznano argv[1], warto�� niepoprawna lub r�wna zero\n";
		#endif

  	 	p_array = new char *[ i ];

  	 	for (int j = 0; j < i; j++)
  	 	{
     		p_array[j] = new char[i];
//     		if ( strlen( argv[j+ 3] ) == 0) system("pause") ;

//     		cout << argc << endl;

//	if ( argv[j + 3] == 0 ) exit(); // not

     		for (int a = 0; a < i; a++)
     			p_array[j][a] =  ( a < strlen( argv[j+2]) ) ? argv[j+2][a] : 'A';   // wype�nianie
		}

    	return i;	// warto�� n, bok tablicy
  	 }

	return 0; 		// program wywo�ano bez parametr�w
}

#endif
