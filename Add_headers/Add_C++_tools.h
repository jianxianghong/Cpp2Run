#include "Resources.h"

/*========================================Define names================================================================*/

extern char Cpp_source_file_path[];
extern char main_file_name[];
extern char main_mod_file_name[];
extern char tmp_file_suffix[];
extern char flag_main_1[];
extern char flag_main_2[];

/*========================================Reset main.cpp==============================================================*/

bool Reset_main(char Path[]){
    char* main_mod=join_chars(Path,main_mod_file_name);
    ifstream mod(main_mod);
    char* main_file=join_chars(Path,main_file_name);
    ofstream Reset(main_file);
    string tmp;
    while(getline(mod,tmp)) Reset<<tmp<<'\n';
    Reset<<flush;
    mod.close(); Reset.close();
    return true;
}

/*========================================Add new C++ filename into main.cpp==========================================*/

bool Add_to_main(char Path[],char file_name[]){
    char* main_file=join_chars(Path,main_file_name);
    ifstream filein(main_file);
    if(!filein.is_open()){
        cout<<"\nerror: Open main.cpp fail."<<endl;
        return false;
    }
    char* main_tmp=join_chars(main_file,tmp_file_suffix);
    ofstream fileout(main_tmp);
    string tmp;
    while(1){
        getline(filein,tmp);
        while(!tmp.length()) getline(filein,tmp);
        char* trans_tmp=string_to_char(tmp);
        if(strncmp(trans_tmp,flag_main_1,strlen(flag_main_1))) break;
        fileout<<trans_tmp<<'\n';
    }
    fileout<<flag_main_1<<join_chars(Cpp_source_file_path,file_name)<<"\"\n\n"<<tmp<<'\n';
    while(tmp[0]!='i'){
        getline(filein,tmp); fileout<<tmp<<'\n';
    }
    string bak; string tmp_;
    while(getline(filein,tmp)){
        if (tmp_.length()>1){
            fileout<<tmp_<<'\n';
            char* trans_bak=string_to_char(bak);
            char* trans_tmp=string_to_char(tmp);
            if(!strncmp_without_balck(trans_bak,flag_main_2,strlen(flag_main_2))
               && strncmp_without_balck(trans_tmp,flag_main_2,strlen(flag_main_2))) break;
        }
        tmp_=bak; bak=tmp;
    }
    int chose[2]={0,0};
    while(tmp_[chose[0]]-'0'>10||tmp_[chose[0]]-'0'<0) ++chose[0];
    --chose[0];
    while(tmp_[++chose[0]]-'0'<10) chose[1]=chose[1]*10+tmp_[chose[0]]-'0';
    fileout<<"            case "<<++chose[1]<<": {cout<<\"Run "<<file_name<<" \\n\"; ";
    file_name[strlen(file_name)-4]='\0';
    fileout<<file_name<<"(); break;}\n"
            "            case "<<++chose[1]<<": {cout<<\"Once again ... \\n\"; main(argc,argv); break;}\n";
    do fileout<<tmp<<'\n';
    while(getline(filein,tmp));
    fileout<<flush;
    filein.close(); fileout.close();
    return true;
}