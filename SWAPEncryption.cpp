//the real purpose of this code is to simply output a 2d array with user plaintext input, prompting user to swap columns to encrypt the message
//"""""SWAP""""" encryption does not exists, i just named it because idk what to name basically
#include <iostream>
#include <string>
using std::string;

/**
 * @brief 
 * 
 * @param arr 
 * @param rows 
 * @param k 
 */
void printArrayWithColumnNumbers(char arr[][100], int rows, int k) 
{
    // Print the column numbers
    for (int j = 0; j < k; j++) 
    {
        std::cout << j + 1 << " ";
    }
    std::cout << std::endl;

    // Print the 2D array with input string
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < k; j++) 
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Print 2D array in vertical manner
    std::cout << "Output: ";
    for (int j = 0; j < k; j++) 
    {
        for (int i = 0; i < rows; i++) 
        {
            if (arr[i][j] != ' ') 
            {
                std::cout << arr[i][j];
            }
        }
    }
    std::cout << std::endl;
}

int main() 
{
    int k;
    std::cout << "Enter the value of k: ";
    std::cin >> k;

    std::cin.ignore(); // Ignore newline character left in the input buffer

    string input;
    std::cout << "Enter a string: ";
    getline(std::cin, input);

    // Calculate number of rows required to fit the input string
    int rows = input.length() / k + (input.length() % k == 0 ? 0 : 1);

    // Create and populate the 2D array with input string
    char arr[rows][100];
    int idx = 0;
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < k; j++) 
        {
            if (idx < input.length()) 
            {
                arr[i][j] = input[idx];
                idx++;
            } 
            else 
            {
                arr[i][j] = ' ';
            }
        }
    }

    // Print the initial array
    std::cout << "Initial Array:\n";
    printArrayWithColumnNumbers(arr, rows, k);

    // Swap columns based on user input
    int column1, column2;
    std::cout << "Enter the column numbers to swap (separated by space): ";
    std::cin >> column1 >> column2;

    if (column1 >= 1 && column1 <= k && column2 >= 1 && column2 <= k) 
    {
        column1--; // Decrement by 1 to match 0-based array indexing
        column2--;

        // Swap columns
        for (int i = 0; i < rows; i++) 
        {
            char temp = arr[i][column1];
            arr[i][column1] = arr[i][column2];
            arr[i][column2] = temp;
        }

        // Print the array after swapping
        std::cout << "Array after swapping columns " << column1 + 1 << " and " << column2 + 1 << ":\n";
        printArrayWithColumnNumbers(arr, rows, k);
    } 
    else 
    {
        std::cout << "Invalid column numbers. Exiting...\n";
    }
    return 0;
}
