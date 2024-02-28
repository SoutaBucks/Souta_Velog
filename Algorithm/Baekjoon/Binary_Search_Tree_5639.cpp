#include <iostream>
#include <vector>
#include <list>

using std::cin;
using std::cout;
using std::vector;
using std::make_pair;
using std::pair;
using std::ios;
using std::list;

vector<int> preorderIndex;
int nodeCount = 0;

struct Node {
    Node * parent;
    Node * left, * right;
    int value;
    Node(int _v): value(_v), parent(NULL), left(NULL), right(NULL) {}
};

Node * root = NULL;

void insert(int value) {
  Node * newNode = new Node(value);
  Node * here = root;

  if(root == NULL) {
    root = new Node(value);
    return;
  } else {
    while(true) {
      if(here->value < newNode->value) {
        if(here->right == NULL) {
          here->right = newNode;
          newNode->parent = here;
          break;
        }
        here = here->right;
      } else {
        if(here->left == NULL) {
          here->left = newNode;
          newNode->parent = here;
          break;
        }
        here = here->left;
      }
    }
  }
}

void makeBinaryTree() {
  int num;
  while(cin >> num) {
    preorderIndex.push_back(num);
    insert(num);
    nodeCount++;
  }
}

void showVector() {
  for(auto & i : preorderIndex)
    cout << i << "\n";
}

void solve(Node * here) {
  if(here == NULL) return;

  solve(here->left);
  solve(here->right);
  cout << here->value << "\n";
}

int main() {
  /* 아래 3문장은
   * 출력과 입력을 빠르게 하기 위해서 적는 문장이다.
   * */
  cin.tie(NULL);
  cout.tie(NULL);
  ios::sync_with_stdio(false);

  makeBinaryTree();
  solve(root);


  return 0;
}
