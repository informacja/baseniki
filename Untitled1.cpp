//----------------------------------------------------------------------------

#include "Map.h"

//----------------------------------------------------------------------------

void show_info( int X, int Y, int* spec, string name) {

	cout<< "\n" << name << " (" << X <<"," << Y << ") ";

	green( spec[0]); green(" "); green( spec[1]); green(" ");
	green( spec[2]); green(" "); green( spec[3]); green(" ");
	green( spec[4]); green("\n");
 }

//----------------------------------------------------------------------------

void __fastcall Map::brutal_3( ) {
		
	// reset do stanu wyj�ciowego
	
// 	for (int i = 0; i < size; i++){

	for (int e = 0; e < size; e++)										// zeruje map� warto��i
		memset( *&value_arr_int[e], 0, size* sizeof(value_arr_int) );	
 	do_value_map( );													// tworzy map� warto��i
 	
//	 cout << "sh";
// 	for (int i = 0; i < size; i++){
//	 	cout << endl;
//	 	for (int e = 0; e < size; e++)
// 		cout << value_arr_int[i][e] << " ";
//	}

//	copy_all_buff_tab();
	for ( int i = 0; i < size; i++ )
		memcpy( *&buff_tab[i], array[i], size);											// tworzenie kopii
		
//	ma si� wykona� tylko gdy do basenu($) �cianki mo�emy przy�o�y� 2 nowe bloki(!)
/*
	* * ! * * 	
	* * ! * *
	! ! # ! ! 
	* * ! * * 
	* * ! * * 
*/		
	for ( int i = 0; i < size; i++ ) 
	{
		for ( int j = 0; j < size; j++ ) 
		{
			if( *&buff_tab[i][j] != 'B' ) continue;										// poni�szy tylko dla basen�w
			// przej�� do add_thrid_pool_sum_size() mo�e tylko pozycja lewego g�rnego baseniku
			if ( i != 0 ) if( buff_tab[i-1] [j]   == 'B' ) continue;			// na lewo
			if ( j != 0 ) if( buff_tab[i]   [j-1] == 'B' ) continue;			// nad aktualn� pozycj� jest basenik wi�c przejdz do nast�pnego obigu 

					Add_Max_Size_brut3( add_thrid_pool_sum_size( i,j ) );

//		 							// przywracanie do stanu wyj�ciowego
	for ( int i = 0; i < size; i++ )
		memcpy( *&buff_tab[i], array[i], size);											// tworzenie kopii


//				if ( i-1 >= 0 )		memcpy( *&buff_tab[i-1], array[i-1], size);			// wi�ksze od indeksu 0
//									memcpy( *&buff_tab[i],   array[i],   size);			// aktualny indeks
//				if ( i+1 < size ) 	memcpy( *&buff_tab[i+1], array[i+1], size);			// je�li nie wykracza poza tablic�
		}
	}
}
//---------------------------------------------------------------------------

int* Map::add_thrid_pool_sum_size(unsigned X, unsigned Y) {



/* funkcja zaczyna od lewego g�rnego rogu, (+) to bloczki kt�rych dok�adanie jest symulowane


		+ + + + +
		+ + + + +
	+ + ->->->->\ + +
	+ + ^ * * * \ + +
	+ + ^ * * * \ + +
	+ + ^<-<-<-<| + +
		+ + + + +
		+ + + + +

sprawdzane pola to (#), dla basen�w (*), o pozycji 0,0

		#
	  # ! #
		!
		* * *
		* * *
		* * *
*/

	vector< vector<int> > tab(1);
	int *s, sumbuff = 0;

	for ( int i = 0; i < tab.size(); i++)
		tab[i].resize(3,0);           	// tworzy list� o 3 kolumnach

	memset( best, 0, 4*5 );         	// 4 bity (int) * 5 kom�rk pami�ci, tablica

	get_pool_size_at( s, X,Y );       	// potrzebna jest informacja o pozycji X,Y pocz�tku basenu s[1], s[2]

//	for ( int i = 0; i < 5; i++) {    //	cout << s[i] << "|";
//		yellow(s[i]); putchar(' ');
//	}
						 get_pool_size_at( s, X, Y );
	if ( s[3] > 1)    	*best = *for_up( tab, X, Y, s );

						 get_pool_size_at( s, X, Y );
	if ( s[3] < size-2 )*best = *for_down( tab, s[3], Y, s );                  	// s[3] czyli dolna granica basenu

						 get_pool_size_at( s, X, Y );
	if ( Y < size-2) 	*best = *for_right( tab, X, s[4], s );

						 get_pool_size_at( s, X, Y );
	if ( Y > 1)         *best = *for_left( tab, X, Y, s );

	return best;
}

//----------------------------------------------------------------------------

int* Map::for_up( vector< vector<int> > &tab, int X, int Y, int* pool_spec ) {
//	show_info( X, Y, pool_spec, "   up" );
	// wymaganie s� bufory poniewa� dane pod wska�nikiem s� tracone(nie mam poj�cia dlaczego)
	int a = pool_spec[2];
	int b = pool_spec[4];
	int c = pool_spec[0];	// bufor rozmiaru jest potrzebny poniewa� pool_spec[0] zeruje si� przy obrocie poni�szej p�tli

	for ( int i = a; i <= b; i++)   	// dla g�rnej kraw�dzi od lewej do prawej -->
	{
		int sumbuff = c;    // formatowanie przy ka�dym obrocie p�tli

		if ( i >= 1 ) {  //cout << "lewo" << X-2 << "  " << i-1 << endl;
			get_pool_size_at( at_0, X-2, i-1 );						// lewo
			add_to_sum_list( tab, at_0);                            // 0
		}

		if ( X >= 3)  { //  cout << "g�ra" << X-3 << "  " << i << endl;
			get_pool_size_at( at_1, X-3, i );						// g�ra
			add_to_sum_list( tab, at_1 );      						// 1
		}

		if ( X >= 2 ) {  //  cout << "prawo " << X-2 << "  " << i+1 << endl;
			get_pool_size_at( at_2, X-2, i+1 );						// prawo
			add_to_sum_list( tab, at_2 );                           // 2
		}

		for (int e = 0; e < tab.size(); e++)	sumbuff += tab[e][0];			// suma do��czanych tablic

		if ( buff_tab[X][i+1] != 'B' ) sumbuff++;				// dwa kocki dok�adane przez brutal_3()
		if ( buff_tab[X][i+2] != 'B' ) sumbuff++;


				if ( best[0] < sumbuff )	// dla toblicy o numerze i por�wnaj rozmiar z dotychczasowo najwi�kszym
				{
					best[0] = sumbuff;
					best[1] = X-1;         	// podaje klocki dla kt�rych otoczenia by�o sprawdzane pole
					best[2] = i;
					best[3] = X-2;
					best[4] = i;
				}

		}

	return *& best;
}
//----------------------------------------------------------------------------

int* Map::for_down( vector< vector<int> > &tab, int X, int Y, int *pool_spec) {

//	 show_info( X, Y, pool_spec, " down" );

		// wymaganie s� bufory poniewa� dane pod wska�nikiem s� tracone(nie mam poj�cia dlaczego)
	int a = pool_spec[1];
	int b = pool_spec[3];
	int c = pool_spec[0];

	for ( int i = X; i <= b; i++)            			   // X = pool_spec[3]
	{
		int sumbuff = c;

		if ( i < size-2 ) {     //cout << "lewo" << X+2 << "  " << i+1 << endl;
			get_pool_size_at( at_0, X+2, i+1 );									// lewo
			add_to_sum_list( tab, at_0);                            			// 0
		}

		if ( X < size-2)  {    //  cout << "g�ra" << X+3 << "  " << i << endl;
			get_pool_size_at( at_1, X+3, i   );									// g�ra
			add_to_sum_list( tab, at_1 );      									// 1
		}

		if ( i > 0 ) {           //   cout << "prawo" << X+2 << "  " << i-1 << endl;
			get_pool_size_at( at_2, X+2, i-1 );									// prawo
			add_to_sum_list( tab, at_2 );                              			// 2
		}
		for (int e = 0; e < tab.size(); e++)	sumbuff += tab[e][0];			// suma do��czanych tablic


		if ( buff_tab[X+1][i] != 'B' ) sumbuff++;								// dwa kocki dok�adane przez brutal_3()
		if ( buff_tab[X+2][i] != 'B' ) sumbuff++;

				if ( best[0] < sumbuff )										// dla toblicy o numerze i por�wnaj rozmiar z dotychczasowo najwi�kszym
				{
					best[0] = sumbuff;
					best[1] = X+1;         										// podaje klocki dla kt�rych otoczenia by�o sprawdzane pole
					best[2] = i;
					best[3] = X+2;
					best[4] = i;
				}
		}
	return *& best;
}
//-----------------------------------------------------------------------------------

int* Map::for_right( vector< vector<int> > &tab, int X, int Y, int *pool_spec ) {

//	 show_info( X, Y, pool_spec, "right" );

		// wymaganie s� bufory poniewa� dane pod wska�nikiem s� tracone(nie mam poj�cia dlaczego)
	int a = pool_spec[1];
	int b = pool_spec[3];
	int c = pool_spec[0];

	for ( int i = a; i <= b; i++)
	{         											                         // dla dolnej kraw�dzi
			int sumbuff = c;

		if ( i > 0 ) {
			get_pool_size_at( at_0, i-1, Y+2 );									// lewo
			add_to_sum_list( tab, at_0);                            			// 0
		}

		if ( Y < size-2)  {
			get_pool_size_at( at_1, i, Y+3   );									// g�ra
			add_to_sum_list( tab, at_1 );      									// 1
		}

		if ( i < size-2 ) {
			get_pool_size_at( at_2, i+1, Y+2 );									// prawo
			add_to_sum_list( tab, at_2 );                              			// 2
		}

		for (int e = 0; e < tab.size(); e++)	sumbuff += tab[e][0];			// suma do��czanych tablic


		if ( buff_tab[i][Y+1] != 'B' ) sumbuff++;								// dwa kocki dok�adane przez brutal_3()
		if ( buff_tab[i][Y+2] != 'B' ) sumbuff++;

				if ( best[0] < sumbuff )										// dla toblicy o numerze i por�wnaj rozmiar z dotychczasowo najwi�kszym
				{
					best[0] = sumbuff;
					best[1] = i;         										// podaje klocki dla kt�rych otoczenia by�o sprawdzane pole
					best[2] = Y+1;
					best[3] = i;
					best[4] = Y+2;
				}
		}
	return *& best;
}
//-----------------------------------------------------------------------------------

int* Map::for_left( vector< vector<int> > &tab, int X, int Y, int *pool_spec ) {
//	   show_info( X, Y, pool_spec,  " left" );

		// wymaganie s� bufory poniewa� dane pod wska�nikiem s� tracone(nie mam poj�cia dlaczego)
	int a = pool_spec[1];
	int b = pool_spec[3];
	int c = pool_spec[0];

	for ( int i = a; i <= b; i++)
	{         										                            // dla dolnej kraw�dzi
	int sumbuff = c;

		if ( i <  size-1 ) {
			get_pool_size_at( at_0, i+1, Y-2 );									// lewo
			add_to_sum_list( tab, at_0);                            			// 0
		}

		if ( Y < 1)  {
			get_pool_size_at( at_1, i, Y-3   );									// g�ra
			add_to_sum_list( tab, at_1 );      									// 1
		}

		if ( i > 0 ) {
			get_pool_size_at( at_2, i-1, Y-2 );									// prawo
			add_to_sum_list( tab, at_2 );                              			// 2
		}

		for (int e = 0; e < tab.size(); e++)	sumbuff += tab[e][0];			// suma do��czanych tablic


		if ( buff_tab[i][Y-1] != 'B' ) sumbuff++;								// dwa kocki dok�adane przez brutal_3()
		if ( buff_tab[i][Y-2] != 'B' ) sumbuff++;

				if ( best[0] < sumbuff )										// dla toblicy o numerze i por�wnaj rozmiar z dotychczasowo najwi�kszym
				{
					best[0] = sumbuff;
					best[1] = i;         										// podaje klocki dla kt�rych otoczenia by�o sprawdzane pole
					best[2] = Y-1;
					best[3] = i;
					best[4] = Y-2;
				}
		}
	return *& best;


}
//-----------------------------------------------------------------------------------

void Map::set_area_pos( ) {       // pozycje konturu maski ograniczaj�cej wyszukiwanie w brutal_2
//							cout << endl;

	int *p = NULL;  // liczymy od 1 bo [0] to rozmiar

	if ( MAX_brut1[1] > 0) {

		get_pool_size_at( p, MAX_brut1[1]-1, MAX_brut1[2] );                   	// g�ra

		area[0] = p[1]; // MIN X
		area[1] = p[2]; // MIN Y
		area[2] = p[3]; // MAX X
		area[3] = p[4]; // MAX Y
	}
		//	for (int i = 1; i < 5; i++) {
//	cout << setw(4) << " "; green( p[i]);
//	}
	if ( MAX_brut1[1] < size-1 ) {

		get_pool_size_at( p, MAX_brut1[1]+1, MAX_brut1[2] );                   	// d�

		if ( area[0] < p[1] ) p[1] = area[0]; // MIN X
		if ( area[1] < p[2] ) p[2] = area[1]; // MIN Y
		if ( area[2] > p[3] ) p[3] = area[2]; // MAX X
		if ( area[3] > p[4] ) p[4] = area[3]; // MAX Y
	}

	if ( MAX_brut1[2] < size-1 ) {

		get_pool_size_at( p, MAX_brut1[1], MAX_brut1[2]+1 );                   	// prawo

		if ( area[0] < p[1] ) p[1] = area[0]; // MIN X
		if ( area[1] < p[2] ) p[2] = area[1]; // MIN Y
		if ( area[2] > p[3] ) p[3] = area[2]; // MAX X
		if ( area[3] > p[4] ) p[4] = area[3]; // MAX Y
	}

	if ( MAX_brut1[2] > 0 ) {

		get_pool_size_at( p, MAX_brut1[1], MAX_brut1[2]-1 );                   	// lewo

		if ( area[0] < p[1] ) p[1] = area[0]; // MIN X
		if ( area[1] < p[2] ) p[2] = area[1]; // MIN Y
		if ( area[2] > p[3] ) p[3] = area[2]; // MAX X
		if ( area[3] > p[4] ) p[4] = area[3]; // MAX Y
	}
	area[0] = p[1]; // MIN X
	area[1] = p[2]; // MIN Y
	area[2] = p[3]; // MAX X
	area[3] = p[4]; // MAX Y

//	for (int i = 0; i < 4; i++) {
//	cout << setw(4) << " "; green( area[i]);
//	}
}
