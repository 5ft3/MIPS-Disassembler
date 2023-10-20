#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include "Assignment1.h"

using namespace std;
using namespace N;

int main() {

    //array of hex values to be disassembled
    unsigned int bitInstructionArray[11] = {0x032BA020, 0x8CE90014, 0x12A90003, 0x022DA822, 0xADB30020, 0x02697824, 
    0xAE8FFFF4,0x018C6020, 0x02A4A825, 0x158FFFF7, 0x8ECDFFF0};

    //initializing variables
    int opcode = 0;
    int sourceRegister1 = 0;
    int sourceRegister2 = 0;
    int sourceRegister3 = 0;
    int functionRegister = 0;
    int destinationRegister = 0;
    int iFormatImmediateValue = 0;

    // defining register values 
    unsigned int Bits_0_to_5;
    unsigned int Bits_6_to_10;
    unsigned int Bits_11_to_15;
    unsigned int Bits_16_to_20;
    unsigned int Bits_21_to_25;
    unsigned int Bits_26_to_31;
    // i-format register 
    signed short Bits_0_to_15;

    //f-format and offset for i-format bit masks
    functionRegister = Bits_0_to_5;  
    sourceRegister3 = Bits_11_to_15 >> 11;
    sourceRegister2= Bits_16_to_20 >> 16;
    sourceRegister1 = Bits_21_to_25 >> 21;
    opcode = Bits_26_to_31 >> 26;
    iFormatImmediateValue = Bits_0_to_15;
    iFormatImmediateValue = Bits_0_to_15;

    //for loop to identify the instruction
    int addressIncrement = 630848;
    
    for (int i = 0; i < 11; i++)
    {
        cout << "\n";

        //setting the bitmasks for every hex value in the array
        Bits_0_to_5 = bitInstructionArray[i] & 0x0000003F;
        Bits_11_to_15 = bitInstructionArray[i] & 0x0000F800;
        Bits_16_to_20 = bitInstructionArray[i] & 0x001F0000;
        Bits_21_to_25 = bitInstructionArray[i] & 0x03E00000;
        Bits_26_to_31 = bitInstructionArray[i] & 0xFC000000;
        Bits_0_to_15 = bitInstructionArray[i];

        //shifting bits in the bitmask
        functionRegister = Bits_0_to_5;  
        sourceRegister3 = Bits_11_to_15 >> 11;
        sourceRegister2= Bits_16_to_20 >> 16;
        sourceRegister1 = Bits_21_to_25 >> 21;
        opcode = Bits_26_to_31 >> 26;
        iFormatImmediateValue = Bits_0_to_15;
        
        cout << "   " << std::hex << addressIncrement << " ";

        //condition to identify which instruction each hex value is. functionRegister value is in decimal
        if (opcode == 0 && functionRegister == 32) 
        {
            cout << "add ";
            cout << "$" << dec << sourceRegister3 <<",";
            cout << "$" << dec << sourceRegister1 << ",";
            cout << "$" << dec << sourceRegister2;
        }

        if (opcode == 0 && functionRegister == 36) 
        {
            cout << "and "; 
            cout << "$" << dec << sourceRegister3 << ",";
            cout << "$" << dec << sourceRegister1 << ",";
            cout << "$" << dec << sourceRegister2;
        }

        if (opcode == 0 && functionRegister == 37) 
        {
            cout << "or ";
            cout << "$" << dec << sourceRegister3 << ",";
            cout << "$" << dec << sourceRegister1 << ",";
            cout << "$" << dec << sourceRegister2;
        }
        
        if (opcode == 0 && functionRegister == 34) 
        {
            cout << "sub ";
            cout << "$" << dec << sourceRegister3 << ",";
            cout << "$" << dec << sourceRegister1 << ",";
            cout << "$" << dec << sourceRegister2;
        }
    
        if (opcode == 0 && functionRegister == 42) 
        {
            cout << "slt ";  
            cout << "$" << dec << sourceRegister3 << ",";
            cout << "$" << dec << sourceRegister1 << ",";
            cout << "$" << dec << sourceRegister2;
        }
    
        if (opcode == 35) 
        {
            cout << "lw ";
            cout << "$" << dec << sourceRegister2 << ",";
            cout << dec << iFormatImmediateValue;
            cout << dec << "(" << "$" << sourceRegister1 << ")";
        }     
    
        if (opcode == 43) 
        {
            cout << "sw ";
            cout << "$" << dec << sourceRegister2 << ",";
            cout <<  dec << iFormatImmediateValue;
            cout << dec << "(" << "$" << sourceRegister1 << ")";
        }
        
        if (opcode == 4) 
        {
            cout << "beq ";
            cout << "$" << dec << sourceRegister1 << ",";
            cout << "$" << dec << sourceRegister2 << ",";
            cout << hex << (iFormatImmediateValue * 4) + addressIncrement + 4;
        }

        if (opcode == 5) 
        {
            cout << "bne ";
            cout << "$" << dec << sourceRegister1 << ",";
            cout << "$" << dec << sourceRegister2 << ",";
            cout << hex << (iFormatImmediateValue * 4) + addressIncrement + 4;
        }

        //incrementing the address for every instruction

            addressIncrement  = addressIncrement + 4;
    }

    return 0;
}