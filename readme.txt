==========================
Hello_idl����Ӧ�ó���
==========================

�����������
------------
��Windowsƽ̨�±���������ӣ���win32Ŀ¼�¶�Ӧ��������װ�ľ���Microsoft Visual Studio�汾(��VS2005��VS2008��VS2010)���̽��б��룬����ʱ��ѡ��ͬ������ѡ��:Debug��Debug Dll��Release��Release Dll��

��Unix��Linuxƽ̨�±���������ӣ���һ���ն��л������ӳ����ļ���Ŀ¼�����������
    $ make -f make/Makefile.<architecture> [DEBUG=1] [SHAREDLIB=1]


�����������
------------
�������Ӧ�ó����ɱ�Ŀ¼��USER_QOS_PROFILES.xml�ļ����ã��������޸�����ļ��ı����ӵ���Ϊ������������QoS�ļ��������滻���QoS�ļ������ݡ�

��Windowsƽ̨����������ӳ�����������ͬһ��������������cmd���ڣ�������������ͬ�Ļ����ϸ�����һ��cmd���ڡ�����Ŀ¼�л������ӳ����ļ���Ŀ¼��Ȼ��������������
    > objs\<architecture>\Hello.exe sub
    > objs\<architecture>\Hello.exe pub

��UNIX��Linuxƽ̨������������ӳ�����������ͬһ���������������նˣ�������������ͬ�Ļ����ϸ�����һ���նˡ�����Ŀ¼�л������ӳ����ļ���Ŀ¼��Ȼ��������������

    $ objs/<architecture>/Hello sub
	hello.exe sub -v -s 1 -c 5
    $ objs/<architecture>/Hello pub
	hello.exe pub -v -s 1 -c 5



ע�⣺(windows���ܹ��汾)���뾲̬��汾ʱ����Ҫ�ڹ����ļ�������-������-����-���������������libhasp_windows.lib���ٽ��б��롣

ע�⣺(linux���ܹ��汾)���뾲̬�汾ʱ����makeĿ¼���ҵ�Makefile.common���༭���ļ�����ZHDDSLIBS = -lzhdds_czd 
       -lzhdds_kernelzd�������-lhasp_linux����ZHDDSLIBS = -lzhdds_cd -lzhdds_kerneld����Ҳ���-lhasp_linux��

*********************************************Mingw***************************************************
��Windowsƽ̨����i86Win32Mingw492�汾��
��cmd���ڣ�����ʾ����������Ŀ¼�����������У�
    > mingw32-make -f make/Makefile.i86Win32Mingw492 [DEBUG=1] [SHAREDLIB=1]

ע�⣺�������ʧ�ܣ�����Ҫ�ֹ���HelloWorld.idlת��ΪC�Ĵ��롣
