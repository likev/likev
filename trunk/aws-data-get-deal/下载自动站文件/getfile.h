#include <comn.h>
#include <afxinet.h>

//��ʾ�û�����վ�� ��ʼʱ�� ����ʱ��
//Ȼ�����������ļ�
void getfile(void);

//������Ҫ���ļ� ��������ǰĿ¼webfiles�ļ�����
//����ʱ������Ϊ [begin,end]
void get_files_by_time(std::string station_num, CTime begin,CTime end);