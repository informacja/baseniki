//-----------------------------------------------------------------------------------

 	// funkcje main'a

#ifndef SOURCE_H
#define SOURCE_H

#include "load.h"	// func wczytywanie mapy baseników do programu
#include "code.h"   // includy, func wyœwietlaj¹ce (kolorowanie)
#include "Map.h"    // klasa



//-----------------------------------------------------------------------------------

//srand(time(0));


// if(Key == 'C' && Shift.Contains( ssCtrl ))
//  {
//        ShowMessage("Wciœniêto kombinacjê klawiszy Ctrl+C");
//  }


//-----------------------------------------------------------------------------------

void get_size_from_user(unsigned &size) {

	string buff;

	cout << "Podaj wielkoœæ maksymaln¹ basenów (1 - 16 010): ";
	cin >> buff;
	size = atoi(buff.c_str());

	while ( size < 1 || size >=  16010 + 1 ) {								// z przedzia³u (w³¹cznie) <1 ; 16 010> // na zapas
		cout << "wartoœæ (" << buff << ") jest nie poprawna, podaj inn¹: ";
		cin >> buff;
		size = atoi(buff.c_str());
	}
}
//-----------------------------------------------------------------------------------

string example( unsigned ilosc ) 						// pokazuje przyk³adow¹ maskê "lini/wiersza" basenu
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
//	 	for (int h = 0; h < size; h++) p_array[i][h] = NULL;				// NULLowanie pamiêci czyszczenie z "krzaczków"
//#endif
// 		cin.ignore();

	// dla pierwszego wprowadzenia losuje przyk³adowe wejœcie
	if ( i == 0 )
		cout << "Podaj uklad " << i + 1 << " (" << example(size)  << ") : " << endl << "               ";

	// wypisuje w nawiasie poprzednio wprowadzon¹ poziom¹ linie mapy
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

		// UWAGA: Dzia³a tylko dla kwadratowych basenów (takich jak na wejœciu)
//		#ifndef FINAL
//		if( array[X][Y] != 'B'){
//			MessageBox( 0, "parametry nie wskazuj¹ na pole basenu 'B'\n(b³¹d kontrolny)\nunsigned* Map::get_pool_size_at()", "B³¹d", MB_OK );
//			red(X); red(Y);
//			}
//		#endif
		 int inf[5] = {0};
			memset( inf, 0, sizeof(inf) ); // sprz¹ta przed zabaw¹
			// inf[] zwracana tablica, [0] pole basenu do którego nale¿y pozycja podana w param, [1][2] pozycja pocz¹tku basenu, [3][4] pozycja koñca(prawy dolny róg)

			if ( array[X][Y] != 'B' ) {

//                inf[1] = -1;	// by wysz³o poza mapê
				return 0;
			}


			while ( array[X][Y] == 'B')	if ( X == 0) break; else X--;		// w góre
				inf[1] = ( array[X][Y] == 'B') ? X : ++X;					// jeœli pod t¹ pozycj¹ jest 'B'(Bez zmian), jeœli nie to przesówamy siê o jeden // preinkrementacja jest wymagana

			while ( array[X][Y] == 'B')	if ( Y == 0) break; else Y--; 		// w lewo
				inf[2] = ( array[X][Y] == 'B') ? Y : ++Y;

			while ( array[X][Y] == 'B')	if ( X+1 >= size) break; else X++;	// w dó³   // mo¿e troszkê nie optymalne iœæ od góry do do³u
				inf[3] = ( array[X][Y] == 'B') ? X : --X;

			while ( array[X][Y] == 'B')	if ( Y+1 >= size) break; else Y++; 	// w prawo
				inf[4] = ( array[X][Y] == 'B') ? Y : --Y;

			inf[0] = (inf[3] - inf[1]+1) * (inf[4] - inf[2]+1);		 		// pole prostok¹tnego basenu

//		cout << "[0] rozmiar spr. basenu, [1][2] pozycja lewa górna, [3][4] pozycja prawa dolna\n";
//		for (int e = 0; e < sizeof(inf)/4; e++) 				// debug wyœwietla zawartoœæ obliczonego powy¿ej
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

	} while ( arr[x][y] == 'B' );         // a¿ znajdzie alejkê(nie basenik)

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

			size = 0; 									// ma siê wykonaæ 4 razy (2*2)

			for (int i = 0; i < 2; i++)
				for (int e = 0; e < 2; e++)
					if ( arr[i][e] == 'B' ) size++;

			if ( size < 4 ) size++;												// przydzielanie dwóch baseników
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
//				printf("%s" , " B");	// powoduje pikanie (systemowe), nie do wy³¹czenia
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
			}
			else
			{

				putchar ( toupper(arr[i][o]) );
//				printf("%s" , &a);
			}

//  SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
//	system("Color 2B");
//	else cout << " "<<((char)toupper(arr[i][o])); // printf drukuje w tej samej lini cout ale na pocz¹tku (kolorowanie nie dziala na strumienieniach bez endl)
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

	pool.brutal_2(); // musi byæ po brutal_1
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
		 << "\nkontrola (wielkœæ) = " << size
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

			cout << "\nWielkoœæ tablicy jest zbyt du¿a. MAX 16 000 (" << i << ")\n";
//			exit();
			#endif
		}
		else cout << "\t(" << i << ")\n\n";								// wartoœæ w nawiasie to wartoœæ n, czyli bok kwadratoweja tablicy

  	 	p_array = new char *[ i ];

  	 	for (int j = 0; j < i; j++)
  	 	{
  	 		line = "";   					// czyœæi linie w przypadku braku lini w pliku powtarza³o ostatni¹
			getline (myfile,line);

  	 		if ( line != "")	cout << line << endl;					// wyœwietla zawartoœæ pliku

     		p_array[j] = new char[i];

     		for (int a = 0; a < i; a++)
     			p_array[j][a] =  ( a < line.size() ) ? line.at(a) : 'A';   // wype³nianie
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
//	return 0; 		// program wywo³ano bez parametrów
}


unsigned __fastcall load_from_file( int argc, char** argv, char** &p_array ) {

	if ( 1 < argc) {													// jeœli s¹ parametry pliku (pierwszy parametr to nazwa programu)

	 cout << "File: " << argv[argc-1] ;// << "\t(" << argc << ")\n" <<  endl ;		// drukuje œcie¿kê pliku i numer parametru

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

			cout << "\nWielkoœæ tablicy jest zbyt du¿a. MAX 16 000 (" << i << ")\n";
//			exit();
			#endif
		}
		else cout << "\t(" << i << ")\n\n";								// wartoœæ w nawiasie to wartoœæ n, czyli bok kwadratoweja tablicy

  	 	p_array = new char *[ i ];

  	 	for (int j = 0; j < i; j++)
  	 	{
  	 		line = "";   					// czyœæi linie w przypadku braku lini w pliku powtarza³o ostatni¹
  	 		getline (myfile,line);

  	 		if ( line != "")	cout << line << endl;					// wyœwietla zawartoœæ pliku

     		p_array[j] = new char[i];

     		for (int a = 0; a < i; a++)
     			p_array[j][a] =  ( a < line.size() ) ? line.at(a) : 'A';   // wype³nianie
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
	return 0; 		// program wywo³ano bez parametrów
}


//-----------------------------------------------------------------------------------
unsigned __fastcall load_from_param ( int argc, char** argv, char** &p_array ) {

	if ( 1 < argc) {

		const int i = atoi(argv[1]);
		#ifndef FINAL
		if ( i == 0 ) cout << "\nNie rozpoznano argv[1], wartoœæ niepoprawna lub równa zero\n";
		#endif

  	 	p_array = new char *[ i ];

  	 	for (int j = 0; j < i; j++)
  	 	{
     		p_array[j] = new char[i];
//     		if ( strlen( argv[j+ 3] ) == 0) system("pause") ;

//     		cout << argc << endl;

//	if ( argv[j + 3] == 0 ) exit(); // not

     		for (int a = 0; a < i; a++)
     			p_array[j][a] =  ( a < strlen( argv[j+2]) ) ? argv[j+2][a] : 'A';   // wype³nianie
		}

    	return i;	// wartoœæ n, bok tablicy
  	 }

	return 0; 		// program wywo³ano bez parametrów
}

#endif
