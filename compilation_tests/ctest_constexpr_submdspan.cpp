//@HEADER
// ************************************************************************
//
//                        Kokkos v. 4.0
//       Copyright (2022) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Part of Kokkos, under the Apache License v2.0 with LLVM Exceptions.
// See https://kokkos.org/LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//@HEADER
#include "ctest_common.hpp"

#include <mdspan.hpp>

namespace stdex = MDSPAN_IMPL_STANDARD_NAMESPACE;
namespace mdex = MDSPAN_IMPL_STANDARD_NAMESPACE::MDSPAN_IMPL_PROPOSED_NAMESPACE;

// Only works with newer constexpr
#if defined(_MDSPAN_USE_CONSTEXPR_14) && _MDSPAN_USE_CONSTEXPR_14

//==============================================================================
// <editor-fold desc="1D dynamic extent ptrdiff_t submdspan"> {{{1

template<class Layout>
constexpr bool
dynamic_extent_1d() {
  int data[] = {1, 2, 3, 4, 5};
  auto s = md::mdspan<int, md::dextents<size_t,1>, Layout>(data, 5);
  int result = 0;
  for (size_t i = 0; i < s.extent(0); ++i) {
    auto ss = mdex::submdspan(s, i);
    result += __MDSPAN_OP0(ss);
  }
  // 1 + 2 + 3 + 4 + 5
  constexpr_assert_equal(15, result);
  return result == 15;
}

MDSPAN_STATIC_TEST(dynamic_extent_1d<md::layout_left>());
MDSPAN_STATIC_TEST(dynamic_extent_1d<md::layout_right>());


// </editor-fold> end 1D dynamic extent ptrdiff_t submdspan }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="1D dynamic extent all submdspan"> {{{1

template<class Layout>
constexpr bool
dynamic_extent_1d_all_slice() {
  int data[] = {1, 2, 3, 4, 5};
  auto s = md::mdspan<
    int, md::extents<size_t,md::dynamic_extent>, Layout>(data, 5);
  int result = 0;
  auto ss = mdex::submdspan(s, md::full_extent);
  for (size_t i = 0; i < s.extent(0); ++i) {
    result += __MDSPAN_OP(ss, i);
  }
  // 1 + 2 + 3 + 4 + 5
  constexpr_assert_equal(15, result);
  return result == 15;
}

MDSPAN_STATIC_TEST(dynamic_extent_1d_all_slice<md::layout_left>());
MDSPAN_STATIC_TEST(dynamic_extent_1d_all_slice<md::layout_right>());

// </editor-fold> end 1D dynamic extent all submdspan }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="1D dynamic extent pair slice"> {{{1

template<class Layout>
constexpr bool
dynamic_extent_1d_pair_full() {
  int data[] = {1, 2, 3, 4, 5};
  auto s = md::mdspan<
    int, md::extents<size_t,md::dynamic_extent>, Layout>(data, 5);
  int result = 0;
  auto ss = mdex::submdspan(s, std::pair<std::ptrdiff_t, std::ptrdiff_t>{0, 5});
  for (size_t i = 0; i < s.extent(0); ++i) {
    result += __MDSPAN_OP(ss, i);
  }
  constexpr_assert_equal(15, result);
  return result == 15;
}

MDSPAN_STATIC_TEST(dynamic_extent_1d_pair_full<md::layout_left>());
MDSPAN_STATIC_TEST(dynamic_extent_1d_pair_full<md::layout_right>());

template<class Layout>
constexpr bool
dynamic_extent_1d_pair_each() {
  int data[] = {1, 2, 3, 4, 5};
  auto s = md::mdspan<
    int, md::extents<size_t,md::dynamic_extent>, Layout>(data, 5);
  int result = 0;
  for (size_t i = 0; i < s.extent(0); ++i) {
    auto ss = mdex::submdspan(s,
      std::pair<std::ptrdiff_t, std::ptrdiff_t>{i, i+1});
    result += __MDSPAN_OP(ss, 0);
  }
  constexpr_assert_equal(15, result);
  return result == 15;
}

// MSVC ICE
#ifndef _MDSPAN_COMPILER_MSVC
MDSPAN_STATIC_TEST(dynamic_extent_1d_pair_each<md::layout_left>());
MDSPAN_STATIC_TEST(dynamic_extent_1d_pair_each<md::layout_right>());
#endif

// </editor-fold> end 1D dynamic extent pair slice submdspan }}}1
//==============================================================================

//==============================================================================
// <editor-fold desc="1D dynamic extent pair, all, ptrdiff_t slice"> {{{1

template<class Layout>
constexpr bool
dynamic_extent_1d_all_three() {
  int data[] = {1, 2, 3, 4, 5};
  auto s = md::mdspan<
    int, md::extents<size_t,md::dynamic_extent>, Layout>(data, 5);
  auto s1 = mdex::submdspan(s, std::pair<std::ptrdiff_t, std::ptrdiff_t>{0, 5});
  auto s2 = mdex::submdspan(s1, md::full_extent);
  int result = 0;
  for (size_t i = 0; i < s.extent(0); ++i) {
    auto ss = mdex::submdspan(s2, i);
    result += __MDSPAN_OP0(ss);
  }
  constexpr_assert_equal(15, result);
  return result == 15;
}

// MSVC ICE
#ifndef _MDSPAN_COMPILER_MSVC
MDSPAN_STATIC_TEST(dynamic_extent_1d_all_three<md::layout_left>());
MDSPAN_STATIC_TEST(dynamic_extent_1d_all_three<md::layout_right>());
#endif

// </editor-fold> end 1D dynamic extent pair, all, ptrdifft slice }}}1
//==============================================================================

template<class Layout>
constexpr bool
dynamic_extent_2d_idx_idx() {
  int data[] = { 1, 2, 3, 4, 5, 6 };
  auto s = md::mdspan<
    int, md::extents<size_t,md::dynamic_extent, md::dynamic_extent>, Layout>(
      data, 2, 3);
  int result = 0;
  for(size_t row = 0; row < s.extent(0); ++row) {
    for(size_t col = 0; col < s.extent(1); ++col) {
      auto ss = mdex::submdspan(s, row, col);
      result += __MDSPAN_OP0(ss);
    }
  }
  constexpr_assert_equal(21, result);
  return result == 21;
}
MDSPAN_STATIC_TEST(dynamic_extent_2d_idx_idx<md::layout_left>());
MDSPAN_STATIC_TEST(dynamic_extent_2d_idx_idx<md::layout_right>());

template<class Layout>
constexpr bool
dynamic_extent_2d_idx_all_idx() {
  int data[] = { 1, 2, 3, 4, 5, 6 };
  auto s = md::mdspan<
    int, md::extents<size_t,md::dynamic_extent, md::dynamic_extent>, Layout>(
      data, 2, 3);
  int result = 0;
  for(size_t row = 0; row < s.extent(0); ++row) {
    auto srow = mdex::submdspan(s, row, md::full_extent);
    for(size_t col = 0; col < s.extent(1); ++col) {
      auto scol = mdex::submdspan(srow, col);
      constexpr_assert_equal(__MDSPAN_OP0(scol), __MDSPAN_OP(srow, col));
      result += __MDSPAN_OP0(scol);
    }
  }
  constexpr_assert_equal(21, result);
  return result == 21;
}

// MSVC ICE
#ifndef _MDSPAN_COMPILER_MSVC
MDSPAN_STATIC_TEST(dynamic_extent_2d_idx_all_idx<md::layout_left>());
MDSPAN_STATIC_TEST(dynamic_extent_2d_idx_all_idx<md::layout_right>());
#endif

//==============================================================================

constexpr int
simple_static_submdspan_test_1(int add_to_row) {
  int data[] = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  };
  auto s = md::mdspan<int, md::extents<size_t,3, 3>>(data);
  int result = 0;
  for(int col = 0; col < 3; ++col) {
    auto scol = mdex::submdspan(s, md::full_extent, col);
    for(int row = 0; row < 3; ++row) {
      auto srow = mdex::submdspan(scol, row);
      result += __MDSPAN_OP0(srow) * (row + add_to_row);
    }
  }
  return result;
}

// MSVC ICE
#if !defined(_MDSPAN_COMPILER_MSVC) && (!defined(__GNUC__) || (__GNUC__>=6 && __GNUC_MINOR__>=4))
MDSPAN_STATIC_TEST(
  // 1 + 2 + 3 + 2*(4 + 5 + 6) + 3*(7 + 8 + 9) = 108
  simple_static_submdspan_test_1(1) == 108
);

MDSPAN_STATIC_TEST(
  // -1 - 2 - 3 + 7 + 8 + 9 = 18
  simple_static_submdspan_test_1(-1) == 18
);

MDSPAN_STATIC_TEST(
  // -1 - 2 - 3 + 7 + 8 + 9 = 18
  md::mdspan<double, md::extents<size_t,simple_static_submdspan_test_1(-1)>>{nullptr}.extent(0) == 18
);
#endif

//==============================================================================

constexpr bool
mixed_submdspan_left_test_2() {
  int data[] = {
    1, 4, 7,
    2, 5, 8,
    3, 6, 9,
    0, 0, 0,
    0, 0, 0
  };
  auto s = md::mdspan<int,
    md::extents<size_t,3, md::dynamic_extent>, md::layout_left>(data, 5);
  int result = 0;
  for(int col = 0; col < 5; ++col) {
    auto scol = mdex::submdspan(s, md::full_extent, col);
    for(int row = 0; row < 3; ++row) {
      auto srow = mdex::submdspan(scol, row);
      result += __MDSPAN_OP0(srow) * (row + 1);
    }
  }
  // 1 + 2 + 3 + 2*(4 + 5 + 6) + 3*(7 + 8 + 9)= 108
  constexpr_assert_equal(108, result);
  for(int row = 0; row < 3; ++row) {
    auto srow = mdex::submdspan(s, row, md::full_extent);
    for(int col = 0; col < 5; ++col) {
      auto scol = mdex::submdspan(srow, col);
      result += __MDSPAN_OP0(scol) * (row + 1);
    }
  }
  result /= 2;
  // 2 * (1 + 2 + 3 + 2*(4 + 5 + 6) + 3*(7 + 8 + 9)) / 2 = 108
  constexpr_assert_equal(108, result);
  return result == 108;
}

// MSVC ICE
#if !defined(_MDSPAN_COMPILER_MSVC) && (!defined(__GNUC__) || (__GNUC__>=6 && __GNUC_MINOR__>=4))
MDSPAN_STATIC_TEST(
  // 2 * (1 + 2 + 3 + 2*(4 + 5 + 6) + 3*(7 + 8 + 9)) / 2 = 108
  mixed_submdspan_left_test_2()
);
#endif

//==============================================================================

template <class Layout>
constexpr bool
mixed_submdspan_test_3() {
  int data[] = {
    1, 4, 7, 2, 5,
    8, 3, 6, 9, 0,
    0, 0, 0, 0, 0
  };
  auto s = md::mdspan<
    int, md::extents<size_t,3, md::dynamic_extent>, Layout>(data, 5);
  int result = 0;
  for(int col = 0; col < 5; ++col) {
    auto scol = mdex::submdspan(s, md::full_extent, col);
    for(int row = 0; row < 3; ++row) {
      auto srow = mdex::submdspan(scol, row);
      result += __MDSPAN_OP0(srow) * (row + 1);
    }
  }
  constexpr_assert_equal(71, result);
  for(int row = 0; row < 3; ++row) {
    auto srow = mdex::submdspan(s, row, md::full_extent);
    for(int col = 0; col < 5; ++col) {
      auto scol = mdex::submdspan(srow, col);
      result += __MDSPAN_OP0(scol) * (row + 1);
    }
  }
  result /= 2;
  // 2 * (1 + 4 + 7 + 2 + 5 + 2*(8 + 3 + 6 + 9)) / 2 = 71
  constexpr_assert_equal(71, result);
  return result == 71;
}

// MSVC ICE
#ifndef _MDSPAN_COMPILER_MSVC
MDSPAN_STATIC_TEST(
  mixed_submdspan_test_3<md::layout_right>()
);
#endif

//==============================================================================

#if defined(MDSPAN_ENABLE_EXPENSIVE_COMPILATION_TESTS) && MDSPAN_ENABLE_EXPENSIVE_COMPILATION_TESTS

template <ptrdiff_t Val, size_t Idx>
constexpr auto _repeated_ptrdiff_t = Val;
template <class T, size_t Idx>
using _repeated_with_idxs_t = T;

template <class Layout, size_t... Idxs>
constexpr bool
submdspan_single_element_stress_test_impl_2(
  std::integer_sequence<size_t, Idxs...>
) {
  using mdspan_t = md::mdspan<
    int, md::extents<size_t,_repeated_ptrdiff_t<1, Idxs>...>, Layout>;
  using dyn_mdspan_t = md::mdspan<
    int, md::extents<size_t,_repeated_ptrdiff_t<md::dynamic_extent, Idxs>...>, Layout>;
  int data[] = { 42 };
  auto s = mdspan_t(data);
  auto s_dyn = dyn_mdspan_t(data, _repeated_ptrdiff_t<1, Idxs>...);
  auto ss = mdex::submdspan(s, _repeated_ptrdiff_t<0, Idxs>...);
  auto ss_dyn = mdex::submdspan(s_dyn, _repeated_ptrdiff_t<0, Idxs>...);
  auto ss_all = mdex::submdspan(s, _repeated_with_idxs_t<md::full_extent_t, Idxs>{}...);
  auto ss_all_dyn = mdex::submdspan(s_dyn, _repeated_with_idxs_t<md::full_extent_t, Idxs>{}...);
  auto val = __MDSPAN_OP(ss_all, (_repeated_ptrdiff_t<0, Idxs>...));
  auto val_dyn = __MDSPAN_OP(ss_all_dyn, (_repeated_ptrdiff_t<0, Idxs>...));
  auto ss_pair = mdex::submdspan(s, _repeated_with_idxs_t<std::pair<ptrdiff_t, ptrdiff_t>, Idxs>{0, 1}...);
  auto ss_pair_dyn = mdex::submdspan(s_dyn, _repeated_with_idxs_t<std::pair<ptrdiff_t, ptrdiff_t>, Idxs>{0, 1}...);
  auto val_pair = __MDSPAN_OP(ss_pair, (_repeated_ptrdiff_t<0, Idxs>...));
  auto val_pair_dyn = __MDSPAN_OP(ss_pair_dyn, (_repeated_ptrdiff_t<0, Idxs>...));
  constexpr_assert_equal(42, ss());
  constexpr_assert_equal(42, ss_dyn());
  constexpr_assert_equal(42, val);
  constexpr_assert_equal(42, val_dyn);
  constexpr_assert_equal(42, val_pair);
  constexpr_assert_equal(42, val_pair_dyn);
  return __MDSPAN_OP0(ss) == 42 && __MDSPAN_OP0(ss_dyn) == 42 && val == 42 && val_dyn == 42 && val_pair == 42 && val_pair_dyn == 42;
}

template <class Layout, size_t... Sizes>
constexpr bool
submdspan_single_element_stress_test_impl_1(
  std::integer_sequence<size_t, Sizes...>
) {
  return _MDSPAN_FOLD_AND(
    submdspan_single_element_stress_test_impl_2<Layout>(
      std::make_index_sequence<Sizes>{}
    ) /* && ... */
  );
}

template <class Layout, size_t N>
constexpr bool
submdspan_single_element_stress_test() {
  return submdspan_single_element_stress_test_impl_1<Layout>(
    std::make_index_sequence<N+2>{}
  );
}

MDSPAN_STATIC_TEST(
  submdspan_single_element_stress_test<md::layout_left, 15>()
);
MDSPAN_STATIC_TEST(
  submdspan_single_element_stress_test<md::layout_right, 15>()
);

#endif // MDSPAN_DISABLE_EXPENSIVE_COMPILATION_TESTS

#endif // defined(_MDSPAN_USE_CONSTEXPR_14) && _MDSPAN_USE_CONSTEXPR_14
