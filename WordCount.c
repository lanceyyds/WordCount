#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 最大文件名长度
#define MAX_FILE 100

// 统计字符数
int count_chars(FILE *fp) {
    int count = 0; 
    char ch; 
    while ((ch = fgetc(fp)) != EOF) { // 从文件中读取一个字符，直到文件结束
        count++; 
    }
    return count; 
}

// 定义统计单词数
int count_words(FILE *fp) {
    int count = 0; 
    char ch; 
    int in_word = 0; // 定义单词标志，0表示不在单词中，1表示在单词中
    while ((ch = fgetc(fp)) != EOF) { // 从文件中读取一个字符，直到文件结束
        if (ch == ' ' || ch == ',' || ch == '\n' || ch == '\t') { // 如果是空格或逗号或换行符或制表符
            if (in_word) { // 如果之前在单词中
                count++; 
                in_word = 0; // 设置单词标志为0，表示不在单词中
            }
        } else { // 如果不是空格或逗号或换行符或制表符
            in_word = 1; // 设置单词标志为1，表示在单词中
        }
    }
    if (in_word) { // 如果文件结束时还在单词中
        count++; 
    }
    return count;
}

// 主函数
int main(int argc, char *argv[]) {
    FILE *fp; 
    char file[MAX_FILE]; 
    char parameter[3]; 

    if (argc != 3) { // 如果参数个数不等于3（包括程序名）
        printf("Usage: WordCount [parameter] [input_file]\n"); // 打印用法提示信息
        exit(1); // 异常退出程序
    }

    strcpy(parameter, argv[1]); // 将第一个参数（控制参数）复制到parameter变量中
    strcpy(file, argv[2]); // 将第二个参数（文件名）复制到file变量中

    if ((fp = fopen(file, "r")) == NULL) { // 如果打开文件失败（返回NULL）
        printf("Cannot open file: %s\n", file); // 打印错误信息
        exit(2); // 异常退出程序
    }

    if (strcmp(parameter, "-c") == 0 || strcmp(parameter, "-C") == 0) { // 如果参数为-c或-c（表示统计字符数）
        printf("字符数：%d\n", count_chars(fp)); // 调用count_chars函数，并打印结果
    } else if (strcmp(parameter, "-w") == 0 || strcmp(parameter, "-W") == 0) { // 如果参数为-w或-W（表示统计单词数）
        printf("单词数：%d\n", count_words(fp)); // 调用count_words函数，并打印结果
    } else { // 如果参数既不是-c或-C也不是-w或-W（表示无效参数）
        printf("Invalid parameter: %s\n", parameter); // 打印错误信息
        exit(3); // 异常退出程序
    }

    fclose(fp); // 关闭文件

    return 0; // 正常退出程序
}
