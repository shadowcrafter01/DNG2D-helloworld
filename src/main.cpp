#include "DNG2D/Main.hpp"

DNG::Window *window = new DNG::Window;
DNG::Camera *camera = new DNG::Camera(window);
DNG::Texture *texture = new DNG::Texture(camera, "assets/textures/test.bmp");

DNG::Dingus *nearest = nullptr;

void GrabNearestDingus()
{
    nearest->ApplyForce((DNG::Input::Mouse::GetMouseWorldPos(camera) - nearest->GetPosition()) * 200.0f);
}
void FindNearestDingus()
{
    nearest = DNG::Dingus::GetNearest(DNG::Input::Mouse::GetMouseWorldPos(camera));
}

DNG::Action *mouseDown = new DNG::Action(FindNearestDingus, SDL_BUTTON_LEFT, ACTION_ON_PRESS);
DNG::Action *mouseHeld = new DNG::Action(GrabNearestDingus, SDL_BUTTON_LEFT, ACTION_WHILE_HELD);

int main(int, char **)
{
    DNG::Init();

    DNG::Dingus *ground = new DNG::Dingus(camera, texture, DNG::Transform2<float>(0, -200, 600, 10));
    ground->AssignCollisionShape(DNG::CollisionShape::CreateBox(ground->GetTransform().size))->SetStatic()->SetName("ground");

    for (int i = 0; i < 10; i++)
    {
        DNG::Dingus *box = new DNG::Dingus(camera, texture);
        box->SetPosition(DNG::Random::GetNext(-200, 200), DNG::Random::GetNext(0, 200))->SetName("box");
        box->AssignCollisionShape(DNG::CollisionShape::CreateBox(box->GetTransform().size));
    }

    while (DNG::Update())
    {
        SDL_Delay(5); // pretend lag
    }

    DNG::Shutdown();
}
