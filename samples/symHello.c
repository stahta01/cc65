// --------------------------------------------------------------------------
// Hello World for Sym-1
//
// Wayne Parham
//
// wayne@parhamdata.com
// --------------------------------------------------------------------------

#include <symio.h>;

void main(void) {
   char c = 0x00;
   int  d = 0x00;
   int  l = 0x00;

   printf( "\nHello World!\n\n" );

   for( l = 0; l < 2; l++ ) {
      beep();
      for( d = 0; d < 10 ; d++ ) {
      }
   }
   printf( "Type a line and press ENTER, please.\n\n" );

   while( c != '\r' ) {
      c = getchar();
      putchar( c );
   }

   printf( "\n\nThanks!\n\n" );

   for( l = 0; l < 5; l++ ) {
      beep();
      for( d = 0; d < 10 ; d++ ) {
      }
   }

   return;
}
