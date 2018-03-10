#include <iostream>
#include <cstring>
#include <fstream>

/*========================================Using standard namespace====================================================*/

using std::string;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::flush;
using std::cout;

/*========================================Filename need for this program==============================================*/

char main_file_name[]="main.cpp";
char main_mod_file_name[]="mods/main.cpp";
char Resource_file_name[]="Resources.h";
char Chose_file_name[]="mods/chosen.txt";
char Cpp_source_file_path[]="cpp_sources/";

/*========================================Change suffix for cache file================================================*/

char tmp_file_suffix[]=".tmp";

/*========================================Recognition symbol==========================================================*/

char flag_main_1[]="#include \"";
char flag_main_2[]="case";

/*========================================Filename screen list========================================================*/

const char* allow_suffix[]={"Don't fill this place.",".cpp"};
const char* block_prefix[]={"Don't fill this place.",".",".."};


/*========================================Pre-treatment===============================================================*/

char* join_chars(char* _s1, char* _s2){
    char* _str=new char[strlen(_s1)+strlen(_s2)+1];
    strcpy(_str,_s1); strcat(_str,_s2);
    return _str;
}

char* string_to_char(string _s){
    const char *trans=_s.data();
    char* tmp=new char[strlen(trans)+1]; strcpy(tmp,trans);
    return tmp;
}

size_t strncmp_without_balck(char* _s1,char* _s2,size_t n){
    int p1=0,p2=0;
    while(n){
        if(_s1[p1]==' '){ ++p1; continue; }
        if(_s2[p2]==' '){ ++p2; continue; }
        if(_s1[p1]==_s2[p2]){ ++p1; ++p2; --n; }
        else break;
    }
    return n;
}

/*========================================Filename check Code=========================================================*/

bool screen(char filename[]){
    bool flag=false;
    size_t tail= sizeof(allow_suffix)/sizeof(char*);
    while(--tail){
        if(!strcmp(filename+(strlen(filename)-strlen(allow_suffix[tail])),allow_suffix[tail])) flag= true;
    }
    if(!flag) return false;
    tail= sizeof(block_prefix)/sizeof(char*);
    while(--tail){
        if(!strncmp(filename,block_prefix[tail],strlen(block_prefix[tail]))) return false;
    }
    return true;
}
