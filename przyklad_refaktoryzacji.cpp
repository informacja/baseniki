  #include "Map.h"

//-----------------------------------------------------------------------------------

unsigned Map::Standard_sum_size( unsigned X, unsigned Y ) {								// dla pozycji na mapie ró¿nych od brzegów/konturu
	
	return 		value_arr_int[X-1]  [Y]    + 		// góra
				value_arr_int[X]	[Y+1] + 		// prawo
				value_arr_int[X+1]	[Y]   + 		// dó³
				value_arr_int[X]	[Y-1] + 1;		// lewo
}
//-----------------------------------------------------------------------------------

unsigned Map::Contur_sum_size( unsigned X, unsigned Y ) {
	
	unsigned buff;
	
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
		else 	buff = value_arr_int[0][Y-1] + value_arr_int[X-1][Y] + value_arr_int[0][Y+1] + 1;	// 0,reszta
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
	//	if ( X == 0 ||  X == size-1 || Y == 0 || Y == size-1 ) ;
//    else buff = Standard_sum_size( X, Y );
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
	
// 	if ( X == 0 || Y == 0) 					buff = value_arr_int[X][1]   + value_arr_int[1][Y] 	+ 1;		// pierwszy wiersz
//	if ( X == 0 || Y == size-1) 			buff = value_arr_int[X][Y-1] + value_arr_int[1][Y] 	+ 1; 		// pierwszy wiersz
//    else if ( X == size-1 || Y == 0) 		buff = value_arr_int[X][1]   + value_arr_int[X-1][Y] 	+ 1; 	// dolny/ostatni wiersz
//    else if ( X == size-1 || Y == size-1)	buff = value_arr_int[X][Y-1] + value_arr_int[X-1][Y] 	+ 1; 
		 
//	if ( X == 0) 		buff += value_arr_int[X+1][Y];
//	if ( X == size-1 )	buff += value_arr_int[X-1][Y];
//	if ( Y == 0)		buff += value_arr_int[X]  [Y+1];
//	if ( Y == size-1 ) 	buff += value_arr_int[X+1][Y];
		

	
	
//	if ( X == Y ) 												/// NIE BANGLA 
//	{
//		if ( X == 0) 		buff = value_arr_int[X+1][Y] + value_arr_int[X]  [Y+1];
//		if ( X == size-1 )	buff = value_arr_int[X-1][Y] + value_arr_int[X+1][Y];
//		else buff = Standard_sum_size( X, Y );
////		{
////			buff = 	value_arr_int[X-1] [Y]   + 		// góra
////				value_arr_int[X]	[Y+1] + 		// prawo
////				value_arr_int[X+1]	[Y]   + 		// dó³
////				value_arr_int[X]	[Y-1] + 1;		// lewo
////			
////    	}
//		// brak obs³ugi wyra¿eñ œrodkowch
//	}
//	else if ( X == size-1 )
//	{
////		if 		( X == Y )		buff = value_arr_int[X][Y-1] + value_arr_int[X-1][Y] 	+ 1; 			// MAX,MAX
//		if ( Y == 0 )		buff = value_arr_int[X][1]   + value_arr_int[X-1][Y] 	+ 1; 			// MAX,0
//		else 	buff = value_arr_int[0][Y-1] + value_arr_int[X-1][Y] + value_arr_int[0][Y+1] + 1;	// 0,reszta
//	} 
//	else if ( Y == 0 )
//	{
////		if 		( X == Y )		buff = value_arr_int[X][Y-1] + value_arr_int[X-1][Y] 	+ 1; // pierwszy warunek to odrzuca
//		if ( X == size-1 )	buff = value_arr_int[X][1]   + value_arr_int[X-1][Y] 	+ 1; 			// MAX,0	
//		else if ( X == 0) { ms("b³¹d wyt¹pi³ który powinien byæ odrzucony przez pierwszego ifa");}	
//		else 	buff = value_arr_int[X-1][Y] + value_arr_int[X][Y+1] + value_arr_int[X+1][Y] + 1;
//	}
//	//	if ( X == 0 ||  X == size-1 || Y == 0 || Y == size-1 ) ;
//    else buff = Standard_sum_size( X, Y );	
	
			 
//	if ( X == 0) 		buff += value_arr_int[X+1][Y];
//	if ( X == size-1 )	buff += value_arr_int[X-1][Y];
//	if ( Y == 0)		buff += value_arr_int[X]  [Y+1];
//	if ( Y == size-1 ) 	buff += value_arr_int[X+1][Y];
	
//	if ( size < 3)  // zabezpieczenie  // TO DO
//	{
//		switch ( size) {
//			
//			case 0: return 0;	break;
//			case 1: return value_arr_int[X][Y];	// 0,0	break;
//			case 2: return value_arr_int // czetery ify
//				if( X == Y)
//				{
//					if( X == 0 )
//					else 
//				}
//				else if ()
//					break;
//			default: {
//				red("error DEFAULT in unsigned __fastcall Map::add_pool_sum_size(unsigned X, unsigned Y)")
//				break;
//		}			
//	}

	////////////////////////////////////////////////////////////////////////////////////
	
//	if ( X == 0 )
//	{
//		if 		( X == Y )		buff = value_arr_int[X][1]   + value_arr_int[1][Y] + 1;				// 0,0
//		else if ( Y == size-1)	buff = value_arr_int[X][Y-1] + value_arr_int[1][Y] + 1;				// 0,MAX
//		else	buff = value_arr_int[0][Y-1] + value_arr_int[X+1][Y] + value_arr_int[0][Y+1] + 1;	// 0,reszta
//	}	
//	else if ( X == size-1 )	
//	{
//		if 		( X == Y )		buff = value_arr_int[X][Y-1] + value_arr_int[X-1][Y] 	+ 1; 		// MAX,MAX
//		else if ( Y == 0 )		buff = value_arr_int[X][1]   + value_arr_int[X-1][Y] 	+ 1; 		// MAX,0
//		else 	buff = value_arr_int[0][Y-1] + value_arr_int[X-1][Y] + value_arr_int[0][Y+1] + 1;	// 0,reszta
//	}	
//	else if ( Y == 0 )	
//	{
//		if 		( X == Y )		buff = value_arr_int[X][Y+1] + value_arr_int[X][Y+1] 	+ 1; 		// 0,0
//		else if ( X == size-1 )	buff = value_arr_int[X]  [Y+1]   + value_arr_int[X-1][Y] 	+ 1; 	// MAX,0
//		else 	buff = value_arr_int[X+1][Y] + value_arr_int[X][Y+1] + value_arr_int[X-1][Y] + 1;	// reszta,0
//	}	
//	else if ( Y == size-1 )	
//	{
//		if ( X == Y )			buff = value_arr_int[X][Y-1] + value_arr_int[X-1][Y] 	+ 1; 		// MAX,MAX
//		else if ( X == 0 )		buff = value_arr_int[X][Y-1] + value_arr_int[1][Y] + 1; 			// 0,MAX
//		else 	buff = value_arr_int[X-1][Y] + value_arr_int[X+1][Y] + value_arr_int[X][Y-1] + 1;	// reszta,MAX
//	}
		buff = Contur_sum_size( X, Y );

    if ( buff == 0 )	
		buff = Standard_sum_size( X, Y );
	
	
	
//	if ( X == 0 ) 																	// pierwszy wiersz
//    {
//		if ( Y == 0 || Y == size-1) 												// lewy górny róg
//		{
//		  	buff = value_arr_int[X][1]   + value_arr_int[1][Y] + 1; // plus wartoœæ dodawana czyli 1
//		}
//		else if ( Y == size-1 ) 													// prawy górny róg
//		{
//			buff = value_arr_int[0][Y-1] + value_arr_int[1][Y] + 1; 
//		} 
////		else  // dla wartœæi konturowych mapy ró¿nych od rogów (poziom)
////		{ red(X);
////			buff = value_arr_int[X+1][Y] + value_arr_int[X][Y+1] + value_arr_int[X][Y-1] + 1;	
////		}
//    }
//    else if ( X == size-1 || Y == size-1) 											// dolny/ostatni wiersz
//    {
//    	if ( Y == 0) 																// lewy dolny róg
//		{
//			buff = value_arr_int[X][1]   + value_arr_int[X-1][Y] + 1; 
//		}
//		else if ( Y == size-1 ) 													// prawy dolny róg
//		{
//			buff = value_arr_int[X][Y-1] + value_arr_int[X-1][Y] + 1; 
//		}  
//		else 																		// dla wartœæi konturowych mapy ró¿nych od rogów (pion)
//		{
//			buff = value_arr_int[X-1][Y] + value_arr_int[X][Y+1] + value_arr_int[X][Y-1] + 1;
//		}   	

//	{
//		buff = 	value_arr_int[X-1] [Y]   + 		// góra
//				value_arr_int[X]	[Y+1] + 		// prawo
//				value_arr_int[X+1]	[Y]   + 		// dó³
//				value_arr_int[X]	[Y-1] + 1;		// lewo
//			
//    }	
//	blue(X); blue(Y); ms(buff);
    
	return buff;
}
//-----------------------------------------------------------------------------------


//		green( s[1] );
//			green( s[2] );
//			red( s[3] );
//			red( s[4] );
			 /*
	if ( X >= 2)																	// by nie wyjechaæ poza mapê
	{     blue("poziom");
		do {                                                                    // dla górnej krawêdzi od lewej do prawej -->
			sumbuff = 0;

			if ( Y > 0 ) {
				get_pool_size_at( at_0, X-2, Y-1 );						// lewo
				add_to_sum_list( tab, at_0);                            // 0
			}

			if ( X >= 3)  {
				get_pool_size_at( at_1, X-3, Y   );						// góra
				add_to_sum_list( tab, at_1 );      						// 1
			}

			if ( Y < size-1 ) {
				get_pool_size_at( at_2, X-2, Y+1 );						// prawo
				add_to_sum_list( tab, at_2 );                           // 2
			}

			for (int i = 0; i < tab.size(); i++)   // suma do³¹czanych tablic
				 sumbuff += tab[i][0];

			if ( buff_tab[X-1][Y] != 'B' ) sumbuff++;				// dwa kocki dok³adane przez brutal_3()
			if ( buff_tab[X-2][Y] != 'B' ) sumbuff++;
//			yellow(sumbuff )  ; putchar(' ');

				if ( best[0] < sumbuff )	// dla toblicy o numerze i porównaj rozmiar z dotychczasowo najwiêkszym
				{
					best[0] = sumbuff;
					best[1] = X-1;         	// podaje klocki dla których otoczenia by³o sprawdzane pole
					best[2] = Y;
					best[3] = X-2;
					best[4] = Y;    	green( best[1] ) 	;
				}
//				  red(Y);  green( tab[0][0] );
//			for (int i = 0; i < 5; i++)
//			{	cout << setw(3);
//					cout << s[i] << " ";
//			}	cout << " \n";
		} while ( buff_tab[X][++Y] == 'B' );
	}	// wiêksze od= 2

//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
				black(X); black(Y);
	if ( Y <= size-3)														   	// by nie wyjechaæ poza mapê          |
	{         blue("prawo pion");                                                                  //                                    |;
		do {                                                                    // dla prawej krawêdzi od góry w dó³  <
			sumbuff = 0;

			if ( X > 0 ) {
				get_pool_size_at( at_0, X-1, Y+2 );						// lewo
				add_to_sum_list( tab, at_0);                            // 0
			}

			if ( X >= 3)  {
				get_pool_size_at( at_1, X, Y+3   );						// góra
				add_to_sum_list( tab, at_1 );      						// 1
			}

			if ( X < size-1 ) {
				get_pool_size_at( at_2, X+1, Y+2 );						// prawo
				add_to_sum_list( tab, at_2 );                           // 2
			}

			for (int i = 0; i < tab.size(); i++)   // suma do³¹czanych tablic
				 sumbuff += tab[i][0];

			if ( buff_tab[X][Y+1] != 'B' ) sumbuff++;					// dwa kocki dok³adane przez brutal_3()
			if ( buff_tab[X][Y+2] != 'B' ) sumbuff++;
//			yellow(sumbuff )  ; putchar(' ');

				if ( best[0] < sumbuff )	// dla toblicy o numerze i porównaj rozmiar z dotychczasowo najwiêkszym
				{
					best[0] = sumbuff;
					best[1] = X;         	// podaje klocki dla których otoczenia by³o sprawdzane pole
					best[2] = Y+1;
					best[3] = X;
					best[4] = Y+2;  //  	green( best[1] ) 	;
				}

			if ( X == size-1) break;


//				  red(Y);  green( tab[0][0] );
//			for (int i = 0; i < 5; i++)
//			{	cout << setw(3);
//					cout << s[i] << " ";
//			}	cout << " \n";
		} while ( buff_tab[++X][Y] == 'B' );
	}	// wiêksze od= 2
//			Y--;
//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
if ( X <= size-3)																// by nie wyjechaæ poza mapê
	{           blue("dól");
		do {                                                                    // dla dolnej krawêdzi od prawej do lewej   <--
			sumbuff = 0;

			if ( Y > 0 ) {
				get_pool_size_at( at_0, X+2, Y-1 );						// lewo
				add_to_sum_list( tab, at_0);                            // 0
			}

			if ( X < size-3)  {
				get_pool_size_at( at_1, X+3, Y   );						// góra
				add_to_sum_list( tab, at_1 );      						// 1
			}

			if ( Y < size-1 ) {
				get_pool_size_at( at_2, X+2, Y+1 );						// prawo
				add_to_sum_list( tab, at_2 );                           // 2
			}

			for (int i = 0; i < tab.size(); i++)   // suma do³¹czanych tablic
				 sumbuff += tab[i][0];

			if ( buff_tab[X+1][Y] != 'B' ) sumbuff++;				// dwa kocki dok³adane przez brutal_3()
			if ( buff_tab[X+2][Y] != 'B' ) sumbuff++;
//			yellow(sumbuff )  ; putchar(' ');

				if ( best[0] < sumbuff )	// dla toblicy o numerze i porównaj rozmiar z dotychczasowo najwiêkszym
				{
					best[0] = sumbuff;
					best[1] = X+1;         	// podaje klocki dla których otoczenia by³o sprawdzane pole
					best[2] = Y;
					best[3] = X+2;
					best[4] = Y;       //	green( best[1] ) 	;
				}
//				  red(Y);  green( tab[0][0] );
//			for (int i = 0; i < 5; i++)
//			{	cout << setw(3);
//					cout << s[i] << " ";
//			}	cout << " \n";
		} while ( buff_tab[X][--Y] == 'B' );
	}	// wiêksze od= 2
//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	if ( Y > 2)			// liczymy od zera								   	// by nie wyjechaæ poza mapê          ^
	{    		                                                                //                                    |
		for( int i = s[2]; i < s[4]; i++) {                                                                    // dla lewej krawêdzi od do³u w górê  |
			sumbuff = 0;
			tab.clear();
//			 black(Y);
			if ( X < size-1 ) {
				get_pool_size_at( at_0, X+1, Y-2 );						// lewo
				add_to_sum_list( tab, at_0);                            // 0
			}

			if ( Y <= size-3)  {
				get_pool_size_at( at_1, X, Y-3   );						// góra
				add_to_sum_list( tab, at_1 );      						// 1
			}

			if ( X > 0 ) {
				get_pool_size_at( at_2, X-1, Y-2 );						// prawo
				add_to_sum_list( tab, at_2 );                           // 2
			}
//
			for (int i = 0; i < tab.size(); i++)   // suma do³¹czanych tablic
			{	 sumbuff += tab[i][0];
//			red(tab[i][0]);   cout << ' ' ;
			}
			if ( buff_tab[X][Y-1] != 'B' ) sumbuff++;					// dwa kocki dok³adane przez brutal_3()
			if ( buff_tab[X][Y-2] != 'B' ) sumbuff++;
////			yellow(sumbuff )  ; putchar(' ');
//
				if ( best[0] < sumbuff )	// dla toblicy o numerze i porównaj rozmiar z dotychczasowo najwiêkszym
				{
					best[0] = sumbuff;
					best[1] = X;         	// podaje klocki dla których otoczenia by³o sprawdzane pole
					best[2] = Y;
					best[3] = X;
					best[4] = Y+1;  //  	green( best[1] ) 	;
				}
////				  red(Y);  green( tab[0][0] );
//			for (int i = 0; i < 5; i++)
//			{	cout << setw(3);
//					cout << s[i] << " ";
//			}	cout << " \n";
		} //while ( buff_tab[--X][Y] == 'B' );
	}	// wiêksze od= 2

//	blue( best[0] );
//					max_v3
//cerr << endl;
//for (int i = 0; i < 5; i++){
//cout << setw(6);
//	cout << s[i] << " ";
//	red( best[i]);
//	swstem("pause");
//}
// putchar(' ' );
//									black(best[0]);
//		   black(best[0]);   yellow(best[1]);       yellow(best[2]);   yellow(best[3]);      yellow(best[4]);

					 */
//	return *&best;
//}
