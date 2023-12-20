#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// 二叉树的存储结构
typedef struct BiTNode {
	char data;				    // 数据域
	struct BiTNode* lchild;		// 左孩子指针
	struct BiTNode* rchild;		// 右孩子指针
	int flag;					// 后根遍历非递归算法会使用到
} BiTNode, *BiTree;

// 初始化二叉树
void InitBiTree(BiTree& T) {
	T = NULL;
}

// 销毁二叉树
void DestroyBiTree(BiTree& T) {
	if (T) {
		if (T->lchild) {
			DestroyBiTree(T->lchild);
		} else {
			DestroyBiTree(T->rchild);
		}
	}
	free(T);
	T = NULL;
}

// 创建二叉树
void CreateBiTree(BiTree& T) {
	char ch;
	scanf("%c", &ch);
	if (ch == '#') T = NULL;
	else {
		T = (BiTree) malloc (sizeof (BiTNode));
		if (!T) return;
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}

// 判断树是否空
bool IsBiTreeEmpty(BiTree T) {
	if (T) {
		return false;
	} else {
		return true;
	}
}

// 访问二叉树的结点内容
void VisitBiTree(BiTree T) {
	if (T) {
		printf("%c ", T->data);
	}
}

// 先根遍历递归算法
//void PreOrderTraverse(BiTree T) {
//	if(T) {
//		VisitBiTree(T);		// 访问根结点
//		PreOrderTraverse(T->lchild); // 访问左子树
//		PreOrderTraverse(T->rchild); // 访问右子树
//	}
//}

// 先根遍历非递归算法
void PreOrderTraverse(BiTree T) {
	if (!T) return;
	stack<BiTree> s;
	s.push(T);
	BiTree p;
	while (!s.empty()) {
		p = s.top();
		s.pop();
		VisitBiTree(p);
		if (p->rchild) {
			s.push(p->rchild);
		}
		if (p->lchild) {
			s.push(p->lchild);
		}
	}
}

// 中根遍历递归算法
//void InOrderTraverse(BiTree T) {
//	if(T) {
//		InOrderTraverse(T->lchild);  // 先访问左子树
//		VisitBiTree(T);			     // 访问根节点
//		InOrderTraverse(T->rchild);  // 访问右子树
//	}
//}

// 中根遍历的递归算法 1
//void InOrderTraverse(BiTree T) {
//	if(!T) return;
//	stack<BiTree> s;
//	BiTree p = T;
//	while(!s.empty() || p) {
//		if(p) {
//			s.push(p);
//			p = p->lchild;
//		} else {
//			p = s.top();
//			s.pop();
//			VisitBiTree(p);
//			p = p->rchild;
//		}
//	}
//}

// 中序遍历非递归算法 2
void InOrderTraverse(BiTree T) {
	if (!T) return;
	stack<BiTree> s;
	s.push(T);
	BiTree p;
	while (!s.empty()) {
		p = s.top();
		while (p) {
			p = p->lchild;
			s.push(p);
		}
		s.pop();
		if (!s.empty()) {
			p = s.top();
			s.pop();
			VisitBiTree(p);
			s.push(p->rchild);
		}
	}
}

// 后根遍历递归算法
//void PostOrderTraverse(BiTree T) {
//	if(T) {
//		PostOrderTraverse(T->lchild); // 访问左子树
//		PostOrderTraverse(T->rchild); // 访问右子树
//		VisitBiTree(T);				  // 访问根结点
//	}
//}

// 后根遍历非递归算法
void PostOrderTraverse(BiTree T) {
	if (!T) return;
	stack<BiTree> s;
	BiTree p = T;
	while (!s.empty() || p) {
		while (p) {
			s.push(p);
			p = p->lchild;
		}
		p = s.top();
		if (p->flag == 0) {
			p->flag = 1;
			p = p->rchild;
		} else {
			s.pop();
			VisitBiTree(p);
			p = NULL;
		}
	}
}

// 层序遍历算法
void LevelOrderTraverse(BiTree T) {
	if (!T) return;
	queue<BiTree> Q;
	Q.push(T);
	BiTree p;
	while (!Q.empty()) {
		p = Q.front();
		Q.pop();
		VisitBiTree(p);
		if (p->lchild) {
			Q.push(p->lchild);
		}
		if (p->rchild) {
			Q.push(p->rchild);
		}
	}
}

// 求二叉树的高度的递归算法
//int BiTreeHeight(BiTree T) {
//	if(!T) return 0;
//	int h1 = BiTreeHeight(T->lchild);
//	int h2 = BiTreeHeight(T->rchild);
//	return h1 > h2 ? h1+1 : h2+1;
//}

// 求二叉树高度的非递归算法
int BiTreeHeight(BiTree T) {
	if (!T) return 0;
	queue<BiTree> Q;
	Q.push(T);
	BiTree r = T;	// r 指向每层最后一个结点
	int height = 0;
	while (!Q.empty()) {
		BiTree u = Q.front();
		Q.pop();
		if (u->lchild) {
			Q.push(u->lchild);
		}
		if (u->rchild) {
			Q.push(u->rchild);
		}
		if (u == r) {
			height++;
			r = Q.back(); // r 继续指向下一层的最后一个结点
		}
	}
	return height;
}

// 求二叉树最宽宽度的算法
int BiTreeMaxWidth(BiTree T) {
	if (!T) return 0;
	queue<BiTree> Q;
	Q.push(T);
	BiTree r = T; // r 指向每一层最后一个结点
	int cnt = 0;  // cnt 为当前层次宽度
	int max = 0;  // max 为最宽宽度
	while (!Q.empty()) {
		BiTree u = Q.front();
		Q.pop();
		cnt++;
		if (u->lchild) {
			Q.push(u->lchild);
		}
		if (u->rchild) {
			Q.push(u->rchild);
		}
		if (u == r) {
			if (cnt > max) {
				max = cnt;
			}
			r = Q.back();
			cnt = 0;
		}
	}
	return max;
}
//
// 测试
// 52#3##41##6## 	键盘输入进行测试
// 		  5
//  2			4
// 	   3	 1	   6

// 先根序列:  5 2 3 4 1 6
// 中根序列:  2 3 5 1 4 6
// 后根序列:  3 2 1 6 4 5
// 层序遍历:  5 2 4 3 1 6

int main() {
	// 创建二叉树
	BiTree T;
	InitBiTree(T);
	CreateBiTree(T);

	// 测试函数
	// 测试先根序列算法
	printf("PreOrderTraverse: ");
	PreOrderTraverse(T);
	printf("\n");

	// 测试中根遍历算法
	printf("InOrderTraverse: ");
	InOrderTraverse(T);
	printf("\n");

	// 测试后根遍历算法
	printf("PostOrderTraverse: ");
	PostOrderTraverse(T);
	printf("\n");

	// 测试层序遍历算法
	printf("LevelOrderTraverse: ");
	LevelOrderTraverse(T);
	printf("\n");

	// 测试求树的高度算法
	printf("The height of the BiTree: %d\n", BiTreeHeight(T));

	// 测试求树的宽度算法
	printf("The max width of BiTree's level is: %d\n", BiTreeMaxWidth(T));

	return 0;
}
