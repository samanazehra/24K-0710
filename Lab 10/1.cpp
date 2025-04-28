#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string text;
    cout << "Enter String = ";
    getline(cin, text);

    cout << "Normal Text:= " << text << endl;

    ofstream fout("data.txt");
    for (int i = 0; i < text.length(); i++) {
        fout << char(int(text[i]) + (i + 1));
    }
    fout.close();
    cout << "Encrypted text inserted in file" << endl;

    ifstream fin("data.txt");
    string encryptedText, decryptedText;
    getline(fin, encryptedText);
    fin.close();

    for (int i = 0; i < encryptedText.length(); i++) {
        decryptedText += char(int(encryptedText[i]) - (i + 1));
    }

    cout << "Decrypted text Read then decoded from file" << endl;
    cout << decryptedText << endl;

    return 0;
}
