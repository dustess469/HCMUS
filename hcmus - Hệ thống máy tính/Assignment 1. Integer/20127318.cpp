#include<iostream>

using namespace std;


void changeBinary(int n, char arr[]) {
	
    int x = 0;
    
    for (int i = 15; i >= 0; i--) {
        int k = n >> i;
        
        if (k & 1) 
		{
            arr[x] = '1';
            ++x;
        }
        else 
		{
            arr[x] = '0';
            ++x;
        }
    }
}

void minusDecimal(char arr[]) {
    for (int i = 0; i < 16; ++i)
	{
        if (arr[i] == '0')
        {
            arr[i] = '1';
        }
        else
            arr[i] = '0';
    }
    for (int i = 15; i >= 0; --i) {
        if (arr[i] == '1')
        {
            arr[i] = '0';
        }
        else 
		{
            arr[i] = '1';
            break;
        }
    }
}

int main() {
    char arr[100];
    short n;
    cout << "Input A(decimal): ";
    cin >> n;
    
    changeBinary(n,arr);
    cout << "A(Binary): ";
    for (int i = 0; i < 16; ++i)
    {
        cout << arr[i];
    }
    
    cout << endl;

    minusDecimal(arr);
    cout << "-A(Binary): ";
    for (int i = 0; i < 16; ++i)
    {
        cout << arr[i];
    }
    
    return 0;
        
        
}
