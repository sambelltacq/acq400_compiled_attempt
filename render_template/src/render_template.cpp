#include <inja/inja.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

string get_timestamp() {
    time_t now = time(nullptr);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%d %b %y %H:%M", localtime(&now));
    return string(buffer);
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cerr << "USAGE: " << argv[0] << " TEMPLATE.j2" << endl;
        return 1;
    }

    string template_filename = argv[1];

    ifstream fs;
    fs.open(template_filename);
    if (!fs.is_open()) {
        cerr << "Error: unable to open template " << template_filename << endl;
        return 1;
    }

    string template_str((istreambuf_iterator<char>(fs)), istreambuf_iterator<char>());

    inja::Environment env;

    env.set_ignore_missing_vars(true);

    inja::json context;
    extern char **environ;
    for (char **env_var = environ; *env_var != nullptr; ++env_var) {
        std::string env_str = *env_var;
        size_t pos = env_str.find('=');
        if (pos != std::string::npos) {
            context[env_str.substr(0, pos)] = env_str.substr(pos + 1);
        }
    }

    context["timestamp"] = get_timestamp();
    //std::cout << context.dump(4) << std::endl;

    cout << env.render(template_str, context);
    return 0;
}