//
//#pragma once
//#include <list>
//#include <cmath>
//#include <cstdlib>
//#include <memory.h>
//
//struct pixel {
//	int r;
//	int c;
//	double x;
//	double y;
//};
//
//struct cluster {
//	const pixel *pixels;
//	size_t size;
//};
//
//struct line {
//	double rho;
//	double theta;
//};
//
//struct point {
//	double x;
//	double y;
//};
//
//typedef std::list<cluster> cluster_list;
//typedef std::list<::line> line_list;
//typedef std::list<pixel> string;
//typedef std::list<string> string_list;
//
//typedef double matrix2x2[4];
//
//class accumulator_t {
//	public:
//
//	// Lower and upper bounds definition.
//	struct bounds_t {
//		double lower;
//		double upper;
//
//		bounds_t(double _lower, double _upper) {
//			lower = _lower;
//			upper = _upper;
//		}
//	};
//
//	private:
//
//	// Accumulator bins ([1,height][1,width] range).
//	int **m_bins;
//
//	// Discretization step.
//	double m_delta;
//
//	// Accumulator height (theta dimention).
//	size_t m_height;
//
//	// Expected image height.
//	size_t m_image_height;
//
//	// Expected image width.
//	size_t m_image_width;
//
//	// Specifies the discretization of the rho dimention ([1,width] range).
//	double *m_rho;
//
//	// Parameters space limits (rho dimention, in pixels).
//	bounds_t m_rho_bounds;
//
//	// Specifies the size of allocated storage for the accumulator (rho dimention).
//	size_t m_rho_capacity;
//
//	// Specifies the discretization of the theta dimention ([1,height] range).
//	double *m_theta;
//
//	// Parameters space limits (theta dimentions, in degrees).
//	bounds_t m_theta_bounds;
//
//	// Specifies the size of allocated storage for the accumulator (theta dimention).
//	size_t m_theta_capacity;
//
//	// Accumulator width (rho dimention).
//	size_t m_width;
//
//	public:
//
//	// Class constructor.
//	accumulator_t() :
//		m_bins(0),
//		m_delta(0),
//		m_height(0),
//		m_image_height(0),
//		m_image_width(0),
//		m_rho(0),
//		m_rho_bounds(0, 0),
//		m_rho_capacity(0),
//		m_theta(0),
//		m_theta_bounds(0, 0),
//		m_theta_capacity(0),
//		m_width(0) {}
//
//	// Class constructor.
//	accumulator_t(const size_t image_width, const size_t image_height, const double delta) :
//		m_bins(0),
//		m_delta(0),
//		m_height(0),
//		m_image_height(0),
//		m_image_width(0),
//		m_rho(0),
//		m_rho_bounds(0, 0),
//		m_rho_capacity(0),
//		m_theta(0),
//		m_theta_bounds(0, 0),
//		m_theta_capacity(0),
//		m_width(0) {
//		init(image_width, image_height, delta);
//	}
//
//	// Class destructor.
//	~accumulator_t() {
//		free(m_bins);
//		free(m_rho);
//		free(m_theta);
//	}
//
//	// Returns the accumulator bins ([1,height][1,width] range).
//	inline
//		int** bins() {
//		return m_bins;
//	}
//
//	// Returns the accumulator bins ([1,height][1,width] range).
//	inline
//		const int** bins() const {
//		return const_cast<const int**>(m_bins);
//	}
//
//	// Set zeros to the accumulator bins.
//	inline
//		void clear() {
//		//memset_2d(m_bins, 0, m_height + 2, m_width + 2, sizeof(int));
//	}
//
//	// Returns the discretization step.
//	inline
//		double delta() const {
//		return m_delta;
//	}
//
//	// Returns the accumulator height (theta dimention).
//	inline
//		size_t height() const {
//		return m_height;
//	}
//
//	// Returns the expected image height.
//	inline
//		size_t image_height() const {
//		return m_image_height;
//	}
//
//	// Returns the expected image width.
//	inline
//		size_t image_width() const {
//		return m_image_width;
//	}
//
//	// Initializes the accumulator.
//	inline
//		void init(const size_t image_width, const size_t image_height, const double delta) {
//		if ((m_delta != delta) || (m_image_width != image_width) || (m_image_height != image_height)) {
//			m_delta = delta;
//			m_image_width = image_width;
//			m_image_height = image_height;
//
//			// Rho.
//			double r = sqrt(static_cast<double>((image_width * image_width) + (image_height * image_height)));
//
//			m_width = static_cast<size_t>((r + 1.0) / delta);
//
//			if (m_rho_capacity < (m_width + 2)) {
//				m_rho = static_cast<double*>(realloc(m_rho, (m_rho_capacity = (m_width + 2)) * sizeof(double)));
//			}
//
//			m_rho[1] = -0.5 * r;
//			for (size_t i = 2; i <= m_width; ++i) {
//				m_rho[i] = m_rho[i - 1] + delta;
//			}
//
//			m_rho_bounds.lower = -0.5 * r;
//			m_rho_bounds.upper = 0.5 * r;
//
//			// Theta.
//			m_height = static_cast<size_t>(180.0 / delta);
//
//			if (m_theta_capacity < (m_height + 2)) {
//				m_theta = static_cast<double*>(realloc(m_theta, (m_theta_capacity = (m_height + 2)) * sizeof(double)));
//			}
//
//			m_theta[1] = 0.0;
//			for (size_t i = 2; i <= m_height; i++) {
//				m_theta[i] = m_theta[i - 1] + delta;
//			}
//
//			m_theta_bounds.lower = 0.0;
//			m_theta_bounds.upper = 180.0 - delta;
//
//			// Accumulator bins.
//			//m_bins = static_cast<int**>(realloc_2d(m_bins, m_height + 2, m_width + 2, sizeof(int)));
//		}
//
//		clear();
//	}
//
//	// Returns the discretization of the rho dimention (in pixels, [1,width] range).
//	inline
//		const double* rho() const {
//		return m_rho;
//	}
//
//	// Returns the parameters space limits (rho dimention, in pixels).
//	inline
//		const bounds_t& rho_bounds() const {
//		return m_rho_bounds;
//	}
//
//	// Returns the discretization of the theta dimention (in degrees, [1,height] range).
//	inline
//		const double* theta() const {
//		return m_theta;
//	}
//
//	// Returns the parameters space limits (theta dimentions, in degrees).
//	inline
//		const bounds_t& theta_bounds() const {
//		return m_theta_bounds;
//	}
//
//	// Returns the accumulator width (rho dimention).
//	inline
//		size_t width() const {
//		return m_width;
//	}
//};
