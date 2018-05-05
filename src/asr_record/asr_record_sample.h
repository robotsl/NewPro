/*
* 语音听写(iFly Auto Transform)技术能够实时地将语音转换成对应的文字。
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

typedef struct _UserData {
	int     build_fini; //标识语法构建是否完成
	int     update_fini; //标识更新词典是否完成
	int     errcode; //记录语法构建或更新词典回调错误码
	char    grammar_id[MAX_GRAMMARID_LEN]; //保存语法构建返回的语法ID
}UserData;

extern FILE* pFile;
//pFile = fopen("./record.log", "a+");
extern char str1[1024];

int build_grammar(UserData *udata); //构建离线识别语法网络
int run_asr(UserData *udata); //进行离线语法识别



int build_grm_cb(int ecode, const char *info, void *udata);

int build_grammar(UserData *udata);

//********************************************TODO*************************************************************************************/
//获取语法结果
void on_result(const char *result, char is_last);

void on_speech_begin();
void on_speech_end(int reason);

/* demo send audio data from a file */
static void demo_file(const char* audio_file, const char* session_begin_params);

/* demo recognize the audio from microphone */
static void demo_mic(const char* session_begin_params);

int run_asr(UserData *udata);

//////注意，此处修改成函数形式
char *retString(char *string);
