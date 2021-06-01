#include <iostream>
#include <fstream>
#include <cstring>

std::string parse(const char *path) {
    std::string buffer;
    std::string line;
    std::ifstream srcfile(path);
    if (srcfile.is_open()) {
        while ( std::getline (srcfile,line)) {
            buffer += line;
        }
        srcfile.close();
        buffer += "\0";
        return buffer;
    }
    else 
        return "\0";
}

void compile(std::string inp) {
    std::ofstream outfile("aout.c");
    outfile << "#include<stdio.h>\nint main(){char arr[30000]={0};char*ptr=arr";
    for (auto &c : inp) {
        switch(c) {
            case '>':
                outfile << "++ptr;";
                break;
            case '<':
                outfile << "--ptr;";
                break; 
            case '+':
                outfile << "++(*ptr);";
                break;
            case '-':
                outfile << "--(*ptr);";
                break;
            case '.':
                outfile << "putchar(*ptr);";
                break;
            case ',':
                outfile << "*(ptr)=getchar();";
                break;
            case '[':
                outfile << "while(*ptr){";
                break;
            case ']':
                outfile << "}";
                break;
        }
    }
    outfile << "return 0;}\n";
    outfile.close();
}

int main(int argc, const char *argv[]) {
    compile(parse(argv[1]));
    return 0;
}
