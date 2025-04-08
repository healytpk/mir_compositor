#include <miral/runner.h>
#include <miral/minimal_window_manager.h>
#include <miral/set_window_management_policy.h>

using namespace miral;

int main(int const argc, char **const argv)
{
    MirRunner runner{argc, const_cast<char const **>(argv)};

    return runner.run_with(
        {
            set_window_management_policy<MinimalWindowManager>()
        });
}
