#include <iostream>
#include <math.h>
#include <bitset>

using namespace std;

void scramble(int prbs[16], int cycle, string inDataLabel = "d", string prbsRegLabel = "", int start = 0){
    if (cycle == 0) {
        // Init the representative value for the initial of prbs register
        // Ex: 1 --> inital value of prbs reg[0]
        //     2 --> inital value of prbs reg[1]
        for (int i = 0; i < 16; i++)
            prbs[i] = pow(2, i);
    }
    else {
        scramble(prbs, cycle - 1, inDataLabel, prbsRegLabel, start);
        // Calculate the next value of prbs reg[0] (combination)
        // following the generating polynomial
        // 1 + x + x^3 + x^12 + x^16
        //  ^([0], [2],  [11],  [15])
        int temp = prbs[15] ^ prbs[11] ^ prbs[2] ^ prbs[0];
        // Shift prbs reg values (next clock)
        for(int i = 15; i > 0; i--)
            prbs[i] = prbs[i-1];
        // Store the next calculated value to flip-flop 0
        prbs[0] = temp;
    }

    // Print the function to calculate the scrambled data output at clock cycle of <cycle>
    // scrambled data = input data ^ prbs[15]
    // prbs[15] at current cycle as calculation above
    // = xor prbs's representative initial values of the power of 2 values 
    // that sum of them is equal to prbs[15]
    // Ex: prbs[15] = 34821
    //              = 32768 + 2048 + 4 + 1
    //              = init_prbs[15] + init_prbs[11] + init_prbs[2] + init_prbs[0]
    // Result will be shown in format of generating polynomial, which starts from 1
    string kq = bitset<16>(prbs[15]).to_string();
    cout << inDataLabel << "_scrambled(" << cycle << ") = ";
    char openChar = (prbsRegLabel != "") ? '[' : '\0';
    char closeChar = (prbsRegLabel != "") ? ']' : '\0';
    for (int j = 0; j < 16; j++)
        if (kq[j] == '1') cout << prbsRegLabel << openChar << 16 - j - (1 - start) << closeChar << " ^ ";
    cout << inDataLabel << endl;
}

int main() {
    cout << "=== nth cycle scrambler data output calculator ===" << endl;
    int cycle, start = 0;
    string inDataLabel = "d", prbsRegLabel = "";
    cout << "The cycle                      : ";
    cin >> cycle;
    cout << "Input data label (d)           : ";
    cin >> inDataLabel;
    cout << "Prbs register label ()         : ";
    cin >> prbsRegLabel;
    cout << "Start position of prbs reg (0) : ";
    cin >> start;
    cout << "--------------------------------------------------" << endl;
    int prbs[16];
    scramble(prbs, cycle, inDataLabel, prbsRegLabel, start);
    return 0;
}