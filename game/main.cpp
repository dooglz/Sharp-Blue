#include "sharp_blue.h"
#include <Entity.h>
#include <components/cmp_3d.h>
#include <components/cmp_camera.h>
#include <components/cmp_light.h>
#include <components/cmp_mesh_renderer.h>
#include <components/cmp_motor_fps.h>
#include <iostream>
#include <math.h>
#include <memory>

using namespace std;
using namespace glm;

void CreateScene() {
  //  ########### Build a Box ###########

  auto box = make_unique<sb::Entity>();
  box->SetName("Box");
  // Add 3D component so it exists in space
  box->AddComponent(make_unique<sb::cmp_3d>());
  // Add mesh renderer
  auto mr = make_unique<sb::cmp_mesh_renderer>();
  mr->SetMesh("sphereI2.obj");
  mr->SetEffect("basic");
  box->AddComponent(move(mr));
  // Add to scene
  sb::GetLevel()->AddToScene(move(box));

  //  ########### Build a Camera ###########
  auto camera = make_unique<sb::Entity>();
  camera->SetName("Camera");
  // Add 3D component so it exists in space
  camera->AddComponent(make_unique<sb::cmp_3d>(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f), vec3(1.0f)));
  // Add camera component
  camera->AddComponent(make_unique<sb::cmp_camera>());
  camera->GetComponent<sb::cmp_camera>().SetActive();
  camera->AddComponent(make_unique<sb::cmp_motor_fps>());
  // Add to scene
  sb::GetLevel()->AddToScene(move(camera));

  //  ########### Build a Lamp ###########
  auto lamp = make_unique<sb::Entity>();
  lamp->SetName("lamp");
  // Add 3D component so it exists in space
  lamp->AddComponent(make_unique<sb::cmp_3d>(vec3(0, 10.0f, 0), vec3(0, -1.0f, 0), vec3(1.0f)));
  // Add light component
  lamp->AddComponent(make_unique<sb::cmp_light>());
  // Add to scene
  sb::GetLevel()->AddToScene(move(lamp));
}

void Update(double dt) {
  static unsigned char frame = 0;
  if ((++frame) >= 60) {
    cout << "fps:" << floor(1.0 / dt) << endl;
    frame = 0;
  }
  auto box = sb::GetLevel()->GetEnt("Box");
  box->GetComponent<sb::cmp_3d>().Rotate(glm::vec3(0, dt, 0));
}

int main(int argc, char *argv[]) {
  cout << "hello world" << endl;
  sb::version();
  if (!sb::init()) {
    return 1;
  }
  sb::SetTickFunc(Update);
  // Do initial load here
  CreateScene();
  // hand over to Engine
  sb::Start();
  cout << "Goodbye from GameCode" << endl;
  return 0;
}
