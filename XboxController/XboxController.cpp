#include <iostream>
#include <Windows.h>
#include <Xinput.h>

#define BIT(a) (1UL << (a))
#pragma comment(lib, "Xinput.lib") // Link with Xinput library

// Function to get the state of the controller

uint8_t scaleToUint8(int value) {
    return static_cast<uint8_t>(value / 256);
}

int8_t scaleToInt8(int value) {
    return static_cast<int8_t>(value / 256);
}

XINPUT_STATE GetControllerState() {
    XINPUT_STATE state;
    DWORD dwResult = XInputGetState(0, &state); // Controller index is 0 (first controller)

    if (dwResult == ERROR_SUCCESS) {
        return state; // Return the state of the controller
    }
    else {
        // Handle error (controller not connected or other error)
        // For simplicity, you can return an empty state
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        return state;
    }
}

// Function to print controller information
void ButtonsInfo(XINPUT_STATE state, int8_t* Buttons) {
    // Print the controller information in a tabular format
    Buttons[0] = ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
    Buttons[1] = ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
    Buttons[2] = ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
    Buttons[3] = ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
    Buttons[4] = scaleToUint8(state.Gamepad.sThumbLY);
    Buttons[5] = scaleToUint8(state.Gamepad.sThumbLX);
}

void PrintButtons(int8_t* Buttons) {
    std::cout << "A\tB\t\X\tY\tLY\tLX\n";
    std::cout << Buttons[0] << '\t';
    std::cout << Buttons[1] << '\t';
    std::cout << Buttons[2] << '\t';
    std::cout << Buttons[3] << '\t';
    std::cout << int(Buttons[4]) << '\t';
    std::cout << int(Buttons[5]) << '\t' << '\n';
}

void CompactControllerState(XINPUT_STATE state, int8_t* Buttons) {
    Buttons[0] = 0;
    Buttons[1] = 0;
    Buttons[2] = 0;
    short int LX = state.Gamepad.sThumbLX;
    short int LY = state.Gamepad.sThumbLY;

    if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
        Buttons[0] |= BIT(0);
    };
    if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0) { 
        Buttons[0] |= BIT(1);
    };
    if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0) {
        Buttons[0] |= BIT(2);
    };
    if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0) {
        Buttons[0] |= BIT(3);
    };
    if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0) {
        Buttons[0] |= BIT(4);
    };
    if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) {
        Buttons[0] |= BIT(5);
    };
    if (state.Gamepad.bRightTrigger != 0) {
        Buttons[0] |= BIT(6);
    };
    if (state.Gamepad.bLeftTrigger != 0) {
        Buttons[0] |= BIT(7);
    };

    if (LX == 32768) { 
        LX--;
    };
    if (LX == -32768) { 
        LX++;
    };
    if (LY == 32768) { 
        LY--;
    };;
    if (LY == -32768) { 
        LY++;
    };
    Buttons[1] = scaleToInt8(state.Gamepad.sThumbLY);
    Buttons[2] = scaleToInt8(state.Gamepad.sThumbLX);
}

void bytePrinter(int8_t inputValue){
    for (int i = 0; i < 8; i++) {
        std::cout << int((inputValue & BIT(i)) == BIT(i));
    };
    std::cout << '\t';
}

int main() {
    while (true) {
        // Get the state of the controller
        int8_t Buttons[3];
        int8_t a = 255;
        XINPUT_STATE state = GetControllerState();

        // Print controller information
        //ButtonsInfo(state,Buttons);
        //PrintButtons(Buttons);
        CompactControllerState(state, Buttons);
        bytePrinter(Buttons[0]);
        bytePrinter(Buttons[1]);
        bytePrinter(Buttons[2]);
        // bytePrinter(a);
        std::cout << std::endl;
 
        // Wait for 100 milliseconds before reading again
        Sleep(500);
    }
    return 0;
}
