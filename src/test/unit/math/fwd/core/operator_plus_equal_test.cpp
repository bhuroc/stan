#include <gtest/gtest.h>
#include <stan/math/fwd/core.hpp>

TEST(AgradFwdOperatorPlusEqual, Fvar) {
  using stan::agrad::fvar;

  fvar<double> a(0.5,1.0);
  fvar<double> x1(0.4,2.0);
  a += x1;
  EXPECT_FLOAT_EQ(0.5 + 0.4, a.val_);
  EXPECT_FLOAT_EQ(1.0 + 2.0, a.d_);

  fvar<double> b(0.5,1.0);
  fvar<double> x2(0.4,2.0);
  b += -x2;
  EXPECT_FLOAT_EQ(0.5 - 0.4, b.val_);
  EXPECT_FLOAT_EQ(1.0 - 2.0, b.d_);

  fvar<double> c(0.6,3.0);
  double x3(0.3);
  c += x3;
  EXPECT_FLOAT_EQ(0.6 + 0.3, c.val_);
  EXPECT_FLOAT_EQ(3.0, c.d_);

  fvar<double> d(0.5,1.0);
  fvar<double> x4(-0.4,2.0);
  d += x4;
  EXPECT_FLOAT_EQ(0.5 - 0.4, d.val_);
  EXPECT_FLOAT_EQ(1.0 + 2.0, d.d_);
}
TEST(AgradFwdOperatorPlusEqual, FvarFvarDouble) {
  using stan::agrad::fvar;

  fvar<fvar<double> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;

  x += 0.3;
  EXPECT_FLOAT_EQ(0.5 + 0.3, x.val_.val_);
  EXPECT_FLOAT_EQ(1, x.val_.d_);
  EXPECT_FLOAT_EQ(0, x.d_.val_);
  EXPECT_FLOAT_EQ(0, x.d_.d_);
}

TEST(AgradFwdOperatorPlusEqual, plus_eq_nan) {
  using stan::agrad::fvar;
  double nan = std::numeric_limits<double>::quiet_NaN();
  double a = 3.0;
  fvar<double> nan_fd = std::numeric_limits<double>::quiet_NaN();
  fvar<double> a_fd = 3.0;
  fvar<fvar<double> > nan_ffd = std::numeric_limits<double>::quiet_NaN();
  fvar<fvar<double> > a_ffd = 3.0;

  EXPECT_TRUE(boost::math::isnan( (nan_fd+=a).val()));
  EXPECT_TRUE(boost::math::isnan( (nan_fd+=a_fd).val()));
  EXPECT_TRUE(boost::math::isnan( (nan_fd+=nan).val()));
  EXPECT_TRUE(boost::math::isnan( (nan_fd+=nan_fd).val()));
  EXPECT_TRUE(boost::math::isnan( (a_fd+=nan).val()));
  EXPECT_TRUE(boost::math::isnan( (a_fd+=nan_fd).val()));

  EXPECT_TRUE(boost::math::isnan( (nan_ffd+=a).val().val()));
  EXPECT_TRUE(boost::math::isnan( (nan_ffd+=a_ffd).val().val()));
  EXPECT_TRUE(boost::math::isnan( (nan_ffd+=nan).val().val()));
  EXPECT_TRUE(boost::math::isnan( (nan_ffd+=nan_ffd).val().val()));
  EXPECT_TRUE(boost::math::isnan( (a_ffd+=nan).val().val()));
  EXPECT_TRUE(boost::math::isnan( (a_ffd+=nan_ffd).val().val()));
}
