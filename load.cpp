//---------------------------------------------------------------------------

#pragma hdrstop

#include "code.h"
#include "load.h"

//---------------------------------------------------------------------------

unsigned get_pool_map_cin(char ** &map) {

	int n = 0;                            	// wymiary boku kwadratu

	cin >> n;

	map = new char *[ n ];

	for (int i = 0; i < n; i++) {

	   map[i] = new char[n
	   ];

		for (int w = 0; w < n; w++) {



			char a = 0;
			cin >> a;
//			cout << a;

			map[i][w] = a;

		}
	}



	return n;
}




#pragma package(smart_init)
