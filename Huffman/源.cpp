#include"scan.h"
#include"Huffman.h"
using namespace std;
int main()
{
	string ifile("Source core.txt");
	string ofile("HFM core.txt");
	scan a;
	a.run(ifile);//ɨ���ļ���ͳ����ĸƵ��
	Huffman b(a.tmp);//������������
	b.encode(ifile,ofile);//����
	b.decode(ofile,"decode.txt");
	system("pause");
	return 0;
}