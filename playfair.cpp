
#include <bits/stdc++.h>
using std::string;

typedef struct
{
	int row;
	int col;
}position;

char mat[5][5]; // global Variable

void generateMatrix(string key)
{
    /* flag to track characters inside matrix*/
	/* flag = 0 -> character not exists in matrix */
	/* flag = 1 -> character do exists in matrix */
    int flag[26] = {0};
    int x = 0, y = 0;

    /* put characters from key to maxtrix */
    for(int i=0; i<key.length(); i++)
    {
        if(key[i] == 'j') key[i] = 'i'; // replaces 'j' to 'i'

        if(flag[key[i]-'a'] == 0)
        {
            mat[x][y++] = key[i];
            flag[key[i]-'a'] = 1;
        }
        if(y==5) x++, y=0;
    }

    /* add remaining characters */
    for(char ch = 'a'; ch <= 'z'; ch++)
    {
        if(ch == 'j') continue; // will not perform, continue

        if(flag[ch - 'a'] == 0)
        {
            mat[x][y++] = ch;
            flag[ch - 'a'] = 1 ;
        }
        if(y==5) x++, y=0;
    }
}

/* add in 'x'*/
string formatMessage(string msg)
{
    for(int i=0; i<msg.length(); i++)
    {
        if(msg[i] == 'j')  msg[i] = 'i';
    }

    for(int i=1; i<msg.length(); i+=2) //pair 2 characters
    {
        if(msg[i-1] == msg[i])  msg.insert(i, "x");
    }
    if(msg.length()%2 != 0)  msg += "x";
    return msg;
}

/* returns character position */
position getPosition(char c)
{
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            if(c == mat[i][j])
            {
                position p = {i, j};
                return p;
            }
    // if the character is not found in the matrix, return an invalid position
    position invalid = {-1, -1};
    return invalid;
}
// function to handle same row case
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

// function to handle same column case
string sameColumnEncrypt(char mat[5][5], int x, int y, int direction) 
{
    char c;
    switch (direction) 
    {
        case 1: // below
            c = mat[(x+1)%5][y];
            break;
        case 2: // above
            c = mat[(x-1+5)%5][y];
            break;
        case 3: // left
            c = mat[(x-1+5)%5][y];
            break;
        case 4: // right
            c = mat[x][(y+1)%5];
            break;
        default:
            c = '\0';
            break;
    }
    return string(1, c);
}

string encrypt(string message)
{
    
    int checkrow, checkcol;
    string ctext = "";
    std::cout<<"Shift if same row ?\n1.For cell on the right \n2.For cell on the left\n3.For cell above\n4.For cell below\n";
    std::cout<<"Input : ";
    std::cin>>checkrow;

    std::cout<<"Shift if same column ?\n1.For cell below \n2.For cell above\n3.For cell on the left\n4.For cell on the right\n";
    std::cout<<"Input : ";
    std::cin>>checkcol;

    for(int i=0; i<message.length(); i+=2)   
    {
		position p1 = getPosition(message[i]);
		position p2 = getPosition(message[i+1]);
        int x1 = p1.row; int y1 = p1.col;
        int x2 = p2.row; int y2 = p2.col;
        
        if( x1 == x2 ) // same row (cell on the right )
        {
            ctext +=  sameRowEncrypt(mat, x1, y1, checkrow);
            ctext +=  sameRowEncrypt(mat, x2, y2, checkrow);   
        }
        else if( y1 == y2 ) // same column (cell below)
        {
            ctext += sameColumnEncrypt(mat, x1, y1, checkcol);
            ctext += sameColumnEncrypt(mat, x2, y2, checkcol);
        }
         //retangle case
        else
        {
            ctext += mat[ x1 ][ y2 ];
            ctext += mat[ x2 ][ y1 ];
        }
    }
    return ctext;
}

string Decrypt(string message)
{
    string ptext = "";
    for(int i=0; i<message.length(); i+=2) 
    {
        position p1 = getPosition(message[i]);
		position p2 = getPosition(message[i+1]);
        int x1 = p1.row; int y1 = p1.col;
        int x2 = p2.row; int y2 = p2.col;

        if( x1 == x2 ) // same row
        {
            ptext += mat[x1][ --y1<0 ? 4: y1 ];    //cell on the left (encryption with right cell)
            ptext += mat[x2][ --y2<0 ? 4: y2 ];
        }
        else if( y1 == y2 ) // same column
        {
            ptext += mat[ --x1<0 ? 4: x1 ][y1];     //cell below (encryption with above cell)
            ptext += mat[ --x2<0 ? 4: x2 ][y2];
        }
        //retangle case
        else
        {
            ptext += mat[ x1 ][ y2 ];
            ptext += mat[ x2 ][ y1 ];
        }
    }
    return ptext;
}

int main()
{
    int a, b;
    string plaintext;
    std::cout << "Enter message : "; 
    std::cin >> plaintext;

    int n; //enter keys
    std::cout << "Enter number of keys : "; 
    std::cin >> n;

    string key[n];
    for(int i=0; i<n; i++)
    {
        std::cout<< "\nEnter key " << i+1 << " : " << key[i];
        std::cin >> key[i];

        generateMatrix(key[i]);

        std::cout << "Key " << i+1 << " Matrix:" << std::endl;
        for(int k=0;k<5;k++)
        {
            for(int j=0;j<5;j++)
            {
                std::cout << mat[k][j] << "  ";
            }
            std::cout << std::endl;
        }
        
        string fmsg = formatMessage(plaintext);
        
        string ciphertext = encrypt(fmsg);
        //output raw message, formatted message
        std::cout << "Actual Message \t\t: " << plaintext << std::endl;
        std::cout << "Formatted Message \t: " << fmsg << std::endl;
        //encrypt function
        std::cout << "Encrypted Message \t: " << ciphertext << std::endl;
        //decrypt function
        string decryptmsg = Decrypt(ciphertext);
        std::cout<< "Decrypted Message \t: " << decryptmsg << std::endl;
    }
}
