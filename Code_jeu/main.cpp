#include "controllers.h"
#include <future>

ControllerMenu* controllerMenu;

unsigned int square(unsigned int i) {
	return i * i;
}


int main() {
	auto f = std::async(std::launch::async, square, 8);
	std::thread t1(square, 1);
	controllerMenu = new ControllerMenu();
	return 0;
}