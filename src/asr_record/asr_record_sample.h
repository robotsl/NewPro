/*
* ������д(iFly Auto Transform)�����ܹ�ʵʱ�ؽ�����ת���ɶ�Ӧ�����֡�
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

typedef struct _UserData {
	int     build_fini; //��ʶ�﷨�����Ƿ����
	int     update_fini; //��ʶ���´ʵ��Ƿ����
	int     errcode; //��¼�﷨��������´ʵ�ص�������
	char    grammar_id[MAX_GRAMMARID_LEN]; //�����﷨�������ص��﷨ID
}UserData;

extern FILE* pFile;
//pFile = fopen("./record.log", "a+");
extern char str1[1024];

int build_grammar(UserData *udata); //��������ʶ���﷨����
int run_asr(UserData *udata); //���������﷨ʶ��



int build_grm_cb(int ecode, const char *info, void *udata);

int build_grammar(UserData *udata);

//********************************************TODO*************************************************************************************/
//��ȡ�﷨���
void on_result(const char *result, char is_last);

void on_speech_begin();
void on_speech_end(int reason);

/* demo send audio data from a file */
static void demo_file(const char* audio_file, const char* session_begin_params);

/* demo recognize the audio from microphone */
static void demo_mic(const char* session_begin_params);

int run_asr(UserData *udata);

//////ע�⣬�˴��޸ĳɺ�����ʽ
char *retString(char *string);
