#pragma once

namespace std
{
	template<class T, T v>
	struct integral_constant {
		static constexpr T value = v;
		using value_type = T;
		using type = integral_constant; // using injected-class-name
		constexpr operator value_type() const noexcept { return value; }
		constexpr value_type operator()() const noexcept { return value; } //since c++14
	};
	struct false_type {
		static constexpr bool value = false;
		constexpr operator bool() const noexcept { return false; }
		constexpr bool operator()() const noexcept { return false; } //since c++14
	};
	struct true_type {
		static constexpr bool value = true;
		constexpr operator bool() const noexcept { return true; }
		constexpr bool operator()() const noexcept { return true; } //since c++14
	};
	template<class T, class U>
	struct is_same : false_type {};
	
	template<class T>
	struct is_same<T, T> : true_type {};	
} // namespace type_traits
