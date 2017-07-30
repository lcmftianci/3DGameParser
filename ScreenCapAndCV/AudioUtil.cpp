#include "stdafx.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


/*
	mixerOpen和mixerClose函数用来打开和关闭混音器设备
	mixerGetNumDevs可以确定系统中有多少混音器设备
	mixerGetDevCaps函数可以确定混音器设备的能力
	mixerGetLineInfo可以检索指定音频线路的信息
	mixerGetLineControls用于检索一个或者多个与音频线路相关的控制的通用信息
	mixerGetControlDetails用于检索与某个音频线路相关的一个控制的属性
	mixerSetControlDetails用于设置制定控制的属性。
*/