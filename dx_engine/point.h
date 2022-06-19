#pragma once
#include <string>
#include <cmath>
#include <concepts>

namespace dx_engine {
	template<typename T>
	concept Number = std::integral<T> || std::floating_point<T>;

	template<Number T>
	class point final {
	public:
		T x, y;

		constexpr std::string to_string() const{
			return "[" + std::to_string(x) + "," + std::to_string(y) + "]";
		}

		constexpr point() = default;

		constexpr point(T _x, T _y) noexcept : x(_x), y(_y) {}

		template<class X, class Y>
		constexpr point(X _x, Y _y) noexcept : x(static_cast<T>(_x)), y(static_cast<T>(_y)) {}

		template<class t>
		constexpr point(const point<t>& p) noexcept : x(static_cast<T>(p.x)), y(static_cast<T>(p.y)) {}

		constexpr point operator +() const{
			return *this;
		}

		constexpr point operator -() const{
			return{ -x, -y };
		}

		constexpr point operator +(const point& other) const{
			return{ x + other.x, y + other.y };
		}

		constexpr point operator -(const point& other) const{
			return{ x - other.x, y - other.y };
		}

		constexpr point operator *(const point& other) const{
			return{ x * other.x, y * other.y };
		}

		constexpr point operator /(const point& other) const{
			return{ x / other.x, y / other.y };
		}

		constexpr point operator %(const point& other) const{
			return{ std::fmod(x, other.x),std::fmod(y, other.y) };
		}

		template<Number t>
		constexpr point operator +(const point<t>& other) const{
			return{ x + static_cast<T>(other.x), y + static_cast<T>(other.y) };
		}

		template<Number t>
		constexpr point operator -(const point<t>& other) const{
			return{ x - static_cast<T>(other.x), y - static_cast<T>(other.y) };
		}

		template<Number t>
		constexpr point operator *(const point<t>& other) const{
			return{ x * static_cast<T>(other.x), y * static_cast<T>(other.y) };
		}

		template<Number t>
		constexpr point operator /(const point<t>& other) const{
			return{ x / static_cast<T>(other.x), y / static_cast<T>(other.y) };
		}

		template<Number t>
		constexpr point operator %(const point<t>& other) const{
			return{ std::fmod(x, other.x),std::fmod(y, other.y) };
		}

		constexpr point& operator +=(const point& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		constexpr point& operator -=(const point& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		constexpr point& operator *=(const point& other) {
			x *= other.x;
			y *= other.y;
			return *this;
		}

		constexpr point& operator /=(const point& other) {
			x /= other.x;
			y /= other.y;
			return *this;
		}

		constexpr point& operator %=(const point& other) {
			x = fmod(x, other.x);
			y = fmod(y, other.y);
			return *this;
		}

		template<Number t>
		constexpr point& operator +=(const point<t>& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		template<Number t>
		constexpr point& operator -=(const point<t>& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		template<Number t>
		constexpr point& operator *=(const point<t>& other) {
			x *= other.x;
			y *= other.y;
			return *this;
		}

		template<Number t>
		constexpr point& operator /=(const point<t>& other) {
			x /= other.x;
			y /= other.y;
			return *this;
		}

		template<Number t>
		constexpr point& operator %=(const point<t>& other) {
			x = fmod(x, other.x);
			y = fmod(y, other.y);
			return *this;
		}

		template<Number t>
		constexpr point operator +(T s) const{
			return{ x + s, y + s };
		}

		template<Number t>
		constexpr point operator -(T s) const{
			return{ x - s, y - s };
		}

		template<Number t>
		constexpr point operator *(T s) const{
			return{ x * s, y * s };
		}

		template<Number t>
		constexpr point operator /(T s) const{
			return{ static_cast<t>(x / s), static_cast<t>(y / s) };
		}

		template<Number t>
		constexpr point operator %(T s) const{
			return{ fmod(x, s),fmod(y, s) };
		}

		template<Number t>
		constexpr point& operator +=(T s) {
			x += s;
			y += s;
			return *this;
		}

		template<Number t>
		constexpr point& operator -=(T s) {
			x -= s;
			y -= s;
			return *this;
		}

		template<Number t>
		constexpr point& operator *=(T s) {
			x *= s;
			y *= s;
			return *this;
		}

		template<Number t>
		constexpr point& operator /=(T s) {
			x /= s;
			y /= s;
			return *this;
		}

		template<Number t>
		constexpr point& operator %=(T s) {
			x = fmodf(x, s);
			y = fmodf(y, s);
			return *this;
		}

		constexpr point& operator ++() {
			++x;
			++y;
			return *this;
		}

		constexpr point& operator --() {
			--x;
			--y;
			return *this;
		}

		template<Number t>
		constexpr point& operator ++(t) {
			x++;
			y++;
			return *this;
		}

		template<Number t>
		constexpr point& operator --(t) {
			x--;
			y--;
			return *this;
		}

		constexpr bool operator ==(const point& other) const{
			return (x == other.x) && (y == other.y);
		}

		constexpr bool operator !=(const point& other) const{
			return (x != other.x) || (y != other.y);
		}

		template<Number t>
		constexpr bool operator ==(const point<t>& other) const{
			return (x == other.x) && (y == other.y);
		}

		template<Number t>
		constexpr bool operator !=(const point<t>& other) const{
			return (x != other.x) || (y != other.y);
		}

		template<Number t>
		constexpr bool operator < (const point<t>& a) const{
			return x < a.x&& y < a.y;
		}

		template<Number t>
		constexpr bool operator > (const point<t>& a)const{
			return x > a.x&& y > a.y;
		}

		template<Number t>
		constexpr bool operator <= (const point<t>& a)const{
			return x <= a.x&& y <= a.y;
		}

		template<Number t>
		constexpr bool operator >= (const point<t>& a) const{
			return x >= a.x&& y >= a.y;
		}

		
	};

	template<Number T>
	class vector3 final {
	public:
		T x, y, z;

		std::string to_string() const {
			return "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
		}

		constexpr vector3() = default;

		constexpr vector3(T _x, T _y, T _z) noexcept : x(_x), y(_y), z(_z) {}

		template<class X, class Y>
		constexpr vector3(X _x, Y _y, T _z) noexcept : x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z)) {}

		template<class t>
		constexpr vector3(const vector3<t>& p) noexcept : x(static_cast<T>(p.x)), y(static_cast<T>(p.y)), z(static_cast<T>(p.z)) {}

		constexpr vector3 operator +() const {
			return *this;
		}

		constexpr vector3 operator -() const {
			return{ -x, -y, -z };
		}

		constexpr vector3 operator +(const vector3& other) const {
			return{ x + other.x, y + other.y, z + other.z };
		}

		constexpr vector3 operator -(const vector3& other) const {
			return{ x - other.x, y - other.y, z - other.z };
		}

		constexpr vector3 operator *(const vector3& other) const {
			return{ x * other.x, y * other.y, z * other.z };
		}

		constexpr vector3 operator /(const vector3& other) const {
			return{ x / other.x, y / other.y, z / other.z };
		}

		constexpr vector3 operator %(const vector3& other) const {
			return{ std::fmod(x, other.x),std::fmod(y, other.y),std::fmod(z, other.z) };
		}

		template<Number t>
		constexpr vector3 operator +(const vector3<t>& other) const {
			return{ x + static_cast<T>(other.x), y + static_cast<T>(other.y), z + static_cast<T>(other.z) };
		}

		template<Number t>
		constexpr vector3 operator -(const vector3<t>& other) const {
			return{ x - static_cast<T>(other.x), y - static_cast<T>(other.y), z - static_cast<T>(other.z) };
		}

		template<Number t>
		constexpr vector3 operator *(const vector3<t>& other) const {
			return{ x * static_cast<T>(other.x), y * static_cast<T>(other.y), z * static_cast<T>(other.z) };
		}

		template<Number t>
		constexpr vector3 operator /(const vector3<t>& other) const {
			return{ x / static_cast<T>(other.x), y / static_cast<T>(other.y), z / static_cast<T>(other.z) };
		}

		template<Number t>
		constexpr vector3 operator %(const vector3<t>& other) const {
			return{ std::fmod(x, other.x),std::fmod(y, other.y),std::fmod(z, other.z) };
		}

		constexpr vector3& operator +=(const vector3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		constexpr vector3& operator -=(const vector3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		constexpr vector3& operator *=(const vector3& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		constexpr vector3& operator /=(const vector3& other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		constexpr vector3& operator %=(const vector3& other) {
			x = fmod(x, other.x);
			y = fmod(y, other.y);
			z = fmod(z, other.z);
			return *this;
		}

		template<Number t>
		constexpr vector3& operator +=(const vector3<t>& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		template<Number t>
		constexpr vector3& operator -=(const vector3<t>& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		template<Number t>
		constexpr vector3& operator *=(const vector3<t>& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		template<Number t>
		constexpr vector3& operator /=(const vector3<t>& other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		template<Number t>
		constexpr vector3& operator %=(const vector3<t>& other) {
			x = fmod(x, other.x);
			y = fmod(y, other.y);
			z = fmod(z, other.z);
			return *this;
		}

		template<Number t>
		constexpr vector3 operator +(T s) const {
			return{ x + s, y + s, z + s };
		}

		template<Number t>
		constexpr vector3 operator -(T s) const {
			return{ x - s, y - s, z - s };
		}

		template<Number t>
		constexpr vector3 operator *(T s) const {
			return{ x * s, y * s, z * s };
		}

		template<Number t>
		constexpr vector3 operator /(T s) const {
			return{ static_cast<t>(x / s), static_cast<t>(y / s), static_cast<t>(z / s) };
		}

		template<Number t>
		constexpr vector3 operator %(T s) const {
			return{ fmod(x, s),fmod(y, s),fmod(z, s) };
		}

		template<Number t>
		constexpr vector3& operator +=(T s) {
			x += s;
			y += s;
			z += s;
			return *this;
		}

		template<Number t>
		constexpr vector3& operator -=(T s) {
			x -= s;
			y -= s;
			z -= s;
			return *this;
		}

		template<Number t>
		constexpr vector3& operator *=(T s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		template<Number t>
		constexpr vector3& operator /=(T s) {
			x /= s;
			y /= s;
			z /= s;
			return *this;
		}

		template<Number t>
		constexpr vector3& operator %=(T s) {
			x = fmodf(x, s);
			y = fmodf(y, s);
			z = fmodf(z, s);
			return *this;
		}

		constexpr vector3& operator ++() {
			++x;
			++y;
			++z;
			return *this;
		}

		constexpr vector3& operator --() {
			--x;
			--y;
			--z;
			return *this;
		}

		template<Number t>
		constexpr vector3& operator ++(t) {
			x++;
			y++;
			z++;
			return *this;
		}

		template<Number t>
		constexpr vector3& operator --(t) {
			x--;
			y--;
			z--;
			return *this;
		}

		constexpr bool operator ==(const vector3& other) const {
			return (x == other.x) && (y == other.y) && (z == other.z);
		}

		constexpr bool operator !=(const vector3& other) const {
			return (x != other.x) || (y != other.y) || (z == other.z);
		}

		template<Number t>
		constexpr bool operator ==(const vector3<t>& other) const {
			return (x == other.x) && (y == other.y) && (z == other.z);
		}

		template<Number t>
		constexpr bool operator !=(const vector3<t>& other) const {
			return (x != other.x) || (y != other.y || (z != other.z));
		}

		template<Number t>
		constexpr bool operator < (const vector3<t>& a) const {
			return x < a.x && y < a.y && z < a.z;
		}

		template<Number t> 
		constexpr bool operator > (const vector3<t>& a)const {
			return x > a.x && y > a.y && z > a.z;
		}

		template<Number t>
		constexpr bool operator <= (const vector3<t>& a)const {
			return x <= a.x && y <= a.y && z <= a.z;
		}

		template<Number t>
		constexpr bool operator >= (const vector3<t>& a) const {
			return x >= a.x && y >= a.y && z >= a.z;
		}


	};
}