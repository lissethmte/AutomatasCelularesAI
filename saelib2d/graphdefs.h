#pragma once
#include <functional>

struct sRGB {
	unsigned char r{ 0 };
	unsigned char g{ 0 };
	unsigned char b{ 0 };

	friend bool operator== (const sRGB& c1, const sRGB& c2);
};


struct sRGBHash {
	//template <typename T1, typename T2>
	//auto operator()(const pair<T1, T2>& p) const -> size_t {
	auto operator()(const sRGB&p) const -> size_t {
		return std::hash<unsigned char>{}(p.r) ^
			std::hash<unsigned char>{}(p.g) ^
			std::hash<unsigned char>{}(p.b);
	}
};


struct sPixel 
{
	int x{ 0 }, y{ 0 };
	sRGB color;
};

