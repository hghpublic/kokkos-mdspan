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

// Only works with newer constexpr
#if defined(_MDSPAN_USE_CONSTEXPR_14) && _MDSPAN_USE_CONSTEXPR_14

constexpr std::ptrdiff_t
layout_stride_simple(int i) {
  using map_t = md::layout_stride::template mapping<
    md::extents<size_t,3>
  >;
  return map_t(md::extents<size_t,3>{}, std::array<size_t,1>{1})(i);
}

MDSPAN_STATIC_TEST(
  layout_stride_simple(0) == 0
);
MDSPAN_STATIC_TEST(
  layout_stride_simple(1) == 1
);

#endif // _MDSPAN_USE_CONSTEXPR_14
