#include "core/application.h"
#include "core/core.h"
using namespace std;

int main(int argc, char** argv)
{

    huan_renderer_cpu::Application::create_instance();

    auto application = huan_renderer_cpu::Application::get_instance();
    application->initialize();

    cout << "Hello world!" << endl;
    std::cout << "Current Cpp standard version: " << __cplusplus << '\n';

    // Render
    application->render();

    application->save_image("test.ppm");

    application->destory();
    return 0;
}
