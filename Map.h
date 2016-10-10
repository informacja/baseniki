//-----------------------------------------------------------------------------------

#ifndef MAP_H
#define MAP_H

#include "code.h"

//-----------------------------------------------------------------------------------

 class Map {	
 	
// 	int l, h; // dla pêtli |TEST|
	char ** array, **buff_tab; // rezygnuje z optymalizacji na char ---> //**value_arr_char;	
	int ** value_arr_int;
	int size, max_size_pool, MAX_brut1[3], MAX_brut2[3], MAX_brut3[5], inf[5]; 	// struktura tablicy MAX_b... [0] rozmiar basenu po dodaniu, [1] pozycja X dodanego, a [2] wartoœæ Y

	int *at_0, *at_1, *at_2;
	int area[4];

	int best[5]; // przechowuje [0] rozmiar najwiêkszego basenu z kombinacji, [1][2] pozycjê do³o¿onego kafelka, [3][4] pozycjê 2 do³o¿onego kafelka

//	char buff_tab[size][size];
	// MAX_brut3 zawiera [0] rozmiar nawjêkszego basenu, [1][2] pozycja pierwszego dodanego baseniku, [3][4] pozycja drugiego baseniku
	
//	vector<int> black_list[2];	
//	void check_biggest();
	unsigned pool_size(unsigned X, unsigned Y);
	unsigned Standard_sum_size( unsigned X, unsigned Y ); 
	unsigned Contur_sum_size( unsigned X, unsigned Y );
	unsigned __fastcall add_pool_sum_size(unsigned X, unsigned Y);
	unsigned add_double_pool_sum_size(unsigned X, unsigned Y);	
	int* add_thrid_pool_sum_size(unsigned X, unsigned Y);
	int* get_pool_size_at(unsigned X, unsigned Y); // zwraca tablice [0] rozmiar basenu, [1][2] pozycja pocz¹tku basenu, [3][4] pozycja koñca basenu
	void get_pool_size_at( int *&in_out, int X, int Y);
	void Add_Max_Size_brut1(unsigned size, unsigned X, unsigned Y);
  	void Add_Max_Size_brut2(unsigned size, unsigned X, unsigned Y);
	void Add_Max_Size_brut3(int* size_and_blocks_pos);
	void do_value_map( );
	void edit_value_map_for_brutal_2( );
	void three_buff_tab( int *height);
	void copy_all_buff_tab( );
	void copy_three_buff_tab( int *height_midle);
	void add_to_sum_list( vector< vector<int> > &sum_tab, int *pool_size_posX_posY );
	int* for_up( vector< vector<int> > &tab, int X, int Y, int *curr_tab_spec );
	int* for_down( vector< vector<int> > &tab, int X, int Y, int *curr_tab_spec );
	int* for_right( vector< vector<int> > &tab, int X, int Y, int *curr_tab_spec );
	int* for_left( vector< vector<int> > &tab, int X, int Y, int *curr_tab_spec );
	void set_area_pos( );
	void zz( int t[]);
//	bool Is_at_black_list( int i, int j );
 
 public:
	
	Map( const unsigned si, char **p_array );
	unsigned Get_MAX();
	void draw();
	char ** Get_ptr() { return buff_tab;	}
	
	void __fastcall brutal_1();		// pierwszy kocek
	void __fastcall brutal_2();
	void __fastcall brutal_3();

	unsigned biggest();
	~Map();
	
 };

//-----------------------------------------------------------------------------------
#endif
