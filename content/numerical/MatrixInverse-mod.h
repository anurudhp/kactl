/**
 * Author: Simon Lindholm
 * Date: 2016-12-08
 * Source: The regular matrix inverse code
 * Description: Invert matrix $A$ modulo a prime.
 * Returns rank; result is stored in $A$ unless singular (rank < n).
 * For prime powers, repeatedly set $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Time: O(n^3)
 * Status: Slightly tested
 */
#pragma once

#include "../number-theory/ModPow.h"

int matInv(vector<vector<ll>>& A) {
	int n = SZ(A); VI col(n);
	vector<vector<ll>> tmp(n, vector<ll>(n));
	REP(i,0,n) tmp[i][i] = 1, col[i] = i;

	REP(i,0,n) {
		int r = i, c = i;
		REP(j,i,n) REP(k,i,n) if (A[j][k]) {
			r = j; c = k; goto found;
		}
		return i;
found:
		A[i].swap(A[r]); tmp[i].swap(tmp[r]);
		REP(j,0,n) swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
		swap(col[i], col[c]);
		ll v = modpow(A[i][i], mod - 2);
		REP(j,i+1,n) {
			ll f = A[j][i] * v % mod;
			A[j][i] = 0;
			REP(k,i+1,n) A[j][k] = (A[j][k] - f*A[i][k]) % mod;
			REP(k,0,n) tmp[j][k] = (tmp[j][k] - f*tmp[i][k]) % mod;
		}
		REP(j,i+1,n) A[i][j] = A[i][j] * v % mod;
		REP(j,0,n) tmp[i][j] = tmp[i][j] * v % mod;
		A[i][i] = 1;
	}

	for (int i = n-1; i > 0; --i) REP(j,0,i) {
		ll v = A[j][i];
		REP(k,0,n) tmp[j][k] = (tmp[j][k] - v*tmp[i][k]) % mod;
	}

	REP(i,0,n) REP(j,0,n)
		A[col[i]][col[j]] = tmp[i][j] % mod + (tmp[i][j] < 0 ? mod : 0);
	return n;
}
