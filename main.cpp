#include "Add_headers/Add_C++_files.h"

int main(int argc,char *argv[]) {
    char *cwd = get_new_cwd(argv[0]);
    char* chosen=join_chars(cwd,Chose_file_name);
    ifstream filein(chosen);
    int chose;
    while (filein >> chose) {
        switch (chose) {
            case 1: {cout<<"Run Add_C++_files.h \n"; Add_C_files(argv[0]); break;}
            case 2: {cout<<"Once again ... \n"; main(argc,argv); break;}
            default: continue;
        }
    }
    return 0;
}

