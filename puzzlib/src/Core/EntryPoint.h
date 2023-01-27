#pragma once
#include "Core/cnt_ptr.h"

extern puzz::cnt_ptr<puzz::Application> puzz::CreateApplication();

int main(int argc, char **argv)
{
    auto app = puzz::CreateApplication();
    app->Init();
    app->Run();
    app->ShotDown();
}