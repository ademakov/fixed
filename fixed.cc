#include <cstdint>
#include <cstdio>

template <unsigned decimals = 12>
struct fixed
{
	using u128 = unsigned __int128;

	static constexpr std::uint64_t div() {
		std::uint64_t d = 1;
		for (unsigned i = 0; i < decimals; i++)
			d *= 10;
		return d;
	}

	std::uint64_t w, f; // whole and fractional parts

	fixed(std::uint64_t w_, std::uint64_t f_) : w(w_), f(f_)
	{
	}

	friend fixed operator+(const fixed a, const fixed b)
	{
		auto f = a.f + b.f;
		return fixed(a.w + b.w + (f < a.f), f);
	}

	friend fixed operator*(const fixed a, const fixed b)
	{
		auto wf = u128(a.w) * b.f + u128(a.f) * b.w + u128(a.f) * b.f / div();
		return fixed(a.w * b.w + wf / div(), wf % div());
	}

	friend fixed operator/(const fixed a, const fixed b)
	{
		auto ax = u128(a.w) * div() + a.f;
		auto bx = u128(b.w) * div() + b.f;
		std::uint64_t w = ax / bx;
		return fixed(w, (ax - w * bx) * div() / bx);
	}
};

#if 1

int
main(int argc, char **argv)
{
	fixed<3> a(1024, 0);	// 1024
	fixed<3> b(1, 1);	// 1.001
	fixed<3> c = a * b;
	printf("%lu.%03lu\n", c.w, c.f);

	uint64_t million = 1000ul * 1000;	// 10^6
	uint64_t billion = 1000ul * million;	// 10^9
	uint64_t trillion = 1000ul * billion;	// 10^12

	fixed<12> x(18ull * 1000 * trillion, 0);
	fixed<12> y(0, billion); // 0.001
	fixed<12> z = x / y;
	printf("%lu.%012lu\n", z.w, z.f);

	fixed<12> xx(18ull * million, 0);
	fixed<12> yy(18ull * 1000 * 1000 * trillion, 0);
	fixed<12> zz = xx / yy;
	printf("%lu.%012lu\n", zz.w, zz.f);

	uint64_t large = 180ull * trillion;
	fixed<12> xxx(large, 0);
	fixed<12> yyy(large + 1, 0);
	fixed<12> zzz = xxx / yyy;
	printf("%lu.%012lu\n", zzz.w, zzz.f);

	return 0;
}

#else

fixed<> add(const fixed<> a, const fixed<> b)
{
    return a + b;
}

fixed<> mul(const fixed<> a, const fixed<> b)
{
    return a * b;
}

fixed<> div(const fixed<> a, const fixed<> b)
{
    return a / b;
}

#endif
