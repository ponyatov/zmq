#include "zmq.hpp"

extern int main(int argc, char* argv[]) {  //
    arg(0, argv[0]);
    setup(argc,argv);
    for (int i = 1; i < argc; i++) arg(i, argv[i]);
    return loop;
}

extern void arg(int argc, char* argv) {  //
    std::clog << "arg[" << argc << "] = <" << argv << "]\n";
}
