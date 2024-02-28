#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::make_pair;
using std::pair;
using std::ios;

vector<pair<int, int>> tree(27, make_pair(-1, -1));
int nodeCount;

// Int -> Char
int charToInt(char c) {
  int result = c - 'A';
  if(c == '.')  result = -1;  // -1은 없는 것을 의미한다
  return result;
}

// Char -> Int
char intToChar(int n) {
  return static_cast<char>(n + 'A');
}

// Binary Tree를 만드는 함수
void makeBinaryTree() {
  // 알파벳을 숫자로 변형해서 Vector에 넣는 방법
  int nodeNum, leftChildNum, rightChildNum;
  char node, leftChild, rightChild;

  cin >> nodeCount;
  for(int i = 0; i < nodeCount; i++) {
    cin >> node >> leftChild >> rightChild;

    nodeNum = charToInt(node);
    leftChildNum = charToInt(leftChild);
    rightChildNum = charToInt(rightChild);

    tree[nodeNum].first = leftChildNum;
    tree[nodeNum].second = rightChildNum;
  }
}

void showBinaryTree() {
  for(int i = 0; i < nodeCount; i++)
    cout << tree[i].first << " " << tree[i].second << "\n";
}

// Leaf Node인지 확인하는 함수
bool isLeaf(int index) {
  return (tree[index].first == -1) and (tree[index].second == -1);
}

void preorderTraversal(int index) {
  if(index == -1) return;

  cout << intToChar(index);
  preorderTraversal(tree[index].first);
  preorderTraversal(tree[index].second);
}

void inorderTraversal(int index) {
  if(index == -1) return;

  inorderTraversal(tree[index].first);
  cout << intToChar(index);
  inorderTraversal(tree[index].second);
}

void postorderTraversal(int index) {
  if(index == -1) return;

  postorderTraversal(tree[index].first);
  postorderTraversal(tree[index].second);
  cout << intToChar(index);

}

void solve() {
  preorderTraversal(0);
  cout << "\n";
  inorderTraversal(0);
  cout << "\n";
  postorderTraversal(0);
  cout << "\n";
}

int main() {
  /* 아래 3문장은
   * 출력과 입력을 빠르게 하기 위해서 적는 문장이다.
   * */
  cin.tie(NULL);
  cout.tie(NULL);
  ios::sync_with_stdio(false);

  makeBinaryTree();
  //showBinaryTree();
  solve();

  return 0;
}
