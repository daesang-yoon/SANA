#include "arguments/ArgumentParser.hpp"
#include "arguments/modeSelector.hpp"
#include "utils/randomSeed.hpp"
#include "utils/utils.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]) {
    cout << unitbuf; //set cout to flush after each insertion

    ArgumentParser args(argc, argv);

    // Assign to unused_ret to shut the compiler warning about igoring return value
    int sysRet = system("hostname -f; date");
    if (sysRet != 0) cerr<<"'hostname -f; date' returned error code "<<sysRet<<endl;

    args.writeArguments();

    if(args.doubles["-seed"] != 0) setSeed(args.doubles["-seed"]);
    else setRandomSeed();
    cout<<"Seed: "<<getRandomSeed()<<endl;

    Mode* mode = modeSelector::selectMode(args);
    mode->run(args);
    delete mode;
}
