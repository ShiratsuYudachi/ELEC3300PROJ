#include <cstring>
#include <cstdio>
#ifndef INC_UTILS_HPP_
#define INC_UTILS_HPP_
#define STRING_LEN 32

class String{
public:
    char str[STRING_LEN];
    int len;
    String(){
        len = 0;
    }
    String(const char* s){
        len = strlen(s);
        strcpy(str, s);
    }
    String(const String& s){
        len = s.len;
        strcpy(str, s.str);
    }
    String(int n){
        len = sprintf(str, "%d", n);
    }
    String(float f){
        len = sprintf(str, "%f", f);
    }
    String(double d){
        len = sprintf(str, "%f", d);
    }
    String(uint8_t* arr, int len){
        // byte array to hex string
        for (int i=0; i<len; i++){
            sprintf(str+i*3, "%02X ", arr[i]);
        }
    }

    String& operator=(const char* s){
        len = strlen(s);
        strcpy(str, s);
        return *this;
    }
    String& operator=(const String& s){
        len = s.len;
        strcpy(str, s.str);
        return *this;
    }
    String operator+(const char* s){
        String newStr;
        newStr.len = len + strlen(s);
        strcpy(newStr.str, str);
        strcat(newStr.str, s);
        return newStr;
    }
    String operator+(const String& s){
        String newStr;
        newStr.len = len + s.len;
        strcpy(newStr.str, str);
        strcat(newStr.str, s.str);
        return newStr;
    }

    char& operator[](int i){
        return str[i];
    }
    int length(){
        return len;
    }
    void clear(){
        len = 0;
        str[0] = '\0';
    }

};

String operator+(const char* s, const String& str);

void printToLCD(const String& string, uint16_t row = 1);
void debugLog(const String& string);

void printArray(const uint8_t* arr, int len, int row = 1);

#endif /* INC_UTILS_HPP_ */