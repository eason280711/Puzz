#pragma once

extern puzz::Application* puzz::CreateApplication();

int main(int argc,char** argv)
{	
    auto app = puzz::CreateApplication();
    app->Init();
    app->Run();
    app->ShotDown();
    delete app;
}