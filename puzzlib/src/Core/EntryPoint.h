#pragma once
#include "Core/ref_ptr.h"
#include <Windows.h>

extern puzz::ref_ptr<puzz::Application> puzz::CreateApplication();

int main(int argc, char **argv)
{
    auto app = puzz::CreateApplication();
    app->Init();
    app->Run();
    app->ShotDown();
}