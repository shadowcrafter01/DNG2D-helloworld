#include "DNG2D/Main.hpp"

int main(int, char **)
{
    DNG::Init();

    while (DNG::Update())
    {

    }

    DNG::Shutdown();
}
