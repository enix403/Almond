
#include "almond/core/Application.h"

#include <iostream>

using Almond::Application;

int main()
{
    Application::Initialize();
    Application* app = Application::Get();
    app->Run();
}
