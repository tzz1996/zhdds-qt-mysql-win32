#include <iostream>
#include <pthread.h> //���߳���ز���ͷ�ļ�������ֲ�ڶ�ƽ̨
 
using namespace std;
#pragma warning(disable:4716)
 
#define NUM_THREADS 5 //�߳���
 
void* say_hello( void* args )
{
    cout << "hello say_hello()..." << endl;
} //�������ص��Ǻ���ָ�룬���ں�����Ϊ����

#if 0
int main()
{
    pthread_t tids[NUM_THREADS]; //�߳�id
    for( int i = 0; i < NUM_THREADS; ++i )
    {
        int ret = pthread_create( &tids[i], NULL, say_hello, NULL ); //�������������߳�id���̲߳������߳����к�������ʼ��ַ�����к����Ĳ���
        if( ret != 0 ) //�����̳߳ɹ�����0
        {
            cout << "pthread_create error:error_code=" << ret << endl;
        }
		cout << "hello main()..." << endl;
    }
    pthread_exit(NULL); //�ȴ������߳��˳��󣬽��̲Ž������������ǿ�ƽ������̴߳���δ��ֹ��״̬
}
#endif
