#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])  
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <number>" << endl;
        return 1; // Return an error code
    }
    int n = stoi(argv[1]);
    for (int i = 0; i < n; i++) {
        ofstream file;
        string filename = "files/File"+to_string(i);
        //cout << filename << endl;
        file.open(filename);
        file << "file number" << to_string(i);
        file.close();
    }
    for (int i = 0; i < n; i++) {
        string filename = "files/File"+to_string(i);
        remove(filename.c_str());
    }

}

