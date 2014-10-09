#include "main.hpp"

int main(int argc, char **argv) {

#if DBG
    cout << "Hello, world!" << endl;
#else
#endif
    
    
#if DBG
    ifstream fileStream ("../examples/pub01.out");
    string buff;
    getline(fileStream,buff);
    cout << "Correct result: " << buff << endl;
    fileStream.close();
#endif

    return 0;
}
