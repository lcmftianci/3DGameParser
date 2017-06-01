#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
//a.txt
//ac, dg, er, eds, d, df
//14, 5f, 56, ff3, fdff, fsd
//15, gg, 34, dfd, 34e, er
//35, re, 434, rer, 34, er

//b.txt
//12, wd, wr, sd, sf, 34.5676
//23, er, df, xc, xc, 12.234

//标准输入输出函数%[]和%n说明符的使用方法
//scanf fscanf, 均从第一个非空格的可显示字符开始读起！
//标准输入输出函数scanf具有相对较多的转换说明符，它常常作为入门级函数出现在各种教材中。但奇怪的是，[]和n这两种都为c89 / c99所规定的标准说明符却鲜少在大多数教材中出现。虽然[]和n说明符的使用频率不及其它说明符，但两者在程序设计中的作用仍然不可小视，尤其是[]说明符。
//众所周之，scanf以空白字符为定界符，但如果输入的字符串是以其它字符为定界符的，那怎么办？[]就是专门处理这个问题的转换说明符。[]转换说明符可以通过两种方式产生结果字符集，如果第一个[字符右边没有抑扬符（^），那么处于[]之间的字符就是结果字符集，不在其中的可输入字符都作为定界符；如果左边[符号紧靠一个抑扬符（^），那么意义相反，^和]之间的字符是定界符，其余可输入字符是结果字符集。
//在使用[]说明符之前，得先明白两个概念：一是扫描列表。扫描列表（scanlist）指的是包含在[和]两个字符之间除紧靠左边[字符的抑扬符之外的字符，例如：
//scanf("%[abcd]", ptr);
//abcd组成扫描列表。二是扫描字符集（scanset）。扫描字符集指的是结果字符集，例如上面的例子，结果字符集就是abcd。如果输入一个字符串“cbadkjf”，那么ptr得到的字符串是cbad，kjf三个字符都属于定界符，输入到k字符时输入字符串被截断，kjf三个字符被留在stdin里面。如果带有抑扬符，例如：
//scanf("%[^abcd]", ptr);
//扫描列表仍然是abcd，但扫描字符集是除abcd外的可输入字符。如果输入字符串“jksferakjjdf”，ptr得到的字符串是“jksfer”。如果想限制输入字符串的字符数量，可以象s说明符那样，在[]前面使用位域，例如：
//scanf("[^abcd]", ptr);
//这样结果字符串最多只能包含10个字符（除'\0'字符外）。
//[符号可以作为扫描列表中的一个成员，但]字符除紧贴最左边的[字符或抑扬符两种情况外，其余情况下都不会被看作扫描列表的成员。例如“%[]abcd]”或者“%[^]abcd]”，上述两种情况下]字符属于扫描列表的成员，但如果是“%[ab]cd]”，中间的]字符不会被看作扫描列表的成员，而且输入输出的结果会是乱七八糟的。
//对于减号 - ，只有在紧贴[字符或抑扬字符以及作为扫描列表最后一个成员时， - 字符才会被视为扫描列表的成员。c标准把其余情况规定为编译器相关的。大多数编译器把这种情况的减号定义为连字符，例如：
//scanf("%[a-zA-Z]", ptr);
//那么扫描列表由大小写各26个字母组成。少数编译器仍旧把这种情况下的减号视为扫描列表成员。
//fscanf(fd, "%*[^\n]\n");//%*是虚读，没有存，只是让指针跳过了这个变量！
//%n说明符输出有效字符数量，%n在scanf和printf中都可使用。与%n相对应的形参是一个int类型的指针，%n不影响scanf和printf的返回值。例如：
//scanf("%d %d%n", &i, &j, &k);
//如果输入434 6434，则k等于8，而scanf的返回值仍然为2。又如：
//scanf("%c%n", &ch, &k);
//输入“sbcdefdg”后，k等于1，而不是8，因为%c只取一个字符，%n输出的是有效字符数量。
//%n用在printf函数里，表示输出的字符数量，例如：
//printf("i=%d, j=%d\n%n", i, j, &k);
//在i = 343、j = 123的情况下，k = 12，同时%n不影响printf的返回值，其返回值仍然为12，而不是14。
//== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
//这个用法是在H264 jm82参考代码上看到的，用来从解码器参数配置文件中读取配置参数，代码如下：
//// read the decoder configuration file
//if ((fd = fopen(config_filename, "r")) == NULL)
//{
//	snprintf(errortext, ET_SIZE, "Error: Control file %s not found\n", config_filename);
//	error(errortext, 300);
//}
//fscanf(fd, "%s", inp->infile);                // H.26L compressed input bitsream
//fscanf(fd, "%*[^\n]");
//fscanf(fd, "%s", inp->outfile);               // YUV 4:2:2 input format
//fscanf(fd, "%*[^\n]");
//fscanf(fd, "%s", inp->reffile);               // reference file
//fscanf(fd, "%*[^\n]");
//对应的配置文件内容如下：
//test.264                 ........H.26L coded bitstream
//test_dec.yuv             ........Output file, YUV 4:2 : 0 format
//test_rec.yuv             ........Ref sequence(for SNR)
//通过这种方式
//inp->infile = "test.264"
//inp->outfile = "test_dec.yuv"
//inp->reffile = "test_rec.yuv"
//而相应的配置文件中的一些注释则不会被读入，这是相当简便的用法，比起通过严格约定注释符并进行一个字符一个字符来解析，这种方式简单了许多！值得借鉴

int main(void)
{
	vector<string> mstr;
	FILE *fp = fopen("a.txt", "rt");
	while (!feof(fp))
	/*char chA[2048];
	char chB[2048], chC[2048], chD[2048], chE[2049], chF[2048];*/
	//while(EOF != fscanf(fp, "%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000]", chA, chB, chC, chD, chE, chF))
	{
		char chA[2048];
		char chB[2048], chC[2048], chD[2048], chE[2049], chF[2048];
		/************************************************************************/
		/* fscanf出错。 在d.dat中有数据430301wang56.345,用fscanf(fp,"%d%s%f",&a,name,&f)读 结果s为wang56.345  
		   fscanf(fp, "%*d%[a-zA-Z]%f", name, &f);  //%*d略过第一个数 第二个扫描提取字符 剩下的我不用解释了吧
		   
		   #include <stdio.h>
		   main()
		   {
		   int i;
		   unsigned int j;
		   char s[5];
		   fscanf(stdin, "%d %x %5[a-z] %*s %f", &i, &j, s, s);
		   printf("%d %d %s \n", i, j, s);
		   }

		   执行：
		   10 0x1b aaaaaaaaa bbbbbbbbbb //从键盘输入
		   10 27 aaaaa
		   */
		/************************************************************************/


		//从一个流中执行格式化输入,fscanf遇到空格和换行时结束，注意空格时也结束

		/*fscanf(fp, "%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z]", chA, chB, chC, chD, chE, chF);
		printf("%s\n", chA);
		printf("%s\n", chB);
		printf("%s\n", chC);
		printf("%s\n", chD);
		printf("%s\n", chE);
		printf("%s\n", chF);*/


		/*	int nAge = 0;
			double dGrade = 0.0;
			fscanf(fp, "%d,%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%lf", &nAge, chB, chC, chD, chE, &dGrade);
			printf("%d\n", nAge);
			printf("%s\n", chB);
			printf("%s\n", chC);
			printf("%s\n", chD);
			printf("%s\n", chE);
			printf("%f\n", dGrade);*/

		/*fscanf(stream, "%[^\n]%*c", line)*/

		//老是读取一行数据
		//FILE *stream;
		//char line[80];

		//while ((fscanf(stream, "%[^\n]", line)) != EOF)
		//{
		//	printf("Line = %s \n", line);
		//}
		//The following code example demonstrates the second method above to work around this problem:
		//FILE *stream;
		//char line[80];

		//while ((fscanf(stream, "%[^\n]", line)) != EOF)
		//{
		//	fgetc(stream);    // Reads in '\n' character and moves file
		//					  // stream past delimiting character
		//	printf("Line = %s \n", line);
		//}

		int nAge = 0;
		double dGrade = 0.0;
		//fscanf(fp, "%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z],%[a-zA-Z]", chA, chB, chC, chD, chE, chF);
		//fscanf(fp, "%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000]", chA, chB, chC, chD, chE, chF);
		fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", chA, chB, chC, chD, chE, chF);
		printf("%s\n", chA);
		mstr.push_back(chA);
		printf("%s\n", chB);
		mstr.push_back(chB);
		printf("%s\n", chC);
		mstr.push_back(chC);
		printf("%s\n", chD);
		mstr.push_back(chD);
		printf("%s\n", chE);
		mstr.push_back(chE);
		printf("%s\n", chF);
		mstr.push_back(chF);

		fgetc(fp);


		//while(fscanf(fp, "%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000],%[a-zA-Z0-10000]", chA, chB, chC, chD, chE, chF) != EOF)
	/*	{
			printf("%s\n", chA);
			printf("%s\n", chB);
			printf("%s\n", chC);
			printf("%s\n", chD);
			printf("%s\n", chE);
			printf("%s\n", chF);
		}
*/
	}
	system("pause");
	return 0;
}