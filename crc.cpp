#include <iostream>
#include <string.h>

using namespace std;

int crc(char *ip, char *op, char *poly, int mode)
{
    strcpy(op, ip);
    if (mode) {
        /* Appending 16 zeroes */
        /* strlen(poly) = 17 */
        for (int i = 1; i < strlen(poly); i++)
            strcat(op, "0");
    }

    /* Perform XOR on the msg with the selected polynomial */
    /* Division of the appended data with the polynomial */
    for (int i = 0; i < strlen(ip); i++) {
        // XOR only to be performed if the MSB is 1
        if (op[i] == '1') {
            for (int j = 0; j < strlen(poly); j++) {
                if (op[i + j] == poly[j])
                    op[i + j] = '0';
                else
                    op[i + j] = '1';
            }
        }
    }

    /* check for errors. return 0 if error detected */
    for (int i = 0; i < strlen(op); i++)
        if (op[i] == '1')
            return 0;
    return 1;
}

int main()
{
    char ip[50], op[50], recv[50];
    // x^16 + x^12 + x^5 + x^0
    char poly[] = "10001000000100001";

    cout << "Enter the input message in binary"<< endl;
    cin >> ip;

    crc(ip, op, poly, 1);
    cout << "The transmitted message is: " << ip << op + strlen(ip) << endl;

    cout << "Enter the recevied message in binary" << endl;
    cin >> recv;

    if (crc(recv, op, poly, 0))
        cout << "No error in data" << endl;
    else
        cout << "Error in data transmission has occurred" << endl;

    return 0;
}
