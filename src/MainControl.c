#include "./aitalk/asr_record/include/msp_cmn.h"
#include "./aitalk/asr_record/include/msp_errors.h"
#include "./aitalk/asr_record/include/qisr.h"
#include "./aitalk/asr_record/speech_recognizer.h"
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
typedef struct operate {
  char operator[10];
  char object[10];
} OP;
/*************************************************************
function:主控功能，进行声卡的监听，并对命令进行解析，送至下层，使用local_command函数
                                处理命令传送的指令
***************************************************************/
int main() {
  int ret1 = 0;
  char ret[20] = " ";
  OP *op = (OP *)(malloc(sizeof(OP)));
  while (1) {
    ret = wake_string(ret);
    split(ret, op);
    ret1 = local_command(op->operator, op->object);
    bzero(op, sizeof(op));
    ret1 = 0;
  }
  return 0;
}
