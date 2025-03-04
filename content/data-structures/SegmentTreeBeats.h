/**
 * Author: Devansh Gautam
 * Date: Unknown 
 * License: CC0
 * Source: folklore
 * Description: example below - range sum query and two range updates: $a_i \leftarrow a_i \mod x$ and $a_i \leftarrow x$
 * Status: untested
 */
#pragma once
bool break_condition() // when can we break 
// eg. (l > rr || r < ll || max_val[node] < x)
bool tag_condition(); // when can we put tag for lazy update 
// eg. (l >= ll && r <= rr && max_val[node] == min_val[node])
void modify(int node, int l, int r, int ll, int rr) {
  if (break_condition()) return;
  if (tag_condition()) { puttag(node); return; }
  pushdown(node);
  int mid = (l + r) >> 1;
  modify(node * 2, l, mid, ll, rr);
  modify(node * 2 + 1, mid + 1, r, ll ,rr);
  update();
}