#include <windows.h>
#include <iostream>

int main(void) {
	if(IsDebuggerPresent()) {
		std::cout << "you are using debugger!" << std::endl;
	}
	else {
		std::cout << "you are not using debugger!" << std::endl;
	}
	return 0;
}
