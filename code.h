//-----------------------------------------------------------------------------------

	// pliki konfiguracyjny code.h

#ifndef CODE_H
#define CODE_H
//-----------------------------------------------------------------------------------

#include <iostream>
#include <windows.h>
#include <stdlib.h> 	// rand
#include <fstream> 		// file read
#include <iomanip> 		// setw, setfill
#include <vector>
#include <string>

//#include <ctime>
//#include <cstdio>
//#include <conio.h>
//#include <cstdlib>

using namespace std;

#define FINAL							// brak kontroli b³êdów
#define zero_memory					// NULLuje pamiêæ dynamicznie alokowan¹ 

//-----------------------------------------------------------------------------------

	void exit();
	char* srodkuj(char* bufor, const char* text_do_srodkowania, int max_len);

	void ms(string comment);
	void ms(char comment);
	void green(string text);
	void green(int num);
	void red(int comment);
	void red(string comment);
	void blue(int comment);
	void blue(string comment);
	void black(string comment);
	void black(int comment);
	void yellow(string comment);
	void yellow(int comment);
	
//-----------------------------------------------------------------------------------



/*

	HANDLE hOut;
	    
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );


//-----------------------------------------------------------------------------------

unsigned find( char **p_array, const unsigned size, unsigned colummn, unsigned row ) {
	
	unsigned count = 0, c = colummn, r =  row ;
		
	do {		
		r++;
		c++;	
		count++;	
		
	} while ( p_array[r][c] == 'B');
	
	return count;
}
//-----------------------------------------------------------------------------------

char **next_pool(char **p_array) {
	
	return 0;
}

//-----------------------------------------------------------------------------------

unsigned search(char **p_array, const unsigned size) {
	
//	std::vector //bufor sprawdzonych
//	vector < unsigned short > tab;
//	tab.resize( 3, 4);

	vector <int>a;
	
 	int ilosc_wierszy=10; 
    int wartosc_domyslna; 
    std::vector< std::vector<int> > tab(ilosc_wierszy);
	for(int i=0;i<ilosc_wierszy;i++) 
    { 
        wartosc_domyslna=i; 
        (tab[i]).resize(i,wartosc_domyslna); 
    } 
    //--- zobaczmy teraz co mamy --- 
    for(int i=0;i<tab.size();i++) 
    { 
        cout<<i<<" : "; 
        for(int x=0;x<(tab[i]).size();x++) 
        {cout<<(tab[i])[x]<<",";} 
        cout<<endl; 
    } 
    
	unsigned l, c, B = 0;							// line, colummn, iloœæ_Basenów
	
	unsigned d;
		
//		tab.push_back( 5 );	
		
//	while ( p_array[l][c] == 'B' )
	{
			
		
		
		B++;
		
		// go down
//		l++;
//		while ( p_array[l][c] == 'B'  )
//		
//		
//		// go right
//		c++;
//		while ( p_array[l][c] == 'B'  )
//		
//		if (p_array[l][c] == 'B') B++;
//		l++;
				
	}		
				
//	do {		
		
		c++;
//		count++;	
		
//	} while ( p_array[r][c] == 'B');	
	
//	for( c = 0; size > c; c++ ) {
//	
//		for ( l = 0; size > l; l++ ) {
//				
//			if (p_array[l][c] == 'B') B++;	
//			else break;
//		}
//	}	
		
	return B;
//-----------------------------------------------------------------------------------

		
//system("pause");
////
//	char a[ sizeof(p_array) ] { 0 };
//	cout << a << endl;
//	memcpy( &a, *p_array, size);
//	cout << a << endl;
//		system("pause");	
////

} */

#endif
