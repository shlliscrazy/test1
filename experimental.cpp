#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

string encrypt(string text);
string decrypt(string text);
void createKeyMatrix(string key);
void findInMatrix(char letter, int &row, int &col);
string createPairs(string input);
string removeX(string text);
  
char keyMatrix[5][5];
 
void output() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            cout << keyMatrix[i][j] << " ";
        cout << "\n";
    }
}
//function to handle same row encrypt
string sameRowEncrypt(char mat[5][5], int x, int y, int direction) 
{
    char c;
    //previously used 'if-else' but switched to 'switch-case' because function not optimized
    switch (direction) 
    {
        case 1: // right
            c = mat[x][(y+1)%5];
            break;
        case 2: // left
            c = mat[x][(y-1+5)%5];
            break;
        case 3: // above
            c = mat[(x-1+5)%5][y];
            break;
        case 4: // below
            c = mat[(x+1)%5][y];
            break;
        default:
            c = '\0';
            break;
    }
    return string(1, c);
}

string sameColEncrypt(char mat[5][5], int x, int y, int direction) 
{
    char c;
    //previously used 'if-else' but switched to 'switch-case' because function not optimized
    switch (direction) 
    {
        case 1: // right
            c = mat[x][(y+1)%5];
            break;
        case 2: // left
            c = mat[x][(y-1+5)%5];
            break;
        case 3: // above
            c = mat[(x-1+5)%5][y];
            break;
        case 4: // below
            c = mat[(x+1)%5][y];
            break;
        default:
            c = '\0';
            break;
    }
    return string(1, c);
}

int main() {
    string input, key, option;
    cout << "key:\n";
    getline(cin, key);
    createKeyMatrix(key);
    output();
    while (1) {
        cout << "mahoa(v)\n";
        cout << "giaima(h)\n";
        cout << "newkey(k)\n";
        getline(cin, option);
        getline(cin, input);
        char c = option[0];
        if (c == 'v') 
        {
            input = createPairs(input);
            cout << input << endl;
            cout << encrypt(input) << endl;
        }
        else if (c == 'h')
            cout << removeX(decrypt(input)) << endl;
        else if (c == 'k') {
            cout << "new key:\n";
            getline(cin, key);
            createKeyMatrix(key);
        }
        else cout << "invalid option\n";
    }
}
 
int mod(int a, int b) {
    int r = a % b;
    return r < 0 ? r + b : r;
}
 
void replace(string &text, int pos, char from, char to) {
    if (text[pos] == from)   text[pos] = to;
    if (text[pos+1] == from) text[pos+1] = to;
}
 
void findInMatrix(char letter, int &row, int &col) {
    for (int r = 0; r < 5; ++r)
        for (int c = 0; c < 5; ++c)
            if (letter == keyMatrix[r][c]) {
                row = r; col = c;
                return;
            }
}
 
string encrypt(string text) 
{
    string output = "";
    int row1, col1, row2, col2, checkrow, checkcol;
    std::cout<<"Shift if same row ?\n1.For cell on the right \n2.For cell on the left\n3.For cell above\n4.For cell below\n";
    std::cout<<"Input : ";
    std::cin>>checkrow;
    std::cout<<"Shift if same row ?\n1.For cell on the right \n2.For cell on the left\n3.For cell above\n4.For cell below\n";
    std::cout<<"Input : ";
    std::cin>>checkcol;
    for (int pos = 0; pos < text.length(); pos += 2) 
    {
        replace(text, pos, 'j', 'i');
        findInMatrix(text[pos], row1, col1);
        findInMatrix(text[pos+1], row2, col2);
        if (row1 == row2) 
		{
            output += sameRowEncrypt(keyMatrix, row1, col1, checkrow);
            output += sameRowEncrypt(keyMatrix, row2, col2, checkrow);
        }
        else if (col1 == col2) 
		{
            output += sameColEncrypt(keyMatrix, row1, col1, checkcol);
            output += sameColEncrypt(keyMatrix, row1, col1, checkcol);
        }
        else 
        {
            output += keyMatrix[row1][col2];
            output += keyMatrix[row2][col1];
        }
    }
    return output;
}
string decrypt(string text) {
    string output = "";
    int row1, col1, row2, col2;
    int size = text.length();
    for (int pos = 0; pos < size; pos += 2) {
        findInMatrix(text[pos], row1, col1);
        findInMatrix(text[pos+1], row2, col2);
        if (row1 == row2) {
            output += keyMatrix[row1][mod(col1-1, 5)];
            output += keyMatrix[row2][mod(col2-1, 5)];
        }
        else if (col1 == col2) {
            output += keyMatrix[mod(row1-1, 5)][col1];
            output += keyMatrix[mod(row2-1, 5)][col2];
        }
        else {
            output += keyMatrix[row1][col2];
            output += keyMatrix[row2][col1];
        }
    }
    return output;
}
 
string removeX(string text) {
    string original = "";
    original += text[0];
    int size = text.length();
    for (int i = 1; i < size-1; ++i) {
        if (!(text[i] == 'x' && text[i-1] == text[i+1]))
            original += text[i];
    }
    original += text[size-1];
    return original;
}
 
bool found(char c, vector<char> used) {
    return find(used.begin(), used.end(), c) != used.end();
}
 
void createKeyMatrix(string key) {
    vector<char> used; 
    used.push_back('j');
    int size = key.length();
    int count = 0;
    char fillLetter = 'a';
 
    for (int row = 0; row < 5; ++row)
        for (int col = 0; col < 5; ++col) {
            if (count < size) { 
                char letter = key[count];
                if (!found(letter, used)) {
                    keyMatrix[row][col] = letter;
                    used.push_back(letter);
                }
                else --col; 
                ++count;
            }
            else {
                if (!found(fillLetter, used))
                    keyMatrix[row][col] = fillLetter;
                else --col; 
                ++fillLetter;
            }
        }
}
 
string createPairs(string input) 
{
    /* string newString = "";
    int size = input.length();
    for (int i = 1; i < size; ++i) {
        if (!isspace(input[i-1])) {
            newString += input[i-1];
            if (input[i-1] == input[i])
                newString += 'x';
        }
    }
    newString += input[size-1];
    if ((newString.length() & 1) == 1)
        newString += 'x';
    return newString; */
    for(int i=1; i<input.length(); i+=2) //pair 2 characters
    {
        if(input[i-1] == input[i])  input.insert(i, "x");
    }
    if(input.length()%2 != 0)  input += "x";
    return input;
    
}
