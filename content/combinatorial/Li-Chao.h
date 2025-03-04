/**
 * Author: Arjun P
 * Date: 2019-12-19
 * License: CC0
 * Description: Maintain a set of functions (only adding functions) and query minimum at a point.
 * Time: $O(n \log n)$
 */
int n, tree[1 << 16]; // set limits correctly
int eval(int f, int x); // evaluate f(x)
// Add func f to set which crosses every other func atmost once
void update(int f, int root = 1, int s = 1, int e = n) {
  int mid = (s + e)/2;
  bool lless = eval(f, s) < eval(tree[root], s);
  bool mless = eval(f, mid) < eval(tree[root], mid);
  if (mless) swap(f, tree[root]);
  if (s == e) return; 
  if (lless != mless) update(f, 2*root, s, mid); 
  else update(f, 2*root + 1, mid + 1, e);
}
// Evaluate mininum at x over all functions.
ll query(int x, int root = 1, int s = 1, int e = n) {
  int mid = (s + e)/2; ll ans = eval(tree[root], x);
  if (s == e) return ans;
  if (x <= mid) return min(query(x, 2*root, s, mid), ans);
  return min(query(x, 2*root + 1, mid + 1, e), ans);
}
