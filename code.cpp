//-----------------------------------------------------------------------------------

#include "code.h"

//-----------------------------------------------------------------------------------

void exit() {
	
	cout << "\nKoniec programu...\n" << endl;			// je�li nie ma endl System("pause") jest kopilowane wcze�niej
	system("pause");
  	exit(0);  	
}
//-----------------------------------------------------------------------------------

#define MAX_LEN 80
char bufor[MAX_LEN+1] = {0,};

char* srodkuj(char* bufor, const char* text_do_srodkowania, int max_len) {
	
    int len = strlen(text_do_srodkowania);
    int a = (max_len-len) / 2;
    memset(bufor, ' ', a);
    strcpy(bufor+a, text_do_srodkowania);
    memset(bufor+a+len, ' ', max_len-a-len);
    return bufor;
    }
    
//-----------------------------------------------------------------------------------

void green(string text) {
				
	HANDLE hOut;
	    
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
//	SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );

	cout << text;	
//	printf( "%s", &text);

	SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
}
//-----------------------------------------------------------------------------------

void green(int num) {
	
	HANDLE hOut;
	    
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY );


	printf("%d", num);	

	SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
	
}
//-----------------------------------------------------------------------------------

void ms(string comment)
	{
		SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY );
		cout << comment << endl;
		SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
	}
//-----------------------------------------------------------------------------------
	
void ms(char comment) {
	
		SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY );
		printf("%d\n", comment);
		SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
	
}
//-----------------------------------------------------------------------------------

void red(int comment) {
	
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY );
	printf("%d", comment);
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
}
//-----------------------------------------------------------------------------------

void red(string comment) {
	
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY );
	cout << comment << endl;
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
}
//-----------------------------------------------------------------------------------

void blue(int comment) {
	
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_INTENSITY );
	printf("%d", comment);
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
}
//-----------------------------------------------------------------------------------

void blue(string comment) {
	
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_INTENSITY );
	cout << comment << endl;
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
}
//-----------------------------------------------------------------------------------

void black(string comment) {
	
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY );
    cout << comment << endl;
    SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
}
//-----------------------------------------------------------------------------------

void black(int comment){
		
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY );
  	printf("%d", comment);
    SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
}
//-----------------------------------------------------------------------------------
void yellow(string comment) {
		
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	cout << comment << endl;
   	 SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
}
//-----------------------------------------------------------------------------------

void yellow(int comment){
	
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
  	printf("%d", comment);
   	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );		
}


//-----------------------------------------------------------------------------------

//void print_center(string text) {
//
////	if ( getch() == '0' ) cout << 11;
//	HANDLE okno = GetStdHandle(STD_OUTPUT_HANDLE);
//
////    cout << GetSystemMetrics( SM_XVIRTUALSCREEN ) << endl;
//
//    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
//    if ( !GetConsoleScreenBufferInfo(okno, &bufferInfo) )
//
//	SMALL_RECT& winInfo = bufferInfo.srWindow;
//	COORD s = bufferInfo.dwSize;
////	cout << s.X << endl << s.Y << endl;
//	
//	int size = text.length() - (text.length() % 2);
//
//	cout.width( s.Y / 2 - size );
//	cout << text << endl << size;
//
//} 
//-----------------------------------------------------------------------------------


