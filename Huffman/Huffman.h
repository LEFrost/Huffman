#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "TreeNode.h"
#include <map>
#include <utility>
#include<sstream>
#include<stack>
#include "Sort.h"
using namespace std;
class Huffman
{
	TreeNode *root;
	map<char, TreeNode*> leaf;//���Ҷ�ӽڵ��rongqi
	void MergeTree(TreeNode* l,TreeNode* r,TreeNode* p)
	{
		p->left = l;
		p->right = r;
		p->data = ' ';
		p->info = l->info + r->info;
		l->parent = p;
		r->parent = p;
	}
public:
	Huffman(map<char,int> a)
	{
		//////////////////////����
		Sort m;
		int n = a.size();
		TreeNode* p, *l, *r;
		TreeNode* list = new TreeNode[n];
		map<char, int>::iterator it = a.begin();
		for (int i = 0; i != n; ++i)
		{
			list[i].data = it->first;
			list[i].info = it->second;
			list[i].parent=list[i].left = list[i].right = NULL;
			m.insert(list+i);
			pair<char, TreeNode*> k(it->first,list+i);
			leaf.insert(k);//��Ҷ�ӽڵ�ָ�����map�������������
			++it;
		}
		for (int i = 0; i < n - 1; ++i)
		{
			p = new TreeNode;
			l = m.pop();
			r = m.pop();
			MergeTree(l, r, p);
			m.insert(p);
			root = p;
		}
	}
	void encode(string file,string file1)//����
	{
		map<char, TreeNode*>::iterator it;
		ifstream in(file.c_str(), ifstream::in);
		ofstream out(file1.c_str(), ifstream::out);
		string word;
		while (getline(in, word))//������
		{
			istringstream line(word);
			string character;
			while (line >> character)//���뵥��
			{
				for (int i = 0; i != character.size(); ++i)//������ĸ
				{
					it = leaf.find(character[i]);
					findfather(it->second, out);
				}
				out << " ";
			}
			out << endl;
		}
	}
	void findfather(TreeNode *p,ofstream& out)//��Ҷ�ӽڵ�����׷�ݣ�������ĸ����
	{
		TreeNode* q = p;
		stack<int> astack;
		while (q->parent != NULL)
		{
			q = q->parent;
			if (q->left == p)
				astack.push(0);
			else
				astack.push(1);
			p = p->parent;
		}
		while (!astack.empty())
		{
			out << astack.top();
			astack.pop();
		}
	}
	void decode(string file, string file1)//����
	{
		ifstream in(file.c_str(), ifstream::in);
		ofstream out(file1.c_str(), ifstream::out);
		string word;
		while (getline(in,word))//������
		{
			istringstream line(word);
			string character;
			while (line >> character)//���뵥��
			{
				TreeNode* p = root;
				for (int i = 0; i != character.size(); ++i)//��������
				{
					if (character[i] == '0')
						p = p->left;
					else
						p = p->right;
					if (p->data!= ' ')
					{
						out << p->data;
						p = root;
					}
				}
				out << " ";
			}
			out << endl;
		}
	}
};
#endif