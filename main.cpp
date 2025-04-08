#include <miral/runner.h>
#include <miral/minimal_window_manager.h>
#include <miral/set_window_management_policy.h>
#include <semaphore>    // binary_semaphore
#include <thread>       // jthread

using namespace miral;

std::binary_semaphore mysem(0);  // starts off acquired

void Other_Thread_To_Do_Hello_World_In_GTK(void);  // defined lower down in this file

int main(int const argc, char **const argv)
{
    MirRunner runner{argc, const_cast<char const **>(argv)};

    std::jthread other_thread(Other_Thread_To_Do_Hello_World_In_GTK);

    mysem.release(1);  // Allow other thread to start another program

    return runner.run_with(
        {
            set_window_management_policy<MinimalWindowManager>()
        });
}

// ======================= Code for "Hello World" program in GTK:

#include <chrono>       // seconds
#include <semaphore>    // binary_semaphore
#include <thread>       // sleep_for
#include <gtk/gtk.h>

extern std::binary_semaphore mysem;

void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *const window = gtk_application_window_new(app);
    GtkWidget *const label = gtk_label_new("Hello World from GTK!");
    gtk_window_set_title(GTK_WINDOW(window), "Hello");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_container_add(GTK_CONTAINER(window), label);
    gtk_widget_show_all(window);
}

void Other_Thread_To_Do_Hello_World_In_GTK(void)
{
    mysem.acquire();  // wait until main thread allows us to proceed
    std::this_thread::sleep_for( std::chrono::seconds(2) );
    GtkApplication *app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), nullptr);
    g_application_run( G_APPLICATION(app), 0, nullptr );
    g_object_unref(app);
}
