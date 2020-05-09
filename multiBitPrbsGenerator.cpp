#include <iostream>
#include <math.h>
#include <bitset>

using namespace std;

void scramble(int lfsr[16], int cycle){
    if (cycle == 0) {
        // Init the representative value for the initial of prbs register
        // Ex: 1 --> inital value of prbs reg[0]
        //     2 --> inital value of prbs reg[1]
        for (int i = 0; i < 16; i++)
            lfsr[i] = pow(2, i);
    }
    else {
        scramble(lfsr, cycle - 1);
        // Calculate the next value of prbs reg[0] (combination)
        // following the generating polynomial
        // 1 + x + x^3 + x^12 + x^16
        //  ^([0], [2],  [11],  [15])
        int temp = lfsr[15] ^ lfsr[11] ^ lfsr[2] ^ lfsr[0];
        // Shift prbs reg values (next clock)
        for(int i = 15; i > 0; i--)
            lfsr[i] = lfsr[i-1];
        // Store the next calculated value to flip-flop 0
        lfsr[0] = temp;
    }
}

int main() {   
    int cycle;
    string prbsRegLabel = "";
    cout << "== nth cycle prbs calculator ==" << endl;
    cout << "The cycle                      : ";
    cin >> cycle;
    cout << "Enter prbs register/lfsr's name: ";
    cin >> prbsRegLabel;
    cout << "--------------------------------------------------" << endl;
    
    int prbs[16];
    scramble(prbs, cycle);

    // Print result
    string lfsr[16];
    for (int i = 0; i < 16; i++)
        lfsr[i] = bitset<16>(prbs[i]).to_string();
    
    for (int i = 0; i < 16; i++) {
        cout << prbsRegLabel << "[" << i << "](" << cycle << ") <= ";
        bool isFirst = true;
        for (int j = 0; j < 16; j++) {
            if (lfsr[i][j] == '1')  {
                cout << prbsRegLabel << "[" << 15 - j << "]";
                isFirst = false;
            }
            if (lfsr[i][j + 1] == '1' && !isFirst) cout << " + ";
        }
        cout << ";" << endl;
    }
    
    return 0;
}
