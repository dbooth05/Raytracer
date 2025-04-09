#ifndef ENTRY_HPP
#define ENTRY_HPP

#include "application.hpp"

extern BaseEngine::Application* BaseEngine::createApplicaion(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace BaseEngine {
    int Main(int argc, char** argv) {
        while (g_ApplicationRunning) {
            BaseEngine::Application* app = BaseEngine::createApplicaion(argc, argv);
            app->run();
            delete app;
        }

        return 0;
    }
}

int main(int argc, char** argv) {
    return BaseEngine::Main(argc, argv);
}

#endif
