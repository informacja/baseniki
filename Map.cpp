
#include "Map.h"
#include <vector>

//-----------------------------------------------------------------------------------

Map::Map( const unsigned si, char **p_array ) {

	array = p_array;
	size  = si;
	max_size_pool = 0;

	memset(  MAX_brut1, 0, sizeof(MAX_brut1)	);
	memset(	 MAX_brut2, 0, sizeof(MAX_brut2)	);
	memset(	 MAX_brut3, 0, sizeof(MAX_brut3)	);
	memset(		   inf, 0, sizeof(inf) 			);
//	red(MAX_brut3[4]);

	value_arr_int = new int	*[size];

	for ( int l = 0; l < size; l++) 			// zeruje tablice
	{
		value_arr_int[l] = new int [ si ];
		memset( value_arr_int[l], 0, size * sizeof(value_arr_int) );
	}

	buff_tab = new char* [size];

	for ( int i = 0; i < size; i++)
		buff_tab[i] = new char [size];

	for ( int i = 0; i < sizeof(best)/4; i++) {
		memset(&best[i],0,4);
	}

	at_0, at_1, at_2 = NULL;

	for (int i = 0; i < sizeof(area)/4; i++)
		memset( &area[i], 0, 4 );

	do_value_map();
}
//-----------------------------------------------------------------------------------

Map::~Map() {

	for ( int i = size-1; i >= 0; i-- ) {

		delete [] buff_tab[i];
//		cout << " " << i;
	}

	delete [] buff_tab;

//	MessageBoxA(0,"DESTRUKTOR",0,0);
}

//-----------------------------------------------------------------------------------

void __fastcall Map::brutal_1( ) {

	copy_all_buff_tab();

	for ( int i = 0; i < size; i++ )
	{
		for ( int j = 0; j < size; j++ )
		{
			if( *&buff_tab[i][j] == 'B' ) continue;										// pomija baseny

					Add_Max_Size_brut1( add_pool_sum_size(i, j), i, j);

			copy_three_buff_tab( &i );
		}
	}
}
//-----------------------------------------------------------------------------------

void __fastcall Map::brutal_2( ) {

	edit_value_map_for_brutal_2( );														// wypelnia tablice pomocnicz¹ z wartoœcii¹ pola danego basenu

//	for ( int i = 0; i < size; i++ )
//		memcpy( *&buff_tab[i], array[i], size);											// tworzenie kopii oryginalnej tablicy
	copy_all_buff_tab();

	set_area_pos( );                                                            // ustawia tablicê area[4] na [0][1] pozycja x,y prawego górnego rogu
																				// prostok¹ta w którym mieszcz¹ sie baseny po³¹czone w brutal_1, a w
//	for (int i = 0; i < 4; i++) {												// [2][3] prawy dolny róg
//	cout << setw(4) << area[i] << " ";
//	}

	for ( int i = 0; i < size; i++ )
	{
		for ( int j = 0; j < size; j++ )
		{
			if( *&buff_tab[i][j] == 'B' ) continue;								// pomija baseny
			if( value_arr_int[i][j] != 0 ) continue;                            // jeœli na tablicy wartoœci ju¿ przypisano wartoœæ(may singed)

			// jeœli pozycja zbyt daleko od basenów do których przy³o¿ono pierwszy
			// UWAGA: POMIJAM sprawdzanie czy dok³adany basenik bêdzie po³¹czony z poprzednim
//			if( area[0]-1 > i ) continue;            								// poziom czyli X
//			if( area[2]+1 < i ) continue;
//			if( area[1]-1 > j ) continue;											// pion czyli Y
//			if( area[3]+1 < j ) continue;
//
//			if ( area[1]-1 == j || area[3]+1 == j )                                      // dla rogów (pomija)
//				if( area[2]+1 == i || area[0]-1 == i ) continue;

					Add_Max_Size_brut2( add_double_pool_sum_size(i, j), i, j);

//		 { // przywracanie do stanu wyjœciowego
				if ( i-1 >= 0 )		memcpy( *&buff_tab[i-1], array[i-1], size);			// wiêksze od indeksu 0
									memcpy( *&buff_tab[i],   array[i], size);			// aktualny indeks
				if ( i+1 < size ) 	memcpy( *&buff_tab[i+1], array[i+1], size);			// jeœli nie wykracza poza tablicê
//			copy_three_buff_tab( &i ); // why dont work's?
//		 }
		}
	}
//	array[ MAX_brut2[1] ][ MAX_brut2[2] ] = 'B';
}
//-----------------------------------------------------------------------------------
//                     przeniesione do Untitled1.cpp
//void __fastcall Map::brutal_3( ) {
//
//	// reset do stanu wyjœciowego
//
//// 	for (int i = 0; i < size; i++){
//
//	for (int e = 0; e < size; e++)										// zeruje mapê wartoœæi
//		memset( *&value_arr_int[e], 0, size* sizeof(value_arr_int) );
// 	do_value_map( );													// tworzy mapê wartoœæi
//
////	 cout << "sh";
//// 	for (int i = 0; i < size; i++){
////	 	cout << endl;
////	 	for (int e = 0; e < size; e++)
//// 		cout << value_arr_int[i][e] << " ";
////	}
//
////	copy_all_buff_tab();
//	for ( int i = 0; i < size; i++ )
//		memcpy( *&buff_tab[i], array[i], size);											// tworzenie kopii
//
////	ma siê wykonaæ tylko gdy do basenu($) œcianki mo¿emy przy³o¿yæ 2 nowe bloki(!)
///*
//	* * ! * *
//	* * ! * *
//	! ! # ! !
//	* * ! * *
//	* * ! * *
//*/
//	for ( int i = 0; i < size; i++ )
//	{
//		for ( int j = 0; j < size; j++ )
//		{
//			if( *&buff_tab[i][j] != 'B' ) continue;										// poni¿szy tylko dla basenów
////			if( value_arr_int[i][j] != 0 ) continue;
//
////			if ( Is_at_contur_of_pool( i,j ) )
//					Add_Max_Size_brut3( add_thrid_pool_sum_size( i,j ) );
//
////		 { // przywracanie do stanu wyjœciowego
////			if ( size  <= 3 )
////			 	for ( int q = 0; q < size; q++ )
////					memcpy( *&buff_tab[q], array[q], size);
////			else {
//				if ( i-1 >= 0 )		memcpy( *&buff_tab[i-1], array[i-1], size);			// wiêksze od indeksu 0
//									memcpy( *&buff_tab[i],   array[i], size);			// aktualny indeks
//				if ( i+1 < size ) 	memcpy( *&buff_tab[i+1], array[i+1], size);			// jeœli nie wykracza poza tablicê
////			}
//
//		}
//	}
////	array[ MAX_brut2[1] ][ MAX_brut2[2] ] = 'B';
//}

//-----------------------------------------------------------------------------------

void Map::do_value_map( ) {

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++) {

			if ( array[i][j] != 'B' ) 		continue; // a¿ do napotkania basenu
			if ( value_arr_int[i][j] != 0) continue; // jeœli ju¿ nadano polu waroœæ (zapobiego ponownemu przypisaniu)

			int *a = get_pool_size_at( i,j );
	/*		//ms( a[0]); // dowód na potrzebê drugiego ifa */

			for (int e = a[1]; e <= a[3]; e++)
				for (int t = a[2]; t <= a[4]; t++)
					value_arr_int[e][t] = a[0];
	/*				memset(value_arr_int[e], a[0], 2 ); // nie bangla */

//		for (int e = 0; e < 5; e++) 													// debug wyœwietla zawartoœæ obliczonego powy¿ej
//		cout << a[e] << " ";	cout << endl;
		}
//	for (int i = 0; i < size; i++) {													// wyœwietla ca³¹ powy¿sz¹ tablice, pola zawieraj¹ wielkoœæ basenu do którego nale¿¹
//		cout << endl;
//		for (int j = 0; j < size; j++)
//		{
//			cout << setfill(' ') << setw(3) << value_arr_int[i][j];
//		}
//	}
//	cout << endl;
}
//-----------------------------------------------------------------------------------

void Map::edit_value_map_for_brutal_2( ) { // ustawia wartoœci basenów s¹siadujacych z dodanym przez brutal_1() klockiem w³¹cznie

	int *a = 0;

	MAX_brut1[0] = 0 - MAX_brut1[0] ; 	// zamienia wartoœæ rozmiaru basenu na o przeciwnym znaku

	if ( MAX_brut1[1] != 0 ) // zabezpieczenie przed wyjechaniem poza obszar tablicy
	{
		a = get_pool_size_at( MAX_brut1[1]-1, MAX_brut1[2] );
		if ( a[0] != 0 ) 	// jeœli wiêksze od zera  ( BO WSTAWIA£O W POS 0,0 )
		for (int i = a[1]; i <= a[3]; i++)
			for (int j = a[2]; j <= a[4]; j++)
				value_arr_int[i][j] = MAX_brut1[0];

	}

	if ( MAX_brut1[1] != size-1 ) {

		a = get_pool_size_at( MAX_brut1[1]+1, MAX_brut1[2] );
		if ( a[0] )
		for (int i = a[1]; i <= a[3]; i++)
			for (int j = a[2]; j <= a[4]; j++)
				value_arr_int[i][j] = MAX_brut1[0];
	}

	if ( MAX_brut1[2] != 0 ) {

		a = get_pool_size_at( MAX_brut1[1], MAX_brut1[2]-1 );
		if ( a[0] )
		for (int i = a[1]; i <= a[3]; i++)
			for (int j = a[2]; j <= a[4]; j++)
				value_arr_int[i][j] = MAX_brut1[0];
	}

	if ( MAX_brut1[2] != size-1 ) {

		a = get_pool_size_at( MAX_brut1[1], MAX_brut1[2]+1 );
		if ( a[0] )
		for (int i = a[1]; i <= a[3]; i++)
			for (int j = a[2]; j <= a[4]; j++)
				value_arr_int[i][j] = MAX_brut1[0];
	}

	value_arr_int[ MAX_brut1[1] ][ MAX_brut1[2] ] = MAX_brut1[0];//	MAX_brut1[0]					 // przypisanie wybranemu punktowi w brutal_1() i basenów stykaj¹cych sumy ich pól

	MAX_brut1[0] = 0 - MAX_brut1[0] ; // przywraca do wartoœci dodatniej  (zmiana by³a konieczna dla powy¿szego kodu)

	array[ MAX_brut1[1] ][ MAX_brut1[2] ] = 'B'; // przeniesione do brutal_1()
//
//	cout << "for brutal2 value map" << endl;
//	for (int i = 0; i<size; i++) {   // wyœwietla tablice edytowan¹ przez powy¿sze
//		cout << endl;
//		for (int h = 0; h<size; h++)
//	 		cout << setw( 4) <<  value_arr_int[i][h];
//	 }
//	cout << endl;
}
//-----------------------------------------------------------------------------------
unsigned Map::Standard_sum_size( unsigned X, unsigned Y ) {								// dla pozycji na mapie ró¿nych od brzegów/konturu

	return 		value_arr_int[X-1]  [Y]    + 		// góra
				value_arr_int[X]	[Y+1] + 		// prawo
				value_arr_int[X+1]	[Y]   + 		// dó³
				value_arr_int[X]	[Y-1] + 1;		// lewo
}
//-----------------------------------------------------------------------------------

unsigned Map::Contur_sum_size( unsigned X, unsigned Y ) {     // for brutal_1() ONLY (no signed var buff)

	unsigned buff = 0;

	if ( X == 0 )
	{
		if 		( X == Y )		buff = value_arr_int[X][1]   + value_arr_int[1][Y] + 1;				// 0,0
		else if ( Y == size-1)	buff = value_arr_int[X][Y-1] + value_arr_int[1][Y] + 1;				// 0,MAX
		else	buff = value_arr_int[0][Y-1] + value_arr_int[X+1][Y] + value_arr_int[0][Y+1] + 1;	// 0,reszta
	}
	else if ( X == size-1 )
	{
		if 		( X == Y )		buff = value_arr_int[X][Y-1] + value_arr_int[X-1][Y] 	+ 1; 		// MAX,MAX
		else if ( Y == 0 )		buff = value_arr_int[X][1]   + value_arr_int[X-1][Y] 	+ 1; 		// MAX,0
		else 	buff = value_arr_int[X][Y-1] + value_arr_int[X-1][Y] + value_arr_int[X][Y+1] + 1;	// 0,reszta
	}
	else if ( Y == 0 )
	{
		if 		( X == Y )		buff = value_arr_int[X][Y+1] + value_arr_int[X][Y+1] 	+ 1; 		// 0,0
		else if ( X == size-1 )	buff = value_arr_int[X]  [Y+1]   + value_arr_int[X-1][Y] 	+ 1; 	// MAX,0
		else 	buff = value_arr_int[X+1][Y] + value_arr_int[X][Y+1] + value_arr_int[X-1][Y] + 1;	// reszta,0
	}
	else if ( Y == size-1 )
	{
		if ( X == Y )			buff = value_arr_int[X][Y-1] + value_arr_int[X-1][Y] 	+ 1; 		// MAX,MAX
		else if ( X == 0 )		buff = value_arr_int[X][Y-1] + value_arr_int[1][Y] + 1; 			// 0,MAX
		else 	buff = value_arr_int[X-1][Y] + value_arr_int[X+1][Y] + value_arr_int[X][Y-1] + 1;	// reszta,MAX
	}

	return buff;
}
//-----------------------------------------------------------------------------------

unsigned __fastcall Map::add_pool_sum_size(unsigned X, unsigned Y) {

	// brak sprawdzeñ o zawartoœci komórki czy basen czy nie
	// czyli brutalne :)

	#ifndef FINAL
	if (value_arr_int[X][Y] != 0) { //red(value_arr_int[X][Y] );
	MessageBoxA( 0,"WARtoœæ ró¿na od zera\n\nunsigned* Map::add_pool_sum_size(unsigned X, unsigned Y)", 0,0);
//	red(X); red(Y);
	}
	#endif

	unsigned buff = 0;

		buff = Contur_sum_size( X, Y ); 		// kontur mapy

    if ( buff == 0 )

		buff = Standard_sum_size( X, Y );		// wewn¹trz

	return buff;
}
//-----------------------------------------------------------------------------------

unsigned Map::add_double_pool_sum_size(unsigned X, unsigned Y) {

	#ifndef FINAL
	if (value_arr_int[X][Y] != 0) { //red(value_arr_int[X][Y] );
	MessageBoxA( 0,"WARtoœæ ró¿na od zera\n\nunsigned* Map::add_double_pool_sum_size(unsigned X, unsigned Y)", 0,0);
//	red(X); red(Y);
	}
	#endif

//	int buff = 0;
	unsigned add, buff = 0;   // mo¿e int?
	add = 0; // kod linie wy¿ej nie zeruje add

	int b[4];
	memset( b, 0, sizeof(b));		// zeruje pamiêæ

	if ( X == 0 )
	{
		if 		( X == Y ) 						// 0,0
		{
					b[0] = value_arr_int[X][1];
					b[1] = value_arr_int[1][Y];
		}
		else if ( Y == size-1)					// 0,MAX
		{
					b[0] = value_arr_int[X][Y-1];
					b[1] = value_arr_int[1][Y];
		}
		else									// 0,reszta
		{
					b[0] = value_arr_int[0][Y-1];
					b[1] = value_arr_int[X+1][Y];
					b[2] = value_arr_int[0][Y+1];
		}
	}
	else if ( X == size-1 )
	{
		if 		( X == Y )						// MAX,MAX
		{
					b[0] = value_arr_int[X][Y-1];
					b[1] = value_arr_int[X-1][Y];
		}
		else if ( Y == 0 )						// MAX,0
		{
					b[0] = value_arr_int[X][1];
					b[1] = value_arr_int[X-1][Y];
		}
		else 									// 0,reszta
		{
					b[0] = value_arr_int[0][Y-1];
					b[1] = value_arr_int[X-1][Y];
					b[2] = value_arr_int[0][Y+1];
		}
	}
	else if ( Y == 0 )
	{
		if 		( X == Y )						// 0,0
		{
					b[0] = value_arr_int[X][Y-1];
					b[1] = value_arr_int[X-1][Y];
		}
		else if ( Y == size-1 )					// MAX,0
		{
					b[0] = value_arr_int[X][1];
					b[1] = value_arr_int[X-1][Y];
		}
		else									// reszta,0
		{
					b[0] = value_arr_int[X-1][Y];
					b[1] = value_arr_int[X][Y+1];
//					black( value_arr_int[4][2] );
					b[2] = value_arr_int[X+1][Y];
		}
	}
	else if ( Y == size-1 )
	{
		if ( X == Y )  							// MAX,MAX
		{
					b[0] = value_arr_int[X][Y-1];
					b[1] = value_arr_int[X-1][Y];
		}
		else if ( X == 0 )						// 0,MAX
		{
					b[0] = value_arr_int[X][Y-1];
					b[1] = value_arr_int[1][Y];
		}
		else 									// reszta,MAX
		{
					b[0] = value_arr_int[X-1][Y];
					b[1] = value_arr_int[X+1][Y];
					b[2] = value_arr_int[X][Y-1];
		}
	}
	else
	{
					b[0] = value_arr_int[X-1] [Y]; 		// góra
					b[1] = value_arr_int[X]	[Y+1]; 		// prawo
					b[2] = value_arr_int[X+1]	[Y]; 	// dó³
					b[3] = value_arr_int[X]	[Y-1];		// lewo
    }

    for (int i = 0; i < sizeof(b)/4; i++)       // 4 liczba bitów inta
    {
		if ( b[i] < 0 )
		{																					// jak dokonaæ DEASEMBLACJI
//		   if ( add == 0 ) 				// jeœli jeszcze nie by³o liczby ujemnej
		        add = 0 - b[i]; 		// zmiana na wartoœæ dodatni¹
		}
		else  buff += b[i];
	}

	buff += add;

	return buff + 1; // plus klocek dodany przez brutal_2()
}
//-----------------------------------------------------------------------------------
//
//unsigned* Map::add_thrid_pool_sum_size(unsigned X, unsigned Y) {
//
//		unsigned *s = get_pool_size_at( X,Y );
//			//no bleow
//			for ( int y = s[1]; y < s[3]; s++)
//				for (int z = s[2]; z < s[4]; z++)
//
////					max_v3
//
//	return MAX_brut1;
//
//}
//-----------------------------------------------------------------------------------

int* Map::get_pool_size_at(unsigned X, unsigned Y) {

		// UWAGA: Dzia³a tylko dla kwadratowych basenów (takich jak na wejœciu)
		#ifndef FINAL
		if( array[X][Y] != 'B'){
			MessageBox( 0, "parametry nie wskazuj¹ na pole basenu 'B'\n(b³¹d kontrolny)\nunsigned* Map::get_pool_size_at()", "B³¹d", MB_OK );
//			red(X); red(Y);
			}
		#endif

			memset( inf, 0, sizeof(inf) ); // sprz¹ta przed zabaw¹
			// inf[] zwracana tablica, [0] pole basenu do którego nale¿y pozycja podana w param, [1][2] pozycja pocz¹tku basenu, [3][4] pozycja koñca(prawy dolny róg)

			if ( array[X][Y] != 'B' ) {

//                inf[1] = -1;	// by wysz³o poza mapê
				return *&inf;
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

	return  *&inf;
}
//-----------------------------------------------------------------------------------

void Map::get_pool_size_at( int *&in_out, int X, int Y) {

		// UWAGA: Dzia³a tylko dla kwadratowych basenów (takich jak na wejœciu)
		#ifndef FINAL
		if( array[X][Y] != 'B'){
	 		MessageBox( 0, "parametry nie wskazuj¹ na pole basenu 'B'\n(b³¹d kontrolny)\nunsigned* Map::get_pool_size_at()", "B³¹d", MB_OK );
//			red(X); red(Y);
			}
		#endif

//		if ( X < 0 || Y < 0	)           {	in_out = inf; return; }        		// zabezpieczeñ nigdy nie za wiele :)
//		if ( X > size-1 || X > size-1 ) {	in_out = inf; return; }

		memset( inf, 0, sizeof(inf) ); // sprz¹ta przed zabaw¹
		// inf[] zwracana tablica, [0] pole basenu do którego nale¿y pozycja podana w param, [1][2] pozycja pocz¹tku basenu, [3][4] pozycja koñca(prawy dolny róg)

		/* 	UWAGA: przy sprawdzaniu pozycji (2,2) gdy wskazuje na alejkê, a pod pozycj¹ (3,3) jest basen
		zwraca rozmiar 1 tego basenu dlatego poni¿szy if jest wymagany			*/

		if (  array[X][Y] != 'B' ) 		{	in_out = inf; return; }

		while ( array[X][Y] == 'B')	if ( X == 0) break; else X--;		// w góre
			inf[1] = ( array[X][Y] == 'B') ? X : ++X;					// jeœli pod t¹ pozycj¹ jest 'B'(Bez zmian), jeœli nie to przesówamy siê o jeden // preinkrementacja jest wymagana

		while ( array[X][Y] == 'B')	if ( Y <= 0) break; else Y--; 		// w lewo
			inf[2] = ( array[X][Y] == 'B') ? Y : ++Y;

		while ( array[X][Y] == 'B')	if ( X+1 >= size) break; else X++;	// w dó³   // mo¿e troszkê nie optymalne iœæ od góry do do³u
			inf[3] = ( array[X][Y] == 'B') ? X : --X;

		while ( array[X][Y] == 'B')	if ( Y+1 >= size) break; else Y++; 	// w prawo
			inf[4] = ( array[X][Y] == 'B') ? Y : --Y;

		inf[0] = (inf[3] - inf[1]+1) * (inf[4] - inf[2]+1);		 		// pole prostok¹tnego basenu

//			for (int i = 0; i < size; i++) {
//			cout << endl;
//				for (int b = 0; b < size; b++) {
//					cout << setw(3) << array[i][b] ;
//				}
//			}
//			cout << endl;

//		cout << "[0] rozmiar spr. basenu, [1][2] pozycja lewa górna, [3][4] pozycja prawa dolna\n";
//		for (int e = 0; e < sizeof(inf)/4; e++) 				// debug wyœwietla zawartoœæ obliczonego powy¿ej
//			cout << inf[e] << " ";	cout << endl;
		in_out = inf;
//		return;
}

//-----------------------------------------------------------------------------------

void Map::Add_Max_Size_brut1(unsigned s, unsigned x, unsigned y) {
//ms(MAX_brut1[0]);
	if ( s > MAX_brut1[0] ) {							// jeœli rozmiar mniejszy od ostatnio zapamiêtanego

	MAX_brut1[0] = s;
	MAX_brut1[1] = x;
	MAX_brut1[2] = y;
	}
}
//-----------------------------------------------------------------------------------

void Map::Add_Max_Size_brut2(unsigned s, unsigned x, unsigned y) {

	if ( s > MAX_brut2[0] ) {							// jeœli rozmiar mniejszy od ostatnio zapamiêtanego

	MAX_brut2[0] = s;
	MAX_brut2[1] = x;
	MAX_brut2[2] = y;
	}
}
//-----------------------------------------------------------------------------------

void Map::Add_Max_Size_brut3(int *s) {

	if ( best[0] > MAX_brut3[0] ) {

		MAX_brut3[0] = best[0];
		MAX_brut3[1] = best[1];
		MAX_brut3[2] = best[2];
		MAX_brut3[3] = best[3];
		MAX_brut3[4] = best[4];
	}
}
//-----------------------------------------------------------------------------------

unsigned Map::Get_MAX() { // musi byæ wywo³ana po wszystkich obliczeniach

	unsigned buff = 0;

	buff = ( MAX_brut1[0] > MAX_brut2[0] ) ? MAX_brut1[0] : MAX_brut2[0];
	buff = ( buff > MAX_brut3[0] ) ? buff : MAX_brut3[0];

//red(MAX_brut1[0]);
//red(MAX_brut2[0]) ;
//red(MAX_brut3[0]) ;

	return buff;
}
//-----------------------------------------------------------------------------------
void Map::draw() {

	int o;

 	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << endl << "  ";
	putchar (' ');
	for ( int z = 0; z < size; z++ ) {
			putchar (' ');
			red(z); // numerowanie kolor
	}
	cout << endl; putchar(' ');     putchar(' ');
	for ( int i = 0; i < size; i++ ) {

		red(i);   // numerowanie
		for( o = 0; o < size; o++ ) {

			putchar (' ');

			if ( i == MAX_brut1[1] &&  o == MAX_brut1[2] && MAX_brut1[0] > 0) 							// podœwietl basen dodany przez brutal_1()
			{
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
				putchar ('B');
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );	// podœwietl basen dodany przez brutal_2()
			}
			else if ( i == MAX_brut2[1] && o == MAX_brut2[2] && MAX_brut2[0] > 0) // gdy zgazaj¹ siê wspórzêdne i wielkoœæ pola jest wiêksza od 0 czyli sprawdza czy istnieje
			{
				SetConsoleTextAttribute( hOut,  FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
				putchar ('B');
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
			}
			else if ( MAX_brut3[0] > 0  && (( i == MAX_brut3[1] && o == MAX_brut3[2] ) || ( i == MAX_brut3[3] && o == MAX_brut3[4] )) ) {	// podœwietl basen dodany przez brutal_3()

				SetConsoleTextAttribute( hOut,  FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
 				putchar ('B');
				SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
			}
			else  																						// reszta
			{

				if ( ((char)toupper(array[i][o])) == 'B' )												// podœwietla baseniki
				{
					SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
					putchar ('B');
					SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
				}
				else
				{
					putchar ( toupper(array[i][o]) );
				}
			}
		}
		cout << endl << "  ";
	}
	cout << endl;
}
//-----------------------------------------------------------------------------------

void Map::copy_all_buff_tab( ) {

		for ( int i = 0; i < size; i++ )
			memcpy( *&buff_tab[i], array[i], size);										// tworzenie kopii oryginalnej tablicy

}
//-----------------------------------------------------------------------------------

void Map::copy_three_buff_tab( int *i)
{
		// przywracanie do stanu wyjœciowego
//			if ( size  <= 3 )
//			 	for ( int q = 0; q < size; q++ )
//					memcpy( *&buff_tab[q], array[q], size);
//			else {
	if ( *i-1 >= 0 )	memcpy( *&buff_tab[*i-1], array[*i-1], size);			// wiêksze od indeksu 0
						memcpy( *&buff_tab[*i],   array[*i], size);			// aktualny indeks
	if ( *i+1 < size ) 	memcpy( *&buff_tab[*i+1], array[*i+1], size);			// jeœli nie wykracza poza tablicê

//	if ( i-1 >= 0 )		memcpy( *&buff_tab[i-1], array[i-1], size);			// wiêksze od indeksu 0
//						memcpy( *&buff_tab[i],   array[i], size);			// aktualny indeks
//	if ( i+1 < size ) 	memcpy( *&buff_tab[i+1], array[i+1], size);

//			}
}
//-----------------------------------------------------------------------------------

//bool  Map::Is_at_black_list( int i, int j ) {
//
////	black_list.push_back( 5 );
//
//
//	for (int i = 0; i < black_list.size(); i++)
//		cout << black_list.at(i) << " ";
//	 cout << endl;
//
//
//	unsigned *a = get_pool_size_at(i,j); // na potrzeby wyznaczenia konuru
//
//
//
//	if ( i == a[1] ) return true;
//	if ( i == a[3] ) return true;
//	if ( j == a[2] ) return true;
//	if ( j == a[4] ) return true;
//
//	return false; // jeœli ¿adne z powy¿szych
//}
//-----------------------------------------------------------------------------------

void Map::add_to_sum_list( vector< vector<int> > &tab, int *a) {

	if ( a[0] == 0) return;    // jeœli rozmiar basenu równy 0 przerwij

	for( int i = 0; i < tab.size(); i++)
	{
		 if ( tab[i][0] == a[0] )
			if ( tab[i][1] == a[1] )
				if ( tab[i][2] == a[2] )  return;	// jeœli tena sam basen przerywa, i pos³any basen nie jest zapisywany
	}
//    cout << endl << tab[tab.size()-1][0] << " -> " << a[0];

	if ( tab[tab.size()-1].at(0) != 0 ) // jeœli ostatnia linia nie zawiera watrtoœci basenu to pomiñ tworzenie nowego wiersza
		tab.resize(tab.size() +1);      // dodaje kolejny wpis (wiersz)
	tab[(tab.size() - 1)].resize(3,0);  // dodaje linie        (kolumny)

	tab[tab.size()-1][0] = a[0];
	tab[tab.size()-1][1] = a[1];
	tab[tab.size()-1][2] = a[2];

	//--- zobaczmy teraz co mamy ---
//	cout << endl;
//	for(int i = 0; i < tab.size(); i++) {
//		cout << i << " : ";
//		for (int x = 0; x < (tab[i]).size(); x++)
//			cout<<(tab[i])[x]<<",";
//		cout<<endl;
//	}
}
//-----------------------------------------------------------------------------------
