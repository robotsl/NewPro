#include "./include/msp_cmn.h"
#include "./include/msp_errors.h"
#include "./include/qisr.h"
#include "./speech_recognizer.h"
#include "./asr_record/asr_record_sample.h"
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
typedef struct operate {
    char operators[10];
    char object[10];
} OP;
/*************************************************************
function:���ع��ܣ����������ļ���������������н����������²㣬ʹ��local_command����
                                ��������͵�ָ��
***************************************************************/
int main() {
    int ret1 = 0;
    char ret[20] = " ";
    OP *op = (OP *)(malloc(sizeof(OP)));
    while (1) {
        ret = wake_string(ret);
        split(ret, op);
        ret1 = local_command(op->operators, op->object);
        bzero(op, sizeof(op));
        ret1 = 0;
    }
    return 0;
}
