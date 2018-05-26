#ifndef __ASR_RECORD_SAMPLE_H__
#define __ASR_RECORD_SAMPLE_H__
#include <stdio.h>

#define FRAME_LEN	640
#define	BUFFER_SIZE	4096
#define SAMPLE_RATE_16K     (16000)
#define SAMPLE_RATE_8K      (8000)
#define MAX_GRAMMARID_LEN   (32)
#define MAX_PARAMS_LEN      (1024)
typedef struct _UserData {
	int     build_fini; //��ʶ�﷨�����Ƿ�����
	int     update_fini; //��ʶ���´ʵ��Ƿ�����
	int     errcode; //��¼�﷨���������´ʵ��ص�������
	char    grammar_id[MAX_GRAMMARID_LEN]; //�����﷨�������ص��﷨ID
}UserData;


FILE *pFile;
char str1[1024];

void logout();
void beforeRecord();

//static char *g_result = NULL;
//static unsigned int g_buffersize = BUFFER_SIZE;

char *getContent(char *elementstart,char *elementend,char *filepath,char *ret);

int build_grammar(UserData *udata); //��������ʶ���﷨����
int run_asr(UserData *udata); //���������﷨ʶ��



int build_grm_cb(int ecode, const char *info, void *udata);

int build_grammar(UserData *udata);

//********************************************TODO*************************************************************************************/
//��ȡ�﷨����
void on_result(const char *result, char is_last);


//void write_log(const char *str,int fd);
void on_speech_begin();
void on_speech_end(int reason);

/* demo send audio data from a file */
static void demo_file(const char* audio_file, const char* session_begin_params);

/* demo recognize the audio from microphone */
static void demo_mic(const char* session_begin_params);

int run_asr(UserData *udata);
void *substring1(char *ret,const char *str,int start);

//////ע�⣬�˴��޸ĳɺ�����ʽ
char *retString(char *string);
#endif
