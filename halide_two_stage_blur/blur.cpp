#include <iostream>
#include <memory>
#include <chrono>
#include <ostream>
#include <string.h>
#include <omp.h>

#define X_MAX 8192
#define Y_MAX 8192
#define TILE_SIZE 32

template <typename T>
class Image
{
private:
    std::unique_ptr<T[]> data;
    int x_len, y_len;

public:
    Image(int y_len, int x_len) : x_len(x_len), y_len(y_len)
    {
        data = std::make_unique<T[]>(x_len * y_len);
    }

    void initialize_zero()
    {
        memset(data.get(), 0, x_len * y_len);
    }

    int x_max() const { return x_len - 2; }
    int y_max() const { return y_len - 2; }

    T &operator()(int i, int j)
    {
        return data[(i + 1) * x_len + j + 1];
    }

    bool operator==(Image &other)
    {
        if (other.x_max() != x_max() || other.y_max() != y_max())
            return false;
        for (int i = 0; i < y_max(); i++)
        {
            for (int j = 0; j < x_max(); j++)
            {
                if (other(i, j) != (*this)(i, j))
                    return false;
            }
        }
        return true;
    }

    friend std::ostream &operator<<(std::ostream &os, Image<T> &img)
    {

        for (int i = 0; i < img.y_max(); i++)
        {
            for (int j = 0; j < img.x_max(); j++)
            {
                os << img(i, j) << " ";
            }
            os << "\n";
        }

        return os;
    }
};

template <typename T>
void init_image(Image<T> &img)
{
    for (int i = 0; i < img.y_max(); i++)
    {
        for (int j = 0; j < img.x_max(); j++)
        {
            img(i, j) = static_cast<int>(rand() % 256);
        }
    }
}

template <typename T>
void breadth_first_blur(Image<T> &img, Image<T> &out)
{
    Image<T> blurx(Y_MAX + 2, X_MAX + 2);

    for (int i = 0; i < blurx.y_max(); i++)
    {

        for (int j = 0; j < blurx.x_max(); j++)
        {
            blurx(i, j) = (img(i, j - 1) + img(i, j) + img(i, j + 1)) / 3;
        }
    }

    for (int i = 0; i < out.y_max(); i++)
    {

        for (int j = 0; j < out.x_max(); j++)
        {
            out(i, j) = (blurx(i - 1, j) + blurx(i, j) + blurx(i + 1, j)) / 3;
        }
    }
}

template <typename T>
void breadth_first_blur_par(Image<T> &img, Image<T> &out)
{
    Image<T> blurx(Y_MAX + 2, X_MAX + 2);

#pragma omp parallel for
    for (int i = 0; i < blurx.y_max(); i++)
    {

        for (int j = 0; j < blurx.x_max(); j++)
        {
            blurx(i, j) = (img(i, j - 1) + img(i, j) + img(i, j + 1)) / 3;
        }
    }

#pragma omp parallel for
    for (int i = 0; i < out.y_max(); i++)
    {

        for (int j = 0; j < out.x_max(); j++)
        {
            out(i, j) = (blurx(i - 1, j) + blurx(i, j) + blurx(i + 1, j)) / 3;
        }
    }
}

template <typename T>
void loop_fusion(Image<T> &img, Image<T> &out)
{
    Image<T> blurx(1 + 2, 3 + 2);
    for (int i = 0; i < out.y_max(); i++)
    {
        for (int j = 0; j < out.x_max(); j++)
        {

            for (int k = 0; k < 3; k++)
            {
                blurx(0, k) = (img(i - 1 + k, j - 1) + img(i - 1 + k, j) + img(i - 1 + k, j + 1)) / 3;
            }

            out(i, j) = (blurx(0, 0) + blurx(0, 1) + blurx(0, 2)) / 3;
        }
    }
}

template <typename T>
void loop_fusion_par(Image<T> &img, Image<T> &out)
{

#pragma omp parallel for
    for (int i = 0; i < out.y_max(); i++)
    {

        for (int j = 0; j < out.x_max(); j++)
        {
            Image<T> blurx(1 + 2, 3 + 2);
            #pragma omp simd
            for (int k = 0; k < 3; k++)
            {
                blurx(0, k) = (img(i - 1 + k, j - 1) + img(i - 1 + k, j) + img(i - 1 + k, j + 1)) / 3;
            }

            out(i, j) = (blurx(0, 0) + blurx(0, 1) + blurx(0, 2)) / 3;
        }
    }
}

template <typename T>
void sliding_window(Image<T> &img, Image<T> &out)
{
    Image<T> blurx(3 + 2, X_MAX + 2);
    for (int i = -1; i < out.y_max(); i++)
    {
        for (int j = 0; j < out.x_max(); j++)
        {

            blurx((i + 1) % 3, j) = (img(i + 1, j - 1) + img(i + 1, j) + img(i + 1, j + 1)) / 3;

            if (i < 0)
            {
                continue;
            }

            out(i, j) = (blurx((i - 1) % 3, j) + blurx(i % 3, j) + blurx((i + 1) % 3, j)) / 3;
        }
    }
}

template <typename T>
void tiled(Image<T> &img, Image<T> &out)
{
    int tile_size = (int)TILE_SIZE;
    Image<T> blurx(tile_size + 2, tile_size + 2);
    for (int ti = 0; ti < out.y_max() / tile_size; ti++)
    {
        for (int tj = 0; tj < out.x_max() / tile_size; tj++)
        {
            for (int i = -1; i < tile_size + 1; i++)
            {
                for (int j = 0; j < tile_size; j++)
                {
                    blurx(i, j) = (img(ti * tile_size + i, tj * tile_size + j - 1) +
                                   img(ti * tile_size + i, tj * tile_size + j) +
                                   img(ti * tile_size + i, tj * tile_size + j + 1)) /
                                  3;
                }
            }

            for (int i = 0; i < tile_size; i++)
            {
                for (int j = 0; j < tile_size; j++)
                {
                    out(ti * tile_size + i, tj * tile_size + j) = (blurx(i - 1, j) + blurx(i, j) + blurx(i + 1, j)) / 3;
                }
            }
        }
    }
}

template <typename T>
void tiled_par(Image<T> &img, Image<T> &out)
{
    int tile_size = (int)TILE_SIZE;
#pragma omp parallel for
    for (int ti = 0; ti < out.y_max() / tile_size; ti++)
    {
        for (int tj = 0; tj < out.x_max() / tile_size; tj++)
        {
            Image<T> blurx(tile_size + 2, tile_size + 2);
            for (int i = -1; i < tile_size + 1; i++)
            {
                #pragma omp simd
                for (int j = 0; j < tile_size; j++)
                {
                    blurx(i, j) = (img(ti * tile_size + i, tj * tile_size + j - 1) +
                                   img(ti * tile_size + i, tj * tile_size + j) +
                                   img(ti * tile_size + i, tj * tile_size + j + 1)) /
                                  3;
                }
            }

            for (int i = 0; i < tile_size; i++)
            {
                #pragma omp simd
                for (int j = 0; j < tile_size; j++)
                {
                    out(ti * tile_size + i, tj * tile_size + j) = (blurx(i - 1, j) + blurx(i, j) + blurx(i + 1, j)) / 3;
                }
            }
        }
    }
}

template <typename T>
void partitioned_sliding_window(Image<T> &img, Image<T> &out)
{
    int partition_size = 64;
    Image<T> blurx(3 + 2, X_MAX + 2);

    for (int ti = 0; ti < out.y_max() / partition_size; ti++)
    {
        for (int i = -2; i < partition_size; i++)
        {
            for (int j = 0; j < out.x_max(); j++)
            {
                blurx((i + 1) % 3, j) = (img(ti * partition_size + i + 1, j - 1) +
                                         img(ti * partition_size + i + 1, j) +
                                         img(ti * partition_size + i + 1, j + 1)) /
                                        3;
            }
            if (i < 0)
            {
                continue;
            }
            for (int j = 0; j < out.x_max(); j++)
            {
                out(ti * partition_size + i, j) = (blurx((i - 1) % 3, j) + blurx((i) % 3, j) + blurx((i + 1) % 3, j)) / 3;
            }
        }
    }
}

template <typename T>
void partitioned_sliding_window_par(Image<T> &img, Image<T> &out)
{
    int partition_size = 64;
    
#pragma omp parallel for
    for (int ti = 0; ti < out.y_max() / partition_size; ti++)
    {
        Image<T> blurx(3 + 2, X_MAX + 2);
        for (int i = -2; i < partition_size; i++)
        {
            #pragma omp simd
            for (int j = 0; j < out.x_max(); j++)
            {
                blurx((i + 1) % 3, j) = (img(ti * partition_size + i + 1, j - 1) +
                                         img(ti * partition_size + i + 1, j) +
                                         img(ti * partition_size + i + 1, j + 1)) /
                                        3;
            }
            if (i < 0)
            {
                continue;
            }
            #pragma omp simd
            for (int j = 0; j < out.x_max(); j++)
            {
                out(ti * partition_size + i, j) = (blurx((i - 1) % 3, j) + blurx((i) % 3, j) + blurx((i + 1) % 3, j)) / 3;
            }
        }
    }
}

int main()
{

    Image<int> img(Y_MAX + 2, X_MAX + 2);
    Image<int> out_bf(Y_MAX + 2, X_MAX + 2);
    Image<int> out(Y_MAX + 2, X_MAX + 2);

    img.initialize_zero();
    out_bf.initialize_zero();
    out.initialize_zero();

    init_image(img);

    // std::cout << "IN : \n";
    // std::cout << img << "\n";

    auto start = std::chrono::system_clock::now();

    breadth_first_blur(img, out_bf);

    auto end = std::chrono::system_clock::now();

    std::cout << "breadth first elapsed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    // loop fusion
    out.initialize_zero();
    start = std::chrono::system_clock::now();

    loop_fusion(img, out);

    end = std::chrono::system_clock::now();

    std::cout << "loop fusion elapsed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    std::cout << "verify : " << (out == out_bf ? "true" : "false") << "\n";

    // sliding window
    out.initialize_zero();
    start = std::chrono::system_clock::now();

    sliding_window(img, out);

    end = std::chrono::system_clock::now();

    std::cout << "sliding window elapsed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    std::cout << "verify : " << (out == out_bf ? "true" : "false") << "\n";

    // tiled
    out.initialize_zero();
    start = std::chrono::system_clock::now();

    tiled(img, out);

    end = std::chrono::system_clock::now();

    std::cout << "tiled elapsed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    std::cout << "verify : " << (out == out_bf ? "true" : "false") << "\n";

    // partitioned sliding window
    out.initialize_zero();
    start = std::chrono::system_clock::now();

    partitioned_sliding_window(img, out);

    end = std::chrono::system_clock::now();

    std::cout << "partitioned sliding window elapsed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    std::cout << "verify : " << (out == out_bf ? "true" : "false") << "\n";

    // breadth first parallel
    out.initialize_zero();
    start = std::chrono::system_clock::now();

    breadth_first_blur_par(img, out);

    end = std::chrono::system_clock::now();

    std::cout << "breadth first parallel elapsed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    std::cout << "verify : " << (out == out_bf ? "true" : "false") << "\n";

    // loop fusion parallel
    out.initialize_zero();
    start = std::chrono::system_clock::now();

    loop_fusion_par(img, out);

    end = std::chrono::system_clock::now();

    std::cout << "loop fusion parallel elapsed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    std::cout << "verify : " << (out == out_bf ? "true" : "false") << "\n";

    // tiled parallel
    out.initialize_zero();
    start = std::chrono::system_clock::now();

    tiled_par(img, out);

    end = std::chrono::system_clock::now();

    std::cout << "tiled parallel elapsed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    std::cout << "verify : " << (out == out_bf ? "true" : "false") << "\n";

    //  partitioned sliding window parallel
    out.initialize_zero();
    start = std::chrono::system_clock::now();

    partitioned_sliding_window_par(img, out);

    end = std::chrono::system_clock::now();

    std::cout << "partitioned sliding window parallel elapsed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    std::cout << "verify : " << (out == out_bf ? "true" : "false") << "\n";

    // std::cout << "OUT BF : \n";
    // std::cout << out_bf << "\n";

    // std::cout << "OUT LF : \n";
    // std::cout << out_lf << "\n";

    // std::cout << "OUT SW : \n";
    // std::cout << out_sw << "\n";

    // std::cout << "OUT T : \n";
    // std::cout << out_t << "\n";

    return 0;
}
