#include "app.hpp"

int main(int argc, char* argv[]) {  //
    arg(0, argv[0]);
    setup(argc, argv);
    for (int i = 1; i < argc; i++) arg(i, argv[i]);
    Dev::init();
    return loop();
}

void arg(int argc, char* argv) {  //
    std::clog << "arg[" << argc << "] = <" << argv << "]\n";
}

void setup(int argc, char* argv[]) {  //
    std::clog << "setup: ok\n";
}

int loop() {  //
    std::clog << "loop: no\n";
    return 0;
}
