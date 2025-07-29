//
//  macros.h
//  my_project
//
//  Created by Hoang Gia Bao on 17/7/25.
//
#pragma once

// ===== BASIC FOR LOOPS =====
#define FOR(i, a, b)         for (int i = (a); i < (b); ++i)         // from a to b-1
#define FOR_DESC(i, a, b)    for (int i = (a); i >= (b); --i)        // from a down to b
#define FOR_EACH(i, n)       for (int i = 0; i < (n); ++i)           // from 0 to n-1
#define FOR_EACH_DESC(i, n)  for (int i = (n) - 1; i >= 0; --i)      // from n-1 down to 0

// ===== 2D FOR LOOPS (for matrix traversal) =====
#define FOR_2D(i, j, rows, cols)  for (int i = 0; i < (rows); ++i) for (int j = 0; j < (cols); ++j)

// Epsilon để so sánh số thực
const double EPS = 1e-9;

