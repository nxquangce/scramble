/**
 * Scrambler
 * Description: 
 *   Sidestream Scramnler/Descrambler 
 *   Generating polynomial: 1 + x + x^3 + x^12 + x^16
 * Input : hex sting
 * Output: scrambled hex string
 */

export class Scrambler {
    private static hex2Uint8(hex: string) {
        return new Uint8Array(hex.split('').map(byte => parseInt(byte, 16)));
    }

    private static uint8hex2bin(hex: number) {
        switch (hex) {
            case 0: return [0, 0, 0, 0];
            case 1: return [0, 0, 0, 1];
            case 2: return [0, 0, 1, 0];
            case 3: return [0, 0, 1, 1];
            case 4: return [0, 1, 0, 0];
            case 5: return [0, 1, 0, 1];
            case 6: return [0, 1, 1, 0];
            case 7: return [0, 1, 1, 1];
            case 8: return [1, 0, 0, 0];
            case 9: return [1, 0, 0, 1];
            case 10: return [1, 0, 1, 0];
            case 11: return [1, 0, 1, 1];
            case 12: return [1, 1, 0, 0];
            case 13: return [1, 1, 0, 1];
            case 14: return [1, 1, 1, 0];
            case 15: return [1, 1, 1, 1];
            default: return [0, 0, 0, 0];
        }
    }

    private static bin2uint8hex(bin: number[]) {
        switch (bin.toString()) {
            case '0,0,0,1': return 1;
            case '0,0,0,0': return 0;
            case '0,0,1,0': return 2;
            case '0,0,1,1': return 3;
            case '0,1,0,0': return 4;
            case '0,1,0,1': return 5;
            case '0,1,1,0': return 6;
            case '0,1,1,1': return 7;
            case '1,0,0,0': return 8;
            case '1,0,0,1': return 9;
            case '1,0,1,0': return 10;
            case '1,0,1,1': return 11;
            case '1,1,0,0': return 12;
            case '1,1,0,1': return 13;
            case '1,1,1,0': return 14;
            case '1,1,1,1': return 15;
            default: return 0;
        }
    }

    private static clock4RandomReg(currentReg: Uint8Array) {
        const reg = [this.uint8hex2bin(currentReg[0]),
        this.uint8hex2bin(currentReg[1]),
        this.uint8hex2bin(currentReg[2]),
        this.uint8hex2bin(currentReg[3])];
        let result = [0, 0, 0, 0];
        result[0] = reg[0][0] ^ reg[1][0] ^ reg[3][1] ^ reg[3][3];
        result[1] = reg[0][0] ^ reg[0][1] ^ reg[1][0] ^ reg[1][1] ^ reg[3][1] ^ reg[3][2] ^ reg[3][3];
        result[2] = reg[0][0] ^ reg[0][1] ^ reg[0][2] ^ reg[1][0] ^ reg[1][1] ^ reg[1][2] ^ reg[3][1] ^ reg[3][2];
        result[3] = reg[0][1] ^ reg[0][2] ^ reg[0][3] ^ reg[1][0] ^ reg[1][1] ^ reg[1][2] ^ reg[1][3] ^ reg[3][2] ^ reg[3][3];
        return this.bin2uint8hex(result);
    }

    static scramble(hex: string, iv: string = 'FFFF') {
        const bit = this.hex2Uint8(hex);
        const init = this.hex2Uint8(iv.substr(0, 4));
        let result = '';
        let randomRegister = init;

        for (let i = 0; i < 64; i += 1) {
            const out = bit[i] ^ randomRegister[0];
            result += out.toString(16);
            const tempRamdomRegister = randomRegister;
            randomRegister[0] = tempRamdomRegister[1];
            randomRegister[1] = tempRamdomRegister[2];
            randomRegister[2] = tempRamdomRegister[3];
            randomRegister[3] = this.clock4RandomReg(tempRamdomRegister);
        }
        return result.toUpperCase();
    }
}