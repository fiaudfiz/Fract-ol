#include "fractol.h"

void    compute_mandelbrot(__m256d *z_re, __m256d *z_im, __m256d c_re, __m256d c_im)
{
    __m256d new_im;
    __m256d new_re;
    __m256d z_re2;
    __m256d z_im2;

    z_im2 = _mm256_mul_pd(*z_im, *z_im);
    z_re2 = _mm256_mul_pd(*z_re, *z_re);
    new_im = _mm256_add_pd(_mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(2.0), *z_re), *z_im), c_im);
    new_re = _mm256_add_pd(_mm256_sub_pd(z_re2, z_im2), c_re);
    *z_re = new_re;
    *z_im = new_im;
}

void    compute_tricorn(__m256d *z_re, __m256d *z_im, __m256d c_re, __m256d c_im)
{
    __m256d new_im;
    __m256d new_re;
    __m256d z_re2;
    __m256d z_im2;

    z_im2 = _mm256_mul_pd(*z_im, *z_im);
    z_re2 = _mm256_mul_pd(*z_re, *z_re);
    new_im = _mm256_add_pd(_mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(-2.0), *z_re), *z_im), c_im);
    new_re = _mm256_add_pd(_mm256_sub_pd(z_re2, z_im2), c_re);
    *z_re = new_re;
    *z_im = new_im;
}

void    compute_celtic(__m256d *z_re, __m256d *z_im, __m256d c_re, __m256d c_im)
{
    __m256d new_im;
    __m256d new_re;
    __m256d z_re2;
    __m256d z_im2;

    z_im2 = _mm256_mul_pd(*z_im, *z_im);
    z_re2 = _mm256_mul_pd(*z_re, *z_re);
    new_im = _mm256_add_pd(_mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(2.0), *z_re), *z_im), c_im);
    new_re = _mm256_add_pd(_mm256_andnot_pd(_mm256_set1_pd(-0.0),_mm256_sub_pd(z_re2, z_im2)), c_re);
    *z_re = new_re;
    *z_im = new_im;
}

void    compute_burning_ship(__m256d *z_re, __m256d *z_im, __m256d c_re, __m256d c_im)
{
    __m256d new_im;
    __m256d new_re;
    __m256d z_re2;
    __m256d z_im2;

    z_im2 = _mm256_mul_pd(*z_im, *z_im);
    z_re2 = _mm256_mul_pd(*z_re, *z_re);
    new_im = _mm256_add_pd(_mm256_or_pd(_mm256_set1_pd(-0.0),
                _mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(2.0),
                    *z_re), *z_im)), c_im);
    new_re = _mm256_add_pd(_mm256_andnot_pd(_mm256_set1_pd(-0.0),
                _mm256_sub_pd(z_re2, z_im2)), c_re);
    *z_re = new_re;
    *z_im = new_im;
}