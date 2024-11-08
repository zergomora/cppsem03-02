#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>

#define UNUSED(v) ((void)(v));

template<typename T, size_t ... Args>
class Grid;

template<typename T, size_t N>
class Grid<T, N> {
private:
    T nvector[N];
public:
    Grid(const T& t) {
        std::fill(nvector, nvector+N, t);
    }

    Grid() {
        std::fill(nvector, nvector+N, T());
    }

    Grid(Grid<T> const &) = delete;
    Grid(Grid<T>&&) = delete;
    Grid<T>& operator=(Grid<T>&) = delete;
    Grid<T>& operator=(Grid<T>&&) = delete;

    T operator[](size_t i) const { return nvector[i]; }
    T& operator[](size_t i) { return nvector[i]; }

    T operator()(size_t i) const { return nvector[i]; }
    T& operator()(size_t i) { return nvector[i]; }

    size_t get_size() { return N; }

};

template <typename T, size_t N, size_t ... Args>
class Grid<T, N, Args ...> {
private:
    Grid<T, Args...> narray[N];
    size_t heights[sizeof...(Args) + 1];
public:
    Grid(const T& t) {
        std::fill(narray, narray+N, Grid<T, Args...>(t));

        heights[0] = N;
        size_t index = 1;
        (..., (heights[index++] = Args));
    }

    Grid() {
        std::fill(narray, narray+N, Grid<T, Args...>());

        heights[0] = N;
        size_t index = 1;
        (..., (heights[index++] = Args));
    }

    Grid<T, Args...> operator[](size_t i) const { return narray[i]; }
    Grid<T, Args...>& operator[](size_t i) { return narray[i]; }

    template<typename... I>
    auto operator()(size_t i, I... left) const { return narray[i](left...); }
    template<typename... I>
    auto& operator()(size_t i, I... left) { return narray[i](left...); }

    size_t get_size(size_t i) { return heights[i]; }

};

int main() {

	Grid<float, 3, 2> g(0.0f);
	assert(3 == g.get_size(0));
	assert(2 == g.get_size(1));

    std::cout << "Operator of indexing simple test: " << g[1][1] << std::endl;
 
	for (size_t y_idx = 0; y_idx != g.get_size(0); ++y_idx) {
		for (size_t x_idx = 0; x_idx != g.get_size(1); ++x_idx) {
			assert(0.0f == g[y_idx][x_idx]);
		}
	}

	for (size_t y_idx = 0; y_idx != g.get_size(0); ++y_idx) {
		for (size_t x_idx = 0; x_idx != g.get_size(1); ++x_idx) {
			g[y_idx][x_idx] = 1.0f;
		}
	}

	for (size_t y_idx = 0; y_idx != g.get_size(0); ++y_idx) {
		for (size_t x_idx = 0; x_idx != g.get_size(1); ++x_idx) {
			assert(1.0f == g(y_idx, x_idx));
		}
	}

	Grid<float, 2, 3, 4> g3(1.0f);
	assert(1.0f == g3(1, 1, 1));

	Grid<float, 3, 4> g2(2.0f);
	assert(2.0f == g2(1, 1));
	std::cout << 1 << std::endl;
	g2 = g3[1];
	assert(1.0f == g2(1, 1));

    std::cout << "Simple visualisation of 3-dimensional array:" << std::endl;
    Grid<float, 3, 4, 5> g4(2.0f);

}
