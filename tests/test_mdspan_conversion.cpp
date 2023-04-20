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


#include <mdspan.hpp>

#include <gtest/gtest.h>

namespace stdex = MDSPAN_IMPL_STANDARD_NAMESPACE;

TEST(TestMdspanConversionConst, test_mdspan_conversion_const) {
  std::array<double, 6> a{};
  md::mdspan<double, md::extents<uint32_t, 2, 3>> s(a.data());
  ASSERT_EQ(s.data_handle(), a.data());
  __MDSPAN_OP(s, 0, 1) = 3.14;
  md::mdspan<double const, md::extents<uint64_t, 2, 3>> c_s(s);
  ASSERT_EQ((__MDSPAN_OP(c_s, 0, 1)), 3.14);
}
