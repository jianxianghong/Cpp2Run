#include <dirent.h>
#include "Add_C++_tools.h"

/*========================================Define names================================================================*/

extern char main_file_name[];
extern char main_mod_file_name[];
extern char tmp_file_suffix[];
extern char Cpp_source_file_path[];

/*========================================Get current path============================================================*/

char* get_new_cwd(char argv[]){
    size_t argc=strlen(argv);
    int count=2;
    while(count) if(argv[--argc]=='/') --count;
    char *cwd=new char[argc];
    for(int tail=0;tail<=argc;++tail) cwd[tail]=argv[tail];
    return cwd;
}

/*========================================Set tmp file================================================================*/

bool ReWrite_files(char basePath[],char file_name[]){
    if(Add_to_main(basePath,file_name)){
        char* main_file=join_chars(basePath,main_file_name);
        char* main_tmp=join_chars(main_file,tmp_file_suffix);
        rename(main_tmp,main_file);
    }else return false;

    return true;
}

/*========================================Search c++ files============================================================*/

bool Search_cpp(char basePath[]){
    char* source_path=join_chars(basePath,Cpp_source_file_path);
    DIR *dir=opendir(source_path);
    dirent* ptr;
    while ((ptr=readdir(dir)) != NULL)
        if(screen(ptr->d_name)) {
            cout << "Trying add " << ptr->d_name << " into main.cpp ... " ;
            if(ReWrite_files(basePath,ptr->d_name)) cout<<"[OK]\n";
            else return false;
        }
    closedir(dir);
    return true;
}

/*========================================Reset files=================================================================*/

bool check_Resource_file(char basePath[]){
    cout<<"Reset main.cpp from "<<main_mod_file_name<<" ... ";
    if(Reset_main(basePath)) cout<<"[OK]\n";
    else return false;

    return true;
}

/*========================================main socket=================================================================*/

int Add_C_files(char argv[]){
    char* cwd=get_new_cwd(argv);

    cout<<"Searching C++ Files in : "<<cwd<<endl;
    if(check_Resource_file(cwd)&&Search_cpp(cwd)) cout<<"Successfully added all CPP files.";
    return 0;
}
