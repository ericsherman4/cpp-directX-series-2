#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>

template <typename T>
class Ball
{
public:
    Ball(T pos, T vel, std::string color = "")
        : pos(pos)
        , vel(vel)
        , color(color)
    { std::cout << "ctor on "<< color << std::endl; }
    Ball(const Ball<T>& other)
        : pos(other. pos)
        , vel(other.vel)
        , color(other.color)
    { std::cout << "copy ctor called on " << color << std::endl; }
    ~Ball() { std::cout << "dtor on " << color <<std::endl; }
    bool operator==(const Ball<T>& rhs) const
    {
        // this is needed for when searching for matches in buckets.
        std::cout << "== called between " << color << " and " << rhs.color << std::endl;
        return pos == rhs.pos && vel == rhs.vel && color == rhs.color;
    }
    T GetPos() const { return pos; }
    T GetVel() const { return vel; }
    std::string GetColor() const { return color; }

private:
    T pos;
    T vel;
    std::string color;
};

struct HashBall
{
    template<typename T>
    size_t operator()(const Ball<T>& ball) const 
    {
        // here's a random hash alg from online 
        // https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
        std::hash<T> hasher;
        auto seed = hasher(ball.GetPos());
        seed ^= hasher(ball.GetVel()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        std::cout << "hash called on " << ball.GetColor() << " and the hash is " << seed << std::endl;
        return seed;
    }
};

int main()
{
    Ball<float> ball1{ 3.3f,5.f,"red" };
    std::unordered_map<Ball<float>, int, HashBall> map =
    {
        {ball1, 1},
        {{7,1,"blue"}, 2},
        {{2,4,"pink"}, 3},
        {{9,1,"purple"}, 4},
        {{3.f, 3.f, "adad"}, 1},
        {{4.f, 3.f, "adad"}, 1},
        {{5.f, 3.f, "adad"}, 1},
        {{6.f, 3.f, "adad"}, 1},
        {{6.f, 10.f, "adad"}, 1},
        // added a bunch of elements till hit the original max size which was 8 and then once it grew
        // it had to rehash everything which explains why all of those hash calls were there.
    };
    std::cout << "end make map" << std::endl;
    std::cout << map[{9,1,"purple"}] << std::endl;
    std::cout << map.bucket_count() << " " << map.max_bucket_count() << std::endl;
    std::cin.get();
    return 0;
}
