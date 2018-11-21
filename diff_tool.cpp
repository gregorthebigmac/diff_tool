#include "root_dir.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

root_dir root;

int main(int argc, char *argv[]) {
	if (argc > 1) {
		string target_path = argv[1];
		root.set_target_dir(target_path);
		vector<string> target_file_list = root.get_target_file_list();
		root.build_dir_list(target_path, target_file_list);
	}
}