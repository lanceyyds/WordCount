#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����ļ�������
#define MAX_FILE 100

// ͳ���ַ���
int count_chars(FILE *fp) {
    int count = 0; 
    char ch; 
    while ((ch = fgetc(fp)) != EOF) { // ���ļ��ж�ȡһ���ַ���ֱ���ļ�����
        count++; 
    }
    return count; 
}

// ����ͳ�Ƶ�����
int count_words(FILE *fp) {
    int count = 0; 
    char ch; 
    int in_word = 0; // ���嵥�ʱ�־��0��ʾ���ڵ����У�1��ʾ�ڵ�����
    while ((ch = fgetc(fp)) != EOF) { // ���ļ��ж�ȡһ���ַ���ֱ���ļ�����
        if (ch == ' ' || ch == ',' || ch == '\n' || ch == '\t') { // ����ǿո�򶺺Ż��з����Ʊ��
            if (in_word) { // ���֮ǰ�ڵ�����
                count++; 
                in_word = 0; // ���õ��ʱ�־Ϊ0����ʾ���ڵ�����
            }
        } else { // ������ǿո�򶺺Ż��з����Ʊ��
            in_word = 1; // ���õ��ʱ�־Ϊ1����ʾ�ڵ�����
        }
    }
    if (in_word) { // ����ļ�����ʱ���ڵ�����
        count++; 
    }
    return count;
}

// ������
int main(int argc, char *argv[]) {
    FILE *fp; 
    char file[MAX_FILE]; 
    char parameter[3]; 

    if (argc != 3) { // �����������������3��������������
        printf("Usage: WordCount [parameter] [input_file]\n"); // ��ӡ�÷���ʾ��Ϣ
        exit(1); // �쳣�˳�����
    }

    strcpy(parameter, argv[1]); // ����һ�����������Ʋ��������Ƶ�parameter������
    strcpy(file, argv[2]); // ���ڶ����������ļ��������Ƶ�file������

    if ((fp = fopen(file, "r")) == NULL) { // ������ļ�ʧ�ܣ�����NULL��
        printf("Cannot open file: %s\n", file); // ��ӡ������Ϣ
        exit(2); // �쳣�˳�����
    }

    if (strcmp(parameter, "-c") == 0 || strcmp(parameter, "-C") == 0) { // �������Ϊ-c��-c����ʾͳ���ַ�����
        printf("�ַ�����%d\n", count_chars(fp)); // ����count_chars����������ӡ���
    } else if (strcmp(parameter, "-w") == 0 || strcmp(parameter, "-W") == 0) { // �������Ϊ-w��-W����ʾͳ�Ƶ�������
        printf("��������%d\n", count_words(fp)); // ����count_words����������ӡ���
    } else { // ��������Ȳ���-c��-CҲ����-w��-W����ʾ��Ч������
        printf("Invalid parameter: %s\n", parameter); // ��ӡ������Ϣ
        exit(3); // �쳣�˳�����
    }

    fclose(fp); // �ر��ļ�

    return 0; // �����˳�����
}
