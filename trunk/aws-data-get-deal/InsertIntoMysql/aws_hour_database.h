//�����Զ�վСʱ���ݼ�¼�����ݿ⽻���Ĳ���
#include "aws_hour_record.h"

//���ļ��л�ȡ����
bool get_aws_hrcods_from_file(const CTime &curtime,	std::vector<aws_hour_record> &records);


// ���ö�ȡʱ��
void SetLastReadTime(CTime last_time);
//��ȡ����ʱ��
void GetLastReadTime(CTime &last_time);

//����������ݿ�ľ������
void deal_all_proc();