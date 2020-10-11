#include <iostream>
#include <fstream>
using namespace std;

string encryptDecrypt(string toEncrypt) {
    char key[8] = { 'Z', 'E', 'P', 'H', 'Y', 'R' }; //Any chars will work
    string output = toEncrypt;

    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

    return output;
}

int main(int argc, const char* argv[])
{
    string encrypted = encryptDecrypt("https://pastebin.com/raw/c51sk9Qh");
    ofstream MyFile("C:\\Users\\zephy\\Downloads\\Test.txt");
    MyFile << encrypted;
    cout << "Encrypted: " << encrypted << "|   Length:" << encrypted.size() << "\n";

    string decrypted = encryptDecrypt(encrypted);
    cout << "Decrypted: " << decrypted << "|   Length:" << decrypted.size() << "\n";

    return 0;
}