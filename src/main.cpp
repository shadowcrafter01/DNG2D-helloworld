#include "DNG2D/Main.hpp"
#include "CustomDingus.hpp"

DNG::Window *window = new DNG::Window;
DNG::Camera *camera = new DNG::Camera(window);
DNG::Texture *texture = new DNG::Texture(camera, "assets/textures/test.bmp");
DNG::Audio *collisionSound = new DNG::Audio("assets/sounds/rock.wav");

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
        CustomDingus *custom = new CustomDingus(camera, texture, {DNG::Random::GetNext(-200, 200), DNG::Random::GetNext(0, 200)});
        custom->AssignCollisionSound(collisionSound);
    }
    while (DNG::Update())
    {
        SDL_Delay(5); // pretend lag
    }
    DNG::Shutdown();
    return 0;
}
