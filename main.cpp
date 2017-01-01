#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
  cout << "Hello World!\n";
  for ( int i = 0; i < argc; i++)
  {
    cout << "arg[" << i << "] = " << argv[i] << "\n";
  }
}
