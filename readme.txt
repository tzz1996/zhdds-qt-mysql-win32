==========================
Hello_idl例子应用程序
==========================

编译这个例子
------------
在Windows平台下编译这个例子，打开win32目录下对应您机器安装的具体Microsoft Visual Studio版本(有VS2005、VS2008、VS2010)工程进行编译，编译时可选择不同的配置选项:Debug、Debug Dll、Release、Release Dll。

在Unix、Linux平台下编译这个例子，打开一个终端切换到例子程序文件夹目录运行下面命令：
    $ make -f make/Makefile.<architecture> [DEBUG=1] [SHAREDLIB=1]


运行这个例子
------------
这个例子应用程序由本目录下USER_QOS_PROFILES.xml文件配置，您可以修改这个文件改变例子的行为，或者用其他QoS文件的内容替换这个QoS文件的内容。

在Windows平台运行这个例子程序，您可以在同一机器上启动两个cmd窗口，或者在两个不同的机器上各启用一个cmd窗口。并把目录切换到例子程序文件夹目录，然后运行下面的命令：
    > objs\<architecture>\Hello.exe sub
    > objs\<architecture>\Hello.exe pub

在UNIX、Linux平台上运行这个例子程序，您可以在同一机器上启动两个终端，或者在两个不同的机器上各启用一个终端。并把目录切换到例子程序文件夹目录，然后运行下面的命令：

    $ objs/<architecture>/Hello sub
	hello.exe sub -v -s 1 -c 5
    $ objs/<architecture>/Hello pub
	hello.exe pub -v -s 1 -c 5



注意：(windows加密狗版本)编译静态库版本时，需要在工程文件的属性-链接器-输入-附加依赖项中添加libhasp_windows.lib，再进行编译。

注意：(linux加密狗版本)编译静态版本时，在make目录中找到Makefile.common，编辑此文件，在ZHDDSLIBS = -lzhdds_czd 
       -lzhdds_kernelzd后面添加-lhasp_linux；在ZHDDSLIBS = -lzhdds_cd -lzhdds_kerneld后面也添加-lhasp_linux。

*********************************************Mingw***************************************************
在Windows平台编译i86Win32Mingw492版本：
打开cmd窗口，进入示例程序所在目录，运行命令行：
    > mingw32-make -f make/Makefile.i86Win32Mingw492 [DEBUG=1] [SHAREDLIB=1]

注意：如果编译失败，则需要手工将HelloWorld.idl转换为C的代码。
