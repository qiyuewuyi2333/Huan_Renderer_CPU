#include <iostream>
#include <memory>
#include "core/application.h"
#include "core/hittable_lists.h"
#include "functional/log/logger.h"
#include "core/core.h"
#include "functional/utils/image/image.h"
#include "functional/utils/image/image_generator.h"
#include "math/vec.h"
#include "primitives/sphere.h"
#include "core/camera.h"
using namespace std;

int main(int argc, char** argv)
{

    cout << "Hello world!" << endl;
    std::cout << "Current Cpp standard version: " << __cplusplus << '\n';

    huan_renderer_cpu::Application::create_instance();

    auto application = huan_renderer_cpu::Application::get_instance();
    application->initialize();

    // Render
    application->render();

    application->save_image("test.ppm");

    application->destory();
    return 0;
}
