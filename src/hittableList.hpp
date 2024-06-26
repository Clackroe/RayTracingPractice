#ifndef RT_HITLISTH
#define RT_HITLISTH

#include <hittable.hpp>
#include <memory>
#include <vector>
class HittableList : public Hittable {
public:
    HittableList() { }
    HittableList(std::shared_ptr<Hittable> obj)
    {
        add(obj);
    }
    ~HittableList() = default;

    void add(std::shared_ptr<Hittable> obj)
    {
        m_List.push_back(obj);
    }

    bool hit(const Ray& ray, Interval rayStep, HitResponse& response) const override
    {

        HitResponse res;
        bool hitSomething = false;
        float closest = rayStep.max;

        for (const std::shared_ptr<Hittable>& h : m_List) {
            if (h->hit(ray, Interval(rayStep.min, closest), res)) {
                hitSomething = true;
                closest = res.step;
                response = res;
            }
        }
        return hitSomething;
    }

private:
    std::vector<std::shared_ptr<Hittable>> m_List;
};
#endif
