/*
* 语音听写(iFly Auto Transform)技术能够实时地将语音转换成对应的文字。
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "../include/qisr.h"
#include "../include/msp_cmn.h"
#include "../include/msp_errors.h"
#include "speech_recognizer.h"



#define FRAME_LEN	640
#define	BUFFER_SIZE	4096
#define SAMPLE_RATE_16K     (16000)
#define SAMPLE_RATE_8K      (8000)
#define MAX_GRAMMARID_LEN   (32)
#define MAX_PARAMS_LEN      (1024)

const char * ASR_RES_PATH        = "fo|res/asr/common.jet"; //离线语法识别资源路径
const char * GRM_BUILD_PATH      = "res/asr/GrmBuilld"; //构建离线语法识别网络生成数据保存路径
const char * GRM_FILE            = "call.bnf"; //构建离线识别语法网络所用的语法文件
const char * LEX_NAME            = "contact"; //新离线识别语法的contact槽（语法文件为此示例中使用的call.bnf）


static char *g_result = NULL;
static unsigned int g_buffersize = BUFFER_SIZE;

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



int build_grm_cb(int ecode, const char *info, void *udata)
{
	UserData *grm_data = (UserData *)udata;


	if (NULL != grm_data) {
		grm_data->build_fini = 1;
		grm_data->errcode = ecode;
	}

	if (MSP_SUCCESS == ecode && NULL != info) {
		sprintf(str1,"构建语法成功！ 语法ID:%s\n", info);
		if (NULL != grm_data)
			snprintf(grm_data->grammar_id, MAX_GRAMMARID_LEN - 1, info);
	}
	else
	{
		sprintf(str1,"构建语法失败！%d\n", ecode);
	}
	write_log(pFile,str1);
	return 0;
}

int build_grammar(UserData *udata)
{
	FILE *grm_file                           = NULL;
	char *grm_content                        = NULL;
	unsigned int grm_cnt_len                 = 0;
	char grm_build_params[MAX_PARAMS_LEN]    = {NULL};
	int ret                                  = 0;

	grm_file = fopen(GRM_FILE, "rb");
	if(NULL == grm_file) {
		bzero(str1,sizeof(str1));
		sprintf(str1,"打开\"%s\"文件失败！[%s]\n", GRM_FILE, strerror(errno));
		write_log(pFile,str1);
		return -1;
	}

	fseek(grm_file, 0, SEEK_END);
	grm_cnt_len = ftell(grm_file);
	fseek(grm_file, 0, SEEK_SET);

	grm_content = (char *)malloc(grm_cnt_len + 1);
	if (NULL == grm_content)
	{
		bzero(str1,sizeof(str1));
		sprintf(str1,"内存分配失败!\n");
		write_log(pFile,str1);
		fclose(grm_file);
		grm_file = NULL;
		return -1;
	}
	fread((void*)grm_content, 1, grm_cnt_len, grm_file);
	grm_content[grm_cnt_len] = '\0';
	fclose(grm_file);
	grm_file = NULL;

	snprintf(grm_build_params, MAX_PARAMS_LEN - 1,
		"engine_type = local, \
		asr_res_path = %s, sample_rate = %d, \
		grm_build_path = %s, ",
		ASR_RES_PATH,
		SAMPLE_RATE_16K,
		GRM_BUILD_PATH
		);
	ret = QISRBuildGrammar("bnf", grm_content, grm_cnt_len, grm_build_params, build_grm_cb, udata);

	free(grm_content);
	grm_content = NULL;

	return ret;
}

//********************************************TODO*************************************************************************************/
//获取语法结果
void on_result(const char *result, char is_last)
{
	int fd = 0;
	if (result) {
		size_t left = g_buffersize - 1 - strlen(g_result);
		size_t size = strlen(result);
		if (left < size) {
			g_result = (char*)realloc(g_result, g_buffersize + BUFFER_SIZE);
			if (g_result)
				g_buffersize += BUFFER_SIZE;
			else {
				bzero(str1,sizeof(str1));
				sprintf(str1,"mem alloc failed\n");
				write_log(pFile,str1);
				return;
			}
		}
		strncat(g_result, result, size);
		if (is_last)
			strcat(g_result,'\0');
		if((fd = open("./result.txt",O_RDWR)) > 0)
		{
			write(fd,g_result,sizeof(g_result));
		}
	}
	close(fd);
}

void on_speech_begin()
{
	if (g_result)
	{
		free(g_result);
	}
	g_result = (char*)malloc(BUFFER_SIZE);
	g_buffersize = BUFFER_SIZE;
	memset(g_result, 0, g_buffersize);
	bzero(str1,sizeof(str1));
	sprintf(str1,"Start Listening...\n");
	write_log(pFile,str1);
}
void on_speech_end(int reason)
{
	bzero(str1,sizeof(str1));
	if (reason == END_REASON_VAD_DETECT)
		sprintf(str1,"Speaking done \n");
	else
		sprintf(str1,"Recognizer error %d\n", reason);
	write_log(pFile,str1);
}

/* demo send audio data from a file */
static void demo_file(const char* audio_file, const char* session_begin_params)
{
	int	errcode = 0;
	FILE*	f_pcm = NULL;
	char*	p_pcm = NULL;
	unsigned long	pcm_count = 0;
	unsigned long	pcm_size = 0;
	unsigned long	read_size = 0;
	struct speech_rec iat;
	struct speech_rec_notifier recnotifier = {
		on_result,
		on_speech_begin,
		on_speech_end
	};

	if (NULL == audio_file)
		goto iat_exit;

	f_pcm = fopen(audio_file, "rb");
	if (NULL == f_pcm)
	{
		bzero(str1,sizeof(str1));
		sprintf(str1,"open [%s] failed! \n", audio_file);
		write_log(pFile,str1);
		goto iat_exit;
	}

	fseek(f_pcm, 0, SEEK_END);
	pcm_size = ftell(f_pcm);
	fseek(f_pcm, 0, SEEK_SET);

	p_pcm = (char *)malloc(pcm_size);
	if (NULL == p_pcm)
	{
		bzero(str1,sizeof(str1));
		sprintf(str1,"out of memory! \n");
		write_log(pFile,str1);
		goto iat_exit;
	}

	read_size = fread((void *)p_pcm, 1, pcm_size, f_pcm);
	if (read_size != pcm_size)
	{
		bzero(str1,sizeof(str1));
		sprintf(str1,"read [%s] error!\n", audio_file);
		write_log(pFile,str1);
		goto iat_exit;
	}

	errcode = sr_init(&iat, session_begin_params, SR_USER, &recnotifier);
	if (errcode) {
		bzero(str1,sizeof(str1));
		sprintf(str1,"speech recognizer init failed : %d\n", errcode);
		write_log(pFile,str1);
		goto iat_exit;
	}

	errcode = sr_start_listening(&iat);
	if (errcode) {
		bzero(str1,sizeof(str1));
		sprintf(str1,"sr_start_listening failed! error code:%d\n", errcode);
		write_log(pFile,str1);
		goto iat_exit;
	}

	while (1)
	{
		unsigned int len = 10 * FRAME_LEN; /* 200ms audio */
		int ret = 0;

		if (pcm_size < 2 * len)
			len = pcm_size;
		if (len <= 0)
			break;

		ret = sr_write_audio_data(&iat, &p_pcm[pcm_count], len);

		if (0 != ret)
		{
			bzero(str1,sizeof(str1));
			sprintf(str1,"write audio data failed! error code:%d\n", ret);
			write_log(pFile,str1);
			goto iat_exit;
		}

		pcm_count += (long)len;
		pcm_size -= (long)len;
	}

	errcode = sr_stop_listening(&iat);
	if (errcode) {
		bzero(str1,sizeof(str1));
		sprintf(str1,"sr_stop_listening failed! error code:%d \n", errcode);
		write_log(pFile,str1);
		goto iat_exit;
	}

iat_exit:
	if (NULL != f_pcm)
	{
		fclose(f_pcm);
		f_pcm = NULL;
	}
	if (NULL != p_pcm)
	{
		free(p_pcm);
		p_pcm = NULL;
	}

	sr_stop_listening(&iat);
	sr_uninit(&iat);
}

/* demo recognize the audio from microphone */
static void demo_mic(const char* session_begin_params)
{
	int errcode;
	int i = 0;

	struct speech_rec iat;

	struct speech_rec_notifier recnotifier = {
		on_result,
		on_speech_begin,
		on_speech_end
	};

	errcode = sr_init(&iat, session_begin_params, SR_MIC, &recnotifier);
	if (errcode) {
		bzero(str1,sizeof(str1));
		sprintf(str1,"speech recognizer init failed\n");
		write_log(pFile,str1);
		return;
	}
	errcode = sr_start_listening(&iat);
	if (errcode) {
		bzero(str1,sizeof(str1));
		sprintf(str1,"start listen failed %d\n", errcode);
		write_log(pFile,str1);
	}
	/* demo 5 seconds recording */
	while(i++ < 5)
		sleep(1);
	errcode = sr_stop_listening(&iat);
	if (errcode) {
		bzero(str1,sizeof(str1));
		sprintf(str1,"stop listening failed %d\n", errcode);
		write_log(pFile,str1);
	}

	sr_uninit(&iat);
}

int run_asr(UserData *udata)
{
	char asr_params[MAX_PARAMS_LEN]    = {NULL};
	const char *rec_rslt               = NULL;
	const char *session_id             = NULL;
	const char *asr_audiof             = NULL;
	FILE *f_pcm                        = NULL;
	char *pcm_data                     = NULL;
	long pcm_count                     = 0;
	long pcm_size                      = 0;
	int last_audio                     = 0;

	int aud_stat                       = MSP_AUDIO_SAMPLE_CONTINUE;
	int ep_status                      = MSP_EP_LOOKING_FOR_SPEECH;
	int rec_status                     = MSP_REC_STATUS_INCOMPLETE;
	int rss_status                     = MSP_REC_STATUS_INCOMPLETE;
	int errcode                        = -1;
	int aud_src                        = 1;
	//离线语法识别参数设置
	snprintf(asr_params, MAX_PARAMS_LEN - 1,
		"engine_type = local, \
		asr_res_path = %s, sample_rate = %d, \
		grm_build_path = %s, local_grammar = %s, \
		result_type = xml, result_encoding = UTF-8, ",
		ASR_RES_PATH,
		SAMPLE_RATE_16K,
		GRM_BUILD_PATH,
		udata->grammar_id
		);
	demo_mic(asr_params);
	return 0;
}

//////注意，此处修改成函数形式
char *retString(char *string)
{
	int fd = 0;
	char strings[100] = {' '};
	const char *login_config    = "appid = 5a38785e"; //登录参数
	UserData asr_data;
	int ret                     = 0 ;
	char c;
	char *str = NULL;
	if ((pFile = fopen("./record.log", "a+")) == NULL)
	{
		bzero(str1,sizeof(str1));
		sprintf(str1,"error open file");
		write_log(pFile,str1);
		return 0;
	}
	ret = MSPLogin(NULL, NULL, login_config); //第一个参数为用户名，第二个参数为密码，传NULL即可，第三个参数是登录参数
	if (MSP_SUCCESS != ret) {
		bzero(str1,sizeof(str1));
		sprintf(str1,"登录失败：%d\n", ret);
		write_log(pFile,str1);
		goto exit;
	}
	memset(&asr_data, 0, sizeof(UserData));
	bzero(str1,sizeof(str1));
	sprintf(str1,"构建离线识别语法网络...\n");
	printf("test, %s\n",str1);
	write_log(pFile,"构建离线识别语法网络...\n");
	ret = build_grammar(&asr_data);  //第一次使用某语法进行识别，需要先构建语法网络，获取语法ID，之后使用此语法进行识别，无需再次构建
	if (MSP_SUCCESS != ret) {
		bzero(str1,sizeof(str1));
		sprintf(str1,"构建语法调用失败！\n");
		write_log(pFile,str1);
		goto exit;
	}
	while (1 != asr_data.build_fini)
		usleep(300 * 1000);
	if (MSP_SUCCESS != asr_data.errcode)
		goto exit;
	bzero(str1,sizeof(str1));
	sprintf(str1,"离线识别语法网络构建完成，开始识别...\n");
	write_log(pFile,str1);
	bzero(str1,sizeof(str1));
	sprintf(str1,"更新离线语法词典...\n");
	write_log(pFile,str1);
	while (1 != asr_data.update_fini)
		usleep(300 * 1000);
	if (MSP_SUCCESS != asr_data.errcode)
		goto exit;
	bzero(str1,sizeof(str1));
	sprintf(str1,"更新离线语法词典完成，开始识别...\n");
	write_log(pFile,str1);
	ret = run_asr(&asr_data);
	if (MSP_SUCCESS != ret || string == NULL) {
		bzero(str1,sizeof(str1));
		strcpy(string,"\0");
		sprintf(str1,"离线语法识别出错: %d \n", ret);
		write_log(pFile,str1);
		goto exit;
	}

exit:
	MSPLogout();
	fd  = open("./result.txt",O_RDWR);
	read(fd,strings,sizeof(strings));
	strings[strlen(strings) + 1] = '\0';
	return strings;
}
